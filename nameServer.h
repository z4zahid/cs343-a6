﻿#ifndef _NAMESERVER_GUARD
#define _NAMESERVER_GUARD

#include <uC++.h>
class Printer;
_Task VendingMachine;

_Task NameServer {
    void main();
  public:
  	~NameServer();
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif