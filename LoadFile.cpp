#include "LoadFile.h"
#include <vector>
#include <sstream>
#include <cstring>

bool strEqual_pred(unsigned char a, unsigned char b) {
	return std::tolower(a) == std::tolower(b);
}

bool strEqual(std::string const& a, std::string const& b) {
	if (a.length() == b.length())
		return std::equal(b.begin(), b.end(), a.begin(), strEqual_pred);
	else
		return false;
}

int getKeyValue(std::string text, std::string& key, std::string& values) {
	int posSeparator = text.find(" ");
	if (posSeparator != -1) {
		key = text.substr(0, posSeparator);
		values = text.substr(posSeparator + 1);
	} else {
		key = text;
		values = "";
	}
	return posSeparator;
}


// Convierte una cadena en entero
int strtoi (std::string string) {
	int integer;
	std::istringstream buffer (string);
	buffer >> integer;
	return integer;
}


// Separan un string en subcadenas separadas por delim

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

// Devuelve un vector con las subcadenas

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


void LoadFile(std::string fileName, System* system) {
	std::string line, command, values, antennaId, antennaCapacity,
				startMin, strNumberX, strNumberY, endMin, message;
	std::ifstream file(fileName.c_str());

	// Lee una a una las lineas del archivo
 	while (getline(file, line)) {

 		// Obtiene un vector con una keyword en cada uno de sus campos
 		std::vector<std::string> strVector = split(line, ' ');
 		// La primera posicion corresponde al comando a ejecutar
 		// (Antena, Inicio, Conectar, etc.)
 		command = strVector[0];

		if (strEqual(command, "Antena")) {
			antennaId = strVector[1];
			antennaCapacity = strVector[2];
			unsigned int id = strtoi(antennaId);
			unsigned int capacity = strtoi(antennaCapacity);

			std::cout << "AntennaId: " << antennaId << " antennaCapacity: "
					<< antennaCapacity << std::endl;

			// Agrega una nueva antena al sistema
			Antenna* antenna = new Antenna(id, capacity);
			system->addAntenna(antenna);

		} else if (strEqual(command, "Inicio")) {
			strNumberX = strVector[1];
			strNumberY = strVector[2];
			startMin = strVector[3];
			unsigned int numberX = strtoi(strNumberX);
			unsigned int numberY = strtoi(strNumberY);
			unsigned int minute = strtoi(startMin);

			// Busca los celulares en el sistema.

			Cellphone* X = system->findCellphone(numberX);
			//X == NULL? (std::cout<<"No lo encontro"):(std::cout<<"Lo encontro");
			Cellphone* Y = system->findCellphone(numberY);
			//Y == NULL? (std::cout<<"No lo encontro"):(std::cout<<"Lo encontro");
			if (!X) {
				X = new Cellphone(numberX);
				system->addCellphone(X);
			}
			if (!Y) {
				X = new Cellphone(numberY);
				system->addCellphone(Y);
			}
			std::cout << "CelularX: " << strNumberX << " Celular Y: "
					<< strNumberY << " Minuto: " << minute << std::endl;

			// Inicia una llamada entre los celulares encontrados
			system->initiateCall(minute, X, Y);

		} else if (strEqual(command, "Fin")) {
			unsigned int numberX = strtoi(strNumberX);
			unsigned int numberY = strtoi(strNumberY);
			unsigned int minute = strtoi(endMin);

			Call* call = system->findCallInProgress(numberX, numberY);
			// Termina la llamada
			if (call) {
				system->terminateCall(call, minute);
			}
			std::cout << "Celular X: " << strNumberX << " Celular Y: "
					<< strNumberY << " Minuto: " << minute << std::endl;

		} else if (strEqual(command, "Msg")) {
			strNumberX = strVector[1];
			strNumberY = strVector[2];
			startMin = strVector[3];
			message = strVector[4];
			int i = 5;
			while (strVector[i] != "") {
				message = message + " " + strVector[i];
				i++;
			}

			unsigned int numberX = strtoi(strNumberX);
			unsigned int numberY = strtoi(strNumberY);
			unsigned int minute = strtoi(startMin);
			Cellphone* X = system->findCellphone(numberX);
			Cellphone* Y = system->findCellphone(numberY);
			if (X && Y) {
				X->sendMessage(numberY, message, minute);
				system->sendUnsentMessages(X);
				Y->receiveNewMessages();
			}


		} else if (strEqual(command, "Conectar")) {

			strNumberX = strVector[1];
			antennaId = strVector[2];
			startMin = strVector[3];
			// Divide el id de la antena separando la "A" del identificador
			std::vector<std::string> antennaIdV = split(antennaId, 'A');
			unsigned int numberX = strtoi(strNumberX);
			unsigned int id = strtoi(antennaIdV[1]);
			unsigned int min = strtoi(startMin);
			// Busca el celular en el sistema.
			// Si no esta, lo agrega
			Cellphone* X = system->findCellphone(numberX);

			// Busca la antena en el sistema
			Antenna* antenna = system->findAntenna(id);
			if (!antenna) {
				// Si no esta la antena en el sistema, la crea y la agrega
				antenna = new Antenna(id, 10);
				system->addAntenna(antenna);
			}
			if (!X) {
				X = new Cellphone(numberX);
				system->addCellphone(X);
			}

			// Conecta el celular X a la antena
			system->connectCellphone(X, antenna);

			std::cout << "Celular X: " << numberX << " Antena: "
					<< id << " Minuto: " << min << std::endl;

		} else if (strEqual(command, "Desconectar")) {

			strNumberX = strVector[1];
			antennaId = strVector[2];
			endMin = strVector[3];
			// Divide el id de la antena separando la "A" del identificador
			std::vector<std::string> antennaIdV = split(antennaId, 'A');

			unsigned int numberX = strtoi(strNumberX);
			unsigned int id = strtoi(antennaIdV[1]);
			unsigned int min = strtoi(endMin);
			// Busca el celular en el sistema.
			// Si no esta, lo agrega
			Cellphone* X = system->findCellphone(numberX);

			if (!X) {
				X = new Cellphone(numberX);
				system->addCellphone(X);
			}
			std::cout << "Celular X: " << numberX << " Antena: "
					<< id << " Minuto: " << min << std::endl;

			// Desonecta el celular X de la antena
			system->disconnectCellphone(X);

		}
	}
}


