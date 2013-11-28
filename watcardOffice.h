#ifndef _WATCardOFFICE_GUARD
#define _WATCardOFFICE_GUARD

#include <uC++.h>
#include "bank.h"
#include "uFuture.h"
#include "watcard.h"

class Printer;

_Task WATCardOffice {

    struct Args {
        //define later
    };

    struct Job {                           // marshalled arguments and return future
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;                   // return future
        Job( Args args ) : args( args ) {}
    };
    _Task Courier {
        
    };                 // communicates with bank

    void main();
  public:
    ~WATCardOffice();
    _Event Lost {};                        // uC++ exception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif