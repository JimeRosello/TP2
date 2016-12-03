#ifndef ANTENNA_H_
#define ANTENNA_H_

#include "Cellphone.h"

class Antenna {

private:
	unsigned int maxConnections;
	unsigned int identification;
	List<Message*>* messages;
	List<Cellphone*>* cellphones;
	List<Cellphone*>* waitingCellphoneList;
	Cellphone* spokeTheMost;               // el que hablo mas
	Cellphone* calledTheMost;              // el que llamo mas
	Cellphone* mostSpoken;                 // al que mas le hablaron
	Cellphone* mostCalled;                 // al que mas llamaron
	Cellphone* receivedBusyTheMost;        // el que mas recibio ocupado
	Cellphone* wasBusyTheMost;             // el que mas dio ocupado
	unsigned int maxConcurrentConnections; // maximo de conexiones simultaneas
	unsigned int cancelledCallsDueToLackOfCapacity;

	/*
	 * pre: ---
	 * post: Si fuera necesario, cambia el maximo de conexiones concurrentes.
	 */
	void checkMaxConcurrentConnections();

public:
	/*
	 * Pre: ---
	 * Post: Crea una Antenna con un identificador "identification" con una cantidad de conexiones
	 *       para llamadas maximas simultaneas de "maxConnections", 10 por default.
	 */
	Antenna(unsigned int identification, unsigned int maxConnections = 10);

	/*
	 * Pre: ---
	 * Post: Crea una Antenna vacia.
	 */
	Antenna();


	/*
	 * Pre: ---
	 * Post: Devuelve el indentificador "identification" de la Antenna.
	 */
	unsigned int getIdentification();

	/*
	 * Pre: ---
	 * Post: Devuelve el maximo permitido de conexiones
	 */
	unsigned int getMaxConnections();

	/*
	 * Pre: ---
	 * Post: Conecta al celular "newCellphone" a la Antenna, en caso de haber conexiones
	 *       libres devuelve TRUE y guarda dicho identificador en la lista de celulares conectados
	 *       "cellphones", o devuelve FALSE en caso de que no haya lugar disponible.
	 */
	bool connectCellphone(Cellphone* newCellphone);

	/*
	 * Pre: El celular con identificador "cellphoneID" se encuentra actualmente en la lista "cellphones".
	 * Post: Desconecta el celular de la Antenna, borrando su identificador de la lista "cellphones".
	 *       Devuelve un puntero al celular desconectado.
	 */
	Cellphone* disconnectCellphone(unsigned int cellphoneID);

	/*
	 * Pre: ---
	 * Post: Devuelve TRUE si el celular con identificador "cellphoneID" se encuentra actualmente en la lista
	 *       "cellphones", o FALSE si no lo esta. En caso de encontrarlo dejara al puntero "cursor"
	 *       de la lista "cellphones" apuntando al celular buscado, de otra forma este sera NULL.
	 */
	bool checkIfConnected(unsigned int cellphoneID);

	/*
	 * Pre: ---
	 * Post: Devuelve la cantidad de conexiones activas que hay actualmente.
	 */
	unsigned int getActiveConnections();

	/*
	 * Pre: ---
	 * Post: Devuelve TRUE si la Antena tiene todos sus canales ocupados o FALSE en el caso contrario.
	 */
	bool checkIfFull();

	/*
	 * Pre: El celular con identificador "transmitterID" se encuentra conectado a la Antenna.
	 * Post: Guarda un Mensaje para posteriormente tener la opcion de mandarlo a su remitente.
	 */
	void saveMessage(unsigned int transmitterID, unsigned int recieverID,
			std::string message, unsigned int minute);

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
	 * Pre: ---
	 * Post: Devuelve el maximo historico concurrente de celulares
	 *       conecados a la antena.
	 */
	unsigned int getMaxConcurrentConnections();

	/*
	 * Pre: ---
	 * Post: Devuelve un puntero a una lista de celulares conectados a una antena.
	 */
	List<Cellphone*>* getListOfCellphones();

	/*
	 * Pre: ---
	 * Post: Devuelve un puntero a una lista de celulares en espera para conectarse.
	 */
	List<Cellphone*>* getWaitingListOfCellphones();

	/*
	 * Pre: ---
	 * Post: Incrementa el numero de llamadas canceladas por falta de capacidad.
	 */
	void increaseCancelledCallsDueToLackOfCapacity();

	/*
	 * Pre: ---
	 * Post: Devuelve el numero d ellamadas canceladas por falta de capacidad.
	 */
	unsigned int getAmountOfCancelledCallsDueToLackOfCapacity();

	/*
	 * Pre: ---
	 * Post: Libera la memoria.
	 */
	~Antenna();
};

#endif /* Antenna_H_ */

