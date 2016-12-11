#include "Index.h"
#include "cancelledCallsPerAntenna.h"

#include <iostream>
#include <string>

Index::Index(System* cellphoneSystem) {
	this->mode = SYSTEM;
	this->currentCellphone = NULL;
	this->systemMenu = new std::string[MAX_OPTIONS_SYSTEM];
	this->cellphoneMenu = new std::string[MAX_OPTIONS_CELLPHONE];
	this->setMode();
	this->setMenues();
	this->inCourse = true;
	this->cellphoneSystem = cellphoneSystem;
}

void Index::setMode() {
	char mode;
	do {
		std::cout << "Ingrese el modo de ejecucion (S: sistema, C: celular)"
				<< std::endl;
		std::cin >> mode;
		mode = toupper(mode);
	} while ((mode != 'S') && (mode != 'C'));
	this->mode = (mode == 'S' ? SYSTEM : CELLPHONE);
	if (this->mode == CELLPHONE) {
		this->changeCellphone();
	}
}

void Index::setMenues() {
	this->systemMenu[0] =
			"Detalle de llamadas entre el Celular X y el Celular Y";
	this->systemMenu[1] =
			"Detalle de mensajes entre el Celular X y el Celular Y";
	this->systemMenu[2] =
			"Celular que mas hablo de todo el Sistema y de cada Antena";
	this->systemMenu[3] =
			"Celular que mas llamo de todo el Sistema y de cada Antena";
	this->systemMenu[4] =
			"Celular que mas recibio ocupado al intentar llamar de todo el Sistema y de cada Antena";
	this->systemMenu[5] =
			"Celular al que mas llamaron de todo el Sistema y de cada Antena";
	this->systemMenu[6] =
			"Celular al que mas le hablaron de todo el Sistema y de cada Antena";
	this->systemMenu[7] =
			"Celular que mas dio ocupado de todo el Sistema y de cada Antena";
	this->systemMenu[8] = "Detalle de llamadas emitidas por un Celular";
	this->systemMenu[9] = "Detalle de llamadas recibidas por un Celular";
	this->systemMenu[10] =
			"Cantidad maxima utilizada concurrentemente de Celulares por Antena";
	this->systemMenu[11] =
			"Detalle de llamadas recibidas por el Celular X y realizadas por el Celular Y";
	this->systemMenu[12] =
			"Cantidad de llamadas anuladas por falta de capacidad por Antena";
	this->systemMenu[13] = "Detalle de Antenas";
	this->systemMenu[14] = "Detalle de Celulares";
	this->systemMenu[15] = "Procesar archivos";
	this->systemMenu[16] = "Salir";
	this->systemMenu[17] = "Cambiar modo";

	this->cellphoneMenu[0] = "Mostrar mensajes nuevos";
	this->cellphoneMenu[1] = "Mostrar historial de mensajes emitidos";
	this->cellphoneMenu[2] = "Mostrar historial de mensajes recibidos";
	this->cellphoneMenu[3] = "Enviar mensaje";
	this->cellphoneMenu[4] = "Cambiar de celular";
	this->cellphoneMenu[5] = "Salir";
	this->cellphoneMenu[6] = "Cambiar modo";
}

List<Call*>* findCallsInCommon(Cellphone* X, Cellphone* Y) {
	List<Call*>* callsInCommon = new List<Call*>();
	List<Call*>* xIncomingCalls = X->getIncomingCalls();
	List<Call*>* xOutgoingCalls = X->getOutgoingCalls();
	xIncomingCalls->initiateCursor();
	xOutgoingCalls->initiateCursor();
	Call* currentCall;
	while (xIncomingCalls->advanceCursor()) {
		currentCall = xIncomingCalls->getCursor();
		if (currentCall->getReceiver() == Y->getNumber()
				|| currentCall->getReceiver() == X->getNumber()) {
			callsInCommon->addNewElement(currentCall);
		}
	}
	while (xOutgoingCalls->advanceCursor()) {
		currentCall = xOutgoingCalls->getCursor();
		if (currentCall->getInitiator() == Y->getNumber()) {
			callsInCommon->addNewElement(currentCall);
		}
	}

	return callsInCommon;
}

List<Message*>* findMessagesInCommon(Cellphone* X, Cellphone* Y) {
	List<Message*>* messagesInCommon = new List<Message*>();
	List<Message*>* xInbox = X->getIncomingMessages();
	List<Message*>* xOutbox = X->getOutgoingMessages();
	xInbox->initiateCursor();
	xOutbox->initiateCursor();
	Message* currentMsg;
	while (xInbox->advanceCursor()) {
		currentMsg = xInbox->getCursor();
		if (currentMsg->getReceiver() == Y->getNumber()) {
			messagesInCommon->addNewElement(currentMsg);
		}
	}
	while (xOutbox->advanceCursor()) {
		currentMsg = xOutbox->getCursor();
		if (currentMsg->getReceiver() == Y->getNumber()) {
			messagesInCommon->addNewElement(currentMsg);
		}
	}

	return messagesInCommon;
}

Cellphone** Index::enterCellphoneNumbers() {
	unsigned int numberX, numberY;
	Cellphone* X, *Y;
	std::cout << "Ingrese los celulares" << std::endl;
	do {
		std::cout << "X: ";
		std::cin >> numberX;
		X = this->cellphoneSystem->findCellphone(numberX);
		if (!X) {
			std::cout << "El celular no se encuentra en el sistema"
					<< std::endl;
		}
	} while (!X);
	do {
		std::cout << "Y: ";
		std::cin >> numberY;
		Y = this->cellphoneSystem->findCellphone(numberY);
		if (!Y) {
			std::cout << "El celular no se encuentra en el sistema"
					<< std::endl;
		}
	} while (!Y);
	Cellphone** returnValue = new Cellphone*[2];
	returnValue[0] = X;
	returnValue[1] = Y;
	return returnValue;
}

void Index::printDetailOfCalls() {
	Cellphone** cellphones = enterCellphoneNumbers();
	List<Call*>* callsInCommon = findCallsInCommon(cellphones[0],
			cellphones[1]);
	delete[] cellphones;
	if (callsInCommon->isEmpty()) {
		std::cout << "No hay llamadas para mostrar. " << std::endl;
	}
	callsInCommon->initiateCursor();
	Call* currentCall;
	unsigned int totalMinutes = 0;
	unsigned int amountOfBusyCalls = 0;
	std::cout << "Horarios de las llamadas: " << std::endl;
	while (callsInCommon->advanceCursor()) {
		currentCall = callsInCommon->getCursor();
		totalMinutes += currentCall->getCallDuration();
		if (currentCall->getStatus() == BUSY) {
			amountOfBusyCalls++;
		}
		List<unsigned int>* involvedAntennas =
				currentCall->getInvolvedAntennas();
		involvedAntennas->initiateCursor();
		std::cout << "Inicio: " << currentCall->getStartMinute() << std::endl
				<< "Fin: " << currentCall->getEndMinute() << std::endl
				<< "Antenas utilizadas: " << std::endl;
		while (involvedAntennas->advanceCursor()) {
			unsigned int currentAntenna = involvedAntennas->getCursor();
			std::cout << currentAntenna << ", ";
		}
		std::cout << std::endl;
	}
	std::cout << "Cantidad total de llamadas: "
			<< callsInCommon->getAmountOfElements() << std::endl
			<< "Duracion total de llamadas: " << totalMinutes << std::endl
			<< "Cantidad de llamadas ocupadas: " << amountOfBusyCalls
			<< std::endl;
}

void Index::printDetailOfMessages() {
	Cellphone** cellphones = enterCellphoneNumbers();
	List<Message*>* messagesInCommon = findMessagesInCommon(cellphones[0],
			cellphones[1]);
	delete[] cellphones;
	if (messagesInCommon->isEmpty()) {
		std::cout << "No hay mensajes para mostrar. " << std::endl;
	}
	messagesInCommon->initiateCursor();
	Message* currentMsg;
	while (messagesInCommon->advanceCursor()) {
		currentMsg = messagesInCommon->getCursor();
		std::cout << "Minuto: " << currentMsg->getMinute() << std::endl
				<< "Mensaje: " << currentMsg->getBody() << std::endl
				<< "Emisor: " << currentMsg->getSender() << std::endl
				<< "Receptor: " << currentMsg->getReceiver() << std::endl;

	}

}

void Index::printCellphonesThatSpokeTheMost() {
	std::cout << "Celular que mas hablo de todo el sistema: ";
	Cellphone* spokeTheMost =
			this->cellphoneSystem->getCellphoneThatSpokeTheMost();
	std::cout << spokeTheMost->getNumber() << std::endl;
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	listOfAntennas->initiateCursor();
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		spokeTheMost = currentAntenna->getCellphoneThatSpokeTheMost();
		unsigned int id = currentAntenna->getIdentification();
		unsigned int number = (spokeTheMost ? spokeTheMost->getNumber() : 0);
		if (id != 0 && number != 0) {
			std::cout << "Celular que mas hablo de la antena " << id << ": "
					<< number << std::endl;
		}
	}
}

void Index::printCellphonesThatCalledTheMost() {
	std::cout << "Celular que mas llamo de todo el sistema: ";
	std::cout
			<< this->cellphoneSystem->getCellphoneThatCalledTheMost()->getNumber()
			<< std::endl;
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	listOfAntennas->initiateCursor();
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		Cellphone* calledTheMost =
				currentAntenna->getCellphoneThatCalledTheMost();
		unsigned int id = currentAntenna->getIdentification();
		unsigned int number = (calledTheMost ? calledTheMost->getNumber() : 0);
		if (id != 0 && number != 0) {
			std::cout << "Celular que mas llamo de la antena " << id << ": "
					<< number << std::endl;
		}
	}
}

void Index::printCellphonesThatReceivedBusyTheMost() {
	std::cout << "Celular que mas recibio ocupado de todo el sistema: ";
	std::cout
			<< this->cellphoneSystem->getCellphoneThatReceivedBusyTheMost()->getNumber();
	std::cout << std::endl;
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	listOfAntennas->initiateCursor();
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		Cellphone* receivedBusyTheMost =
				currentAntenna->getCellphoneThatReceivedBusyTheMost();
		unsigned int id = currentAntenna->getIdentification();
		unsigned int number = (
				receivedBusyTheMost ? receivedBusyTheMost->getNumber() : 0);
		if (id != 0 && number != 0) {
			std::cout << "Celular que mas recibio ocupado de la antena " << id
					<< ": " << number << std::endl;
		}
	}
}

void Index::printCellphonesThatWereCalledTheMost() {
	std::cout << "Celular que mas fue llamado de todo el sistema: ";
	std::cout
			<< this->cellphoneSystem->getCellphoneThatWasCalledTheMost()->getNumber();
	std::cout << std::endl;
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	listOfAntennas->initiateCursor();
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		Cellphone* mostCalled =
				currentAntenna->getCellphoneThatWasCalledTheMost();
		unsigned int id = currentAntenna->getIdentification();
		unsigned int number = (mostCalled ? mostCalled->getNumber() : 0);
		if (id != 0 && number != 0) {
			std::cout << "Celular que mas fue llamado de la antena " << id
					<< ": " << number << std::endl;
		}
	}
}

void Index::printCellphonesThatWereSpokenToTheMost() {
	std::cout << "Celular al que mas se le hablo de todo el sistema: ";
	std::cout
			<< this->cellphoneSystem->getCellphoneThatWasSpokenToTheMost()->getNumber();
	std::cout << std::endl;
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	listOfAntennas->initiateCursor();
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		Cellphone* mostSpoken =
				currentAntenna->getCellphoneThatWasSpokenToTheMost();
		unsigned int id = currentAntenna->getIdentification();
		unsigned int number = (mostSpoken ? mostSpoken->getNumber() : 0);
		std::cout << "Celular al que mas se le hablo de la antena " << id
				<< ": " << number << std::endl;
	}
}

void Index::printCellphonesThatWereBusyTheMost() {
	std::cout << "Celular que mas dio ocupado de todo el sistema: ";
	std::cout
			<< this->cellphoneSystem->getCellphoneThatWasCalledTheMost()->getNumber();
	std::cout << std::endl;
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	listOfAntennas->initiateCursor();
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		Cellphone* busiest = currentAntenna->getCellphoneThatWasBusyTheMost();
		unsigned int id = currentAntenna->getIdentification();
		unsigned int number = (busiest ? busiest->getNumber() : 0);
		if (id != 0 && number != 0) {
			std::cout << "Celular que mas dio ocupado de la antena " << id
					<< ": " << number << std::endl;
		}
	}

}

void Index::printDetailOfOutgoingPhoneCalls() {
	unsigned int number;
	Cellphone* X;
	do {
		std::cout << "Ingrese el celular" << std::endl;
		std::cin >> number;
		X = this->cellphoneSystem->findCellphone(number);
	} while (!X);
	List<Call*>* outgoingPhoneCalls = X->getOutgoingCalls();
	if (outgoingPhoneCalls->isEmpty()) {
		std::cout << "No hay llamadas para mostrar. " << std::endl;
	}
	outgoingPhoneCalls->initiateCursor();
	Call* currentCall;
	while (outgoingPhoneCalls->advanceCursor()) {
		currentCall = outgoingPhoneCalls->getCursor();
		if (currentCall->getStatus() == BUSY) {
			std::cout << "Llamada ocupada a " << currentCall->getReceiver()
					<< std::endl;
		} else {
			std::cout << "Receptor de la llamada: "
					<< currentCall->getReceiver() << std::endl
					<< "Minuto de inicio: " << currentCall->getStartMinute()
					<< std::endl << "Minuto de fin: "
					<< currentCall->getEndMinute() << std::endl;
		}
	}
}

void Index::printDetailOfIncomingPhoneCalls() {
	unsigned int number;
	Cellphone* X;
	do {
		std::cout << "Ingrese el celular" << std::endl;
		std::cin >> number;
		X = this->cellphoneSystem->findCellphone(number);
	} while (!X);
	List<Call*>* incomingPhoneCalls = X->getIncomingCalls();
	if (incomingPhoneCalls->isEmpty()) {
		std::cout << "No hay llamadas para mostrar. " << std::endl;
	}
	incomingPhoneCalls->initiateCursor();
	Call* currentCall;
	while (incomingPhoneCalls->advanceCursor()) {
		currentCall = incomingPhoneCalls->getCursor();
		if (currentCall->getStatus() == BUSY) {
			std::cout << "Llamada ocupada de " << currentCall->getInitiator()
					<< std::endl;
		} else {
			std::cout << "Emisor de la llamada: " << currentCall->getInitiator()
					<< std::endl << "Minuto de inicio: "
					<< currentCall->getStartMinute() << std::endl
					<< "Minuto de fin: " << currentCall->getEndMinute()
					<< std::endl;
		}
	}
}

void Index::printDetailOfIncomingPhoneCallsFromCellphone() {
	Cellphone** cellphones = enterCellphoneNumbers();
	List<Call*>* incomingPhoneCalls = cellphones[0]->getIncomingCalls();
	if (incomingPhoneCalls->isEmpty()) {
		std::cout << "No hay llamadas para mostrar. " << std::endl;
	}
	incomingPhoneCalls->initiateCursor();
	Call* currentCall;
	while (incomingPhoneCalls->advanceCursor()) {
		currentCall = incomingPhoneCalls->getCursor();
		if (currentCall->getInitiator() == cellphones[1]->getNumber()) {
			if (currentCall->getStatus() == BUSY) {
				std::cout << "Llamada ocupada de "
						<< currentCall->getInitiator() << ", minuto "
						<< currentCall->getStartMinute() << std::endl;
			} else {
				std::cout << "Emisor de la llamada: "
						<< currentCall->getInitiator() << std::endl
						<< "Minuto de inicio: " << currentCall->getStartMinute()
						<< std::endl << "Minuto de fin: "
						<< currentCall->getEndMinute() << std::endl;
			}
		}
	}
}

void Index::printMaxAmountOfCellphonesPerAntenna() {
	List<Antenna*>* antennas = this->cellphoneSystem->getListOfAntennas();
	antennas->initiateCursor();
	Antenna* currentAntenna;
	while (antennas->advanceCursor()) {
		currentAntenna = antennas->getCursor();
		std::cout << "Antena " << currentAntenna->getIdentification()
				<< std::endl << "Maximo concurrente utilizado: "
				<< currentAntenna->getMaxConcurrentConnections() << std::endl;
	}
}

/*
 * Quick sort
 * Pre: Recibe un arreglo de llamadas canceladas por antena
 * 		(cancelledCallsPerAntenna), una posicion inicial (first) y una
 * 		posicion final (last).
 * Post: Ordena el vector pasado como parametro. No tiene valor de retorno.
 */

void QS(cancelledCallsPerAntenna* vector, unsigned int first,
		unsigned int last) {

	if (first < last) {
		unsigned int left, right, pivot, tempNumber, tempAntenna;

		pivot = vector[first].getNumberOfCancelledCalls();
		left = first;
		right = last;

		while (left < right) {
			while (vector[right].getNumberOfCancelledCalls() > pivot) {
				right--;
			}

			while ((left < right)
					&& (vector[left].getNumberOfCancelledCalls() <= pivot)) {
				left++;
			}

			if (left < right) {
				tempNumber = vector[left].getNumberOfCancelledCalls();
				tempAntenna = vector[left].getAntennaId();
				vector[left].changeNumberOfCancelledCalls(
						vector[right].getNumberOfCancelledCalls());
				vector[left].changeAntennaId(vector[right].getAntennaId());
				vector[right].changeNumberOfCancelledCalls(tempNumber);
				vector[right].changeAntennaId(tempAntenna);
			}
		}

		tempNumber = vector[right].getNumberOfCancelledCalls();
		tempAntenna = vector[right].getAntennaId();
		vector[right].changeNumberOfCancelledCalls(
				vector[first].getNumberOfCancelledCalls());
		vector[right].changeAntennaId(vector[first].getAntennaId());
		vector[first].changeNumberOfCancelledCalls(tempNumber);
		vector[first].changeAntennaId(tempAntenna);

		unsigned int postpivot = right;

		QS(vector, first, postpivot - 1);
		QS(vector, postpivot + 1, last);
	}
}

void Index::printAmountOfCancelledCallsDueToLackOfCapacity() {
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	unsigned int numberOfAntennas = listOfAntennas->getAmountOfElements();
	cancelledCallsPerAntenna* cancelledCallsVector =
			new cancelledCallsPerAntenna[numberOfAntennas];
	listOfAntennas->initiateCursor();
	unsigned int i = 0;
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		unsigned int id = currentAntenna->getIdentification();
		unsigned int numberOfCancelledCalls =
				currentAntenna->getAmountOfCancelledCallsDueToLackOfCapacity();
		cancelledCallsVector[i].changeAntennaId(id);
		cancelledCallsVector[i].changeNumberOfCancelledCalls(
				numberOfCancelledCalls);
		i++;
	}
	QS(cancelledCallsVector, i, 0); //ordenado de forma descendente
	i = 0;
	while (i <= numberOfAntennas) {
		std::cout << "Antena: " << cancelledCallsVector[i].getAntennaId()
				<< " ~ Numero de llamadas canceladas: "
				<< cancelledCallsVector[i].getNumberOfCancelledCalls()
				<< std::endl;
		i++;
	}
	delete[] cancelledCallsVector;
}

void Index::printDetailOfAntennas() {
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	listOfAntennas->initiateCursor();
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		unsigned int id = currentAntenna->getIdentification();
		unsigned int maxSupported = currentAntenna->getMaxConnections();
		unsigned int maxConnections =
				currentAntenna->getMaxConcurrentConnections();
		std::cout << "Antena: " << id << "; "
				<< "maximas conexiones soportadas: " << maxSupported << "; "
				<< "maximas conexiones concurrentes: " << maxConnections
				<< std::endl;
	}
}

void Index::printDetailOfCellphones() {
	List<Cellphone*>* listOfCellphones =
			this->cellphoneSystem->getListOfCellphones();
	listOfCellphones->initiateCursor();
	while (listOfCellphones->advanceCursor()) {
		Cellphone* currentCellphone = listOfCellphones->getCursor();
		unsigned int number = currentCellphone->getNumber();
		unsigned int lastConnection = currentCellphone->getLastConnection();
		std::cout << "Celular: " << number << "; " << "ID ultima antena: A"
				<< lastConnection << " " << std::endl;
	}
}

void Index::processFiles() {
	//std::string filename = FILENAME; // /home/jime/Desktop/Algoritmos/TP2/src/prueba1.txt";
	LoadFile(FILENAME, this->cellphoneSystem);
}

void Index::showNewMessages() {
	List<Message*>* newMessages = this->currentCellphone->getNewMessages();
	Message* currentMessage;
	if (newMessages->isEmpty()) {
		std::cout << "No hay mensajes para mostrar" << std::endl;
	} else {
		while (!newMessages->isEmpty()) {
			currentMessage = newMessages->removeNextElement();
			std::cout << "Mensaje de " << currentMessage->getSender()
					<< " en el minuto " << currentMessage->getMinute() << ": "
					<< std::endl << currentMessage->getBody() << std::endl;
		}
	}
}

void Index::showHistoryOfSentMessages() {
	List<Message*>* outbox = this->currentCellphone->getOutgoingMessages();
	outbox->initiateCursor();
	Message* currentMsg;
	while (outbox->advanceCursor()) {
		currentMsg = outbox->getCursor();
		std::cout << "Minuto: " << currentMsg->getMinute() << std::endl
				<< "Mensaje: " << currentMsg->getBody() << std::endl
				<< "Receptor: " << currentMsg->getReceiver() << std::endl;
	}
}

void Index::showHistoryOfReceivedMessages() {
	List<Message*>* inbox = this->currentCellphone->getIncomingMessages();
	Message* currentMsg;
	if (inbox->isEmpty()) {
		std::cout << "No hay mensajes para mostrar" << std::endl;
	} else {
		inbox->initiateCursor();
		while (inbox->advanceCursor()) {
			currentMsg = inbox->getCursor();
			std::cout << "Minuto: " << currentMsg->getMinute() << std::endl
					<< "Mensaje: " << currentMsg->getBody() << std::endl
					<< "Remitente: " << currentMsg->getSender() << std::endl;
		}
	}
}

void Index::sendMessage() {
	unsigned int receiver;
	std::string message;
	do {
		std::cout << "Ingrese el destinatario del mensaje" << std::endl;
		std::cin >> receiver;
	} while (!this->cellphoneSystem->findCellphone(receiver));
	std::cout << std::endl << "Ingrese el mensaje" << std::endl;
	message = RequestTextLineInput();
	unsigned int minute = getMinutesSinceMidnight();
	this->currentCellphone->sendMessage(receiver, message, minute);
	this->cellphoneSystem->sendUnsentMessages(this->currentCellphone);
}

void Index::changeCellphone() {
	unsigned int number;
	std::cout << "Ingrese el numero de celular" << std::endl;
	std::cin >> number;
	Cellphone* cellphone = this->cellphoneSystem->findCellphone(number);
	if (!cellphone) {
		std::cout << "El celular ingresado no se encuentra en el sistema"
				<< std::endl;
	}
	if (cellphone->getStatus() == CONNECTED) {
		cellphone->receiveNewMessages();
	}
	this->currentCellphone = cellphone;
}

void Index::changeMode() {
	this->mode == SYSTEM ? this->mode = CELLPHONE : this->mode = SYSTEM;
	std::cout << "Se ha cambiado el modo del programa. " << std::endl
			<< "El modo actual es "
			<< (this->mode == SYSTEM ? "sistema." : "celular.") << std::endl;
	if (this->mode == CELLPHONE) {
		this->currentCellphone = 0;
		while (this->currentCellphone == 0) {
			this->changeCellphone();
		}
	}
}

void Index::printMenu() {
	if (this->mode == SYSTEM) {
		for (int i = 0; i < MAX_OPTIONS_SYSTEM; i++) {
			std::cout << i + 1 << ". " << systemMenu[i] << std::endl;
		}
	} else {
		for (int i = 0; i < MAX_OPTIONS_CELLPHONE; i++) {
			std::cout << i + 1 << ". " << cellphoneMenu[i] << std::endl;
		}
	}
}

MODE Index::getMode() {
	return this->mode;
}

int Index::chooseOption() {
	/*
	 * Guarda el maximo numero de opcion
	 * Es decir, la cantidad de elementos del arreglo de opciones del modo
	 * sistema, si el modo es sistema, o la de la lista de opciones del
	 * modo celular, si el modo es celular.
	 */
	int maxOption =
			this->getMode() == SYSTEM ?
					MAX_OPTIONS_SYSTEM : MAX_OPTIONS_CELLPHONE;
	int option;
	do {
		std::cout << std::endl << "Elija un numero de opcion (entre 1 y "
				<< maxOption << ")" << std::endl;
		std::cin >> option;
	} while ((option <= 0) || (option > maxOption));

	return option;
}

void Index::executeAction(int optionNumber) {
	if (this->mode == SYSTEM) {
		switch (optionNumber) {
		case 1:
			printDetailOfCalls();
			break;
		case 2:
			printDetailOfMessages();
			break;
		case 3:
			printCellphonesThatSpokeTheMost();
			break;
		case 4:
			printCellphonesThatCalledTheMost();
			break;
		case 5:
			printCellphonesThatReceivedBusyTheMost();
			break;
		case 6:
			printCellphonesThatWereCalledTheMost();
			break;
		case 7:
			printCellphonesThatReceivedBusyTheMost();
			break;
		case 8:
			printCellphonesThatWereBusyTheMost();
			break;
		case 9:
			printDetailOfOutgoingPhoneCalls();
			break;
		case 10:
			printDetailOfIncomingPhoneCalls();
			break;
		case 11:
			printMaxAmountOfCellphonesPerAntenna();
			break;
		case 12:
			this->printDetailOfIncomingPhoneCallsFromCellphone();
			break;
		case 13:
			printAmountOfCancelledCallsDueToLackOfCapacity();
			break;
		case 14:
			printDetailOfAntennas();
			break;
		case 15:
			printDetailOfCellphones();
			break;
		case 16:
			delete this->cellphoneSystem;
			this->cellphoneSystem = new System();
			processFiles();
			break;
		case 17:
			this->inCourse = false;
			break;
		case 18:
			this->changeMode();
		}
	} else {
		switch (optionNumber) {
		case 1:
			showNewMessages();
			break;
		case 2:
			showHistoryOfSentMessages();
			break;
		case 3:
			showHistoryOfReceivedMessages();
			break;
		case 4:
			sendMessage();
			break;
		case 5:
			changeCellphone();
			break;
		case 6:
			this->inCourse = false;
			break;
		case 7:
			changeMode();
		}
	}
}

bool Index::isInCourse() {
	return this->inCourse;
}

Index::~Index() {
	delete[] this->systemMenu;
	delete[] this->cellphoneMenu;
	delete this->cellphoneSystem;
}
