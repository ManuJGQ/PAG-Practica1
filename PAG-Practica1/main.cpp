#include <iostream>

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>

#include "PagAssistantClass.h"

int main(int argc, char** argv) {
	PagAssistantClass("Prueba.txt");
	std::cout << "UE" << std::endl;
	return 0;
}