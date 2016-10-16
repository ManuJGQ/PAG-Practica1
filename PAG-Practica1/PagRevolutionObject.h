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
public:
	PagRevolutionObject();
	PagRevolutionObject(int _numPuntosPerfilOriginal, int _numDivisiones, PuntosPerfil& _perfilOriginal,
		bool _flagBottomTape, bool _flagTopTape, int _slices);
	~PagRevolutionObject();
};

