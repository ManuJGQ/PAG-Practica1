#include "PagRevolutionObject.h"

PagRevolutionObject::PagRevolutionObject() {};

PagRevolutionObject::PagRevolutionObject(int _numPuntosPerfilOriginal, int _numDivisiones,
	PuntosPerfil* _perfilOriginal, bool _flagBottomTape, bool _flagTopTape){

	flagBottomTape = _flagBottomTape;
	flagTopTape = _flagTopTape;

	subdivisionProfiles = PagSubdivisionProfile(_numPuntosPerfilOriginal, _numDivisiones,
		_perfilOriginal);
}

PagRevolutionObject::~PagRevolutionObject(){}
