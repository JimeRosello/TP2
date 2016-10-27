#include "Index.h"

int main() {

	Index index;
	index.printMenu();
	int option = index.chooseOption();
	index.executeAction(option);

	return 0;
}
