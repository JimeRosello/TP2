#include "message.h"


Message::Message(string body, int receiver) {
	this->body = body;
	this->receiver = receiver;
}

string Message::getBody() {
	return this->body;
}

int Message::getReceiver() {
	return this->receiver;
}
