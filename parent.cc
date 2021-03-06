﻿#include "parent.h"

using namespace std;

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) {
	Parent::prt=&prt;
	Parent::bank=&bank;
	Parent::numStudents=numStudents;
	delay=parentalDelay;
}

void Parent::main() {

	prt->print(Printer::Parent,'S');

	MPRNG mprng;
	for (;;){
		//check for a call to its destructor to know when to terminate
		_Accept(~Parent){
			break;
		}
		_Else{
			int randAmt=mprng(1,3);
			int randStudent=mprng(numStudents-1); 
		    
		    yield(delay);

		    prt->print(Printer::Parent,'D',randStudent,randAmt);
			bank->deposit(randStudent,randAmt);
		}
		
	}
}

Parent::~Parent() {
	prt->print(Printer::Parent,'F');
}