#include <iostream>
#include "PagSubdivisionProfile.h"

class PagRevolutionObject{
	bool flagBottomTape;
	bool flagTopTape;
	PagSubdivisionProfile subdivisionProfiles;
	Geometria *geometria;
	CoordTexturas *coordtext;
	int *indices;
	int *indicesBottomTape;
	int *indicesTopTape;
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
	int& getIndicesBottomTape() { return *indicesBottomTape; }
	int& getIndicesTopTape() { return *indicesTopTape; }
	int getTamaGeometriaCoordText() { return tamaGeometriaCoordText; }
	int getTamaIndices() { return tamaIndices; }
	int getTamaIndicesTapes() { return slices + 1; }
	~PagRevolutionObject();
};

