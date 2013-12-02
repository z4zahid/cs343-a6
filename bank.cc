#include "bank.h"

Bank::Bank( unsigned int numStudents ) {
	for (unsigned int i=0;i<numStudents;i++){
		studentBalances.push_back(0);
	}
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
	studentBalances[id]+=amount;
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
	studentBalances[id]-=amount;
}

Bank::~Bank() {

}