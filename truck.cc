#include "truck.h"

using namespace std;

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &bottlingPlant,
			  unsigned int numVendingMachines_, unsigned int maxStockPerFlavour_) {
	printer = &prt;
	server = &nameServer;
	plant = &bottlingPlant;
	numVendingMachines = numVendingMachines_;
	maxStockPerFlavour = maxStockPerFlavour_;
	cargo = new unsigned int[4]; // number of flavours
	machineList = server->getMachineList();	
}

void Truck::initCargo() {
	for (int i=0; i<4; i++) {
		cargo[i] = 0;
	}
}

void Truck::main() {

	printer->print(Printer::Truck, 'S');
	while (true) {
		//get coffee from Timmies
		yield(rng(1,10));

		//existing cargo is past due date
		initCargo();
		isPlantClosed = plant->getShipment(cargo);

		if (isPlantClosed) {
			break; 
		}
		printer->print(Printer::Truck, 'P', getTotalSodaInStock());

		int vendingMachineCount = 0;
		while (isMoreSodaInStock() && machineList && vendingMachineCount < numVendingMachines) {
			
			VendingMachine* vendingMachine = machineList[vendingMachineCount];
			unsigned int* inventory = vendingMachine->inventory();
			printer->print(Printer::Truck, 'd', vendingMachineCount, getTotalSodaInStock());
			for (int i=0;i<4;i++) {
				if (inventory[i] < maxStockPerFlavour) {
					int amountTransferred = (cargo[i] < (maxStockPerFlavour-inventory[i]))? cargo[i] : maxStockPerFlavour-inventory[i];
					inventory[i] = inventory[i] + amountTransferred;
					cargo[i] = cargo[i] - amountTransferred;
				}
			}

			int totalInventoryBottles = 0;
			for (int i=0;i<4;i++) {
				totalInventoryBottles += inventory[i];
			}
			if (totalInventoryBottles < 4*maxStockPerFlavour) {
				printer->print(Printer::Truck, 'U', vendingMachineCount, (4*maxStockPerFlavour - maxStockPerFlavour));
			}

			vendingMachine->restocked();
			printer->print(Printer::Truck, 'D', vendingMachineCount, getTotalSodaInStock());
			vendingMachineCount++;
		}
	}
	printer->print(Printer::Truck, 'F');
}

unsigned int Truck::getTotalSodaInStock() {
	int total =0;
	for (int i=0; i<4; i++) {
		total += cargo[i];
	}
	return total;
}

bool Truck::isMoreSodaInStock() {
	return (getTotalSodaInStock() > 0);
}

Truck::~Truck() {
	delete []cargo;
}

