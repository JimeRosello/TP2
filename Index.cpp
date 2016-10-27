#include "Index.h"

#include <iostream>
#include <string>
#include "List.h"

const int MAX_OPTIONS_SYSTEM = 18;
const int MAX_OPTIONS_CELLPHONE = 6;

Index::Index() {
	this->mode = SYSTEM;
	this->systemMenu = NULL;
	this->cellphoneMenu = NULL;
	this->setMode();
	this->setMenues();
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

void Index::changeMode() {
	this->mode == SYSTEM? this->mode = CELLPHONE:
			      this->mode = SYSTEM;
	std::cout << "Se ha cambiado el modo del programa. "
		  << std::endl
		  << "El modo actual es "
		  << (this->mode == SYSTEM? "sistema.":"celular.")
		  << std::endl;
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
			case 1: break;
			case 2: break;
			case 3: break;
			case 4: break;
			case 5: break;
			case 6: break;
			case 7: break;
			case 8: break;
			case 9: break;
			case 10: break;
			case 11: break;
			case 12: break;
			case 13: break;
			case 14: break;
			case 15: break;
			case 17: break;
			case 18: this->changeMode();
				 break;
		}
	} else {
		switch (optionNumber) {
			case 1: break;
			case 2: break;
			case 3: break;
			case 4: break;
			case 5: break;
			case 6: this->changeMode();
				break; 
		}
	}

}
