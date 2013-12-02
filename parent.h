#ifndef _PARENT_GUARD
#define _PARENT_GUARD

#include <uC++.h>
#include "bank.h"
#include "printer.h"
#include "MPRNG.h"

_Task Parent {
	int delay;
	Printer *prt;
	Bank *bank;
	int numStudents; 
    void main();
  public:
  	~Parent();
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif