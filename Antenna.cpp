#include "Antenna.h"

Antenna::Antenna(unsigned int identification, unsigned int maxConnections) {
	this->identification = identification;
	this->maxConnections = maxConnections;
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

		// Revisa si los punteros estan en NULL y en tal caso los actualiza.
		if (!this->mostCalled) {
			this->mostCalled = newCellphone;
		}
		if (!this->mostSpoken) {
			this->mostSpoken = newCellphone;
		}
		if (!this->receivedBusyTheMost) {
			this->receivedBusyTheMost = newCellphone;
		}
		if (!this->spokeTheMost) {
			this->spokeTheMost = newCellphone;
		}
		if (!this->calledTheMost) {
			this->calledTheMost = newCellphone;
		}
		if (!this->wasBusyTheMost) {
			this->wasBusyTheMost = newCellphone;
		}
		this->checkMaxConcurrentConnections();
	} else {
		waitingCellphoneList->addNewElement(newCellphone);
	}
	return cellphoneConnected;
}

void Antenna::checkMaxConcurrentConnections() {
	if (this->maxConcurrentConnections
			< this->cellphones->getAmountOfElements()) {
		this->maxConcurrentConnections =
				this->cellphones->getAmountOfElements();
	}
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
			cellphonePointer = nextCellphone;
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

void Antenna::checkCellphoneThatSpokeTheMost(Cellphone* X) {
	if (this->spokeTheMost->getMinutesOfOutgoingCalls()
			< X->getMinutesOfOutgoingCalls()) {
		this->spokeTheMost = X;
	}
}

void Antenna::checkCellphoneThatCalledTheMost(Cellphone* X) {
	if (this->calledTheMost->getNumberOfOutgoingCalls()
			< X->getNumberOfOutgoingCalls()) {
		this->calledTheMost = X;
	}
}

void Antenna::checkCellphoneThatWasSpokenToTheMost(Cellphone* X) {
	if (this->mostSpoken->getNumberOfIncomingCalls()
			< X->getNumberOfIncomingCalls()) {
		this->mostSpoken = X;
	}
}

void Antenna::checkCellphoneThatWasCalledTheMost(Cellphone* X) {
	if (this->mostCalled->getNumberOfIncomingCalls()
			< X->getNumberOfIncomingCalls()) {
		this->mostCalled = X;
	}
}

void Antenna::checkCellphoneThatReceivedBusyTheMost(Cellphone* X) {
	if (this->receivedBusyTheMost->getNumberOfRejectedOutgoingCalls()
			< X->getNumberOfRejectedOutgoingCalls()) {
		this->receivedBusyTheMost = X;
	}
}

void Antenna::checkCellphoneThatWasBusyTheMost(Cellphone* X) {
	if (this->wasBusyTheMost->getNumberOfRejectedIncomingCalls()
			< X->getNumberOfRejectedIncomingCalls()) {
		this->wasBusyTheMost = X;
	}
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
	delete this->waitingCellphoneList;
}
