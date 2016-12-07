#ifndef FILEFUNCTIONS_H_
#define FILEFUNCTIONS_H_

#include <fstream>
#include <iostream>

#include <sstream>
#ifdef linux
#include <direct.h>
#elif _WIN32
#include <windows.h>
#endif

/*
 * Crea el directorio especificado.
 * Pre: directoryName debe ser un nombre de directorio valido
 * Post: crea el directorio.
 */
void createDir(std::string directoryName);

/*
 * Convierte un string a int
 * Pre: -
 * Post: -
 */
std::string intToString(int number);

#endif /* FILEFUNCTIONS_H_ */
