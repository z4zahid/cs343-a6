#ifndef _BOTTLING_GUARD
#define _BOTTLING_GUARD

#include <uC++.h>
#include "printer.h"
#include "nameServer.h"

_Task BottlingPlant {
    void main();
  public:
  	~BottlingPlant();
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
};

#endif