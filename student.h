#ifndef _STUDENT_GUARD
#define _STUDENT_GUARD

#include <uC++.h>
#include "watcardOffice.h"
class Printer;
_Task NameServer;

_Task Student {
    void main();
  public:
  	~Student();
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif





