#include "Cellphone.h"

Cellphone::Cellphone(unsigned int cellphoneNumber) {
	this->cellphoneNumber = cellphoneNumber;
	this->lastConnection = 0;
	this->waitingMessages = new List<Message*>();
	this->status = DISCONNECTED;
	this->inbox = new List<Message*>();
	this->outbox = new List<Message*>();
	this->unsentMessages = new List<Message*>();
	this->newMessages = new List<Message*>();
	this->incomingCalls = new List<Call*>();
	this->outgoingCalls = new List<Call*>();
	this->minutesOfOutgoingCalls = 0;
	this->minutesOfIncomingCalls = 0;
	this->numberOfRejectedOutgoingCalls = 0;
	this->numberOfRejectedIncomingCalls = 0;
	this->numberOfOutgoingCalls = 0;
	this->numberOfIncomingCalls = 0;
	//this->entryFile.open(entryFilename.c_str());
	//this->exitFile.open(exitFilename.c_str());
}

Cellphone::Cellphone() {
	this->cellphoneNumber = 0;
	this->lastConnection = 0;
	this->waitingMessages = new List<Message*>();
	this->status = DISCONNECTED;
	this->incomingCalls = new List<Call*>();
	this->outgoingCalls = new List<Call*>();
	this->inbox = new List<Message*>();
	this->outbox = new List<Message*>();
	this->unsentMessages = new List<Message*>();
	this->newMessages = new List<Message*>();
	this->minutesOfOutgoingCalls = 0;
	this->minutesOfIncomingCalls = 0;
	this->numberOfRejectedOutgoingCalls = 0;
	this->numberOfRejectedIncomingCalls = 0;
	this->numberOfOutgoingCalls = 0;
	this->numberOfIncomingCalls = 0;
	//this->entryFile.open(entryFilename.c_str());
	//this->exitFile.open(exitFilename.c_str());
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
	if (this->status == CONNECTED) {
		while (!(this->waitingMessages->isEmpty())) {
			Message* newMessage = this->waitingMessages->removeNextElement();
			this->newMessages->addNewElement(newMessage);
			this->inbox->addNewElement(newMessage);
		}
	}
}

void Cellphone::sendMessage(unsigned int receiverNumber, std::string message,
												unsigned int minute) {
	Message* msg = new Message(message, receiverNumber, this->cellphoneNumber,
											minute);
	this->outbox->addNewElement(msg);
	this->unsentMessages->addNewElement(msg);
	
	persistMessage(msg);
}

void Cellphone::persistMessage(Message* msg) {
	std::string pathBase = "/home/jime/Desktop/Algoritmos/TP2/src/Celulares/";
	std::string senderCellPath = intToString(msg->getSender());
	std::string receiverCellPath = intToString(msg->getReceiver());
	std::string exitFilename = pathBase + senderCellPath + "/egresos.txt";
	std::string incomingFilename = pathBase + receiverCellPath + "/ingresos.txt";
	createDir(pathBase);
	createDir(pathBase + senderCellPath);
	createDir(pathBase + receiverCellPath);

	std::string line = "MSG " + intToString(msg->getSender()) + " "
			+ intToString(msg->getReceiver()) + " "
			+ intToString(msg->getMinute()) + " " + msg->getBody();

	std::ofstream fileIn(exitFilename.c_str(), std::ofstream::out | std::ofstream::app);
	fileIn << line << std::endl;
	fileIn.close();

	std::ofstream fileOut(incomingFilename.c_str(), std::ofstream::out | std::ofstream::app);
	fileOut << line << std::endl;
	fileOut.close();
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

void Cellphone::addMinutesOfOutgoingCalls(unsigned int newValue) {
	this->minutesOfOutgoingCalls += newValue;
}

void Cellphone::addMinutesOfIncomingCalls(unsigned int newValue) {
	this->minutesOfIncomingCalls += newValue;
}

void Cellphone::increaseNumberOfRejectedOutgoingCalls() {
	this->numberOfRejectedOutgoingCalls++;
}

void Cellphone::increaseNumberOfRejectedIncomingCalls() {
	this->numberOfRejectedIncomingCalls++;
}

void Cellphone::increaseNumberOfOutgoingCalls() {
	this->numberOfOutgoingCalls++;
}

void Cellphone::increaseNumberOfIncomingCalls() {
	this->numberOfIncomingCalls++;
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

void Cellphone::addOutgoingCall(Call* call) {
	this->outgoingCalls->addNewElement(call);
}

List <Call*>* Cellphone::getIncomingCalls() {
	return this->incomingCalls;
}

void Cellphone::addIncomingCall(Call* call) {
	this->incomingCalls->addNewElement(call);
}
List<Message*>* Cellphone::getWaitingMessages() {
	return this->waitingMessages;
}

List<Message*>* Cellphone::getNewMessages() {
	return this->newMessages;
}

Cellphone::~Cellphone() {
	delete this->inbox;
	delete this->outbox;
	delete this->waitingMessages;
	delete this->newMessages;
	delete this->incomingCalls;
	delete this->outgoingCalls;
}
