#include "Call.h"


Call::Call(unsigned int startMin, Cellphone* initiator, Cellphone* receiver) {
	this->startMin = startMin;
	this->endMin = startMin;
	this->initiator = initiator;
	this->receiver = receiver;
	if ((initiator->getStatus() == CONNECTED) &&
		(receiver->getStatus() == CONNECTED)) {
		initiator->changeStatus(CURRENTLY_SPEAKING);
		unsigned int outgoingCalls = initiator->getNumberOfOutgoingCalls();
		unsigned int incomingCalls = receiver->getNumberOfIncomingCalls();
		initiator->changeNumberOfOutgoingCalls(++outgoingCalls);
		receiver->changeNumberOfIncomingCalls(++incomingCalls);
		receiver->changeStatus(CURRENTLY_SPEAKING);
		this->status = IN_PROGRESS;
	} else {
		this->status = BUSY;
		unsigned int numberOfRejectedOutgoingCalls =
				initiator->getNumberOfRejectedOutgoingCalls();
		numberOfRejectedOutgoingCalls++;
		initiator->changeNumberOfRejectedOutgoingCalls(numberOfRejectedOutgoingCalls);
		unsigned int numberOfRejectedIncomingCalls =
				receiver->getNumberOfIncomingCalls();
		receiver->changeNumberOfRejectedIncomingCalls(numberOfRejectedIncomingCalls);

	}
}

unsigned int Call::getCallDuration() {
	return ((this->endMin)-(this->startMin));
}

void Call::endCall(unsigned int endMin) {
	if (this->status == IN_PROGRESS) {
		this->endMin = endMin;
		this->initiator->changeStatus(CONNECTED);
		this->initiator->changeMinutesOfOutgoingCalls(this->getCallDuration());
		this->receiver->changeStatus(CONNECTED);
		this->receiver->changeMinutesOfIncomingCalls(this->getCallDuration());
	} else {
		throw std::string("La llamada no se encuentra en curso y no puede ser "
				"terminada");
	}
}

CallStatus Call::getCallStatus() {
	return this->status;
}

Cellphone* Call::getInitiator() {
	return this->initiator;
}

Cellphone* Call::getReceiver() {
	return this->receiver;
}
