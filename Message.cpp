#include "Message.h"

using namespace std;

Message::Message() {
	this->body = "\0";
	this->receiver = 0;
}

Message::Message(string body, int receiver) {
	this->body = body;
	this->receiver = receiver;
}

string Message::getBody() {
	return this->body;
}

unsigned int Message::getReceiver() {
	return this->receiver;
}
