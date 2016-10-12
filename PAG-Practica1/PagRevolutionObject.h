#include <iostream>
#include "PagSubdivisionProfile.h"

class PagRevolutionObject{
	bool flagBottomTape;
	bool flagTopTape;
	PagSubdivisionProfile subdivisionProfiles;
public:
	PagRevolutionObject();
	PagRevolutionObject(int _numPuntosPerfilOriginal, int _numDivisiones, PuntosPerfil* _perfilOriginal,
		bool _flagBottomTape, bool _flagTopTape);
	~PagRevolutionObject();
};

