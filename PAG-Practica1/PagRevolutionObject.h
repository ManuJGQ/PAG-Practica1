#include <iostream>
#include "PagSubdivisionProfile.h"

struct Geometria {
	PuntosVertices vertice;
	NormalesTangentes normal;
	NormalesTangentes tangente;
};

class PagRevolutionObject{
	bool flagBottomTape;
	bool flagTopTape;
	PagSubdivisionProfile subdivisionProfiles;
	Geometria *geometria;
	CoordTexturas *coordtext;
	int *indices;
	void revolution();
	int slices;
	int tamaGeometriaCoordText;
	int tamaIndices;
public:
	PagRevolutionObject();
	PagRevolutionObject(int _numPuntosPerfilOriginal, int _numDivisiones, PuntosPerfil& _perfilOriginal,
		bool _flagBottomTape, bool _flagTopTape, int _slices);
	Geometria& getGeometria() { return *geometria; }
	CoordTexturas& getCoordText() { return *coordtext; }
	int& getIndices() { return *indices; }
	int getTamaGeometriaCoordText() { return tamaGeometriaCoordText; }
	int getTamaIndices() { return tamaIndices; }
	~PagRevolutionObject();
};

