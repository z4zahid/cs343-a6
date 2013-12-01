#ifndef _NAMESERVER_GUARD
#define _NAMESERVER_GUARD

#include <uC++.h>
#include "printer.h"
_Task VendingMachine;
#include <vector>;

_Task NameServer {
    void main();
    Printer* printer;
    unsigned int numVendingMachines;
    unsigned int numStudents;
    VendingMachine** machineList;
    std::vector<int> studentMachine;
    int registeredMachineCounter;
  public:
  	~NameServer();
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif