
#ifndef CELLPHONE_H_
#define CELLPHONE_H_

#include <fstream>
#include <iostream>

#include "List.h"
#include "Message.h"
#include "Call.h"
using namespace std;

/*
 * Celular es un dispositivo que se conecta a una Antenna y permite:
 *        mostrar en pantalla el historial de mensajes recibidos a partir de un minuto inicial;
 *        mostrar en pantalla el historial de todos los mensajes recibidos;
 *        mostrar en pantalla el historial de mensajes emitidos;
 *        emitir un mensaje a otro celular;
 * Cada celular tiene dos archivos de texto, uno indicando las operaciones de Egreso (desde el celular
 *    hacia el Sistema) y otro para las operaciones de Ingreso (desde el Sistema hacia el Celular).
 * Al momento de realizar una consulta, los celulares se indican por ID o por Numero.
 */

enum CellphoneStatus {
	CONNECTED,
	DISCONNECTED,
	CURRENTLY_SPEAKING,
	WAITING_FOR_CONNECTION
};

class Cellphone {

private:
	unsigned int cellphoneNumber;
	List<Message*>* waitingMessages;
	List<Message*>* inbox;
	List<Message*>* outbox;
	List<Message*>* unsentMessages;
	List<Message*>* newMessages;
	List<Call*>* incomingCalls;
	List<Call*>* outgoingCalls;
	unsigned int lastConnection;
	CellphoneStatus status;
	unsigned int minutesOfOutgoingCalls;
	unsigned int minutesOfIncomingCalls;
	unsigned int numberOfRejectedOutgoingCalls;
	unsigned int numberOfRejectedIncomingCalls;
	unsigned int numberOfOutgoingCalls;
	unsigned int numberOfIncomingCalls;
	fstream entryFile;
	fstream exitFile;


public:
	/*
	 * Pre: ---
	 * Post: Construye un celular asignandole un numero, crea los archivos de egreso e ingreso
	 *       e inicializa la lista de los mensajes en espera.
	 */
	Cellphone(unsigned int cellphoneNumber);

	/*
	 * Pre: ---
	 * Post: Construye un celular vacio (cellphone number = 0), crea los archivos 
	 *	de egreso e ingreso e inicializa la lista de los mensajes en espera.
	 */
	Cellphone();

	/*
	 * Pre: ---
	 * Post: Devuelve el numero del celular.
	 */
	unsigned int getNumber();

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
	 * Pre: "receiverNumber" es un numero de celular registrado en el Sistema.
	 * Post: Escribe el mensaje enviado en el archivo de egreso de este celular y lo guarda en la lista de
	 *       mensajes de la Antenna a la que esta conectado. En caso de no estar conectado a ninguna Antenna
	 *       lo guarda en una lista de mensajes propia.
	 */
	void sendMessage(unsigned int receiverNumber, std::string message,
														unsigned int minute);

	/*
	 * Pre: ---
	 * Post: Agrega un mensaje a la lista de espera. Cuando el celular este
	 *       conectado, los mensajes se agregaran a la lista de mensajes de
	 *       entrada inbox.
	 */
	void addWaitingMessage(Message* message);

	/*
	 * Pre: ---
	 * Post: Devuelve la ultima conexion del celular.
	 */
	unsigned int getLastConnection();

	/*
	 * Pre: ---
	 * Post: Libera la memoria de la lista "waitingMessages".
	 */
	void cleanWaitingMessagesList();

	/*
	 * Pre: ---
	 * Post: Devuelve el estado en que se encuentra el celular (CONNECTED,
	 * 	     DISCONNECTED, o CURRENTLY_SPEAKING).
	 */
	CellphoneStatus getStatus();

	/*
	 * Pre: El celular se encuentra conectado.
	 * Post: Los mensajes en lista de espera son transferidos al buzon de entrada.
	 */
	void receiveNewMessages();

	/*
	 * Pre: El estado pasado como parametro es valido.
	 * Post: Cambia el estado del celular al pasado como parametro.
	 */
	void changeStatus(CellphoneStatus status);

	/*
	 * Pre: ---
	 * Post: Devuelve los minutos de llamadas salientes.
	 */
	unsigned int getMinutesOfOutgoingCalls();

	/*
	 * Pre: ---
	 * Post: Devuelve los minutos de llamadas entrantes.
	 */
	unsigned int getMinutesOfIncomingCalls();

	/*
	 * Pre: ---
	 * Post: Devuelve el numero de llamadas salientes rechazadas.
	 */
	unsigned int getNumberOfRejectedOutgoingCalls();

	/*
	 * Pre: ---
	 * Post: Devuelve el numero de llamadas entrantes rechazadas.
	 */
	unsigned int getNumberOfRejectedIncomingCalls();

	/*
	 * Pre: ---
	 * Post: Devuelve el numero de llamadas salientes rechazadas.
	 */
	unsigned int getNumberOfOutgoingCalls();

	/*
	 * Pre: ---
	 * Post: Devuelve el numero de llamadas entrantes rechazadas.
	 */
	unsigned int getNumberOfIncomingCalls();

	/*
	 * Pre: Los minutos pasados como parametro son validos.
	 * Post: Cambia el atributo correspondiente por el pasado como parametro.
	 */
	void addMinutesOfOutgoingCalls(unsigned int newValue);

	/*
	 * Pre: Los minutos pasados como parametro son validos.
	 * Post: Cambia el atributo correspondiente por el pasado como parametro.
	 */
	void addMinutesOfIncomingCalls(unsigned int newValue);

	/*
	 * Pre: Los minutos pasados como parametro son validos.
	 * Post: Cambia el atributo correspondiente por el pasado como parametro.
	 */
	void increaseNumberOfRejectedOutgoingCalls();

	/*
	 * Pre: Los minutos pasados como parametro son validos.
	 * Post: Cambia el atributo correspondiente por el pasado como parametro.
	 */
	void increaseNumberOfRejectedIncomingCalls();

	/*
	 * Pre: Los minutos pasados como parametro son validos.
	 * Post: Cambia el atributo correspondiente por el pasado como parametro.
	 */
	void increaseNumberOfOutgoingCalls();

	/*
	 * Pre: Los minutos pasados como parametro son validos.
	 * Post: Cambia el atributo correspondiente por el pasado como parametro.
	 */
	void increaseNumberOfIncomingCalls();

	/*
	 * Pre: antennaId es una identificacion valida.
	 * Post: Cambia la ultima conexion del celular.
	 */
	void changeLastConnection(unsigned int antennaId);

	/*
	 * Pre: ---
	 * Post: Devuelve un puntero a una Lista de mensajes de salida.
	 */
	List<Message*>* getOutgoingMessages();

	/*
	 * Pre: ---
	 * Post: Devuelve un puntero a una lista de los mensajes aun no enviados.
	 */
	List<Message*>* getUnsentMessages();

	/*
	 * Pre: ---
	 * Post: Devuelve un putnero a una pila de mensajes de entrada.
	 */
	List<Message*>* getIncomingMessages();

	/*
	 * Pre: ---
	 * Post: Devuelve un puntero a una pila de llamadas salientes.
	 */
	List<Call*>* getOutgoingCalls();

	/*
	 * Pre: ---
	 * Post: Devuelve un puntero a una pila de llamadas entrantes.
	 */
	List<Call*>* getIncomingCalls();

	/*
	 * Pre: ---
	 * Post: Devuelve la lista de mensajes en espera.
	 */
	List<Message*>* getWaitingMessages();

	/*
	 * Pre: ---
	 * Post: Devuelve la lista de los ultimos mensajes recibidos.
	 */
	List<Message*>* getNewMessages();

	/*
	 * Pre: ---
	 * Post: Libera la memoria borrando la lista de mensajes y cerrando los archivos de entrada y salida.
	 */
	~Cellphone();

};

#endif /* CELLPHONE_H_ */
