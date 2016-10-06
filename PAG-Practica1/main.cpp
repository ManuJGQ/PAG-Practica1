#include <iostream>

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>

#include "PagSubdivisionProfile.h"

int main(int argc, char** argv) {
	PagSubdivisionProfile perfilPrueba("prueba.txt");
	system("Pause");
	return 0;
}