#include <iostream>

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>

#include "PagAssistantClass.h"

int main(int argc, char** argv) {
	char* docdir = getenv("userprofile");
	std::string path = docdir;
	path += "/Desktop/prueba.txt";
	PagAssistantClass(std::string(path));
	system("pause");
	return 0;
}