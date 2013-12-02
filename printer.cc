#include "printer.h"
#include <sstream>
#include <iostream>

using namespace std;

Printer::Printer( unsigned int numStudents_, unsigned int numVendingMachines_, unsigned int numCouriers_) {
	numStudents = numStudents_;
	numVendingMachines = numVendingMachines_;
	numCouriers = numCouriers_;
	havePrintedColumnLabels = false;
	totalTasks = 5 + numStudents + numVendingMachines + numCouriers;
	stateBuffer = new vector<string>();
	stateBuffer->resize(totalTasks);
}

void Printer::printColumnLabels() {

	string columnHeaders[] = {"Parent","WATOffice","Names","Truck","Plant"}; 
	for (int i=0; i<5; i++) {
		cout << columnHeaders[i] << "\t";
	}

	//student, machine, couriers
	for (int i = 0; i < numStudents; i++) {
		cout << "Stud" << i << "\t";
	}

	for (int i = 0; i < numVendingMachines; i++) {
		cout << "Mach" << i << "\t";
	}

	for (int i = 0; i < numCouriers; i++) {
		cout << "Cour" << i << "\t";
	}
	cout << endl;

	//print the row of stars
	for (int j = 0; j < totalTasks; j++) {
		cout << "******" << "\t";
	}
	cout << endl;
}

void Printer::clearBuffer() {
	stateBuffer->clear();
	stateBuffer->resize(totalTasks);
}

void Printer::flushBuffers() {
	//print everything in the buffers, clear them out
	
	if (!havePrintedColumnLabels) {
		printColumnLabels();
		havePrintedColumnLabels = true;
	}

	//print states and noodle count if present
	for (int i=0; i< stateBuffer->size(); i++) {
		
		if(stateBuffer->at(i).size() >0) {
			cout << stateBuffer->at(i);
		} else {
			cout << "   ";
		}
		
		cout << "\t";
	}
	cout << endl;

	//clear buffers
  	clearBuffer();
}

void Printer::printFinishedRow(unsigned int index) {
	for (int i=0; i< totalTasks; i++) {
		if (i == index) {
			cout << "F" << "\t";
		} else {
			cout << "..." << "\t";
		}
	}
	cout << endl;
}

int Printer::getStateBufferIndex(Kind kind, unsigned int id) {
	if (kind < Student) 
		return kind;

	int curIndex = Student;
	switch(kind) {
		case Student: 
			curIndex += id;
			break;
		case Vending:
			curIndex += numStudents + id;
			break;
		case Courier:
			curIndex += numStudents + numVendingMachines + id;
			break;
	}

	return curIndex;
}

void Printer::updateStateBufferForIndex(unsigned int stateBufferIndex, char state, string data ="") {

	if (stateBuffer->at(stateBufferIndex).size() > 0) {
		flushBuffers();	//overwriting
	}

	stateBuffer->at(stateBufferIndex) = (data == "")? string(1,state) : data;

	if (state == 'F') {
		printFinishedRow(stateBufferIndex);
		clearBuffer();
	}
}

void Printer::print( Kind kind, char state ) {
	print(kind, 0, state);
}

void Printer::print( Kind kind, unsigned int lid, char state ) {
	updateStateBufferForIndex(getStateBufferIndex(kind, lid), state);	
}

void Printer::print( Kind kind, char state, int value1 ) {
	print(kind, 0, state, value1);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {

	ostringstream value1String; 
    value1String << value1; 

    string data = string(1,state) + value1String.str(); 
	updateStateBufferForIndex(getStateBufferIndex(kind, lid), state, data);	
}

void Printer::print( Kind kind, char state, int value1, int value2 )  {
	print(kind,0,state, value1, value2);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
	
	ostringstream value1String; 
    value1String << value1; 

	ostringstream value2String; 
    value2String << value2; 

    string data = string(1,state) + value1String.str() + "," + value2String.str(); 
	updateStateBufferForIndex(getStateBufferIndex(kind, lid), state, data);	
}

Printer::~Printer() {
	delete stateBuffer;
}
