#ifndef _BANK_GUARD
#define _BANK_GUARD

#include <uC++.h>
#include <vector>

_Monitor Bank {
    std::vector<int>studentBalances;
    uCondition* sufficientFunds;
  public:
  	~Bank();
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif