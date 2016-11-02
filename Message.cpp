#include "Message.h"

using namespace std;

Message::Message() {
	this->body = "\0";
	this->receiver = 0;
	this->sender = 0;
	this->minute = 0;
}

Message::Message(string body, int receiver, int sender, int minute) {
	this->body = body;
	this->receiver = receiver;
	this->sender = sender;
	this->minute = minute;
}

string Message::getBody() {
	return this->body;
}

unsigned int Message::getReceiver() {
	return this->receiver;
}

unsigned int Message::getMinute() {
	return this->minute;
}

unsigned int Message::getSender() {
	return this->sender;
}

