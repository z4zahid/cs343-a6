#include "student.h"
#include "vendingMachine.h"
#include "watcard.h"
#include <iostream>

using namespace std;
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
    
    prt->print(Printer::Student,id,'S',randFlavour,randBottles);  
    WATCard::FWATCard card=cardOffice->create(id,5);

    VendingMachine *machine;

    while (randBottles>=0) {

        machine = nameServer->getMachine(id);
        prt->print(Printer::Student,'V',machine->getId());    

        yield(mprng(1,10));

        int balance=(card())->getBalance();
        int sodaCost=machine->cost(); 
       
        while (true) {
            VendingMachine::Status status=machine->buy((VendingMachine::Flavours)randFlavour,*card);
            try { 
                if (status==VendingMachine::BUY) {
                    int balance = (card())->getBalance();
                    prt->print(Printer::Student,'B',balance); 
                    randBottles--;
                    break;

                } else if (status==VendingMachine::FUNDS) {
                    card = cardOffice->transfer(id,sodaCost+5,card);
                } else if (status==VendingMachine::STOCK) {
                    machine=nameServer->getMachine(id);
                }
            } catch(WATCardOffice::Lost) {
                //In case of WATCardOffice::Lost exception
                prt->print(Printer::Student,'L');
                card = cardOffice->create(id,5);
                status=machine->buy((VendingMachine::Flavours)randFlavour,*card);
            }
        }
        
    }
    prt->print(Printer::Student,'F');
}


Student::~Student() {

}