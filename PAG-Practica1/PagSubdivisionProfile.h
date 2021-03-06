#include <iostream>

#include "Structs.h"

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>

using namespace Structs;

class PagSubdivisionProfile{
private:
	PuntosPerfil* perfilOriginal;
	PuntosPerfil* perfilSubdividido;
	int numDivisiones;
	int numPuntosPerfilOriginal;
	int numPuntosPerfilSubdividido;
	void subdivisionPolilineas();
public:
	PagSubdivisionProfile();
	PagSubdivisionProfile(int _numPuntosPerfilOriginal, int _numDivisiones, PuntosPerfil& _perfilOriginal);
	PuntosPerfil& getPerfil() { return *perfilSubdividido; }
	int getNumPuntosPerfil() { return numPuntosPerfilSubdividido; }
	~PagSubdivisionProfile();
};

