#ifndef INDEX_H_
#define INDEX_H_

#include <string>
#include "LoadFile.h"
#include "Console.h"
#include "TimeFunctions.h"

enum MODE {
	SYSTEM,
	CELLPHONE
};

class Index {

	private:
		MODE mode;
		Cellphone* currentCellphone;
		std::string* systemMenu;
		std::string* cellphoneMenu;
		bool inCourse;
		System* cellphoneSystem;

		/*
		 * Pre: ----
		 * Post: Inicializa los menues para el modo Sistema y Celular
		 */
		void setMenues();

		/*
		 * Pre: ----
		 * Post: Inicializa el modo de comportamiento del programa
		 */
		void setMode();

		/*
		 * Metodos correspondientes a las acciones a llevar a cabo
		 * de acuerdo a la opcion elegida por el usuario.
		 * Pre: ---
		 * Post: Se imprimen los datos indicados.
		 */

		void printDetailOfCalls();
		void printDetailOfMessages();
		void printCellphonesThatSpokeTheMost();
		void printCellphonesThatCalledTheMost();
		void printCellphonesThatReceivedBusyTheMost();
		void printCellphonesThatWereCalledTheMost();
		void printCellphonesThatWereSpokenToTheMost();
		void printCellphonesThatWereBusyTheMost();
		void printDetailOfOutgoingPhoneCalls();
		void printDetailOfIncomingPhoneCalls();
		void printMaxAmountOfCellphonesPerAntenna();
		void printDetailOfReceivedPhoneCalls();
		void printAmountOfCancelledCallsDueToLackOfCapacity();
		void printDetailOfAntennas();
		void printDetailOfCellphones();
		void processFiles();

		void showNewMessages();
		void showHistoryOfSentMessages();
		void showHistoryOfReceivedMessages();
		void sendMessage();
		void changeCellphone();
		void sendAllNewMessages();

		/*
		 * Pre: ---
		 * Post: Devuelve un arreglo de punteros a Cellphone*
		 * 		 en su primera (0) y segunda (1) posicion.
		 * 		 Reserva memoria para dicho arreglo.
		 */
		Cellphone** enterCellphoneNumbers();

	public:

		/*
		 * Constructor
		 * Pre: ---
		 * Post: Crea un indice con los comportamientos del programa
		 * 		 (Sistema o Celular)
		 */
		Index(System* cellphoneSystem);

		/*
		 * Pre: ---
		 * Post: Cambia el comportamiento/modo del programa (Sistema
		 * 		 o Celular)
		 */
		void changeMode();

		/*
		 * Pre: ---
		 * Post: Devuelve el modo (Sistema o Celular) en que esta corriendo
		 *       el programa
		 */
		MODE getMode();

		/*
		 * Pre: ---
		 * Post: Imprime la lista de opciones correspondientes
		 *       al comportamiento del programa
		 */
		void printMenu();

		/*
		 * Permite elegir una opcion del menu
		 * Pre: ---
		 * Post: Devuelve la opcion elegida
		 */
		int chooseOption();

		/*
		 * Pre: optionNumber es una opcion valida (mayor que 0 y menor que el maximo
		 *      de opciones correspondiente al comportamiento del programa
		 * Post: Ejecuta la opcion del menu correspondiente a optionNumber
		 */
		void executeAction(int optionNumber);

		/*
		 * Pre: ---
		 * Post: Devuelve true si el programa esta en curso. False si no
		 */
		bool isInCourse();

		/*
		 * Destructor
		 * Pre: ---
		 * Post: El indice fue destruido.
		 */
		~Index();
};

#endif //INDEX_H_
