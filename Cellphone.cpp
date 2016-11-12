#include "Cellphone.h"

Cellphone::Cellphone(unsigned int cellphoneNumber) {
	this->cellphoneNumber = cellphoneNumber;
	this->lastConnection = 0;
	this->waitingMessages = new List<Message*>();
	this->status = DISCONNECTED;
	this->inbox = new List<Message*>();
	this->outbox = new List<Message*>();
	this->unsentMessages = new List<Message*>();
	this->incomingCalls = new List<Call*>();
	this->outgoingCalls = new List<Call*>();
	this->minutesOfOutgoingCalls = 0;
	this->minutesOfIncomingCalls = 0;
	this->numberOfRejectedOutgoingCalls = 0;
	this->numberOfRejectedIncomingCalls = 0;
	this->numberOfOutgoingCalls = 0;
	this->numberOfIncomingCalls = 0;
//	  this->entryFile.open("a");
//	  this->exitFile.open("a");
}

Cellphone::Cellphone() {
	this->cellphoneNumber = 0;
	this->lastConnection = 0;
	this->waitingMessages = new List<Message*>();
	this->status = DISCONNECTED;
	this->incomingCalls = new List<Call*>();
	this->outgoingCalls = new List<Call*>();
//	this->entryFile.open("\0");
// 	this->exitFile.open("\0");
	this->inbox = new List<Message*>();
	this->outbox = new List<Message*>();
	this->unsentMessages = new List<Message*>();
	this->minutesOfOutgoingCalls = 0;
	this->minutesOfIncomingCalls = 0;
	this->numberOfRejectedOutgoingCalls = 0;
	this->numberOfRejectedIncomingCalls = 0;
	this->numberOfOutgoingCalls = 0;
	this->numberOfIncomingCalls = 0;
}

unsigned int Cellphone::getNumber() {
	return this->cellphoneNumber;
}


CellphoneStatus Cellphone::getStatus() {
	return this->status;
}

void Cellphone::changeStatus(CellphoneStatus status) {
	this->status = status;
	if (this->status == CONNECTED) {
		this->receiveNewMessages();
	}
}

void Cellphone::receiveNewMessages() {
	if (this->status != CONNECTED) {
		throw std::string("No se pueden recibir mensajes nuevos");
	}
	while (!(this->waitingMessages->isEmpty())) {
		Message* newMessage = this->waitingMessages->removeNextElement();
		this->inbox->addNewElement(newMessage);
	}
}

void Cellphone::sendMessage(unsigned int receiverNumber, std::string message,
												unsigned int minute) {
	Message* msg = new Message(message, receiverNumber, this->cellphoneNumber,
												minute);
	this->outbox->addNewElement(msg);
	this->unsentMessages->addNewElement(msg);
}

void Cellphone::addWaitingMessage(Message* message) {
	this->waitingMessages->addNewElement(message);
}

unsigned int Cellphone::getLastConnection() {
	return this->lastConnection;
}

unsigned int Cellphone::getMinutesOfOutgoingCalls() {
	return this->minutesOfOutgoingCalls;
}

unsigned int Cellphone::getMinutesOfIncomingCalls() {
	return this->minutesOfIncomingCalls;
}

unsigned int Cellphone::getNumberOfRejectedOutgoingCalls() {
	return this->numberOfRejectedOutgoingCalls;
}

unsigned int Cellphone::getNumberOfRejectedIncomingCalls() {
	return this->numberOfRejectedIncomingCalls;
}

unsigned int Cellphone::getNumberOfOutgoingCalls() {
	return this->numberOfOutgoingCalls;
}

unsigned int Cellphone::getNumberOfIncomingCalls() {
	return this->numberOfIncomingCalls;
}

void Cellphone::changeMinutesOfOutgoingCalls(unsigned int newValue) {
	this->minutesOfOutgoingCalls = newValue;
}

void Cellphone::changeMinutesOfIncomingCalls(unsigned int newValue) {
	this->minutesOfIncomingCalls = newValue;
}

void Cellphone::changeNumberOfRejectedOutgoingCalls(unsigned int newValue) {
	this->numberOfOutgoingCalls = newValue;
}

void Cellphone::changeNumberOfRejectedIncomingCalls(unsigned int newValue) {
	this->numberOfRejectedIncomingCalls = newValue;
}

void Cellphone::changeNumberOfOutgoingCalls(unsigned int newValue) {
	this->numberOfOutgoingCalls = newValue;
}

void Cellphone::changeNumberOfIncomingCalls(unsigned int newValue) {
	this->numberOfIncomingCalls = newValue;
}

void Cellphone::changeLastConnection(unsigned int antennaId) {
	this->lastConnection = antennaId;
}

List<Message*>* Cellphone::getOutgoingMessages() {
	return this->outbox;
}

List<Message*>* Cellphone::getUnsentMessages() {
	return this->unsentMessages;
}

List<Message*>* Cellphone::getIncomingMessages() {
	return this->inbox;
}


List<Call*>* Cellphone::getOutgoingCalls() {
	return this->outgoingCalls;
}

List <Call*>* Cellphone::getIncomingCalls() {
	return this->incomingCalls;
}

List<Message*>* Cellphone::getWaitingMessages() {
	return this->waitingMessages;
}

Cellphone::~Cellphone() {
//	this->entryFile.close();
//	this->exitFile.close();
	delete waitingMessages;
}
