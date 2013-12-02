#include <uC++.h>
#include <iostream> 
#include <stdlib.h>

#include <fstream>
#include <sstream>

#include "MPRNG.h"
#include "config.h"
#include "printer.h"
#include "bank.h"
#include "parent.h" 
#include "watcardOffice.h" 
#include "nameServer.h"
#include "vendingMachine.h" 
#include "bottlingPlant.h"
#include "student.h"

#include <time.h>
#include <string>
#include <vector>

using namespace std; 

void uMain::main() {

    string errorMessage = "Usage: ./soda [ config-file [ random-seed ] ]";

    //valid number of arguments (less than or equal to 2)
    if (argc > 3) {
        cout << errorMessage <<endl;
        return;
    }

    //valid config file name
    string configFileName = (argc > 1)? argv[1]: "soda.config";

    istream *infile = &cin;                     // default value
    try {
        infile = new ifstream(configFileName.c_str());
    } catch( uFile::Failure ) {
        cerr << "Error! Could not open input file \"" << configFileName << "\"" << endl;
        cout << errorMessage <<endl;
        return;
    } // try

    //valid seed
    MPRNG rng;
    int seed = (argc > 2)? atoi(argv[2]): time(NULL);
    if (seed <= 0) {
        cout << errorMessage <<endl;
        delete infile;
        return;
    }
    rng.seed(seed);
    
    ConfigParms params;
    processConfigFile(configFileName.c_str(), params);

    Printer* printer = new Printer(params.numStudents, params.numVendingMachines, params.numCouriers);
    Bank* bank = new Bank(params.numStudents);
    Parent *parent = new Parent(*printer, *bank, params.numStudents, params.parentalDelay);
    WATCardOffice *office = new WATCardOffice(*printer, *bank, params.numCouriers);
    NameServer* server = new NameServer(*printer, params.numVendingMachines, params.numStudents);
    
    vector<VendingMachine*> machines;
    for (int id =0; id<params.numVendingMachines; id++) {
        machines.push_back(new VendingMachine(*printer, *server, id, params.sodaCost, params.maxStockPerFlavour));
    }

    BottlingPlant *plant = new BottlingPlant(*printer, *server, params.numVendingMachines, params.maxShippedPerFlavour,
                params.maxStockPerFlavour, params.timeBetweenShipments);

    vector<Student*> students;
    for (int id =0; id<params.numStudents; id++) {
        students.push_back(new Student(*printer, *server, *office, id, params.maxPurchases));
    }

    //clean up
    for (int i=0; i<params.numStudents; i++) {
        delete students[i];
    }

    delete parent;
    //delete the bottling plant before deleting the vending machines
    delete plant;
    
    for (int i=0; i<params.numVendingMachines; i++) {
        delete machines[i];
    }

    delete server;
    delete office;
    delete bank;
    delete printer;
    delete infile;

    cout << "***********************" << endl;
    
}

