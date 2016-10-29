#include "Cellphone.h"

Cellphone::Cellphone(unsigned int cellphoneNumber) {
	this->cellphoneNumber = cellphoneNumber;
	this->assignedAntenna = 0;
	this->waitingMessages = new List<Message*>();
	this->status = DISCONNECTED;
	this->minutesOfOutgoingCalls = 0;
	this->minutesOfIncomingCalls = 0;
	this->numberOfRejectedOutgoingCalls = 0;
	this->numberOfRejectedIncomingCalls = 0;
	this->numberOfOutgoingCalls = 0;
	this->numberOfIncomingCalls = 0;

//	this->entryFile.open("a");
//	this->exitFile.open("a");
}

Cellphone::Cellphone() {
	this->cellphoneNumber = 0;
	this->assignedAntenna = 0;
	this->waitingMessages = new List<Message*>();
	this->status = DISCONNECTED;
//	this->entryFile.open("\0");
//	this->exitFile.open("\0");
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

void Cellphone::assignAntenna(unsigned int assignedAntenna) {
	this->assignedAntenna = assignedAntenna;
}

void Cellphone::disassignAntenna() {
	this->assignedAntenna = 0;
}

CellphoneStatus Cellphone::getStatus() {
	return this->status;
}

void Cellphone::changeStatus(CellphoneStatus status) {
	this->status = status;
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


Cellphone::~Cellphone() {
//	this->entryFile.close();
//	this->exitFile.close();
	delete waitingMessages;
}

