#include "Cellphone.h"

Cellphone::Cellphone(unsigned int cellphoneNumber) {
	this->cellphoneNumber = cellphoneNumber;
	this->assignedAntenna = 0;
	this->waitingMessages = new List<Message>();
//	this->entryFile.open("a");
//	this->exitFile.open("a");
}

Cellphone::Cellphone() {
	this->cellphoneNumber = 0;
	this->assignedAntenna = 0;
	this->waitingMessages = new List<Message>();
//	this->entryFile.open("\0");
//	this->exitFile.open("\0");
}

unsigned int Cellphone::getNumber() {
	return this->cellphoneNumber;
}

void Cellphone::assignAntenna(unsigned int assignedAntenna) {
	this->assignedAntenna = assignedAntenna;
}

Cellphone::~Cellphone() {
//	this->entryFile.close();
//	this->exitFile.close();
	delete waitingMessages;
}

