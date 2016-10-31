#include "LoadFile.h"
#include <sstream>

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


void LoadFile(std::string fileName, int maxLogical, System* system) {
	std::string line, command, values, antennaId, antennaCapacity;
	std::string strNumberX, rest;
	int i = 0, posSeparator = 0;
	std::ifstream file(fileName.c_str());
	std::string keyword;
	if (!file) {
		std::cout << "no se abrio";
	}
 	while (getline(file, line)) {
		posSeparator = getKeyValue(line, command, values);
		if (posSeparator != -1) {

			if (strEqual(command, "Antena")) {
				posSeparator = getKeyValue(values, antennaId, antennaCapacity);
				std::cout << "AntennaId: " << antennaId << " antennaCapacity: "
						<< antennaCapacity << std::endl;

				unsigned int id = strtoi(antennaId);
				unsigned int capacity = strtoi(antennaCapacity);

				// Agrega una nueva antena al sistema
				Antenna* antenna = new Antenna(id, capacity);
				system->addAntenna(antenna);

			} else if (strEqual(command, "Inicio")) {
				std::string startMin;
				posSeparator = getKeyValue(values, strNumberX, rest);
				std::string strNumberY = rest.substr(0,posSeparator+1);
				startMin = rest.substr(posSeparator+1);
				unsigned int numberX = strtoi(strNumberX);
				unsigned int numberY = strtoi(strNumberY);
				unsigned int minute = strtoi(startMin);
				// Busca los celulares en el sistema.
				// Si no estan, los agrega
				Cellphone* X = system->findCellphone(numberX);
				Cellphone* Y = system->findCellphone(numberY);
				if (!X) {
					X = new Cellphone(numberX);
					system->addCellphone(X);
				}
				if (!Y) {
					Y = new Cellphone(numberY);
					system->addCellphone(Y);
				}
				std::cout << "Celular X: " << strNumberX << " Celular Y: "
						<< strNumberY << " Minuto: " << minute << std::endl;
				// Inicia una llamada entre los celulares encontrados
				if (X->getStatus() == CONNECTED && Y->getStatus() == CONNECTED) {
					system->initiateCall(X, Y);
				}

			} else if (strEqual(command, "Fin")) {
				std::string endMin;
				posSeparator = getKeyValue(values, strNumberX, rest);
				std::string strNumberY = rest.substr(0,posSeparator+1);
				endMin = strNumberY.substr(posSeparator+1);
				unsigned int numberX = strtoi(strNumberX);
				unsigned int numberY = strtoi(strNumberY);
				unsigned int minute = strtoi(endMin);
				// Busca los celulares en el sistema.
				// Si no estan, los agrega
				Cellphone* X = system->findCellphone(numberX);
				Cellphone* Y = system->findCellphone(numberY);
				if (!X) {
					X = new Cellphone(numberX);
					system->addCellphone(X);
				}
				if (!Y) {
					Y = new Cellphone(numberY);
					system->addCellphone(Y);
				}

				// Excepciones
				if (X == NULL || Y == NULL ||
					X->getStatus() != CURRENTLY_SPEAKING ||
					Y->getStatus() != CURRENTLY_SPEAKING) {
					throw std::string("Estos celulares no se encuentran hablando");
				}
				// Termina la llamada
				system->terminateCall(X, Y);
				std::cout << "Celular X: " << strNumberX << " Celular Y: "
						<< strNumberY << " Minuto: " << minute << std::endl;

			} else if (strEqual(command, "Msg")) {

				// Enviar mensaje

			} else if (strEqual(command, "Conectar")) {

				std::string minute;
				posSeparator = getKeyValue(values, strNumberX, rest);
				std::string antennaId = rest.substr(0,posSeparator+1);
				minute = rest.substr(posSeparator+1);
				unsigned int numberX = strtoi(strNumberX);
				unsigned int id = strtoi(antennaId);
				unsigned int min = strtoi(minute);
				// Busca el celular en el sistema.
				// Si no esta, lo agrega
				Cellphone* X = system->findCellphone(numberX);

				// Busca la antena en el sistema
				Antenna* antenna = system->findAntenna(id);
				if (!X) {
					X = new Cellphone(numberX);
					system->addCellphone(X);
				}
				std::cout << "Celular X: " << numberX << " Antena: "
						<< id << " Minuto: " << min << std::endl;

				// Conecta el celular X a la antena
				system->connectCellphone(X, antenna);

			} else if (strEqual(command, "Desconectar")) {

				std::string minute;
				posSeparator = getKeyValue(values, strNumberX, rest);
				std::string antennaId = rest.substr(0,posSeparator+1);
				minute = rest.substr(posSeparator+1);
				unsigned int numberX = strtoi(strNumberX);
				unsigned int id = strtoi(antennaId);
				unsigned int min = strtoi(minute);
				// Busca el celular en el sistema.
				// Si no esta, lo agrega
				Cellphone* X = system->findCellphone(numberX);

				// Busca la antena en el sistema
				// Antenna* antenna = system->findAntenna(id);
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
		i++;
	}
	maxLogical = i;
}


