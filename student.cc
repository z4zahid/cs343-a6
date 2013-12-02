#include "student.h"
#include "vendingMachine.h"
#include "watcard.h"

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases ) {
	Student::prt=&prt;
    Student::nameServer=&nameServer;
    Student::cardOffice=&cardOffice;
    Student::id=id;
    Student::maxPurchases=maxPurchases;
}

void Student::main() {

    MPRNG mprng;
    int randBottles=mprng(1,maxPurchases);                                 
    int randFlavour=mprng(3);                                  
    
    prt->print(Printer::Student,'S',randFlavour,randBottles);    

    while(randBottles>=0){
        WATCard::FWATCard card=cardOffice->create(id,5);
        VendingMachine *machine=nameServer->getMachine(id);
        prt->print(Printer::Student,'V',machine->getId());    

        int randN=mprng(1,10);
        this->yield(randN);

        int balance=(card())->getBalance();
        int sodaCost=machine->cost(); 
        VendingMachine::Status status=machine->buy((VendingMachine::Flavours)randFlavour,*card);
        
        while (true){
        	if (status==VendingMachine::BUY)
	        {
	            //int newBalance=card.getBalance();
	            //_When(newBalance==balance-sodaCost) 
	            //_Accept
	            int balance=0;//card.getBalance();
	            prt->print(Printer::Student,'B',balance); 
	            randBottles--;
	            status=machine->buy((VendingMachine::Flavours)randFlavour,*card);
	        }
	        else if (status==VendingMachine::FUNDS)
	        {
	            int randN=mprng(1,10);
	            this->yield(randN);
	            cardOffice->transfer(id,sodaCost+5,card);
	        }
	        else if (status==VendingMachine::STOCK)
	        {
	            /*machine=nameServer->getMachine(id);
	            int randN=mprng(1,10);
	            this->yield(randN);
	            status=machine->buy((VendingMachine::Flavours)randFlavour,*card);
	            */
	            break;
	        }
        }
        
        //In case of WATCardOffice::Lost exception
        //prt->print(Printer::Student,'L');
        //card=cardOffice->create(id,5);
        //status=machine->buy((VendingMachine::Flavours)randFlavour,*card);
    }
    prt->print(Printer::Student,'F');
}


Student::~Student() {

}