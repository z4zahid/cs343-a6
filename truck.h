#ifndef _TRUCK_GUARD
#define _TRUCK_GUARD

#include <uC++.h>
#include "bottlingPlant.h"
class Printer;
_Task NameServer;

_Task Truck {
    void main();
  public:
  	~Truck();
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif