#ifndef CALL_H_
#define CALL_H_

#include "List.h"

enum CallStatus {
	BUSY, IN_PROGRESS, TERMINATED, WAITING
};

class Call {
private:
	unsigned int initiator;
	unsigned int receiver;
	unsigned int startMin;
	unsigned int endMin;
	CallStatus status;
	List<unsigned int>* involvedAntennas;

public:

	/*
	 * Constructor
	 * Pre: ---
	 * Post: Crea una llamada con minuto de inicio startMin,
	 *       minuto de fin por default = startMin
	 */
	Call(unsigned int startMin, unsigned int initiator, unsigned int receiver);

	/*
	 * Pre: El minuto pasado como parametro endMin es valido (>= startMin)
	 * Post: Cambia el minuto de fin de la llamada y el estado de la llamada
	 */
	void endCall(unsigned int endMin);

	/*
	 * Pre: ---
	 * Post: Devuelve la duracion de la llamada
	 */
	unsigned int getCallDuration();

	/*
	 * Pre: ---
	 * Post: Devuelve el numero del celular que inicio la llamada.
	 */
	unsigned int getInitiator();

	/*
	 * Pre: ----
	 * Post: Devuelve el numero del celular que recibio la llamada.
	 */
	unsigned int getReceiver();

	/*
	 * Pre: El estado pasado como parametro es valido (BUSY o IN_PROGRESS)
	 * Post: Cambia el estado de la llamada al pasado como parametro
	 */
	void changeStatus(CallStatus status);

	/*
	 * Pre: ---
	 * Post: Devuelve el estado de la llamada (IN_PROGRESS, BUSY o TERMINATED)
	 */
	CallStatus getStatus();

	/*
	 * Pre: ---
	 * Post: Devuelve el minuto de inicio de la llamada
	 */
	unsigned int getStartMinute();

	/*
	 * Pre: ---
	 * Post: Devuelve el minuto de fin de la llamada
	 */
	unsigned int getEndMinute();

	/*
	 * Pre: antennaID es valido
	 * Post: Agrega un id de una anetna a la lista
	 */
	void addInvolvedAntenna(unsigned int antennaID);

	/*
	 * Pre: ---
	 * Post: Devuelve una lista de las antenas involucradas en la llamada
	 */
	List<unsigned int>* getInvolvedAntennas();

	/*
	 * Destructor
	 * Pre: ---
	 * Post: La instancia de llamada fue destruida
	 */
	~Call();
};

#endif
