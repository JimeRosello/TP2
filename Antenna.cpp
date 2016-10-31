#include "Antenna.h"
#include "Cellphone.h"

using namespace std;

Antenna::Antenna(unsigned int identification, unsigned int maxConnections) {
	this->identification = identification;
	this->maxConnections = maxConnections;
	this->messages = new List<Message*>();
	this->cellphones = new List<Cellphone*>();
	this->spokeTheMost = NULL;
	this->calledTheMost = NULL;
	this->mostSpoken = NULL;
	this->mostCalled = NULL;
	this->receivedBusyTheMost = NULL;
	this->wasBusyTheMost = NULL;
	this->maxConcurrentConnections = 0;
}

Antenna::Antenna() {
	this->identification = 0;
	this->maxConnections = 0;
	this->messages = new List<Message*>();
	this->cellphones = new List<Cellphone*>();
	this->spokeTheMost = NULL;
	this->calledTheMost = NULL;
	this->mostSpoken = NULL;
	this->mostCalled = NULL;
	this->receivedBusyTheMost = NULL;
	this->wasBusyTheMost = NULL;
	this->maxConcurrentConnections = 0;
}

unsigned int Antenna::getIdentification() {
	return this->identification;
}

unsigned int Antenna::getMaxConnections() {
	return this->maxConnections;
}

bool Antenna::connectCellphone(Cellphone* newCellphone) {
	bool cellphoneConnected = false;
	if (!checkIfFull()) {
		//newCellphone->assignAntenna(this->getIdentification()); //TODO: Ver si estaba bien eliminar ese metodo assignAntenna.
		cellphones->addNewElement(newCellphone);
		cellphoneConnected = true;
	}
	if (cellphoneConnected) {
		newCellphone->changeStatus(CONNECTED);
	}
	return cellphoneConnected;
}

Cellphone* Antenna::disconnectCellphone(unsigned int cellphoneID) {
	bool cellphoneFound = false;
	Cellphone* cellphonePointer = NULL;
	cellphones->initiateCursor();
	while (!cellphoneFound && cellphones->advanceCursor()) {
		unsigned int currentCellNumber = cellphones->getCursor()->getNumber();
		cellphonePointer = cellphones->getCursor();
		if (currentCellNumber == cellphoneID) {
			cellphoneFound = true;
		}
	}
	if (!cellphoneFound) {
		throw string("El Celular a eliminar no se encuentra en esta Lista");
	}
	cellphonePointer->changeStatus(DISCONNECTED);
	//cellphonePointer->disassignAntenna(); //TODO: Ver si esta bien haber eliminado el metodo disassignAntenna.
	return cellphonePointer;
}

bool Antenna::checkIfConnected(unsigned int cellphoneID) {
	bool cellphoneFound = false;
	cellphones->initiateCursor();
	while (!cellphoneFound && cellphones->advanceCursor()) {
		if (cellphones->getCursor()->getNumber() == cellphoneID) {
			cellphoneFound = true;
		}
	}
	return cellphoneFound;
}

unsigned int Antenna::getActiveConnections() {
	return (cellphones->getAmountOfElements());
}

bool Antenna::checkIfFull() {
	return (getActiveConnections() == this->maxConnections);
}

void Antenna::saveMessage(unsigned int receiverID, string message) {
	Message* newMessage = new Message(message, receiverID);
	messages->addNewElement(newMessage);
}

Cellphone* Antenna::getCellphoneThatSpokeTheMost() {
	return this->spokeTheMost;
}

Cellphone* Antenna::getCellphoneThatCalledTheMost() {
	return this->calledTheMost;
}

Cellphone* Antenna::getCellphoneThatWasSpokenToTheMost() {
	return this->mostSpoken;
}

Cellphone* Antenna::getCellphoneThatWasCalledTheMost() {
	return this->mostCalled;
}

Cellphone* Antenna::getCellphoneThatReceivedBusyTheMost() {
	return this->receivedBusyTheMost;
}

Cellphone* Antenna::getCellphoneThatWasBusyTheMost() {
	return this->wasBusyTheMost;
}

unsigned int Antenna::getMaxConcurrentConnections() {
	return this->maxConcurrentConnections;
}

List<Cellphone*>* Antenna::getListOfCellphones() {
	return this->cellphones;
}

Antenna::~Antenna() {
	delete this->cellphones;
	delete this->messages;
}



