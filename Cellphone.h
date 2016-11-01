
#ifndef CELLPHONE_H_
#define CELLPHONE_H_

#include <fstream>

#include "List.h"
#include "Message.h"
#include "Call.h"
#include "List.h"

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
	CURRENTLY_SPEAKING
};

class Cellphone {

private:
	unsigned int cellphoneNumber;
	List<Message*>* waitingMessages;
	List<Message*>* inbox;
	List<Message*>* outbox;
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
	void sendMessage(unsigned int receiverNumber, std::string message);

	/*
	 * Pre: ---
	 * Post: Libera la memoria de la lista "waitingMessages".
	 */
	void cleanWaitingMessagesList();

	/*
	 * Pre: ---
	 * Post: Devuelve el estado en que se encuentra el celular (CONNECTED,
	 * 	     DISCONNECTED, o CURRENTLY_SPEAKING)
	 */
	CellphoneStatus getStatus();

	/*
	 * Pre: El estado pasado como parametro es valido.
	 * Post: Cambia el estado del celular al pasado como parametro.
	 */
	void changeStatus(CellphoneStatus status);

	/*
	 * Pre: ---
	 * Post: Devuelve los minutos de llamadas salientes
	 */
	unsigned int getMinutesOfOutgoingCalls();

	/*
	 * Pre: ---
	 * Post: Devuelve los minutos de llamadas entrantes
	 */
	unsigned int getMinutesOfIncomingCalls();

	/*
	 * Pre: ---
	 * Post: Devuelve el numero de llamadas salientes rechazadas
	 */
	unsigned int getNumberOfRejectedOutgoingCalls();

	/*
	 * Pre: ---
	 * Post: Devuelve el numero de llamadas entrantes rechazadas
	 */
	unsigned int getNumberOfRejectedIncomingCalls();

	/*
	 * Pre: ---
	 * Post: Devuelve el numero de llamadas salientes rechazadas
	 */
	unsigned int getNumberOfOutgoingCalls();

	/*
	 * Pre: ---
	 * Post: Devuelve el numero de llamadas entrantes rechazadas
	 */
	unsigned int getNumberOfIncomingCalls();

	/*
	 * Pre: Los minutos pasados como parametro son validos
	 * Post: Cambia el atributo correspondiente por el pasado como parametro
	 */
	void changeMinutesOfOutgoingCalls(unsigned int newValue);

	/*
	 * Pre: Los minutos pasados como parametro son validos
	 * Post: Cambia el atributo correspondiente por el pasado como parametro
	 */
	void changeMinutesOfIncomingCalls(unsigned int newValue);

	/*
	 * Pre: Los minutos pasados como parametro son validos
	 * Post: Cambia el atributo correspondiente por el pasado como parametro
	 */
	void changeNumberOfRejectedOutgoingCalls(unsigned int newValue);

	/*
	 * Pre: Los minutos pasados como parametro son validos
	 * Post: Cambia el atributo correspondiente por el pasado como parametro
	 */
	void changeNumberOfRejectedIncomingCalls(unsigned int newValue);

	/*
	 * Pre: Los minutos pasados como parametro son validos
	 * Post: Cambia el atributo correspondiente por el pasado como parametro
	 */
	void changeNumberOfOutgoingCalls(unsigned int newValue);

	/*
	 * Pre: Los minutos pasados como parametro son validos
	 * Post: Cambia el atributo correspondiente por el pasado como parametro
	 */
	void changeNumberOfIncomingCalls(unsigned int newValue);

	/*
	 * Pre: ---
	 * Post: Devuelve un puntero a una pila (List) de mensajes de salida
	 */
	List<Message*>* getOutgoingMessages();

	/*
	 * Pre: ---
	 * Post: Devuelve un putnero a una pila de mensajes de entrada
	 */
	List<Message*>* getIncomingMessages();

	/*
	 * Pre: ---
	 * Post: Devuelve un puntero a una pila de llamadas salientes
	 */
	List<Call*>* getOutgoingCalls();

	/*
	 * Pre: ---
	 * Post: Devuelve un puntero a una pila de llamadas entrantes
	 */
	List<Call*>* getIncomingCalls();

	/*
	 * Pre: ---
	 * Post: Libera la memoria borrando la lista de mensajes y cerrando los archivos de entrada y salida.
	 */
	~Cellphone();

};

#endif /* CELLPHONE_H_ */
