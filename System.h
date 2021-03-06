#include "Antenna.h"
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
		 * Pre: La lista de antenas fue inicializada. Recibe un puntero
		 *      valido a Antenna.
		 * Post: Se agrega una antena a la lista de antenas del sistema.
		 */
		void addAntenna(Antenna* antenna);

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
		void disconnectCellphone(Cellphone* X);

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
		 * Pre: El puntero pasado como parametro es valido.
		 * Post: Compara el valor del celular que mas hablo con el de un celular
		 *       que recientemente efectuo una llamada para decidir si es necesario
		 *       cambiar el atributo spokeTheMost
		 */
		void checkCellphoneThatSpokeTheMost(Cellphone* X);


		/*
		 * Pre: El puntero pasado como parametro es valido.
		 * Post: Compara el valor del celular que mas hablo con el de un celular
		 *       que recientemente efectuo una llamada para decidir si es necesario
		 *       cambiar el atributo calledTheMost
		 */
		void checkCellphoneThatCalledTheMost(Cellphone* X);

		/*
		 * Pre: El puntero pasado como parametro es valido.
		 * Post: Compara el valor del celular que mas hablo con el de un celular
		 *       que recientemente efectuo una llamada para decidir si es necesario
		 *       cambiar el atributo mostSpoken
		 */
		void checkCellphoneThatWasSpokenToTheMost(Cellphone* X);

		/*
		 * Pre: El puntero pasado como parametro es valido.
		 * Post: Compara el valor del celular que mas hablo con el de un celular
		 *       que recientemente efectuo una llamada para decidir si es necesario
		 *       cambiar el atributo mostCalled
		 */
		void checkCellphoneThatWasCalledTheMost(Cellphone* X);

		/*
		 * Pre: El puntero pasado como parametro es valido.
		 * Post: Compara el valor del celular que mas hablo con el de un celular
		 *       que recientemente efectuo una llamada para decidir si es necesario
		 *       cambiar el atributo receivedBusyTheMost
		 */
		void checkCellphoneThatReceivedBusyTheMost(Cellphone* X);

		/*
		 * Pre: El puntero pasado como parametro es valido.
		 * Post: Compara el valor del celular que mas hablo con el de un celular
		 *       que recientemente efectuo una llamada para decidir si es necesario
		 *       cambiar el atributo wasBusyTheMost
		 */
		void checkCellphoneThatWasBusyTheMost(Cellphone* X);

		/*
		 * Pre: ---
		 * Post: Devuelve un puntero a una lista de antenas del sistema.
		 */
		List<Antenna*>* getListOfAntennas();

		/*
		 * Pre: ---
		 * Post: Devuelve un puntero a una lista de celulares del sistema.
		 */
		List<Cellphone*>* getListOfCellphones();

		/*
		 * Destructor
		 * Pre: -
		 * Post: El sistema fue destruido.
		 */
		~System();
};

