#ifndef _STUDENT_GUARD
#define _STUDENT_GUARD

#include <uC++.h>
#include "watcardOffice.h"
#include "printer.h"
#include "nameServer.h"
#include "MPRNG.h"


_Task Student {
    void main();
    Printer *prt;
    NameServer *nameServer;
    WATCardOffice *cardOffice;
    unsigned int id;
    unsigned int maxPurchases;

  public:
  	~Student();
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif




