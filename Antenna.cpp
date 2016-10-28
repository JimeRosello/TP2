#include "Antenna.h"

using namespace std;

Antenna::Antenna(unsigned int identification, unsigned int maxConnections) {
	this->identification = identification;
	this->maxConnections = maxConnections;
	this->messages = new List<Message>();
	this->cellphones = new List<Cellphone>();
	this->spokeTheMost = NULL;
	this->calledTheMost = NULL;
	this->mostSpoken = NULL;
	this->mostCalled = NULL;
	this->receivedBusyTheMost = NULL;
	this->wasBusyTheMost = NULL;
}

Antenna::Antenna() {
	this->identification = 0;
	this->maxConnections = 0;
	this->messages = new List<Message>();
	this->cellphones = new List<Cellphone>();
}

unsigned int Antenna::getIdentification() {
	return this->identification;
}

bool Antenna::conectCellphone(Cellphone* newCellphone) {
	bool cellphoneConnected = false;
	if (!checkIfFull()) {
		newCellphone->assignAntenna(this->getIdentification());
		cellphones->addNewElement(newCellphone);
		cellphoneConnected = true;
	}
	return cellphoneConnected;
}

Cellphone* Antenna::disconnectCellphone(unsigned int cellphoneID) {
	bool cellphoneFound = false;
	Node<Cellphone>* cellphonePointer = NULL;
	cellphones->initiateCursor();
	while (!cellphoneFound && cellphones->advanceCursor()) {
		if (cellphones->getElement(cellphones->getCursor()).getNumber()
				== cellphoneID) {
			cellphoneFound = true;
		} else {
			cellphonePointer = cellphones->getCursor();
		}
	}
	if (!cellphoneFound) {
		throw string("El Celular a eliminar no se encuentra en esta Lista");
	}
	return (cellphones->getPointerNextElement(cellphonePointer));
}

bool Antenna::checkIfConnected(unsigned int cellphoneID) {
	bool cellphoneFound = false;
	cellphones->initiateCursor();
	while (!cellphoneFound && cellphones->advanceCursor()) {
		if ((cellphones->getElement()).getNumber() == cellphoneID) {
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

Antenna::~Antenna() {
	delete this->cellphones;
	delete this->messages;
}



