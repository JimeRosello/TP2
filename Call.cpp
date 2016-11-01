#include "Call.h"


Call::Call(unsigned int startMin, unsigned int initiator, unsigned int receiver) {
	this->startMin = startMin;
	this->endMin = startMin;
	this->initiator = initiator;
	this->receiver = receiver;
	this->status = BUSY;
}

unsigned int Call::getCallDuration() {
	return ((this->endMin)-(this->startMin));
}

void Call::endCall(unsigned int endMin) {
	if (this->status == IN_PROGRESS) {
		this->endMin = endMin;
		this->status = TERMINATED;
	} else {
		throw std::string("La llamada no se encuentra en curso y no puede ser "
				"terminada");
	}
}

void Call::changeStatus(CallStatus status) {
	this->status = status;
}

CallStatus Call::getStatus() {
	return this->status;
}

unsigned int Call::getInitiator() {
	return this->initiator;
}

unsigned int Call::getReceiver() {
	return this->receiver;
}

unsigned int Call::getStartMinute() {
	return this->startMin;
}

unsigned int Call::getEndMinute() {
	return this->endMin;
}
