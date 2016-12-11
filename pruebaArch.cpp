/*void LoadFile(std::string fileName, System* system) {
	std::string line, keyWord;
	std::string strNumberX, strNumberY;
	int i = 0, posSeparator = 0;
	std::ifstream file(fileName.c_str());
	if (!file) {
		throw std::string("No se pudo abrir el archivo");
	}





	while (getline(file, line)) {
		std::cout << line;
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
				posSeparator = getKeyValue(values, strNumberX, strNumberY);
				unsigned int numberX = strtoi(strNumberX);
				unsigned int numberY = strtoi(strNumberY);
				// Busca los celulares en el sistema.
				// Si no estan, los agrega
				Cellphone* X = system->findCellphone(numberX);
				if (X == NULL) {
					X = new Cellphone(numberX);
					system->addCellphone(X);
				}
				Cellphone* Y = system->findCellphone(numberY);
				if (Y == NULL) {
					Y = new Cellphone(numberY);
					system->addCellphone(Y);
				}
				// Inicia una llamada entre los celulares encontrados
				if (X->getStatus() == CONNECTED && Y->getStatus() == CONNECTED) {
					system->initiateCall(X, Y);
				}

			} else if (strEqual(command, "Fin")) {

				posSeparator = getKeyValue(values, strNumberX, strNumberY);
				unsigned int numberX = strtoi(strNumberX);
				unsigned int numberY = strtoi(strNumberY);
				Cellphone* X = system->findCellphone(numberX);
				Cellphone* Y = system->findCellphone(numberY);
				// Excepciones
				if (X == NULL || Y == NULL ||
					X->getStatus() != CURRENTLY_SPEAKING ||
					Y->getStatus() != CURRENTLY_SPEAKING) {
					throw std::string("Estos celulares no se encuentran hablando");
				}
				// Termina la llamada
				system->terminateCall(X, Y);

			} else if (strEqual(command, "Msg")) {


			} else if (strEqual(command, "Conectar")) {
				//TODO: Implementar...
			} else if (strEqual(command, "Desconectar")) {
				//TODO: Implementar...
			}
		}
		i++;
	}
	maxLogical = i;
}


*/
