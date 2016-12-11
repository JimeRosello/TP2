#include "Console.h"

int RequestNumericInput() {
	unsigned int number = 0;
	if (!(std::cin >> number)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Debe ingresar un numero valido." << std::endl;
	}
	return number;
}

std::string RequestTextLineInput() {
	std::string textLine = "";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, textLine);
	return textLine;
}
