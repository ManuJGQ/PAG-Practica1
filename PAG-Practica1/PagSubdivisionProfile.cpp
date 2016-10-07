#include "PagSubdivisionProfile.h"
#include <string>
#include <fstream>


PagSubdivisionProfile::PagSubdivisionProfile(std::string archivoIN){
	std::string linea_actual;
	int numPuntos;
	int coma;
	try {
		// Leemos la primera linea del archivo
		std::ifstream archivoPuntosPerfil;
		archivoPuntosPerfil.open(archivoIN);

		if (!archivoPuntosPerfil.good()) throw std::string("No se puedo leer el archivo");

		std::getline(archivoPuntosPerfil, linea_actual);
		coma = linea_actual.find(',');
		numPuntos = stoi(linea_actual.substr(0, coma));
		numDivisiones = stoi(linea_actual.substr(coma + 1, linea_actual.length()));

		if (numPuntos < 2) throw std::string("Se necesitan 2 o mas puntos");

		
		perfilOriginal = new puntosPerfil[numPuntos];
		puntosPerfil puntos;

		for (int i = 0; i < numPuntos; i++) {
			//Leemos los puntos del Perfil
			std::getline(archivoPuntosPerfil, linea_actual);
			coma = linea_actual.find(',');
			puntos.x = stof(linea_actual.substr(0, coma));

			if (puntos.x < 0) throw std::string("Punto con coordenada X menor que 0");
	
			puntos.y = stof(linea_actual.substr(coma + 1, linea_actual.length()));

			perfilOriginal[i] = puntos;

			std::cout << perfilOriginal[i].x << " " << perfilOriginal[i].y << std::endl;
		}
			
		archivoPuntosPerfil.close();

	} catch (std::string &e) {
		std::cout << "ERROR!: " << e << std::endl;
	}
}


PagSubdivisionProfile::~PagSubdivisionProfile(){
	delete[] perfilOriginal;
	delete[] perfilSubdividido;
}
