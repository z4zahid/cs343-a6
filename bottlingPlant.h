#ifndef _BOTTLING_GUARD
#define _BOTTLING_GUARD

#include <uC++.h>
#include "printer.h"
#include "nameServer.h"
#include "MPRNG.h"
_Task Truck;

_Task BottlingPlant {
    void main();
    Printer* printer;
    NameServer* server;
    Truck* truck;
    unsigned int numVendingMachines;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
    unsigned int* shipment;
    MPRNG rng;
    bool shipmentWasPickedUp;
    bool plantClosingDown;
    void initShipment();
  public:
  	~BottlingPlant();
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    bool getShipment( unsigned int cargo[] );
};

#endif