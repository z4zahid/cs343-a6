#ifndef _VENDINGMACHINE_GUARD
#define _VENDINGMACHINE_GUARD

#include <uC++.h>
#include "watcard.h"
#include "nameServer.h"
#include "printer.h"

_Task VendingMachine {
    void main();
    Printer* printer;
    NameServer* server;
    unsigned int id;
    unsigned int sodaPrice;
    unsigned int maxStockPerFlavour;
    unsigned int* stock;
    bool restocking;
    void initStock();
  public:
    ~VendingMachine();
    enum Flavours {BLUES, BLACKCHERRY, CLASSICAL, CREAMSODA};
    enum Status { BUY, STOCK, FUNDS };  // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
    Status buy(Flavours flavour, WATCard &card);
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif