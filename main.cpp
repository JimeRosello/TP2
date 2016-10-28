#include "Index.h"

int main() {

	Index index;
	do {
		index.printMenu();
		int option = index.chooseOption();
		index.executeAction(option);
	} while (index.isInCourse());
	return 0;
}
