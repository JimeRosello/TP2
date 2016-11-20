#include "cancelledCallsPerAntenna.h"

cancelledCallsPerAntenna::cancelledCallsPerAntenna() {
	this->antennaId = 0;
	this->numberOfCalls = 0;
}

unsigned int cancelledCallsPerAntenna::getAntennaId() {
	return this->antennaId;
}

unsigned int cancelledCallsPerAntenna::getNumberOfCancelledCalls() {
	return this->numberOfCalls;
}

void cancelledCallsPerAntenna::changeAntennaId(unsigned int antennaId) {
	this->antennaId = antennaId;
}

void cancelledCallsPerAntenna::changeNumberOfCancelledCalls(unsigned int numberOfCancelledCalls) {
	this->numberOfCalls = numberOfCancelledCalls;
}
