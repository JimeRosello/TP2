//#include "vector.h"
#include <string>
#include "List.h"

enum MODE {
	SYSTEM,
	CELLPHONE
};

class Index {

	private:
		MODE mode;
		std::string* systemMenu;
		std::string* cellphoneMenu;
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

	public:

		/*
		 * Constructor
		 * Pre: ---
		 * Post: Crea un indice con los comportamientos del programa
		 * 		 (Sistema o Celular)
		 */
		Index();

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
};


