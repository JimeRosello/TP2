#ifndef CANCELLEDCALLSPERANTENNA_H_
#define CANCELLEDCALLSPERANTENNA_H_

class cancelledCallsPerAntenna {
	private:
		unsigned int antennaId;
		unsigned int numberOfCalls;

	public:

		/*
		 * Constructor
		 */
		cancelledCallsPerAntenna();

		/*
		 * Pre: ---;
		 * Post: Devuelve el identificador de la antena.
		 */
		unsigned int getAntennaId();

		/*
		 * Pre: ---;
		 * Post: Devuelve el numero de llamadas canceladas.
		 */
		unsigned int getNumberOfCancelledCalls();

		/*
		 * Pre: El numero de llamadas es valido.
		 * Post: Cambia el numero de llamadas del objeto.
		 */
		void changeNumberOfCancelledCalls(unsigned int numberOfCancelledCalls);

		/*
		 * Pre: El id de la antena es valido.
		 * Post: Cambia el id de la antena del objeto.
		 */
		void changeAntennaId(unsigned int antennaId);

		/*
		 * Destructor
		 */
		~cancelledCallsPerAntenna();

};

#endif
