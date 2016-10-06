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
		archivoPuntosPerfil.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		archivoPuntosPerfil.open(archivoIN);
		std::getline(archivoPuntosPerfil, linea_actual);
		coma = linea_actual.find(',');
		numPuntos = stoi(linea_actual.substr(0, coma));
		numDivisiones = stoi(linea_actual.substr(coma + 1, linea_actual.length()));

		if (numPuntos < 2) {
			std::cout << "ERROR! Se necesitan 2 o mas puntos" << std::endl;
			return;
		}
		
		perfilOriginal = new puntosPerfil[numPuntos];
		puntosPerfil puntos;

		for (int i = 0; i < numPuntos; i++) {
			//Leemos los puntos del Perfil
			std::getline(archivoPuntosPerfil, linea_actual);
			coma = linea_actual.find(',');
			puntos.x = stof(linea_actual.substr(0, coma));

			if (puntos.x < 0) {
				std::cout << "ERROR! Punto con coordenada X menor que 0" << std::endl;
				return;
			}

			puntos.y = stof(linea_actual.substr(coma + 1, linea_actual.length()));

			perfilOriginal[i] = puntos;

			std::cout << perfilOriginal[i].x << " " << perfilOriginal[i].y << std::endl;
		}
			
		archivoPuntosPerfil.close();

	} catch (std::ifstream::failure &e) {
		std::cerr << "Excepcion leyendo el archivo: " << e.what() << std::endl;
	}
}


PagSubdivisionProfile::~PagSubdivisionProfile(){
	delete[] perfilOriginal;
	delete[] perfilSubdividido;
}
