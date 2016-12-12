#ifndef LOADFILE_H_
#define LOADFILE_H_

#include <iostream>
#include <fstream>
#include <string>
#include "System.h"
#include <vector>

//Carga el contenido del archivo de texto.
void LoadFile(std::string fileName, System* system);

// Divide el id de la antena separando la "A" del identificador y agrega una nueva antena al sistema
void commandAntenna(std::string antennaId, std::string antennaCapacity, std::vector<std::string> vec,System* system);

// Busca los celulares en el sistema e inicia una llamada entre los celulares encontrados
void commandInicio(System* system, std::string strNumberX, std::string strNumberY,std::string startMin, std::vector<std::string> vec);

// Termina la llamada
void commandFin(std::string strNumberX, std::string strNumberY, std::string endMin, std::vector<std::string> vec, System* system);

//Busca los celulares en el sistema y manda los mensajes no enviados de un celular a otro
void commandMsg(std::string strNumberX, std::string strNumberY, std::string startMin,
                std::string message, std::vector<std::string> vec, System* system);

// Divide el id de la antena separando la "A" del identificador
// Busca el celular en el sistema (si no esta, lo agrega)
// Busca la antena en el sistema (si no esta, la crea y la agrega)
// Conecta el celular X a la antena
void commandConectar(std::string strNumberX, std::string antennaId, std::string startMin,
                     std::vector<std::string> vec, System* system);

// Divide el id de la antena separando la "A" del identificador
// Busca el celular en el sistema (si no esta, lo agrega)
// Desonecta el celular X de la antena
void commandDesconectar(std::string strNumberX, std::vector<std::string> vec,
                        std::string antennaId, System* system);

#endif /* LOADFILE_H_ */
