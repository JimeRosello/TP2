#include "Antenna.h"

Antenna::Antenna(unsigned int identification, unsigned int maxConnections) {
	this->identification = identification;
	this->maxConnections = maxConnections;
	this->messages = new List<Message*>();
	this->cellphones = new List<Cellphone*>();
	this->waitingCellphoneList = new List<Cellphone*>();
	this->spokeTheMost = NULL;
	this->calledTheMost = NULL;
	this->mostSpoken = NULL;
	this->mostCalled = NULL;
	this->receivedBusyTheMost = NULL;
	this->wasBusyTheMost = NULL;
	this->maxConcurrentConnections = 0;
	this->cancelledCallsDueToLackOfCapacity = 0;
}

Antenna::Antenna() {
	this->identification = 0;
	this->maxConnections = 0;
	this->messages = new List<Message*>();
	this->cellphones = new List<Cellphone*>();
	this->waitingCellphoneList = new List<Cellphone*>();
	this->spokeTheMost = NULL;
	this->calledTheMost = NULL;
	this->mostSpoken = NULL;
	this->mostCalled = NULL;
	this->receivedBusyTheMost = NULL;
	this->wasBusyTheMost = NULL;
	this->maxConcurrentConnections = 0;
	this->cancelledCallsDueToLackOfCapacity = 0;
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
		cellphones->addNewElement(newCellphone);
		cellphoneConnected = true;
		newCellphone->changeStatus(CONNECTED);
		newCellphone->changeLastConnection(this->identification);
	} else {
		waitingCellphoneList->addNewElement(newCellphone);
	}
	return cellphoneConnected;
}

Cellphone* Antenna::disconnectCellphone(unsigned int cellphoneID) {
	bool cellphoneFound = false;
	Cellphone* cellphonePointer = NULL;
	if (cellphones->isEmpty()) {
		throw std::string("La lista esta vacia");
	}
	this->cellphones->initiateCursor();
	do {
		Cellphone* nextCellphone = this->cellphones->getNextElement();
		if (nextCellphone->getNumber() == cellphoneID) {
			cellphoneFound = true;
			cellphonePointer = nextCellphone
			cellphonePointer = this->cellphones->removeNextElement();
		}
	} while (!cellphoneFound && this->cellphones->advanceCursor());
	if (!waitingCellphoneList->isEmpty()) {
		Cellphone* newCellphone = waitingCellphoneList->removeNextElement();
		this->connectCellphone(newCellphone);
	}
	cellphonePointer->changeStatus(DISCONNECTED);
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

void Antenna::saveMessage(unsigned int transmitterID, unsigned int receiverID,
		std::string message, unsigned int minute) {
	Message* newMessage = new Message(message, receiverID, transmitterID, minute);
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

List<Cellphone*>* Antenna::getWaitingListOfCellphones() {
	return this->waitingCellphoneList;
}

void Antenna::increaseCancelledCallsDueToLackOfCapacity() {
	this->cancelledCallsDueToLackOfCapacity++;
}

unsigned int Antenna::getAmountOfCancelledCallsDueToLackOfCapacity() {
	return this->cancelledCallsDueToLackOfCapacity;
}

Antenna::~Antenna() {
	delete this->cellphones;
	delete this->messages;
	delete this->waitingCellphoneList;
}
