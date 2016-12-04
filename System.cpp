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
	if (!this->mostCalled) {
		this->mostCalled = cellphone;
	}
	if (!this->mostSpoken) {
		this->mostSpoken = cellphone;
	}
	if (!this->receivedBusyTheMost) {
		this->receivedBusyTheMost = cellphone;
	}
	if (!this->spokeTheMost) {
		this->spokeTheMost = cellphone;
	}
	if (!this->calledTheMost) {
		this->calledTheMost = cellphone;
	}
	if (!this->wasBusyTheMost) {
		this->wasBusyTheMost = cellphone;
	}
}

void System::initiateCall(unsigned int minute, Cellphone* X, Cellphone* Y) {

	Call* newCall = new Call(minute, X->getNumber(), Y->getNumber());
	if ((X->getStatus() == CONNECTED) &&
		(Y->getStatus() == CONNECTED)) {
		newCall->addInvolvedAntenna(X->getLastConnection());
		newCall->addInvolvedAntenna(Y->getLastConnection());
		newCall->changeStatus(IN_PROGRESS);
		X->changeStatus(CURRENTLY_SPEAKING);
		Y->changeStatus(CURRENTLY_SPEAKING);
		X->increaseNumberOfOutgoingCalls();
		Y->increaseNumberOfIncomingCalls();

	} else if (Y->getStatus() == CURRENTLY_SPEAKING) {

		X->increaseNumberOfRejectedOutgoingCalls();
		Y->increaseNumberOfRejectedIncomingCalls();

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
	else {
		newCall->changeStatus(TERMINATED);
	}

	/*
	 * Se fija si tiene que cambiar el puntero al celular que mas llamo
	 * o al que mas fue llamado.
	 */
	this->checkCellphoneThatCalledTheMost(X);
	this->checkCellphoneThatWasCalledTheMost(Y);
	this->callsInProgress->addNewElement(newCall);
}

unsigned int System::terminateCall(Call* call, unsigned int endMin) {
	Cellphone* X = findCellphone(call->getInitiator());
	call->endCall(endMin);
	X->changeStatus(CONNECTED);
	X->addMinutesOfOutgoingCalls(call->getCallDuration());
	Cellphone* Y = findCellphone(call->getReceiver());
	Y->changeStatus(CONNECTED);
	Y->addMinutesOfIncomingCalls(call->getCallDuration());
	this->checkCellphoneThatSpokeTheMost(X);
	this->checkCellphoneThatWasSpokenToTheMost(Y);
	return call->getCallDuration();
}

void System::sendUnsentMessages(Cellphone* cellphone) {
	List<Message*>* unsentMessages = cellphone->getUnsentMessages();
	while (!unsentMessages->isEmpty()) {
		Message* message = unsentMessages->removeNextElement();
		unsigned int receiverNumber = message->getReceiver();
		Cellphone* receiver = this->findCellphone(receiverNumber);
		receiver->addWaitingMessage(message);
	}
}


Call* System::findCallInProgressByCellphone(unsigned int initiator) {
	this->callsInProgress->initiateCursor();
	bool found = false;
	Call* foundCall;
	while (!found && this->callsInProgress->advanceCursor()) {
		foundCall = this->callsInProgress->getCursor();
		if ((foundCall->getInitiator() == initiator) &&
			(foundCall->getStatus() == IN_PROGRESS)) {
			found = true;
		}
	}
	return (found? foundCall:NULL);
}

void System::connectCellphone(Cellphone* X, Antenna* antenna) {
	/* Si el celular ya esta conectado a una antena, lo desconecta previo a
	 * conectarlo a una nueva. */
	if (X->getStatus() == CONNECTED) {
		Antenna* previousAntenna = this->findAntennaToWhichCellIsConnected(X);
		previousAntenna->disconnectCellphone(X->getNumber());
		antenna->connectCellphone(X);
	} else if (X->getStatus() == CURRENTLY_SPEAKING) {
		Antenna* previousAntenna = this->findAntennaToWhichCellIsConnected(X);
		previousAntenna->disconnectCellphone(X->getNumber());
		Call* call = this->findCallInProgressByCellphone(X->getNumber());
		call->addInvolvedAntenna(antenna->getIdentification());
		if (!antenna->connectCellphone(X)) {
			call->changeStatus(WAITING);
		}
	} else {
		antenna->connectCellphone(X);
	}
}


void System::disconnectCellphone(Cellphone* X) {
	if (X->getStatus() == DISCONNECTED) {
		throw std::string ("No se puede desconectar el celular");
	}
	Antenna* antenna = this->findAntennaToWhichCellIsConnected(X);
	Cellphone* waitingCellphone;
	Call* waitingCall;
	if (!antenna->getWaitingListOfCellphones()->isEmpty()) {
		waitingCellphone = antenna->getWaitingListOfCellphones()->getFirst();
		waitingCall = this->findCallInProgressByCellphone(waitingCellphone->getNumber());
	}
	if (antenna) {
		antenna->disconnectCellphone(X->getNumber());
		this->addCellphone(X);
		if (waitingCall) {
			waitingCall->changeStatus(IN_PROGRESS);
		}
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

System::~System() {
	delete this->listOfAntennas;
	delete this->listOfCellphones;
	delete this->callsInProgress;
}
