#include "PagRevolutionObject.h"

#include <math.h>

#define PI 3.14159265358979323846

PagRevolutionObject::PagRevolutionObject() {};

PagRevolutionObject::PagRevolutionObject(int _numPuntosPerfilOriginal, int _numDivisiones,
	PuntosPerfil& _perfilOriginal, bool _flagBottomTape, bool _flagTopTape){

	flagBottomTape = _flagBottomTape;
	flagTopTape = _flagTopTape;

	subdivisionProfiles = PagSubdivisionProfile(_numPuntosPerfilOriginal, _numDivisiones,
		_perfilOriginal);

	revolution();
}

void PagRevolutionObject::revolution() {
	int numPuntosPerfil = subdivisionProfiles.getNumPuntosPerfil();
	geometria = new Geometria[numPuntosPerfil * 20];

	PuntosPerfil *perfil = &subdivisionProfiles.getPerfil();

	float angleRadIncrement = (2 * PI) / 20;

	for (int j = 0; j < numPuntosPerfil; j++) {
		for (int i = 0; i < 20; i++) {
			float x = perfil[j].x * cos(angleRadIncrement * i);
			float z = perfil[j].x * -sin(angleRadIncrement * i);
			PuntosVertices vert;
			vert.x = x;
			vert.y = perfil[j].y;
			vert.z = z;
			geometria[(i*numPuntosPerfil - 1) + j].vertice = vert;
		}
	}

	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < numPuntosPerfil; i++) {

		}
	}
}

PagRevolutionObject::~PagRevolutionObject(){}
