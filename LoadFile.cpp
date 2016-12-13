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
int strtoi(std::string string) {
	int integer;
	std::istringstream buffer(string);
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
	elems.push_back("nullptr");
}

// Devuelve un vector con las subcadenas

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

void LoadFile(std::string fileName, System* system) {
	std::string line, command, values, antennaId, antennaCapacity, startMin,
			strNumberX, strNumberY, endMin, message;
	std::ifstream file(fileName.c_str());

	if (!file.fail()) {
		cout << "Archivo '" << fileName << "' abierto correctamente." << std::endl;

		// Lee una a una las lineas del archivo
		while (getline(file, line)) {

			// Obtiene un vector con una keyword en cada uno de sus campos
			std::vector<std::string> strVector = split(line, ' ');
			// La primera posicion corresponde al comando a ejecutar
			// (Antena, Inicio, Conectar, etc.)
			command = strVector[0];

			if (strEqual(command, "Antena")) {
				commandAntenna(antennaId, antennaCapacity, strVector, system);

			} else if (strEqual(command, "Inicio")) {

				commandInicio(system, strNumberX, strNumberY, startMin,
						strVector);

			} else if (strEqual(command, "Fin")) {

				commandFin(strNumberX, strNumberY, endMin, strVector, system);

			} else if (strEqual(command, "Msg")) {

				commandMsg(strNumberX, strNumberY, startMin, message, strVector,
						system);

			} else if (strEqual(command, "Conectar")) {

				commandConectar(strNumberX, antennaId, startMin, strVector,
						system);

			} else if (strEqual(command, "Desconectar")) {

				commandDesconectar(strNumberX, strVector, antennaId, system);

			}
		}
	} else {
		cout << "Ha ocurrido un error al abrir el archivo " << fileName << endl;
	}
}

void commandAntenna(std::string antennaId, std::string antennaCapacity,
		std::vector<std::string> vec, System* system) {
// Divide el id de la antena separando la "A" del identificador
	antennaId = vec[1];
	std::vector<std::string> antennaIdV = split(antennaId, 'A');
	unsigned int id = strtoi(antennaIdV[1]);
	antennaCapacity = vec[2];
	unsigned int capacity = strtoi(antennaCapacity);

//  agrega una nueva antena al sistema
	Antenna* antenna = new Antenna(id, capacity);
	system->addAntenna(antenna);

}

void commandInicio(System* system, std::string strNumberX,
		std::string strNumberY, std::string startMin,
		std::vector<std::string> vec) {

	strNumberX = vec[1];
	strNumberY = vec[2];
	startMin = vec[3];
	unsigned int numberX = strtoi(strNumberX);
	unsigned int numberY = strtoi(strNumberY);
	unsigned int minute = strtoi(startMin);

// Busca los celulares en el sistema.
	Cellphone* X = system->findCellphone(numberX);
	Cellphone* Y = system->findCellphone(numberY);

	if (!X) {
		X = new Cellphone(numberX);
		system->addCellphone(X);
	}
	if (!Y) {
		X = new Cellphone(numberY);
		system->addCellphone(Y);
	}

// Inicia una llamada entre los celulares encontrados
	system->initiateCall(minute, X, Y);

}

void commandFin(std::string strNumberX, std::string strNumberY,
		std::string endMin, std::vector<std::string> vec, System* system) {
	strNumberX = vec[1];
	strNumberY = vec[2];
	endMin = vec[3];
	unsigned int numberX = strtoi(strNumberX);
	unsigned int numberY = strtoi(strNumberY);
	unsigned int minute = strtoi(endMin);

	Call* call = system->findCallInProgress(numberX, numberY);
// Termina la llamada
	if (call) {
		system->terminateCall(call, minute);
	}

}

void commandMsg(std::string strNumberX, std::string strNumberY,
		std::string startMin, std::string message, std::vector<std::string> vec,
		System* system) {
	strNumberX = vec[1];
	strNumberY = vec[2];
	startMin = vec[3];
	message = vec[4];
	int i = 5;
	while (vec[i] != "nullptr") {
		message = message + " " + vec[i];
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

}

void commandConectar(std::string strNumberX, std::string antennaId,
		std::string startMin, std::vector<std::string> vec, System* system) {
	strNumberX = vec[1];
	antennaId = vec[2];
	startMin = vec[3];
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
}

void commandDesconectar(std::string strNumberX, std::vector<std::string> vec,
		std::string antennaId, System* system) {
	strNumberX = vec[1];
// Divide el id de la antena separando la "A" del identificador
	std::vector<std::string> antennaIdV = split(antennaId, 'A');

	unsigned int numberX = strtoi(strNumberX);
// Busca el celular en el sistema.
// Si no esta, lo agrega
	Cellphone* X = system->findCellphone(numberX);

	if (!X) {
		X = new Cellphone(numberX);
		system->addCellphone(X);
	}
	std::cout << std::endl;

// Desonecta el celular X de la antena
	system->disconnectCellphone(X);

}

