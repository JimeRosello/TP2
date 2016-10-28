#include "Antenna.h"
#include "Cellphone.h"
#include "List.h"


enum CallStatus {
	BUSY,
	IN_PROGRESS
};


class System {
	private:
		List<Antenna*>* listOfAntennas;
		List<Cellphone*>* listOfCellphones;
		Cellphone* spokeTheMost;        // el que hablo mas
		Cellphone* calledTheMost;       // el que llamo mas
		Cellphone* mostSpoken;          // al que mas le hablaron
		Cellphone* mostCalled;          // al que mas llamaron
		Cellphone* receivedBusyTheMost; // el que mas recibio ocupado
		Cellphone* wasBusyTheMost;      // el que mas dio ocupado

	public:

		/*
		 * Constructor
		 * pre: -
		 * post: se inicio el sistema
		 */
		System();

		/*
		 * Crea una lista de antenas
		 * Pre: -
		 * Post: Se crea una lista de punteros a Antenna, vacia.
		 *       Devuelve un puntero a la lista.
		 */
		List<Antenna*>* createAntennaList();

		/*
		 * Pre: La lista de antenas fue inicializada. Recibe un puntero
		 *      valido a Antenna.
		 * Post: Se agrega una antena a la lista de antenas del sistema.
		 */
		void addAntenna(Antenna* antenna);

		/*
		 * Crea una lista de celulares
		 * Pre: -
		 * Post: Se crea una lista de punteros a CellPhone, vacia.
		 *       Devuelve un puntero a la lista.
		 */
		List<Cellphone*>* createCellphoneList();

		/*
		 * Pre: La lista de celulares fue inicializada. Recibe un puntero
		 *      valido a CellPhone.
		 * Post: Se agrega un celular a la lista de celulares del sistema.
		 */
		void addCellphone(Cellphone* cellphone);

		/*
		 * Inicia una llamada entre dos celulares.
		 * Pre: Los celulares se encuentran en el sistema.
		 * Post: Devuelve un estado (BUSY o IN_PROGRESS). En caso de
		 *       poder efectuarse, inicia una llamada entre los celulares
		 *       X e Y.
		 */
		CallStatus initiateCall(Cellphone* X, Cellphone* Y);

		/*
		 * Pre: Una llamada entre X e Y se encuentra en curso (IN_PROGRESS).
		 * Post: Concluye la llamada.
		 */
		void terminateCall(Cellphone* X, Cellphone* Y);

		/*
		 * Pre: El celular X se encuentra en el sistema.
		 * Post: El celular X se conecta a la antena pasada como parametro
		 */
		void connectCellphone(Cellphone* X, Antenna* antenna);

		/*
		 * Pre: El celular x se encuentra conectado a una antena.
		 * Post: El celular X se desconecta de la antena.
		 */
		void disconnectCellPhone(Cellphone* X);

		/*
		 * Pre: ---
		 * Post: Devuelve el Celular que mas hablo de todo el sistema
		 */
		Cellphone* getCellphoneThatSpokeTheMost();

		/*
		 * Pre: ---
		 * Post: Devuelve el Celular que mas llamo de todo el sistema
		 */
		Cellphone* getCellphoneThatCalledTheMost();

		/*
		 * Pre: ---
		 * Post: Devuelve el celular al que mas le hablaron de todo el sistema
		 */
		Cellphone* getCellphoneThatWasSpokenToTheMost();

		/*
		 * Pre: ---
		 * Post: Devuelve el celular al que mas llamaron de todo el sistema
		 */
		Cellphone* getCellphoneThatWasCalledTheMost();

		/*
		 * Pre: ---
		 * Post: Devuelve el celular que mas recibio ocupado al intentar
		 *       efectuar una llamada de todo el sistema
		 */
		Cellphone* getCellphoneThatReceivedBusyTheMost();

		/*
		 * Pre: ---
		 * Post: Devuelve el celular que mas dio ocupado de todo el sistema
		 */
		Cellphone* getCellphoneThatWasBusyTheMost();

		/*
		 * Destructor
		 * Pre: -
		 * Post: El sistema fue destruido.
		 */
		~System();
};

