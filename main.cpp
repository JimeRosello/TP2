#include "Index.h"

int main() {


	System* system = new System();
	//LoadFile(FILENAME, system);
	Index index(system);
	do {
		index.printMenu();
		int option = index.chooseOption();
		index.executeAction(option);
	} while (index.isInCourse());

	return 0;
}

