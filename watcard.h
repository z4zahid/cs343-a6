#ifndef _WATCard_GUARD
#define _WATCard_GUARD

#include <uC++.h>
#include "uFuture.h"

class WATCard {
    int balance;
    WATCard( const WATCard & );            // prevent copying
    WATCard &operator=( const WATCard & );
  public:
  	~WATCard();
    WATCard();
    typedef Future_ISM<WATCard *> FWATCard; // future WATCard pointer
    void deposit( unsigned int amount );
    void withdraw( unsigned int amount );
    unsigned int getBalance();
};

#endif