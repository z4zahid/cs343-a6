﻿#include "student.h"
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
        prt->print(Printer::Student,id,'V',machine->getId());    

        yield(mprng(1,10));
       
        while (true) {
            try { 
                VendingMachine::Status status=machine->buy((VendingMachine::Flavours)randFlavour,*(card()));
                if (status==VendingMachine::BUY) {
                    int balance = (card())->getBalance();
                    prt->print(Printer::Student,id,'B',balance); 
                    randBottles--;
                    break;

                } else if (status==VendingMachine::FUNDS) {
                    card = cardOffice->transfer(id,machine->cost()+5,card());
                } else if (status==VendingMachine::STOCK) {
                    machine=nameServer->getMachine(id);
                }
            } catch(WATCardOffice::Lost event) {
                //In case of WATCardOffice::Lost exception
                prt->print(Printer::Student,id,'L');
                card = cardOffice->create(id,5);
            }
        }
        
    }
    delete card;
    prt->print(Printer::Student,id,'F');
}


Student::~Student() {

}