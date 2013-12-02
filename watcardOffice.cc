#include "watcardOffice.h"

//the couriers are created by theWATCard office
 
WATCardOffice::Courier::Courier(){

} 
WATCardOffice::Courier::~Courier(){

} 
WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) {
	WATCardOffice::prt=&prt;
    WATCardOffice::bank=&bank; 
    WATCardOffice::numCouriers=numCouriers;
    Courier courier[numCouriers];
}                   
void WATCardOffice::Courier::main(){
	//WATCardOffice::prt->print(Printer::Courier,'S');
	//prt->print(Printer::Courier,'t',sid,amt);
	//prt->print(Printer::Courier,'T',sid,amt);
	//WATCardOffice::prt->print(Printer::Courier,'F');
} 

void WATCardOffice::main() {
	prt->print(Printer::WATCardOffice,'S');

	

	prt->print(Printer::WATCardOffice,'W');
	prt->print(Printer::WATCardOffice,'F');

}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	prt->print(Printer::WATCardOffice,'C',sid,amount);
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	prt->print(Printer::WATCardOffice,'T',sid,amount);
}

WATCardOffice::Job *WATCardOffice::requestWork() {
	//courier task:
	//bank->withdraw(sid,amt);
	//card->deposit(amt);
}

WATCardOffice::~WATCardOffice() {

}