#include <iostream>

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>

struct puntosPerfil {
	float x;
	float y;
};

class PagSubdivisionProfile{
private:
	puntosPerfil* perfilOriginal;
	puntosPerfil* perfilSubdividido;
	int numDivisiones;
	int numPuntosPerfilOriginal;
	void subdivisionPolilineas();
public:
	PagSubdivisionProfile(std::string archivoIN);
	~PagSubdivisionProfile();
};

