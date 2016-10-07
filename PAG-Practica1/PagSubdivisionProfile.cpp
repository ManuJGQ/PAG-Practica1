#include "PagSubdivisionProfile.h"
#include <string>
#include <fstream>


PagSubdivisionProfile::PagSubdivisionProfile(std::string archivoIN){
	std::string linea_actual;
	int coma;
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

		
		perfilOriginal = new puntosPerfil[numPuntosPerfilOriginal];
		puntosPerfil puntos;

		for (int i = 0; i < numPuntosPerfilOriginal; i++) {
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

	subdivisionPolilineas();
}

void PagSubdivisionProfile::subdivisionPolilineas() {
	perfilSubdividido = perfilOriginal;
	int numPuntos = numPuntosPerfilOriginal;
	int expectedNumberOfPoints = (2 * numPuntos) - 1;
	puntosPerfil* perfiltemporal;

	for (int j = 0; j < numDivisiones; j++) {
		perfiltemporal = new puntosPerfil[expectedNumberOfPoints];
		perfiltemporal[0] = perfilSubdividido[0];
		perfiltemporal[expectedNumberOfPoints - 1] = perfilSubdividido[numPuntos - 1];
		for (int i = 1; i < numPuntos-1; i++) {
			
			puntosPerfil h1;
			h1.x = (perfilSubdividido[i-1].x + perfilSubdividido[i].x) / 2;
			h1.y = (perfilSubdividido[i-1].y + perfilSubdividido[i].y) / 2;

			puntosPerfil h2;
			h2.x = (perfilSubdividido[i].x + perfilSubdividido[i + 1].x) / 2;
			h2.y = (perfilSubdividido[i].y + perfilSubdividido[i + 1].y) / 2;

			puntosPerfil pi;
			pi.x = ((perfilSubdividido[i].x / 2) + (h1.x / 4) + (h2.x / 4));
			pi.y = ((perfilSubdividido[i].y / 2) + (h1.y / 4) + (h2.y / 4));

			perfiltemporal[(i * 2) - 1] = h1;
			perfiltemporal[i * 2] = pi;
			perfilSubdividido[i] = pi;
			perfiltemporal[(i * 2) + 1] = h2;

		}
		for (int i = 0; i < expectedNumberOfPoints; i++) {
			std::cout << "Tanda de puntos " << j << std::endl;
			std::cout << perfiltemporal[i].x << " " << perfiltemporal[i].y << std::endl;
		}
		numPuntos = expectedNumberOfPoints;
		perfilSubdividido = perfiltemporal;
		expectedNumberOfPoints = (2 * expectedNumberOfPoints) - 1;
	}
}

PagSubdivisionProfile::~PagSubdivisionProfile(){
	delete[] perfilOriginal;
	delete[] perfilSubdividido;
}
