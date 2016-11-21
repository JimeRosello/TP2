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
	this->callsInProgress = new List<Call*>();
}


void System::addAntenna(Antenna* antenna) {
	this->listOfAntennas->addNewElement(antenna);
}


void System::addCellphone(Cellphone* cellphone) {
	this->listOfCellphones->addNewElement(cellphone);
}


Call* System::initiateCall(unsigned int minute, Cellphone* X, Cellphone* Y) {
	Call* newCall = new Call(minute, X->getNumber(), Y->getNumber());
	if ((X->getStatus() == CONNECTED) &&
		(Y->getStatus() == CONNECTED)) {
		newCall->addInvolvedAntenna(X->getLastConnection());
		newCall->addInvolvedAntenna(Y->getLastConnection());
		newCall->changeStatus(IN_PROGRESS);
		X->changeStatus(CURRENTLY_SPEAKING);
		Y->changeStatus(CURRENTLY_SPEAKING);
		unsigned int outgoingCalls = X->getNumberOfOutgoingCalls();
		unsigned int incomingCalls = Y->getNumberOfIncomingCalls();
		X->changeNumberOfOutgoingCalls(++outgoingCalls);
		Y->changeNumberOfIncomingCalls(++incomingCalls);

	} else if (Y->getStatus() == CURRENTLY_SPEAKING) {

		unsigned int numberOfRejectedOutgoingCalls =
				X->getNumberOfRejectedOutgoingCalls();
		numberOfRejectedOutgoingCalls++;
		X->changeNumberOfRejectedOutgoingCalls(numberOfRejectedOutgoingCalls);
		unsigned int numberOfRejectedIncomingCalls =
				Y->getNumberOfIncomingCalls();
		Y->changeNumberOfRejectedIncomingCalls(numberOfRejectedIncomingCalls);

		/*
		 * Se fija si tiene que cambiar el puntero al celular que mas recibio
		 * o dio ocupado.
		 */
		this->checkCellphoneThatReceivedBusyTheMost(X);
		this->checkCellphoneThatWasBusyTheMost(Y);
	} else if (X->getStatus() == WAITING_FOR_CONNECTION) {
		Antenna* antenna = this->findAntennaToWhichCellIsConnected(X);
		antenna->increaseCancelledCallsDueToLackOfCapacity();
		newCall->changeStatus(TERMINATED);

	}

	/*
	 * Se fija si tiene que cambiar el puntero al celular que mas llamo
	 * o al que mas fue llamado.
	 */
	this->checkCellphoneThatCalledTheMost(X);
	this->checkCellphoneThatWasCalledTheMost(Y);
	this->callsInProgress->addNewElement(newCall);

	return newCall;
}

unsigned int System::terminateCall(Call* call, unsigned int endMin) {
	Cellphone* X = findCellphone(call->getInitiator());
	call->endCall(endMin);
	X->changeStatus(CONNECTED);
	X->changeMinutesOfOutgoingCalls(call->getCallDuration());
	Cellphone* Y = findCellphone(call->getReceiver());
	Y->changeStatus(CONNECTED);
	Y->changeMinutesOfIncomingCalls(call->getCallDuration());
	this->checkCellphoneThatSpokeTheMost(X);
	this->checkCellphoneThatWasSpokenToTheMost(Y);
	return call->getCallDuration();
}

void System::sendAllUnsentMessages() {
	List<Cellphone*>* cellphones = this->listOfCellphones;
	cellphones->initiateCursor();
	while (cellphones->advanceCursor()) {
		List<Message*>* unsentMessages = cellphones->getCursor()->getUnsentMessages();
		while (!unsentMessages->isEmpty()) {
			Message* message = unsentMessages->removeNextElement();
			unsigned int receiverNumber = message->getReceiver();
			Cellphone* receiver = this->findCellphone(receiverNumber);
			receiver->addWaitingMessage(message);
		}
	}
}

void System::connectCellphone(Cellphone* X, Antenna* antenna) {
	antenna->connectCellphone(X);
}


void System::disconnectCellphone(Cellphone* X) {
	if (X->getStatus() != CONNECTED) {
		throw std::string ("No se puede desconectar el celular en este momento");
	}
	Antenna* antenna = this->findAntennaToWhichCellIsConnected(X);
	if (antenna) {
		antenna->disconnectCellphone(X->getNumber());
	}
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
	if (this->spokeTheMost == NULL) {
		this->spokeTheMost = X;
	} else if (this->spokeTheMost->getMinutesOfOutgoingCalls() <
			X->getMinutesOfOutgoingCalls()) {
		this->spokeTheMost = X;
	}
}

void System::checkCellphoneThatCalledTheMost(Cellphone* X) {
	if (this->spokeTheMost == NULL) {
		this->spokeTheMost = X;
	} else if (this->calledTheMost->getNumberOfOutgoingCalls() <
			X->getNumberOfOutgoingCalls()) {
		this->calledTheMost = X;
	}
}

void System::checkCellphoneThatWasSpokenToTheMost(Cellphone* X) {
	if (this->spokeTheMost == NULL) {
		this->spokeTheMost = X;
	} else if (this->mostSpoken->getNumberOfIncomingCalls() <
			X->getNumberOfIncomingCalls()) {
		this->mostSpoken = X;
	}
}

void System::checkCellphoneThatWasCalledTheMost(Cellphone* X) {
	if (this->spokeTheMost == NULL) {
		this->spokeTheMost = X;
	} else if (this->mostCalled->getNumberOfIncomingCalls() <
			X->getNumberOfIncomingCalls()) {
		this->mostCalled = X;
	}
}

void System::checkCellphoneThatReceivedBusyTheMost(Cellphone* X) {
	if (this->spokeTheMost == NULL) {
		this->spokeTheMost = X;
	} else if (this->receivedBusyTheMost->getNumberOfRejectedOutgoingCalls() <
			X->getNumberOfRejectedOutgoingCalls()) {
		this->receivedBusyTheMost = X;
	}
}

void System::checkCellphoneThatWasBusyTheMost(Cellphone* X) {
	if (this->spokeTheMost == NULL) {
		this->spokeTheMost = X;
	} else if (this->wasBusyTheMost->getNumberOfRejectedIncomingCalls() <
			X->getNumberOfRejectedIncomingCalls()) {
		this->wasBusyTheMost = X;
	}
}

List<Antenna*>* System::getListOfAntennas() {
	return this->listOfAntennas;
}

List<Cellphone*>* System::getListOfCellphones() {
	return this->listOfCellphones;
}

Cellphone* System::findCellphone(unsigned int cellphoneNumber) {
	this->listOfCellphones->initiateCursor();
	bool found = false;
	Cellphone* foundCellphone;
	while (!found && this->listOfCellphones->advanceCursor()) {
		foundCellphone = this->listOfCellphones->getCursor();
		if (foundCellphone->getNumber() == cellphoneNumber) {
			found = true;
		}
	}
	return (found? foundCellphone:NULL);
}

Antenna* System::findAntenna(unsigned int idAntenna) {
	this->listOfAntennas->initiateCursor();
	bool found = false;
	Antenna* foundAntenna;
	while (!found && this->listOfAntennas->advanceCursor()) {
		foundAntenna = this->listOfAntennas->getCursor();
		if (foundAntenna->getIdentification() == idAntenna) {
			found = true;
		}
	}
	return (found? foundAntenna:NULL);
}

Call* System::findCallInProgress(unsigned int initiator, unsigned int receiver) {
	this->callsInProgress->initiateCursor();
	bool found = false;
	Call* foundCall;
	while (!found && this->callsInProgress->advanceCursor()) {
		foundCall = this->callsInProgress->getCursor();
		if ((foundCall->getInitiator() == initiator) &&
			(foundCall->getReceiver() == receiver)) {
			found = true;
		}
	}
	return (found? foundCall:NULL);

}

Antenna* System::findAntennaToWhichCellIsConnected(Cellphone* cellphone) {
	List<Antenna*>* listOfAntennas = this->listOfAntennas;
	listOfAntennas->initiateCursor();
	bool found = false;
	Antenna* currentAntenna;
	Cellphone* currentCellphone;
	while (!found && listOfAntennas->advanceCursor()) {
		currentAntenna = listOfAntennas->getCursor();
		List<Cellphone*>* listOfCellphones = currentAntenna->getListOfCellphones();
		listOfCellphones->initiateCursor();
		while (!found && listOfCellphones->advanceCursor()) {
			currentCellphone = listOfCellphones->getCursor();
			if (currentCellphone->getNumber() == cellphone->getNumber()) {
				found = true;
			}
		}
	}
	return (found? currentAntenna:NULL);
}

