#ifndef SYSTEM_H_
#define SYSTEM_H_


#include "Antenna.h"


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
		List<Call*>* callsInProgress;

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
		 *      startMin es un minuto valido.
		 * Post: Hay una nueva llamada en la lista de llamadas en curso.
		 */
		void initiateCall(unsigned int startMin, Cellphone* X, Cellphone* Y);

		/*
		 * Pre: Una llamada entre X e Y se encuentra en curso (IN_PROGRESS).
		 * Post: Concluye la llamada. Devuelve la duracion de la llamada.
		 */
		unsigned int terminateCall(Call* call, unsigned int endMin);

		/*
		 * Pre: Recibe un puntero valido a Cellphone.
		 * Post: Todos los mensajes no enviados del celular (cellphone
		 * 	     son enviados a sus correspondientes receptores.
		 */
		void sendUnsentMessages(Cellphone* cellphone);

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
		 * Busca un celular en la lista de celulares.
		 * Pre: El numero pasado como parametro es un numero de celular valido.
		 * Post: Devuelve un puntero al celular buscado, o NULL si no lo encontro.
		 */
		Cellphone* findCellphone(unsigned int cellphoneNumber);

		/*
		 * Busca una antena en la lista de antenas.
		 * Pre: El numero pasado como parametro es un id valido.
		 * Post: Devuelve un puntero a la antena buscada, o NULL si no la encontro.
		 */
		Antenna* findAntenna(unsigned int idAntenna);

		/*
		 * Pre: El celular se encuentra en el sistema
		 * Post: Devuelve un puntero a la antena a la que se encuentra conectado
		 *       el celular cellphone pasado como parametro.
		 *       Devuelve NULL si no se encuentra conectado a ninguna antena.
		 */
		Antenna* findAntennaToWhichCellIsConnected(Cellphone* cellphone);

		/*
		 * Pre: El celular se encuentra en el sistema
		 * Post: Devuelve un puntero a la antena en la que esta esperando a
		 * 		 conectarse el celular pasado como parametro.
		 *       Devuelve NULL si no se encuentra conectado a ninguna antena.
		 */
		Antenna* findAntennaToWhichCellIsWaitingForConnection(Cellphone* cellphone);

		/*
		 * Busca una llamada en la lista de llamadas del sistema
		 * Pre: Recibe un numero de celular emisor y receptor validos.
		 * Post: Devuelve un puntero a la llamada encontrada o NULL si no la
		 *       encontro.
		 */
		Call* findCallInProgress(unsigned int initiator, unsigned int receiver);

		/*
		 * Busca una llamada en la lista de llamadas del sistema,
		 * iniciada por X y que se encuentra en curso.
		 * Pre: Recibe un numero de celular valido.
		 * Post: Devuelve un puntero a la llamada encontrada o NULL si no la
		 * 	 	 encontro.
		 */
		Call* findCallInProgressByCellphone(unsigned int initiator);

		/*
		 * Envia todos los mensajes pendientes.
		 * Pre:
		 * Post:
		 */
		void sendAllUnsentMessages();
		
		/*
		 * Pre: --
		 * Post: Devuelve una lista de punteros a llamada.
		 */
		List<Call*>* getListOfCalls();

		/*
		 * Destructor
		 * Pre: -
		 * Post: El sistema fue destruido.
		 */
		~System();
};

#endif //SYSTEM_H_

