#ifndef _TRUCK_GUARD
#define _TRUCK_GUARD

#include <uC++.h>
#include "bottlingPlant.h"
#include "printer.h"
#include "nameServer.h"
#include "vendingMachine.h"
#include "MPRNG.h"

_Task Truck {
    void main();
    Printer* printer;
    NameServer* server;
    BottlingPlant* plant;
    unsigned int numVendingMachines;
    unsigned int maxStockPerFlavour;
    VendingMachine** machineList;
    MPRNG rng;
    unsigned int* cargo;
    void initCargo();
    int getTotalCargoItems();
    unsigned int getTotalSodaInStock();
    bool isMoreSodaInStock();
    bool isPlantClosed;
  public:
  	~Truck();
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif