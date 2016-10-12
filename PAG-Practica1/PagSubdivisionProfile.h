#include <iostream>

#include "Structs.h"

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>

class PagSubdivisionProfile{
private:
	puntosPerfil* perfilOriginal;
	puntosPerfil* perfilSubdividido;
	int numDivisiones;
	int numPuntosPerfilOriginal;
	void subdivisionPolilineas();
public:
	PagSubdivisionProfile();
	~PagSubdivisionProfile();
};

