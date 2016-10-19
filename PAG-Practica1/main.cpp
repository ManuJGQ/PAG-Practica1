#include <iostream>
#include <string>

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>

#include "PagAssistantClass.h"

int main(int argc, char** argv) {
	char* docdir = getenv("userprofile");
	std::string path = docdir;
	std::string archivo;
	path += "/Desktop/";
	std::cout << "Escriba el nombre del fichero (con .txt)" << std::endl;
	std::getline(std::cin, archivo);
	path += archivo;

	int slices;
	std::cout << "Escriba el numero de slices" << std::endl;
	std::cin >> slices;
	PagAssistantClass(path, slices, archivo);
	system("pause");
	return 0;
}