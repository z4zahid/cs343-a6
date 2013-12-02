#include "nameServer.h"
#include "printer.h"
#include "vendingMachine.h"

using namespace std;

//The NameServer is an administrator task used to manage the vending-machine names. 
NameServer::NameServer( Printer &prt, unsigned int numVendingMachines_, unsigned int numStudents_) {
	printer = &prt;
	numVendingMachines = numVendingMachines_;
	numStudents = numStudents_;
	machineList = new VendingMachine*[numVendingMachines];
	studentMachine.resize(numStudents);
	registeredMachineCounter = 0;
}

void NameServer::main() { 

	printer->print(Printer::NameServer, 'S');
	//distribute the students evenly across the vending machines
	for (int i=0; i<numStudents; i++) {
		studentMachine[i] = i%numVendingMachines;
	}

	while (true) {
		_Accept(~NameServer) {
			break;
		} or _Accept(VMregister) {

		} or _When(registeredMachineCounter == (numVendingMachines-1)) _Accept(getMachine, getMachineList) {

		} 
	}
	printer->print(Printer::NameServer, 'F');
}

void NameServer::VMregister( VendingMachine *vendingmachine ) {
 	machineList[registeredMachineCounter]=  vendingmachine;
 	printer->print(Printer::NameServer, 'R', registeredMachineCounter);
 	registeredMachineCounter++;
}

VendingMachine* NameServer::getMachine( unsigned int id )  {
	int curMachineId = studentMachine[id];
	studentMachine[id] = (curMachineId+1)%numVendingMachines;
	printer->print(Printer::NameServer, 'N', id, curMachineId);
	return machineList[curMachineId];
}

VendingMachine** NameServer::getMachineList()  {
	return machineList;
}

NameServer::~NameServer() {

}
