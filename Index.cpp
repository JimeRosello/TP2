#include "Index.h"

#include <iostream>
#include <string>

const int MAX_OPTIONS_SYSTEM = 18;
const int MAX_OPTIONS_CELLPHONE = 6;

Index::Index(System* cellphoneSystem) {
	this->mode = SYSTEM;
	this->systemMenu = NULL;
	this->cellphoneMenu = NULL;
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
	this->mode = (mode == 'S'? SYSTEM:CELLPHONE);
	if (this->mode == CELLPHONE) {
		int numero;
		std::cout << "Ingrese el numero de celular"
				  << std::endl;
		std::cin >> numero;
	}
}

void Index::setMenues() {
	this->systemMenu = new std::string[MAX_OPTIONS_SYSTEM];
	this->systemMenu[0] = "Detalle de llamadas entre el Celular X y el Celular Y";
	this->systemMenu[1] = "Detalle de mensajes entre el Celular X y el Celular Y";
	this->systemMenu[2] = "Celular que mas hablo de todo el Sistema y de cada Antena";
	this->systemMenu[3] = "Celular que mas llamo de todo el Sistema y de cada Antena";
	this->systemMenu[4] = "Celular que mas recibio ocupado al intentar llamar de todo el Sistema y de cada Antena";
	this->systemMenu[5] = "Celular al que mas llamaron de todo el Sistema y de cada Antena";
	this->systemMenu[6] = "Celular al que mas le hablaron de todo el Sistema y de cada Antena";
	this->systemMenu[7] = "Celular que mas dio ocupado de todo el Sistema y de cada Antena";
	this->systemMenu[8] = "Detalle de llamadas emitidas por un Celular";
	this->systemMenu[9] = "Detalle de llamadas recibidas por un Celular";
	this->systemMenu[10] = "Cantidad maxima utilizada concurrentemente de Celulares por Antena";
	this->systemMenu[11] = "Detalle de llamadas recibidas por el Celular X y realizadas por el Celular Y";
	this->systemMenu[12] = "Cantidad de llamadas anuladas por falta de capacidad por Antena";
	this->systemMenu[13] = "Detalle de Antenas";
	this->systemMenu[14] = "Detalle de Celulares";
	this->systemMenu[15] = "Procesar archivos";
	this->systemMenu[16] = "Salir";
	this->systemMenu[17] = "Cambiar modo";

	this->cellphoneMenu = new std::string[MAX_OPTIONS_CELLPHONE];
	this->cellphoneMenu[0] = "Mostrar mensajes nuevos";
	this->cellphoneMenu[1] = "Mostrar historial de mensajes emitidos";
	this->cellphoneMenu[2] = "Mostrar historial de mensajes recibidos";
	this->cellphoneMenu[3] = "Enviar mensaje";
	this->cellphoneMenu[4] = "Cambiar de celular";
	this->cellphoneMenu[5] = "Cambiar modo";
}

void Index::printDetailOfCalls() {

}

void Index::printDetailOfMessages() {

}

void Index::printCellphonesThatSpokeTheMost() {
	std::cout << "Celular que mas hablo de todo el sistema: ";
	std::cout << this->cellphoneSystem->getCellphoneThatSpokeTheMost()->
			getNumber();
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	listOfAntennas->initiateCursor();
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		Cellphone* spokeTheMost = currentAntenna->getCellphoneThatSpokeTheMost();
		unsigned int id = currentAntenna->getIdentification();
		std::cout << "Celular que mas hablo de la antena " << id << ": "
		          << spokeTheMost->getNumber()
		          << std::endl;
	}
}

void Index::printCellphonesThatCalledTheMost() {
	std::cout << "Celular que mas llamo de todo el sistema: ";
	std::cout << this->cellphoneSystem->getCellphoneThatCalledTheMost()->
			     getNumber()
		      << std::endl;
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	listOfAntennas->initiateCursor();
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		Cellphone* calledTheMost = currentAntenna->getCellphoneThatCalledTheMost();
		unsigned int id = currentAntenna->getIdentification();
		std::cout << "Celular que mas llamo de la antena " << id << ": "
		          << calledTheMost->getNumber()
		          << std::endl;
	}
}

void Index::printCellphonesThatReceivedBusyTheMost() {
	std::cout << "Celular que mas recibio ocupado de todo el sistema: ";
	std::cout << this->cellphoneSystem->getCellphoneThatReceivedBusyTheMost()->
			getNumber();
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	listOfAntennas->initiateCursor();
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		Cellphone* receivedBusyTheMost = currentAntenna->getCellphoneThatReceivedBusyTheMost();
		unsigned int id = currentAntenna->getIdentification();
		std::cout << "Celular que mas recibio ocupado de la antena " << id << ": "
		          << receivedBusyTheMost->getNumber()
		          << std::endl;
	}
}

void Index::printCellphonesThatWereCalledTheMost() {
	std::cout << "Celular que mas fue llamado de todo el sistema: ";
	std::cout << this->cellphoneSystem->getCellphoneThatWasCalledTheMost()->
			getNumber();
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	listOfAntennas->initiateCursor();
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		Cellphone* mostCalled = currentAntenna->getCellphoneThatWasCalledTheMost();
		unsigned int id = currentAntenna->getIdentification();
		std::cout << "Celular al que mas se llamo de la antena " << id << ": "
		          << mostCalled->getNumber()
		          << std::endl;
	}
}

void Index::printCellphonesThatWereSpokenToTheMost() {
	std::cout << "Celular al que mas se le hablo de todo el sistema: ";
	std::cout << this->cellphoneSystem->getCellphoneThatWasSpokenToTheMost()->
			getNumber();
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	listOfAntennas->initiateCursor();
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		Cellphone* mostSpokenTo = currentAntenna->getCellphoneThatWasSpokenToTheMost();
		unsigned int id = currentAntenna->getIdentification();
		std::cout << "Celular al que mas se le hablo de la antena " << id << ": "
		          << mostSpokenTo->getNumber()
		          << std::endl;
	}
}

void Index::printCellphonesThatWereBusyTheMost() {
	std::cout << "Celular que mas dio ocupado de todo el sistema: ";
	std::cout << this->cellphoneSystem->getCellphoneThatWasCalledTheMost()->
			getNumber();
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	listOfAntennas->initiateCursor();
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		Cellphone* busiest = currentAntenna->getCellphoneThatWasBusyTheMost();
		unsigned int id = currentAntenna->getIdentification();
		std::cout << "Celular que mas dio ocupado de la antena " << id << ": "
		          << busiest->getNumber()
		          << std::endl;
	}

}

void Index::printDetailOfOutgoingPhoneCalls() {

}

void Index::printDetailOfIncomingPhoneCalls() {

}

void Index::printMaxAmountOfCellphonesPerAntenna() {

}

void Index::printDetailOfReceivedPhoneCalls() {
	unsigned int phoneNumber;
	std::cout << "Ingrese el numero de celular: ";
	std::cin >> phoneNumber;
	//Cellphone* getCellphone(phoneNumber);
	/*
	 *
	 * Completar!!!!
	 *
	 *
	 */
}

void Index::printAmountOfCancelledCallsDueToLackOfCapacity() {
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	listOfAntennas->initiateCursor();
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		unsigned int id = currentAntenna->getIdentification();
		unsigned int maxConnections = currentAntenna->getMaxConcurrentConnections();
		std::cout << "Antena " << id << ": " << maxConnections << std::endl;
	}
}

void Index::printDetailOfAntennas() {
	List<Antenna*>* listOfAntennas = this->cellphoneSystem->getListOfAntennas();
	listOfAntennas->initiateCursor();
	while (listOfAntennas->advanceCursor()) {
		Antenna* currentAntenna = listOfAntennas->getCursor();
		unsigned int id = currentAntenna->getIdentification();
		unsigned int maxSupported = currentAntenna->getMaxConnections();
		unsigned int maxConnections = currentAntenna->getMaxConcurrentConnections();
		std::cout << "Antena: " << id << "; "
				  << "maximas conexiones soportadas: " << maxSupported << "; "
				  << "maximas conexiones concurrentes: " << maxConnections
				  << std::endl;
	}
}

void Index::printDetailOfCellphones() {
	List<Cellphone*>* listOfCellphones = this->cellphoneSystem->getListOfCellphones();
	listOfCellphones->initiateCursor();
	while (listOfCellphones->advanceCursor()) {
		Cellphone* currentCellphone = listOfCellphones->getCursor();
		unsigned int number = currentCellphone->getNumber();
		unsigned int lastConnection = currentCellphone->getLastConnection();
		std::cout << "Celular: " << number << "; "
				  << "ID ultima antena: " << lastConnection << " "
				  << std::endl;
	}
}

void Index::processFiles() {

}

void Index::showNewMessages() {

}

void Index::showHistoryOfSentMessages() {

}

void Index::showHistoryOfReceivedMessages() {

}

void Index::sendMessage() {

}

void Index::changeCellphone() {

}


void Index::changeMode() {
	this->mode == SYSTEM? this->mode = CELLPHONE:
						  this->mode = SYSTEM;
	std::cout << "Se ha cambiado el modo del programa. "
		      << std::endl
			  << "El modo actual es "
			  << (this->mode == SYSTEM? "sistema.":"celular.")
			  << std::endl;
	//Joel: comento las siguientes lineas porque considero que
	//      las que estan en el do-while del main son suficientes
	//      (de otra forma mostraria 2 veces el menu)
	//this->printMenu();
	//this->chooseOption();
}

void Index::printMenu() {
	if (this->mode == SYSTEM) {
		for (int i = 0; i < MAX_OPTIONS_SYSTEM; i++) {
			std::cout << i+1
					  << ". "
					  << systemMenu[i]
					  << std::endl;
		}
	} else {
		for (int i = 0; i < MAX_OPTIONS_CELLPHONE; i++) {
			std::cout << i+1
					  << ". "
					  << cellphoneMenu[i]
					  << std::endl;
		}
	}
}


MODE Index::getMode() {
	return this->mode;
}

int Index::chooseOption() {
	// Guarda el maximo numero de opcion
	// Es decir, la cantidad de elementos del arreglo de opciones del modo
	// sistema, si el modo es sistema, o la de la lista de opciones del
	// modo celular, si el modo es celular.
	int maxOption = this->getMode() == SYSTEM ? MAX_OPTIONS_SYSTEM:
												MAX_OPTIONS_CELLPHONE;

	int option;
	do {
		std::cout << std::endl
				  << "Elija un numero de opcion (entre 1 y "
				  << maxOption
				  << ")"
				  << std::endl;
		std::cin >> option;
	} while ((option <= 0) || (option > maxOption));

	return option;
}

void Index::executeAction(int optionNumber) {
	if (this->mode == SYSTEM) {
		switch (optionNumber) {

			case 1: printDetailOfCalls();
				    break;
			case 2: printDetailOfMessages();
			        break;
			case 3: printCellphonesThatSpokeTheMost();
			        break;
			case 4: printCellphonesThatCalledTheMost();
			        break;
			case 5: printCellphonesThatReceivedBusyTheMost();
			        break;
			case 6: printCellphonesThatWereCalledTheMost();
			        break;
			case 7: printCellphonesThatReceivedBusyTheMost();
			        break;
			case 8: printCellphonesThatWereBusyTheMost();
			        break;
			case 9: printDetailOfOutgoingPhoneCalls();
			        break;
			case 10: printDetailOfIncomingPhoneCalls();
			         break;
			case 11: printMaxAmountOfCellphonesPerAntenna();
			         break;
			case 12: printDetailOfReceivedPhoneCalls();
			         break;
			case 13: printAmountOfCancelledCallsDueToLackOfCapacity();
			         break;
			case 14: printDetailOfAntennas();
			         break;
			case 15: printDetailOfCellphones();
			         break;
			case 16: processFiles();
			         break;
			case 17: this->inCourse = false;
					 break;
			case 18: this->changeMode();
		}
	} else {
		switch (optionNumber) {

			case 1: showNewMessages();
			        break;
			case 2: showHistoryOfSentMessages();
			        break;
			case 3: showHistoryOfReceivedMessages();
			        break;
			case 4: sendMessage();
			        break;
			case 5: changeCellphone();
			        break;
			case 6: this->changeMode();
		}
	}
}

bool Index::isInCourse() {
	return this->inCourse;
}

