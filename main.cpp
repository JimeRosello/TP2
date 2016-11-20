#include "Index.h"

int main() {


	System* system = new System();
	std::string filename = "/home/jime/Desktop/Algoritmos/TP2/src/hola.txt";
	int maxLogical = 0;
//	LoadFile(filename, maxLogical, system);
	Index index(system);
	do {
		index.printMenu();
		int option = index.chooseOption();
		index.executeAction(option);
	} while (index.isInCourse());

	return 0;
}

