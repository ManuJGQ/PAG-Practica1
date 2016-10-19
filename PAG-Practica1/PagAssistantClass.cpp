#include "PagAssistantClass.h"

#include <fstream>
#include <string>

#define Epsilon 0.000001

PagAssistantClass::PagAssistantClass(std::string archivoIN, int slices, std::string _nombreAlumno){
	int linea;
	linea = _nombreAlumno.find('-');
	nombreAlumno = _nombreAlumno.substr(0, linea);

	std::string linea_actual;
	int numPuntosPerfilOriginal;
	int numDivisiones;
	int coma;
	flagBottomTape = false;
	flagTopTape = false;
	try {
		// Leemos la primera linea del archivo
		std::ifstream archivoPuntosPerfil;
		archivoPuntosPerfil.open(archivoIN);

		if (!archivoPuntosPerfil.good()) throw std::string("No se puedo leer el archivo");

		std::getline(archivoPuntosPerfil, linea_actual);
		coma = linea_actual.find(',');
		numPuntosPerfilOriginal = stoi(linea_actual.substr(0, coma));
		numDivisiones = stoi(linea_actual.substr(coma + 1, linea_actual.length()));

		if (numPuntosPerfilOriginal < 2) throw std::string("Se necesitan 2 o mas puntos");
		if (numDivisiones < 0) throw std::string("No se permite un numero negativo de divisiones");

		PuntosPerfil *perfil = new PuntosPerfil[numPuntosPerfilOriginal];
		PuntosPerfil puntos;

		for (int i = 0; i < numPuntosPerfilOriginal; i++) {
			//Leemos los puntos del Perfil
			std::getline(archivoPuntosPerfil, linea_actual);
			coma = linea_actual.find(',');
			puntos.x = stof(linea_actual.substr(0, coma));

			if ((puntos.x < 0) ||
				(puntos.x == 0 && (i > 0 && i < numPuntosPerfilOriginal - 1))) {
				numPuntosPerfilOriginal--;
				i--;
			}else {
				if (puntos.x == 0) {
					if (i == 0) flagBottomTape = true;
					if (i == numPuntosPerfilOriginal - 1) flagTopTape = true;
				}

				puntos.y = stof(linea_actual.substr(coma + 1, linea_actual.length()));

				perfil[i] = puntos;

			}

		}

		archivoPuntosPerfil.close();

		PuntosPerfil *perfilTemp = new PuntosPerfil[numPuntosPerfilOriginal];
		for (int i = 0; i < numPuntosPerfilOriginal; i++) {
			perfilTemp[i] = perfil[i];
		}

		delete[] perfil;

		perfil = perfilTemp;

		revolutionObject = PagRevolutionObject(numPuntosPerfilOriginal, numDivisiones, *perfil, 
			flagBottomTape, flagTopTape, slices);

		devolverDatos();
	}
	catch (std::string &e) {
		std::cout << "ERROR: " << e << std::endl;
	}

}

void PagAssistantClass::devolverDatos() {
	Geometria *geometria = &revolutionObject.getGeometria();
	CoordTexturas *coordtext = &revolutionObject.getCoordText();
	int *indices = &revolutionObject.getIndices();
	int tamaGeometriaCoordText = revolutionObject.getTamaGeometriaCoordText();
	int tamaIndices = revolutionObject.getTamaIndices();
	int tamIndicesTapes = revolutionObject.getTamaIndicesTapes();

	char* docdir = getenv("userprofile");
	std::string path = docdir;
	path += "/Desktop/";
	path += nombreAlumno;
	std::string nombreFichero;

	//ARCHIVO GEOMETRIA

	nombreFichero = path;
	nombreFichero += "-out-geom.txt";
	std::ofstream ficheroGeom;
	ficheroGeom.open(nombreFichero);
	ficheroGeom << tamaGeometriaCoordText << std::endl;
	for (int i = 0; i < tamaGeometriaCoordText; i++) {
		ficheroGeom << geometria[i].vertice.x << ","
			<< geometria[i].vertice.y << ","
			<< geometria[i].vertice.z << ","
			<< geometria[i].normal.x << ","
			<< geometria[i].normal.y << ","
			<< geometria[i].normal.z << ","
			<< geometria[i].tangente.x << ","
			<< geometria[i].tangente.y << ","
			<< geometria[i].tangente.z << std::endl;
	}
	ficheroGeom.close();

	//ARCHIVO COORDTEXT

	nombreFichero = path;
	nombreFichero += "-out-text.txt";
	std::ofstream ficheroText;
	ficheroText.open(nombreFichero);
	ficheroText << tamaGeometriaCoordText << std::endl;
	for (int i = 0; i < tamaGeometriaCoordText; i++) {
		ficheroText << coordtext[i].s << ","
			<< coordtext[i].t << std::endl;
	}
	ficheroText.close();

	//ARCHIVOS INDICES

	nombreFichero = path;
	nombreFichero += "-out-ind.txt";
	std::ofstream ficheroInd;
	ficheroInd.open(nombreFichero);
	ficheroInd << tamaIndices << std::endl;
	for (int i = 0; i < tamaIndices; i++) {
		ficheroInd << indices[i] << std::endl;
	}
	ficheroInd.close();

	if (flagBottomTape) {
		int *indicesBottom = &revolutionObject.getIndicesBottomTape();
		nombreFichero = path;
		nombreFichero += "-out-ind_BottomTape.txt";
		std::ofstream ficheroIndBottom;
		ficheroIndBottom.open(nombreFichero);
		ficheroIndBottom << tamIndicesTapes << std::endl;
		for (int i = 0; i < tamIndicesTapes; i++) {
			ficheroIndBottom << indicesBottom[i] << std::endl;
		}
		ficheroInd.close();
	}

	if (flagTopTape) {
		int *indicesTop = &revolutionObject.getIndicesTopTape();
		nombreFichero = path;
		nombreFichero += "-out-ind_TopTape.txt";
		std::ofstream ficheroIndTop;
		ficheroIndTop.open(nombreFichero);
		ficheroIndTop << tamIndicesTapes << std::endl;
		for (int i = 0; i < tamIndicesTapes; i++) {
			ficheroIndTop << indicesTop[i] << std::endl;
		}
		ficheroIndTop.close();
	}
}

PagAssistantClass::~PagAssistantClass(){}
