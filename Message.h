#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <iostream>

class Message {

private:
	std::string body;
	unsigned int receiver;
	unsigned int sender;
	unsigned int minute;

public:

	/*
	 * Pre: El identificador del remitente pasado como parametro (sender) es valido.
	 * Post: Se creo un mensaje, con los atributos cuerpo (body) y remitente (sender).
	 */
	Message(std::string body, int receiver, int sender, int minute);

	/*
	 * Pre: ---
	 * Post: Crea un mensaje vacio.
	 */
	Message();

	/*
	 *Pre: ---
	 *Post: Devuelve el cuerpo del mensaje.
	 */
	std::string getBody();

	/*
	 *Pre: ---
	 *Post: Devuelve el identificador del destinatario del mensaje.
	 */
	unsigned int getReceiver();

	/*
	 *Pre: ---
	 *Post: Devuelve el identificador del remitente del mensaje.
	 */
	unsigned int getSender();

	/*
	 * Pre: ----
	 * Post: Devuelve el minuto en que fue enviado el mensaje.
	 */
	unsigned int getMinute();

};

#endif /* MESSAGE_H_ */

