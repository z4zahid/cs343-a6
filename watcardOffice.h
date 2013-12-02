#ifndef _WATCardOFFICE_GUARD
#define _WATCardOFFICE_GUARD

#include <uC++.h>
#include "bank.h"
#include "uFuture.h"
#include "watcard.h"
#include "printer.h"
#include <vector>
#include "MPRNG.h"

_Task WATCardOffice {

    struct Args {
        int sid;
        int amt;
        WATCard *card;
    };

    struct Job {                           // marshalled arguments and return future
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;                   // return future
        Job( Args args ) : args( args ) {}
        ~Job() {delte args.card;}
    };
    _Task Courier {
        void main();
        WATCardOffice *office;
        Printer *prt;
        Bank *bank; 
        public:
            ~Courier();
            Courier(WATCardOffice &office,Printer &prt,Bank &bank);
    };                 // communicates with bank

    void main();
    Printer *prt;
    Bank *bank; 
    bool isOfficeClosed;
    int numCouriers;
    std::vector<Job*>jobsList;
    uCondition jobCondition;
    std::vector<Courier *>courierList;
  public:
    ~WATCardOffice();
    _Event Lost {};                        // uC++ exception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif