#include <string>

using namespace std;


class Message {

	private:
		string body;
		int receiver;

	public:

		// Constructor
		// pre: El identificador del remitente pasado como parametro
		//      (sender) es valido
		// post: Se creo un mensaje, con los atributos cuerpo (body)
		//       y el celular que lo recibe (receiver)
		Message(string body, int receiver);

		// pre: -
		// post: Devuelve el cuerpo del mensaje
		string getBody();

		// pre: -
		// post: Devuelve el identificador del celular que recibe el
		//       mensaje
		int getReceiver();

		// Destructor
		// pre: -
		// post: El mensaje fue destruido
		~Message();
};



