#include "PagRevolutionObject.h"

#include <math.h>

#define PI 3.14159265358979323846

PagRevolutionObject::PagRevolutionObject() {};

PagRevolutionObject::PagRevolutionObject(int _numPuntosPerfilOriginal, int _numDivisiones,
	PuntosPerfil& _perfilOriginal, bool _flagBottomTape, bool _flagTopTape, int _slices) {

	flagBottomTape = _flagBottomTape;
	flagTopTape = _flagTopTape;

	subdivisionProfiles = PagSubdivisionProfile(_numPuntosPerfilOriginal, _numDivisiones,
		_perfilOriginal);

	slices = _slices;

	revolution();
}

void PagRevolutionObject::revolution() {
	int numPuntosPerfil = subdivisionProfiles.getNumPuntosPerfil();

	int numTapas = 0;
	int cambioIndice = 0;
	if (flagBottomTape) {
		numTapas++;
		cambioIndice++;
	}
	if (flagTopTape) numTapas++;

	tamaGeometriaCoordText = ((numPuntosPerfil - numTapas) * slices) + numTapas;
	tamaIndices = (((numPuntosPerfil - (numTapas * 2)) * 2) + 1) * slices;
	geometria = new Geometria[tamaGeometriaCoordText];
	coordtext = new CoordTexturas[tamaGeometriaCoordText];
	indices = new int[tamaIndices];

	PuntosPerfil *perfil = &subdivisionProfiles.getPerfil();

	float angleRadIncrement = (2 * PI) / slices;

	// VERTICES

	for (int j = 0; j < numPuntosPerfil; j++) {
		if (j == 0 && flagBottomTape) {
			PuntosVertices vert;
			vert.x = 0;
			vert.y = perfil[j].y;
			vert.z = 0;
			geometria[tamaGeometriaCoordText - numTapas].vertice = vert;
			std::cout << numPuntosPerfil << std::endl;
		}
		else if (j == numPuntosPerfil - 1 && flagTopTape) {
			PuntosVertices vert;
			vert.x = 0;
			vert.y = perfil[j].y;
			vert.z = 0;
			geometria[tamaGeometriaCoordText - 1].vertice = vert;
		}
		else {
			for (int i = 0; i < slices; i++) {
				float x = perfil[j].x * cos(angleRadIncrement * i);
				float z = perfil[j].x * -sin(angleRadIncrement * i);

				PuntosVertices vert;
				vert.x = x;
				vert.y = perfil[j].y;
				vert.z = z;
				geometria[(j - cambioIndice) * slices + i].vertice = vert;
			}
		}

	}


	// NORMALES

	for (int j = 0; j < numPuntosPerfil; j++) {
		if (j == 0 && flagBottomTape) {
			NormalesTangentes normal;

			normal.x = 0;
			normal.y = -1;
			normal.z = 0;

			geometria[tamaGeometriaCoordText - numTapas].normal = normal;
		}
		else if (j == numPuntosPerfil - 1 && flagTopTape) {
			NormalesTangentes normal;

			normal.x = 0;
			normal.y = 1;
			normal.z = 0;

			geometria[tamaGeometriaCoordText - 1].normal = normal;
		}
		else {
			for (int i = 0; i < slices; i++) {
				if (j == 1 && flagBottomTape) {
					NormalesTangentes normal;

					normal.x = 0;
					normal.y = -1;
					normal.z = 0;

					geometria[(j - cambioIndice) * slices + i].normal = normal;
				}
				else if (j == numPuntosPerfil - 2 && flagTopTape) {
					NormalesTangentes normal;

					normal.x = 0;
					normal.y = 1;
					normal.z = 0;

					geometria[(j - cambioIndice) * slices + i].normal = normal;
				}
				else {
					PuntosVertices p1 = geometria[(j - 1) * slices + i - 1].vertice;
					PuntosVertices pi = geometria[(j - 1) * slices + i].vertice;
					PuntosVertices p2 = geometria[(j - 1) * slices + i + 1].vertice;

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

					geometria[(j - cambioIndice) * slices + i].normal = normal;
				}
			}
		}

	}

	// TANGENTES

	for (int j = 0; j < numPuntosPerfil; j++) {
		if (j == 0 && flagBottomTape) {
			NormalesTangentes tangente;

			tangente.x = 1;
			tangente.y = 0;
			tangente.z = 0;

			geometria[tamaGeometriaCoordText - numTapas].tangente = tangente;
		}
		else if (j == numPuntosPerfil - 1 && flagTopTape) {
			NormalesTangentes tangente;

			tangente.x = 1;
			tangente.y = 0;
			tangente.z = 0;

			geometria[tamaGeometriaCoordText - 1].tangente = tangente;
		}
		else {
			for (int i = 0; i < slices; i++) {
				NormalesTangentes tangente;

				tangente.x = -1 * sin(angleRadIncrement * i);
				tangente.y = 0;
				tangente.z = -1 * cos(angleRadIncrement * i);

				geometria[(j - cambioIndice) * slices + i].tangente = tangente;
			}
		}
	}

	// COORDENADAS TEXTURAS

	if (flagBottomTape || flagTopTape) {
		for (int i = 0; i < slices; i++) {
			float s = (cos(angleRadIncrement * float(i)) / 2.0) + 0.5;
			float t = (sin(angleRadIncrement * float(i)) / 2.0) + 0.5;
			if (flagBottomTape) {
				coordtext[i].s = s;
				coordtext[i].t = t;
			}
			if (flagTopTape){
				coordtext[(numPuntosPerfil - numTapas - 1) * slices + i].s = s;
				coordtext[(numPuntosPerfil - numTapas - 1) * slices + i].t = t;
			}
		}
		if (flagBottomTape) {
			coordtext[tamaGeometriaCoordText - numTapas].s = 0.5;
			coordtext[tamaGeometriaCoordText - numTapas].t = 0.5;
		}
		if (flagTopTape) {
			coordtext[tamaGeometriaCoordText - 1].s = 0.5;
			coordtext[tamaGeometriaCoordText - 1].t = 0.5;
		}
	}

	float *modulo = new float[numPuntosPerfil - (numTapas * 2)];

	for (int j = 0; j < slices; j++) {

		float s = j * float(float(1) / float(slices - 1));

		float sumatorio = 0;

		modulo[0] = sumatorio;

		for (int i = numTapas + 1; i < numPuntosPerfil - numTapas; i++) {

			PuntosVertices p1 = geometria[(i - cambioIndice) * slices + j].vertice;
			PuntosVertices p2 = geometria[(i - cambioIndice - 1) * slices + j].vertice;

			PuntosVertices v1;
			v1.x = p1.x - p2.x;
			v1.y = p1.y - p2.y;
			v1.z = p1.z - p2.z;

			float modV1 = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));

			sumatorio += modV1;

			modulo[i - 2] = sumatorio;
		}

		for (int i = 2; i < numPuntosPerfil - 2; i++) {

			float t = (modulo[i - 2]) / (sumatorio);

			coordtext[(i - cambioIndice) * slices + j].s = s;
			coordtext[(i - cambioIndice) * slices + j].t = t;
		}
	}

	// INDICES

	if (flagBottomTape && flagTopTape) {
		int k = 1;
		indices[0] = tamaGeometriaCoordText - 2;
		for (int i = 0; i < slices; i++) {
			indices[k] = i;
			k++;
		}
		for (int i = 0; i < slices; i++) {
			for (int j = 2; j < numPuntosPerfil - 3; j++) {
				indices[k] = i + (j * (slices + 1));
				indices[k + 1] = (i + 1) + (j * (slices + 1));
				k += 2;
			}
			indices[k] = 0xFFFF;
			k++;
		}
		for (int i = 0; i < slices; i++) {
			indices[k] = (numPuntosPerfil - 3) * slices + i;
			k++;
		}
		indices[k] = tamaGeometriaCoordText - 1;

	}
	else if (flagBottomTape || flagTopTape) {
		if (flagBottomTape) {
			int k = 1;
			indices[0] = slices;
			for (int i = 0; i < slices; i++) {
				indices[k] = i;
				k++;
			}
			for (int j = 2; j < numPuntosPerfil; j++) {
				for (int i = 0; i < slices; i++) {
					indices[k] = i + (j * (slices + 1));
					indices[k + 1] = (i + 1) + (j * (slices + 1));
					k += 2;
				}
				indices[k] = 0xFFFF;
				k++;
			}
		}
		else {
			int k = 0;
			for (int i = 0; i < slices; i++) {
				for (int j = 0; j < numPuntosPerfil - 2; j++) {
					indices[k] = i + (j * (slices + 1));
					indices[k + 1] = (i + 1) + (j * (slices + 1));
					k += 2;
				}
				indices[k] = 0xFFFF;
				k++;
			}
			for (int i = 0; i < slices; i++) {
				indices[k] = i;
				k++;
			}
			indices[k] = slices;
		}
	}
	else {
		int k = 0;
		for (int i = 0; i < slices; i++) {
			for (int j = 0; j < numPuntosPerfil; j++) {
				indices[k] = i + (j * (slices + 1));
				indices[k + 1] = (i + 1) + (j * (slices + 1));
				k += 2;
			}
			indices[k] = 0xFFFF;
			k++;
		}
	}
}

PagRevolutionObject::~PagRevolutionObject() {}
