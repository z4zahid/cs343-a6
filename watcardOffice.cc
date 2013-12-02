#include "watcardOffice.h"
#include <iostream>

using namespace std;

//Courier
 
WATCardOffice::Courier::Courier(WATCardOffice &office,Printer &prt,Bank &bank){
	prt.print(Printer::Courier,'S');
	Courier::office=&office;
	Courier::prt=&prt;
    Courier::bank=&bank; 
} 

WATCardOffice::Courier::~Courier(){
	prt->print(Printer::Courier,'F');
} 

void WATCardOffice::Courier::main(){

	MPRNG mprng;
	
	for (;;){

		if (office->isOfficeClosed) {
			break;
		}

		WATCardOffice::Job *job=office->requestWork();
		WATCard* card = job->args.card;

		prt->print(Printer::Courier,'t',job->args.sid,job->args.amt);
		bank->withdraw(job->args.sid,job->args.amt);

		card->deposit(job->args.amt);
		prt->print(Printer::Courier,'T',job->args.sid,job->args.amt);

		int randN=mprng(1,6);
		if (randN==1){										//One-sixth probability
			delete card;
			job->result.exception(new WATCardOffice::Lost);
		} else {
			job->result.delivery(card);
		}
	}
}

//WATCardOffice

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) {
	prt.print(Printer::WATCardOffice,'S');

	WATCardOffice::prt=&prt;
    WATCardOffice::bank=&bank; 
    WATCardOffice::numCouriers=numCouriers;
    isOfficeClosed = false;
    for (int i=0;i<numCouriers;i++){
    	courierList.push_back(new Courier(*this,prt,bank));
    }
}                    

void WATCardOffice::main() {
	
	for(;;){
		_Accept(~WATCardOffice){
			while(!jobCondition.empty()) {
				jobCondition.signal();
			}
			isOfficeClosed = true;
			break;
		}
		or _Accept(create,transfer,requestWork){

		}
	}
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	Args args;
	args.sid=sid;
	args.amt=amount;
	args.card= new WATCard();
	Job *job=new Job(args);
	jobsList.push_back(job);
	jobCondition.signal();
	prt->print(Printer::WATCardOffice,'C',sid,amount);
	return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	Args args;
	args.sid=sid;
	args.amt=amount;
	args.card=card;
	Job *job=new Job(args);
	jobsList.push_back(job);
	jobCondition.signal();
	prt->print(Printer::WATCardOffice,'T',sid,amount);
	return job->result;
}

WATCardOffice::Job *WATCardOffice::requestWork() {
	
	while(jobsList.size() ==0) {
		jobCondition.wait();
	}

	prt->print(Printer::WATCardOffice,'W');
	Job* job = jobsList[0];
	jobsList.erase(jobsList.begin());
	return job; 
	
}

WATCardOffice::~WATCardOffice() {
	prt->print(Printer::WATCardOffice,'F');
	for (int i=0;i<numCouriers;i++){
		delete courierList[i];
    }
}