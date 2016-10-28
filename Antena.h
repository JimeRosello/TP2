#ifndef ANTENA_H_
#define ANTENA_H_

#include "Cellphone.h"

class Antena {

private:
	unsigned int maxConnections;
	unsigned int identification;
	List<Message>* messages;
	List<Cellphone>* cellphones;

public:
	/*
	 * Pre: ---
	 * Post: Crea una Antena con un identificador "identification" con una cantidad de conexiones
	 *       para llamadas maximas simultaneas de "maxConnections", 10 por default.
	 */
	Antena(unsigned int identification, unsigned int maxConnections = 10);

	/*
	 * Pre: ---
	 * Post: Crea una Antena vacia.
	 */
	Antena();

	/*
	 * Pre: ---
	 * Post: Devuelve el indentificador "identification" de la Antena.
	 */
	unsigned int getIdentification();

	/*
	 * Pre: ---
	 * Post: Conecta al celular "newCellphone" a la Antena, en caso de haber conexiones
	 *       libres devuelve TRUE y guarda dicho identificador en la lista de celulares conectados
	 *       "cellphones", o devuelve FALSE en caso de que no se haya lugar disponible.
	 */
	bool conectCellphone(Cellphone* newCellphone);

	/*
	 * Pre: El celular con identificador "cellphoneID" se encuentra actualmente en la lista "cellphones".
	 * Post: Desconecta el celular de la Antena, borrando su identificador de la lista "cellphones".
	 *       Devuelve un puntero al celular desconectado.
	 */
	Cellphone* disconnectCellphone(unsigned int cellphoneID);

	/*
	 * Pre: ---
	 * Post: Devuelve TRUE si el celular con identificador "cellphoneID" se encuentra actualmente en la lista
	 *       "cellphones", o FALSE si no lo est�. En caso de encontrarlo dejara al puntero "cursor"
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
	 * Pre: El celular con identificador "transmitterID" se encuentra conectado a la Antena.
	 * Post: Guarda un Mensaje para posteriormente tener la opcion de mandarlo a su remitente.
	 */
	void saveMessage(unsigned int recieverID, std::string message);

	/*
	 * Pre: ---
	 * Post: Libera la memoria.
	 */
	~Antena();
};

#endif /* ANTENA_H_ */
