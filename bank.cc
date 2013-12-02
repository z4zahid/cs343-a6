#include "bank.h"

using namespace std;

Bank::Bank( unsigned int numStudents ) {

	sufficientFunds = new uCondition[numStudents];
	for (unsigned int i=0;i<numStudents;i++){
		studentBalances.push_back(0);
	}
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
	studentBalances[id]+=amount;
	sufficientFunds[id].signal();
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
	
	while (amount > studentBalances[id]) {
		sufficientFunds[id].wait();
	}
	studentBalances[id]-=amount;
}

Bank::~Bank() {
	delete []sufficientFunds;
}