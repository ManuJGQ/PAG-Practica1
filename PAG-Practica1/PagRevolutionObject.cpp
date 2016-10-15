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
	if (flagBottomTape && flagTopTape) {
		geometria = new Geometria[((numPuntosPerfil - 2) * 20) + 2];
		coordtext = new CoordTexturas[((numPuntosPerfil - 2) * 20) + 2];		//CASO 1: DOS TAPAS
		indices = new int[(((numPuntosPerfil - 2) * 20) * 2) + 2];
	}
	else if (flagBottomTape || flagTopTape) {
		geometria = new Geometria[((numPuntosPerfil - 1) * 20) + 1];
		coordtext = new CoordTexturas[((numPuntosPerfil - 1) * 20) + 1];		//CASO 2: UNA TAPA
		indices = new int[(((numPuntosPerfil - 1) * 20) * 2) + 1];
	}
	else {
		geometria = new Geometria[numPuntosPerfil * 20];
		coordtext = new CoordTexturas[numPuntosPerfil * 20];			//CASO 3: SIN TAPAS
		indices = new int[numPuntosPerfil * 20 * 2];
	}

	PuntosPerfil *perfil = &subdivisionProfiles.getPerfil();

	// VERTICES

	float angleRadIncrement = (2 * PI) / 20;

	for (int j = 0; j < numPuntosPerfil; j++) {
		if (flagTopTape && flagBottomTape) {
			if (j == 0) {
				PuntosVertices vert;
				vert.x = 0;
				vert.y = perfil[j].y;
				vert.z = 0;
				geometria[(20 * numPuntosPerfil) - 2].vertice = vert;
			}
			else if (j == numPuntosPerfil - 1) {
				PuntosVertices vert;
				vert.x = 0;
				vert.y = perfil[j].y;
				vert.z = 0;
				geometria[(20 * numPuntosPerfil) - 1].vertice = vert;
			}
			else {
				for (int i = 0; i < 20; i++) {
					float x = perfil[j].x * cos(angleRadIncrement * i);
					float z = perfil[j].x * -sin(angleRadIncrement * i);
					PuntosVertices vert;
					vert.x = x;
					vert.y = perfil[j].y;
					vert.z = z;
					geometria[((i*numPuntosPerfil - 1) + j) - 1].vertice = vert;
				}
			}

		}
		else if(flagTopTape || flagBottomTape) {
			if (j == 0 && flagBottomTape) {
				PuntosVertices vert;
				vert.x = 0;
				vert.y = perfil[j].y;
				vert.z = 0;
				geometria[(20 * numPuntosPerfil) - 1].vertice = vert;
			}
			else if (j == numPuntosPerfil - 1 && flagTopTape) {
				PuntosVertices vert;
				vert.x = 0;
				vert.y = perfil[j].y;
				vert.z = 0;
				geometria[(20 * numPuntosPerfil) - 1].vertice = vert;
			}
			else {
				for (int i = 0; i < 20; i++) {
					float x = perfil[j].x * cos(angleRadIncrement * i);
					float z = perfil[j].x * -sin(angleRadIncrement * i);
					PuntosVertices vert;
					vert.x = x;
					vert.y = perfil[j].y;
					vert.z = z;
					if(flagBottomTape) geometria[((i*numPuntosPerfil - 1) + j) - 1].vertice = vert;
					else geometria[((i*numPuntosPerfil - 1) + j)].vertice = vert;
				}
			}
		}
		else {
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
	}

	// NORMALES

	for (int j = 0; j < numPuntosPerfil; j++) {
		if (flagTopTape && flagBottomTape) {
			if (j == 0) {
				NormalesTangentes normal;

				normal.x = 0;
				normal.y = -1;
				normal.z = 0;

				geometria[(20 * numPuntosPerfil) - 2].normal = normal;
			}
			else if (j == numPuntosPerfil - 1) {
				NormalesTangentes normal;

				normal.x = 0;
				normal.y = 1;
				normal.z = 0;

				geometria[(20 * numPuntosPerfil) - 1].normal = normal;
			}
			else {
				for (int i = 0; i < 20; i++) {
					if (j == 1) {
						NormalesTangentes normal;

						normal.x = 0;
						normal.y = -1;
						normal.z = 0;

						geometria[((i*numPuntosPerfil - 1) + j) - 1].normal = normal;
					}
					else if (j == numPuntosPerfil - 2) {
						NormalesTangentes normal;

						normal.x = 0;
						normal.y = 1;
						normal.z = 0;

						geometria[((i*numPuntosPerfil - 1) + j) - 1].normal = normal;
					}
					else {
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

						geometria[((i*numPuntosPerfil - 1) + j) - 1].normal = normal;
					}
				}
			}

		}
		else if (flagTopTape || flagBottomTape) {
			if (j == 0 && flagBottomTape) {
				NormalesTangentes normal;

				normal.x = 0;
				normal.y = -1;
				normal.z = 0;

				geometria[(20 * numPuntosPerfil) - 1].normal = normal;
			}
			else if (j == numPuntosPerfil - 1 && flagTopTape) {
				NormalesTangentes normal;

				normal.x = 0;
				normal.y = 1;
				normal.z = 0;

				geometria[(20 * numPuntosPerfil) - 1].normal = normal;
			}
			else {
				for (int i = 0; i < 20; i++) {
					if (j == 1 && flagBottomTape) {
						NormalesTangentes normal;

						normal.x = 0;
						normal.y = -1;
						normal.z = 0;

						geometria[((i*numPuntosPerfil - 1) + j) - 1].normal = normal;
					}
					else if (j == numPuntosPerfil - 2 && flagTopTape) {
						NormalesTangentes normal;

						normal.x = 0;
						normal.y = 1;
						normal.z = 0;

						geometria[((i*numPuntosPerfil - 1) + j)].normal = normal;
					}
					else {
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

						if(flagBottomTape) geometria[((i*numPuntosPerfil - 1) + j) - 1].normal = normal;
						else geometria[((i*numPuntosPerfil - 1) + j)].normal = normal;
					}
				}
			}
		}
		else {
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
	}

	// TANGENTES

	for (int j = 0; j < numPuntosPerfil; j++) {
		if (flagTopTape && flagBottomTape) {
			if (j == 0) {
				NormalesTangentes tangente;

				tangente.x = 1;
				tangente.y = 0;
				tangente.z = 0;

				geometria[(20 * numPuntosPerfil) - 2].tangente = tangente;
			}
			else if (j == numPuntosPerfil - 1) {
				NormalesTangentes tangente;

				tangente.x = 1;
				tangente.y = 0;
				tangente.z = 0;

				geometria[(20 * numPuntosPerfil) - 1].tangente = tangente;
			}
			else {
				for (int i = 0; i < 20; i++) {
					NormalesTangentes tangente;

					tangente.x = -1 * sin(i * angleRadIncrement);
					tangente.y = 0;
					tangente.z = -1 * cos(i * angleRadIncrement);

					geometria[((i*numPuntosPerfil - 1) + j) - 1].tangente = tangente;
				}
			}
		}
		else if (flagTopTape || flagBottomTape) {
			if (j == 0 && flagBottomTape) {
				NormalesTangentes tangente;

				tangente.x = 1;
				tangente.y = 0;
				tangente.z = 0;

				geometria[(20 * numPuntosPerfil) - 1].tangente = tangente;
			}
			else if (j == numPuntosPerfil - 1 && flagTopTape) {
				NormalesTangentes tangente;

				tangente.x = 1;
				tangente.y = 0;
				tangente.z = 0;

				geometria[(20 * numPuntosPerfil) - 1].tangente = tangente;
			}else{
				for (int i = 0; i < 20; i++) {
					NormalesTangentes tangente;

					tangente.x = -1 * sin(i * angleRadIncrement);
					tangente.y = 0;
					tangente.z = -1 * cos(i * angleRadIncrement);

					if(flagBottomTape) geometria[((i*numPuntosPerfil - 1) + j) - 1].tangente = tangente;
					else geometria[((i*numPuntosPerfil - 1) + j)].tangente = tangente;
				}
			}
		}
		else {
			for (int i = 0; i < 20; i++) {
				NormalesTangentes tangente;

				tangente.x = -1 * sin(i * angleRadIncrement);
				tangente.y = 0;
				tangente.z = -1 * cos(i * angleRadIncrement);

				geometria[(i*numPuntosPerfil - 1) + j].tangente = tangente;
			}
		}
	}

	// COORDENADAS TEXTURAS

	if (flagTopTape && flagBottomTape) {
		for (int i = 0; i < 20; i++) {
			float s = (cos(angleRadIncrement * float(i)) / 2.0) + 0.5;
			float t = (sin(angleRadIncrement * float(i)) / 2.0) + 0.5;
			coordtext[(i * numPuntosPerfil - 1)].s = s;
			coordtext[(i * numPuntosPerfil - 1)].t = t;
			coordtext[(i * numPuntosPerfil - 1) + numPuntosPerfil - 2].s = s;
			coordtext[(i * numPuntosPerfil - 1) + numPuntosPerfil - 2].t = t;
		}
		coordtext[(numPuntosPerfil * 18) + 1].s = 0.5;
		coordtext[(numPuntosPerfil * 18) + 1].t = 0.5;
		coordtext[(numPuntosPerfil * 18)].s = 0.5;
		coordtext[(numPuntosPerfil * 18)].t = 0.5;

		float *modulo = new float[numPuntosPerfil - 4];

		for (int j = 0; j < 20; j++) {

			float s = j * (1 / 20);

			float sumatorio = 0;

			modulo[0] = sumatorio;

			for (int i = 3; i < numPuntosPerfil - 2; i++) {

				PuntosVertices p1 = geometria[(j*numPuntosPerfil - 1) + i].vertice;
				PuntosVertices p2 = geometria[(j*numPuntosPerfil - 1) + i - 1].vertice;

				PuntosVertices v1;
				v1.x = p1.x - p2.x;
				v1.y = p1.y - p2.y;
				v1.z = p1.z - p2.z;

				float modV1 = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));

				sumatorio += modV1;

				//std::cout << numPuntosPerfil - 4 << " - " << i - 2 << " - " << modulo[i - 2] << std::endl;

				modulo[i - 2] = sumatorio;
			}

			for (int i = 2; i < numPuntosPerfil - 2; i++) {

				std::cout << numPuntosPerfil - 4 << " - " << i - 2 << " - " << modulo[i - 2] << std::endl;

				float t = (modulo[i - 2]) / (sumatorio);

				coordtext[(j*numPuntosPerfil - 1) + i -1].s = s;
				coordtext[(j*numPuntosPerfil - 1) + i -1].t = t;
			}
		}

		/*std::cout << "BORRO" << std::endl;

		delete[] modulo;*/
	}
	else if (flagTopTape || flagBottomTape) {
		if (flagTopTape) {
			for (int i = 0; i < 20; i++) {
				float s = (cos(angleRadIncrement * float(i)) / 2.0) + 0.5;
				float t = (sin(angleRadIncrement * float(i)) / 2.0) + 0.5;
				coordtext[(i * numPuntosPerfil - 1) + numPuntosPerfil - 2].s = s;
				coordtext[(i * numPuntosPerfil - 1) + numPuntosPerfil - 2].t = t;
			}
			coordtext[(numPuntosPerfil * 18) + 1].s = 0.5;
			coordtext[(numPuntosPerfil * 18) + 1].t = 0.5;

			float *modulo = new float[numPuntosPerfil - 2];
			
			for (int j = 0; j < 20; j++) {

				float s = j * (1 / 20);

				float sumatorio = 0;

				modulo[0] = sumatorio;

				for (int i = 1; i < numPuntosPerfil - 2; i++) {

					PuntosVertices p1 = geometria[(j*numPuntosPerfil - 1) + i].vertice;
					PuntosVertices p2 = geometria[(j*numPuntosPerfil - 1) + i - 1].vertice;

					PuntosVertices v1;
					v1.x = p1.x - p2.x;
					v1.y = p1.y - p2.y;
					v1.z = p1.z - p2.z;

					float modV1 = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));

					sumatorio += modV1;

					modulo[i] = sumatorio;
				}

				for (int i = 0; i < numPuntosPerfil - 2; i++) {

					float t = (modulo[i]) / (sumatorio);

					coordtext[(j*numPuntosPerfil - 1) + i - 1].s = s;
					coordtext[(j*numPuntosPerfil - 1) + i - 1].t = t;
				}

				//delete[] modulo;
			}
		}
		else {
			for (int i = 0; i < 20; i++) {
				float s = (cos(angleRadIncrement * float(i)) / 2.0) + 0.5;
				float t = (sin(angleRadIncrement * float(i)) / 2.0) + 0.5;
				coordtext[(i * numPuntosPerfil - 1)].s = s;
				coordtext[(i * numPuntosPerfil - 1)].t = t;
			}
			coordtext[(numPuntosPerfil * 18) + 1].s = 0.5;
			coordtext[(numPuntosPerfil * 18) + 1].t = 0.5;

			float *modulo = new float[numPuntosPerfil - 2];

			for (int j = 0; j < 20; j++) {

				float s = j * (1 / 20);

				float sumatorio = 0;

				modulo[0] = sumatorio;

				for (int i = 3; i < numPuntosPerfil; i++) {

					PuntosVertices p1 = geometria[(j*numPuntosPerfil - 1) + i].vertice;
					PuntosVertices p2 = geometria[(j*numPuntosPerfil - 1) + i - 1].vertice;

					PuntosVertices v1;
					v1.x = p1.x - p2.x;
					v1.y = p1.y - p2.y;
					v1.z = p1.z - p2.z;

					float modV1 = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));

					sumatorio += modV1;

					modulo[i - 2] = sumatorio;
				}

				for (int i = 2; i < numPuntosPerfil; i++) {

					float t = (modulo[i - 2]) / (sumatorio);

					coordtext[(j*numPuntosPerfil - 1) + i].s = s;
					coordtext[(j*numPuntosPerfil - 1) + i].t = t;
				}

				//delete[] modulo;
			}
		}
	}
	else {
		float *modulo = new float[numPuntosPerfil];

		for (int j = 0; j < 20; j++) {

			float s = j * (1 / 20);

			float sumatorio = 0;

			modulo[0] = sumatorio;

			for (int i = 1; i < numPuntosPerfil; i++) {

				PuntosVertices p1 = geometria[(j*numPuntosPerfil - 1) + i].vertice;
				PuntosVertices p2 = geometria[(j*numPuntosPerfil - 1) + i - 1].vertice;

				PuntosVertices v1;
				v1.x = p1.x - p2.x;
				v1.y = p1.y - p2.y;
				v1.z = p1.z - p2.z;

				float modV1 = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));

				sumatorio += modV1;

				modulo[i] = sumatorio;
			}

			for (int i = 0; i < numPuntosPerfil; i++) {

				float t = (modulo[i]) / (sumatorio);

				coordtext[(j*numPuntosPerfil - 1) + i].s = s;
				coordtext[(j*numPuntosPerfil - 1) + i].t = t;
			}

			//delete[] modulo;
		}
	}

	// INDICES

	if (flagBottomTape && flagTopTape) {
		int k = 1;
		indices[0] = 20;
		for (int i = 0; i < 20; i++) {
			indices[k] = i;
			k ++;
		}
		for (int i = 0; i < 20; i++) {
			for (int j = 2; j < numPuntosPerfil - 2; j++) {
				indices[k] = i + (j * 21);
				indices[k + 1] = (i + 1) + (j * 21);
				k += 2;
			}
		}
		for (int i = 0; i < 20; i++) {
			indices[k] = i;
			k++;
		}
		indices[k] = 20;

	}
	else if (flagBottomTape || flagTopTape) {
		if (flagBottomTape) {
			int k = 1;
			indices[0] = 20;
			for (int i = 0; i < 20; i++) {
				indices[k] = i;
				k++;
			}
			for (int i = 0; i < 20; i++) {
				for (int j = 2; j < numPuntosPerfil; j++) {
					indices[k] = i + (j * 21);
					indices[k + 1] = (i + 1) + (j * 21);
					k += 2;
				}
			}
		}
		else {
			int k = 0;
			for (int i = 0; i < 20; i++) {
				for (int j = 0; j < numPuntosPerfil - 2; j++) {
					indices[k] = i + (j * 21);
					indices[k + 1] = (i + 1) + (j * 21);
					k += 2;
				}
			}
			for (int i = 0; i < 20; i++) {
				indices[k] = i;
				k++;
			}
			indices[k] = 20;
		}
	}
	else {
		int k = 0;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < numPuntosPerfil; j++) {
				indices[k] = i + (j * 21);
				indices[k + 1] = (i + 1) + (j * 21);
				k += 2;
			}
		}
	}
}

PagRevolutionObject::~PagRevolutionObject(){}
