#include "System.h"


System::System() {
	this->listOfAntennas = new List<Antenna*>();
	this->listOfCellphones = new List<Cellphone*>();
	this->spokeTheMost = NULL;
	this->calledTheMost = NULL;
	this->mostSpoken = NULL;
	this->mostCalled = NULL;
	this->receivedBusyTheMost = NULL;
	this->wasBusyTheMost = NULL;
}


void System::addAntenna(Antenna* antenna) {
	this->listOfAntennas->addNewElement(antenna);
}


void System::addCellphone(Cellphone* cellphone) {
	this->listOfCellphones->addNewElement(cellphone);
}


CallStatus System::initiateCall(Cellphone* X, Cellphone* Y) {
	CallStatus status;
	if (Y->getStatus() != CONNECTED) {
		status = BUSY;
		// Cambia los valores de llamadas rechazadas para X y para Y
		unsigned int numberOfRejectedOutgoingCalls =
				X->getNumberOfRejectedOutgoingCalls();
		numberOfRejectedOutgoingCalls++;
		X->changeNumberOfRejectedOutgoingCalls(numberOfRejectedOutgoingCalls);
		unsigned int numberOfRejectedIncomingCalls =
				Y->getNumberOfIncomingCalls();
		Y->changeNumberOfRejectedIncomingCalls(numberOfRejectedIncomingCalls);
		// Se fija si tiene que cambiar el puntero al celular que mas recibio
		// o dio ocupado
		this->checkCellphoneThatReceivedBusyTheMost(X);
		this->checkCellphoneThatWasBusyTheMost(Y);
	} else {
		status = IN_PROGRESS;
		X->changeStatus(CURRENTLY_SPEAKING);
		Y->changeStatus(CURRENTLY_SPEAKING);
	}
	return status;
}


void System::terminateCall(Cellphone* X, Cellphone* Y) {

}


void System::connectCellphone(Cellphone* X, Antenna* antenna) {

}


void System::disconnectCellphone(Cellphone* X) {

}

Cellphone* System::getCellphoneThatSpokeTheMost() {
	return this->spokeTheMost;
}

Cellphone* System::getCellphoneThatCalledTheMost() {
	return this->calledTheMost;
}

Cellphone* System::getCellphoneThatWasSpokenToTheMost() {
	return this->mostSpoken;
}

Cellphone* System::getCellphoneThatWasCalledTheMost() {
	return this->mostCalled;
}

Cellphone* System::getCellphoneThatReceivedBusyTheMost() {
	return this->receivedBusyTheMost;
}

Cellphone* System::getCellphoneThatWasBusyTheMost() {
	return this->wasBusyTheMost;
}

void System::checkCellphoneThatSpokeTheMost(Cellphone* X) {
	if (this->spokeTheMost->getMinutesOfOutgoingCalls() <
			X->getMinutesOfOutgoingCalls()) {
		this->spokeTheMost = X;
	}
}

void System::checkCellphoneThatCalledTheMost(Cellphone* X) {
	if (this->calledTheMost->getNumberOfOutgoingCalls() <
			X->getNumberOfOutgoingCalls()) {
		this->calledTheMost = X;
	}
}

void System::checkCellphoneThatWasSpokenToTheMost(Cellphone* X) {
	if (this->mostSpoken->getNumberOfIncomingCalls() <
			X->getNumberOfIncomingCalls()) {
		this->mostSpoken = X;
	}
}

void System::checkCellphoneThatWasCalledTheMost(Cellphone* X) {
	if (this->mostCalled->getNumberOfIncomingCalls() <
			X->getNumberOfIncomingCalls()) {
		this->mostCalled = X;
	}
}

void System::checkCellphoneThatReceivedBusyTheMost(Cellphone* X) {
	if (this->receivedBusyTheMost->getNumberOfRejectedOutgoingCalls() <
			X->getNumberOfRejectedOutgoingCalls()) {
		this->receivedBusyTheMost = X;
	}
}

void System::checkCellphoneThatWasBusyTheMost(Cellphone* X) {
	if (this->wasBusyTheMost->getNumberOfRejectedIncomingCalls() <
			X->getNumberOfRejectedIncomingCalls()) {
		this->wasBusyTheMost = X;
	}
}

System::~System() {
	delete[] this->listOfAntennas;
	delete[] this->listOfCellphones;
}
