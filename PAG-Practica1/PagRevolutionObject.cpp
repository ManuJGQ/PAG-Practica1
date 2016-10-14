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

	// VERTICES

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

	// NORMALES

	for (int j = 0; j < numPuntosPerfil; j++) {
		for (int i = 0; i < 20; i++) {
			PuntosVertices p1 = geometria[(i*numPuntosPerfil - 1) + j - 1].vertice;
			PuntosVertices pi = geometria[(i*numPuntosPerfil - 1) + j].vertice;
			PuntosVertices p2 = geometria[(i*numPuntosPerfil - 1) + j + 1].vertice;

			PuntosVertices v1;
			v1.x = pi.x - p1.x;
			v1.y = pi.y - p1.y;
			v1.z = pi.z - p1.z;

			float modV1 = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
			v1.x = v1.x / modV1;
			v1.y = v1.y / modV1;
			v1.z = v1.z / modV1;

			float xTemp = v1.x;
			v1.x = v1.y;
			v1.y = xTemp * -1;

			PuntosVertices vi;
			vi.x = p2.x - pi.x;
			vi.y = p2.y - pi.y;
			vi.z = p2.z - pi.z;

			float modVi = sqrt((vi.x * vi.x) + (vi.y * vi.y) + (vi.z * vi.z));
			vi.x = vi.x / modVi;
			vi.y = vi.y / modVi;
			vi.z = vi.z / modVi;

			xTemp = vi.x;
			vi.x = vi.y;
			vi.y = xTemp * -1;

			NormalesTangentes normal;

			normal.x = (v1.x + vi.x) / 2;
			normal.y = (v1.y + vi.y) / 2;
			normal.z = (v1.z + vi.z) / 2;

			geometria[(i*numPuntosPerfil - 1) + j].normal = normal;
		}
	}

	// TANGENTES

	for (int j = 0; j < numPuntosPerfil; j++) {
		for (int i = 0; i < 20; i++) {
			NormalesTangentes tangente;

			tangente.x = -1 * sin(i * angleRadIncrement);
			tangente.y = 0;
			tangente.z = -1 * cos(i * angleRadIncrement);

			geometria[(i*numPuntosPerfil - 1) + j].tangente = tangente;
		}
	}

	// COORDENADAS TEXTURAS

	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < numPuntosPerfil; i++) {

		}
	}

	// INDICES

}

PagRevolutionObject::~PagRevolutionObject(){}
