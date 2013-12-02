#include "watcardOffice.h"
using namespace std;

//the couriers are created by theWATCard office
 
WATCardOffice::Courier::Courier(WATCardOffice &office,Printer &prt,Bank &bank){
	prt.print(Printer::Courier,'S');
	Courier::office=&office;
	Courier::prt=&prt;
    Courier::bank=&bank; 
} 
WATCardOffice::Courier::~Courier(){
	prt->print(Printer::Courier,'F');
} 
WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) {
	prt.print(Printer::WATCardOffice,'S');

	WATCardOffice::prt=&prt;
    WATCardOffice::bank=&bank; 
    WATCardOffice::numCouriers=numCouriers;
    Courier *courier =new Courier(*this,prt,bank);
    for (int i=0;i<numCouriers;i++){
    	courierList.push_back(courier);
    }
}                   
void WATCardOffice::Courier::main(){

	MPRNG mprng;
	
	for (;;){
		Args args;
		WATCardOffice::Job *job=office->requestWork();
		args.sid=job->args.sid;
		args.amt=job->args.amt;
		args.card=job->args.card;

		prt->print(Printer::Courier,'t',args.sid,args.amt);
		bank->withdraw(args.sid,args.amt);
		args.card->deposit(args.amt);
		prt->print(Printer::Courier,'T',args.sid,args.amt);

		int randN=mprng(1,6);
		if (randN==1){										//One-sixth probability
			delete job->args.card;
			job->result.exception(new WATCardOffice::Lost);
		}
		job->result.delivery(job->args.card);
	}
} 

void WATCardOffice::main() {
	
	for(;;){
		_Accept(~WATCardOffice){
			break;
		}
		or _Accept(create,transfer,requestWork){

		}
	}
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	WATCard *card;
	Args args;
	args.sid=sid;
	args.amt=amount;
	args.card=card;
	Job *job=new Job(args);
	jobsList.push_back(job);
	jobCondition.signal();
	prt->print(Printer::WATCardOffice,'C',sid,amount);
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	Args args;
	args.sid=sid;
	args.amt=amount;
	Job *job=new Job(args);
	jobsList.push_back(job);
	jobCondition.signal();
	prt->print(Printer::WATCardOffice,'T',sid,amount);
}

WATCardOffice::Job *WATCardOffice::requestWork() {
	
	if (jobsList.size()>0)
	{
		prt->print(Printer::WATCardOffice,'W');
		return jobsList[0]; 
	}
	else {
		jobCondition.wait();
	}


}

WATCardOffice::~WATCardOffice() {
	prt->print(Printer::WATCardOffice,'F');
}