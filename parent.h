#ifndef _PARENT_GUARD
#define _PARENT_GUARD

#include <uC++.h>
#include "bank.h"
#include "printer.h"

_Task Parent {
    void main();
  public:
  	~Parent();
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif