#include "PagAssistantClass.h"

#include <fstream>
#include <string>

#define Epsilon 0.000001

PagAssistantClass::PagAssistantClass(std::string archivoIN){
	std::string linea_actual;
	int numPuntosPerfilOriginal;
	int numPuntosPerfilModificado;
	int numDivisiones;
	int coma;
	bool flagBottomTape = false;
	bool flagTopTape = false;
	try {
		// Leemos la primera linea del archivo
		std::ifstream archivoPuntosPerfil;
		archivoPuntosPerfil.open(archivoIN);

		if (!archivoPuntosPerfil.good()) throw std::string("No se puedo leer el archivo");

		std::getline(archivoPuntosPerfil, linea_actual);
		coma = linea_actual.find(',');
		numPuntosPerfilOriginal = stoi(linea_actual.substr(0, coma));
		numPuntosPerfilModificado = numPuntosPerfilOriginal;
		numDivisiones = stoi(linea_actual.substr(coma + 1, linea_actual.length()));

		if (numPuntosPerfilOriginal < 2) throw std::string("Se necesitan 2 o mas puntos");
		if (numDivisiones < 0) throw std::string("No se permite un numero negativo de divisiones");

		PuntosPerfil *perfilOriginal = new PuntosPerfil[numPuntosPerfilOriginal];
		PuntosPerfil puntos;

		for (int i = 0; i < numPuntosPerfilOriginal; i++) {
			//Leemos los puntos del Perfil
			std::getline(archivoPuntosPerfil, linea_actual);
			coma = linea_actual.find(',');
			puntos.x = stof(linea_actual.substr(0, coma));

			if ((puntos.x < 0) || 
				(puntos.x == 0 && (i > 0 || i < numPuntosPerfilOriginal - 1))) numPuntosPerfilModificado--;
			else {
				if (puntos.x == 0) {
					if (i == 0) flagBottomTape = true;
					if (i == numPuntosPerfilOriginal - 1) flagTopTape = true;
				}

				puntos.y = stof(linea_actual.substr(coma + 1, linea_actual.length()));

				perfilOriginal[i] = puntos;

				std::cout << perfilOriginal[i].x << " " << perfilOriginal[i].y << std::endl;
			}

		}

		archivoPuntosPerfil.close();

		PuntosPerfil *perfilTemp = new PuntosPerfil[numPuntosPerfilModificado];
		for (int i = 0; i < numPuntosPerfilModificado; i++) {
			perfilTemp[i] = perfilOriginal[i];
		}
		delete[] perfilOriginal;

		perfilOriginal = perfilTemp;

		revolutionObject = PagRevolutionObject(numPuntosPerfilModificado, numDivisiones, perfilOriginal, 
			flagBottomTape, flagTopTape);

	}
	catch (std::string &e) {
		std::cout << "ERROR: " << e << std::endl;
	}
}

PagAssistantClass::~PagAssistantClass(){}
