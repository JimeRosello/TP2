#ifndef CELLPHONE_H_
#define CELLPHONE_H_

#include <fstream>

#include "List.h"
#include "Message.h"

/*
 * Celular es un dispositivo que se conecta a una antena y permite:
 *        mostrar en pantalla el historial de mensajes recibidos a partir de un minuto inicial;
 *        mostrar en pantalla el historial de todos los mensajes recibidos;
 *        mostrar en pantalla el historial de mensajes emitidos;
 *        emitir un mensaje a otro celular;
 * Cada celular tiene dos archivos de texto, uno indicando las operaciones de Egreso (desde el celular
 *    hacia el Sistema) y otro para las operaciones de Ingreso (desde el Sistema hacia el Celular).
 * Al momento de realizar una consulta, los celulares se indican por ID o por Numero.
 */

class Cellphone {

private:
	unsigned int cellphoneNumber;		//Almacena el numero de este celular.
	unsigned int assignedAntena;//Identificacion de la antena a la cual esta conectado el celular.
//	std::fstream exitFile;				//Archivo con mensajes de egreso.
//	std::fstream entryFile;				//Archivo con mensajes de ingreso.
	List<Message>* waitingMessages;	//Lista para almacenar los mensajes que aun no se han enviado.

public:
	/*
	 * Pre: ---
	 * Post: Construye un celular asignandole un numero, crea los archivos de egreso e ingreso
	 *       e inicializa la cola de los mensajes en espera.
	 */
	Cellphone(unsigned int cellphoneNumber);

	/*
	 * Pre: ---
	 * Post: Construye un celular vacio (cellphone number = 0) con una cola vacia.
	 */
	Cellphone();

	/*
	 * Pre: ---
	 * Post: Devuelve el numero del celular.
	 */
	unsigned int getNumber();

	/*
	 * Pre: ---
	 * Post: Le asigna la Antena a la que esta conectado el celular ("pointerToAntena")
	 */
	void assignAntena(unsigned int assignedAntena);

	/*
	 * Pre: El celular tiene una antena asignada.
	 * Post: Desasigna la Antena, dejando a "pointerToAntena" en NULL
	 */
	void disassignAntena();

	/*
	 * Pre: Minuto es mayor a 0 y menor a 1440 (cantidad maxima de minutos en un dia).
	 * Post: Muestra en pantalla mensajes nuevos a partir de un minuto inicial.
	 */
	void readMessages(unsigned int minute);

	/*
	 * Pre: ---
	 * Post: Muestra en pantalla todos los mensajes recibidos.
	 */
	void showInbox();

	/*
	 * Pre: ---
	 * Post: Muestra en pantalla todos los mensajes enviados.
	 */
	void showOutbox();

	/*
	 * Pre: ---
	 * Post: Devulve TRUE en caso de estar conectado a una Antena o FALSE en caso contrario.
	 */
	bool checkIfOnline();

	/*
	 * Pre: "receiverNumber" es un numero de celular registrado en el Sistema.
	 * Post: Escribe el mensaje enviado en el archivo de egreso de este celular y lo guarda en la lista de
	 *       mensajes de la antena a la que esta conectado. En caso de no estar conectado a ninguna antena
	 *       lo guarda en una lista de mensajes propia.
	 */
	void sendMessage(unsigned int receiverNumber, std::string message);

	/*
	 * Pre: ---
	 * Post: Libera la memoria de la lista "waitingMessages".
	 */
	void cleanWaitintMessagesList();

	/*
	 * Pre: ---
	 * Post: Libera la memoria borrando la lista de mensajes y cerrando los archivos de entrada y salida.
	 */
	~Cellphone();

};

#endif /* CELLPHONE_H_ */
