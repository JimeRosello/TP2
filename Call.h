#ifndef CALL_H_
#define CALL_H_

#include "Cellphone.h"

enum CallStatus {
	BUSY,
	IN_PROGRESS
};

class Call {
	private:
		Cellphone* initiator;
		Cellphone* receiver;
		unsigned int startMin;
		unsigned int endMin;
		CallStatus status;

	public:

		/*
		 * Constructor
		 * Pre: ---
		 * Post: Crea una llamada con minuto de inicio startMin,
		 *       minuto de fin por default = startMin
		 */
		Call(unsigned int startMin, Cellphone* initiator, Cellphone* receiver);

		/*
		 * Pre: El minuto pasado como parametro endMin es valido (>= startMin)
		 * Post: Cambia el minuto de fin de la llamada y el estado de los celulares
		 *       involucrados en la llamada.
		 */
		void endCall(unsigned int endMin);

		/*
		 * Pre: ---
		 * Post: Devuelve la duracion de la llamada
		 */
		unsigned int getCallDuration();

		/*
		 * Pre: ---
		 * Post: Devuelve el estado de la llamada
		 */
		CallStatus getCallStatus();

		/*
		 * Pre: ---
		 * Post: Devuelve un puntero al celular que inicio la llamada.
		 */
		Cellphone* getInitiator();

		/*
		 * Pre: ----
		 * Post: Devuelve un putnero al celular que recibio la llamada.
		 */
		Cellphone* getReceiver();



		/*
		 * Destructor
		 * Pre: ---
		 * Post: La instancia de llamada fue destruida
		 */
		~Call();
};

#endif
