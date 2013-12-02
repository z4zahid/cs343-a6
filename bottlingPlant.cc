#include "bottlingPlant.h"
#include "truck.h"

using namespace std;

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines_,
                 unsigned int maxShippedPerFlavour_, unsigned int maxStockPerFlavour_,
                 unsigned int timeBetweenShipments_)  {
	printer = &prt;
	server = &nameServer;
	numVendingMachines = numVendingMachines_;
	maxShippedPerFlavour = maxShippedPerFlavour_;
	maxStockPerFlavour = maxStockPerFlavour_;
	timeBetweenShipments = timeBetweenShipments_;
	truck = new Truck(*printer, *server, *this, numVendingMachines, maxStockPerFlavour);
	shipment = new unsigned int[4];	
	shipmentWasPickedUp = false;
	plantClosingDown = false;
}

void BottlingPlant::initShipment() {
	for (int i=0; i<4; i++) {
		shipment[i] = 0;
	}
}

void BottlingPlant::main() {
	printer->print(Printer::BottlingPlant, 'S');
	initShipment();

	while (true) {

		if (shipmentWasPickedUp) {
			int bottlesProduced = 0;
			for (int i=0; i<4; i++) {
				int bottles = rng(maxShippedPerFlavour);
				shipment[i] = bottles;
				bottlesProduced += bottles;
			}
			printer->print(Printer::BottlingPlant, 'G', bottlesProduced);
			shipmentWasPickedUp = false;	
		}

		_Accept(~BottlingPlant) {
			break;
		} or _When(!shipmentWasPickedUp) _Accept(getShipment) {
			yield(timeBetweenShipments);
		}
	}

	printer->print(Printer::BottlingPlant, 'F');
}

bool BottlingPlant::getShipment( unsigned int cargo[] ) {

	if (plantClosingDown) {
		//plant is closing down and cargo is not changed 
		return true;
	}

	for (int i=0; i<4; i++) {
		cargo[i] = shipment[i];
	}

	shipmentWasPickedUp = true;
	printer->print(Printer::BottlingPlant, 'P');
	return false;
}

BottlingPlant::~BottlingPlant() {
	plantClosingDown = true;
	_Accept(getShipment);
	delete truck;
	delete []shipment;
}




