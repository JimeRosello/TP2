#include "Antena.h"

using namespace std;

Antena::Antena(unsigned int identification, unsigned int maxConnections) {
	this->identification = identification;
	this->maxConnections = maxConnections;
	this->messages = new List<Message>();
	this->cellphones = new List<Cellphone>();
}

Antena::Antena() {
	this->identification = 0;
	this->maxConnections = 0;
	this->messages = new List<Message>();
	this->cellphones = new List<Cellphone>();
}

unsigned int Antena::getIdentification() {
	return this->identification;
}

bool Antena::conectCellphone(Cellphone* newCellphone) {
	bool cellphoneConnected = false;
	if (!checkIfFull()) {
		newCellphone->assignAntena(this->getIdentification());
		cellphones->addNewElement(newCellphone);
		cellphoneConnected = true;
	}
	return cellphoneConnected;
}

Cellphone* Antena::disconnectCellphone(unsigned int cellphoneID) {
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

bool Antena::checkIfConnected(unsigned int cellphoneID) {
	bool cellphoneFound = false;
	cellphones->initiateCursor();
	while (!cellphoneFound && cellphones->advanceCursor()) {
		if ((cellphones->getElement()).getNumber() == cellphoneID) {
			cellphoneFound = true;
		}
	}
	return cellphoneFound;
}

unsigned int Antena::getActiveConnections() {
	return (cellphones->getAmountOfElements());
}

bool Antena::checkIfFull() {
	return (getActiveConnections() == this->maxConnections);
}

void Antena::saveMessage(unsigned int receiverID, string message) {
	Message* newMessage = new Message(message, receiverID);
	messages->addNewElement(newMessage);
}

Antena::~Antena() {
	delete this->cellphones;
	delete this->messages;
}
