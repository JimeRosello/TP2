#include "FileFunctions.h"

void createDir(std::string directoryName) {
#ifdef linux
	mkdir(directoryName.c_str(), S_IRWXU);
#elif _WIN32
	if (CreateDirectory(directoryName.c_str(), NULL)) {
		//Accion a realizar si el directorio se creo exitosamente.
	} else if (ERROR_ALREADY_EXISTS == GetLastError()) {
		//Accion a realizar si el directorio ya existia.
	} else {
		//Accion a realizar si ocurre un error.
	}
#endif
}

std::string intToString(int number) {
	std::ostringstream convert;
	convert << number;
	return convert.str();
}
