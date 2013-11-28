#ifndef _BANK_GUARD
#define _BANK_GUARD

#include <uC++.h>

_Monitor Bank {
  public:
  	~Bank();
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif