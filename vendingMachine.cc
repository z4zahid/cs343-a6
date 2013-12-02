#include "vendingMachine.h"

using namespace std;

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id_, unsigned int sodaCost, unsigned int maxStockPerFlavour_ ) {
	printer = &prt;
    server = &nameServer;
    id = id_;
    sodaPrice = sodaCost;
    maxStockPerFlavour = maxStockPerFlavour_;
    server->VMregister(this);
    stock = new unsigned int[4];
    restocking = false;
}

void VendingMachine::initStock() {
	for (int i=0; i<4; i++) {
		stock[i] = 0;
	}
}

void VendingMachine::main() {

	printer->print(Printer::Vending, 'S', sodaPrice);
	initStock();

	while(true) {
		_Accept(~VendingMachine) {
			break;
		} or _When (!restocking) _Accept(buy) {

		} or _Accept(inventory, restocked) {

		}
	}
	printer->print(Printer::Vending, 'F');
}

VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard &card) {

	Status status = BUY;
	if (stock[flavour] < 1) {
		status = STOCK;
	} else if (card.getBalance() < sodaPrice) {
		status = FUNDS;
	}  else {
		stock[flavour] -= 1;
		card.withdraw(sodaPrice);
		printer->print(Printer::Vending, 'B', flavour, stock[flavour]);
	}

	return status;
}


unsigned int *VendingMachine::inventory()  {
	restocking = true;
	printer->print(Printer::Vending, 'r');
	return stock;
}

void VendingMachine::restocked() {
	restocking = false;
	printer->print(Printer::Vending, 'R');
}

_Nomutex unsigned int VendingMachine::cost() {
	return sodaPrice;
}

_Nomutex unsigned int VendingMachine::getId() {
	return id;
}

VendingMachine::~VendingMachine() {
	delete stock;
}

