#include "PagSubdivisionProfile.h"

PagSubdivisionProfile::PagSubdivisionProfile() {};

PagSubdivisionProfile::PagSubdivisionProfile(int _numPuntosPerfilOriginal, int _numDivisiones,
	PuntosPerfil& _perfilOriginal): numPuntosPerfilOriginal(_numPuntosPerfilOriginal), 
	numDivisiones(_numDivisiones){

	perfilOriginal = &_perfilOriginal;

	subdivisionPolilineas();
}

void PagSubdivisionProfile::subdivisionPolilineas() {
	perfilSubdividido = perfilOriginal;
	int numPuntos = numPuntosPerfilOriginal;
	int expectedNumberOfPoints = (2 * numPuntos) - 1;
	PuntosPerfil* perfiltemporal;

	for (int j = 0; j < numDivisiones; j++) {
		perfiltemporal = new PuntosPerfil[expectedNumberOfPoints];
		perfiltemporal[0] = perfilSubdividido[0];
		perfiltemporal[expectedNumberOfPoints - 1] = perfilSubdividido[numPuntos - 1];
		for (int i = 1; i < numPuntos-1; i++) {
			
			PuntosPerfil h1;
			h1.x = (perfilSubdividido[i-1].x + perfilSubdividido[i].x) / 2;
			h1.y = (perfilSubdividido[i-1].y + perfilSubdividido[i].y) / 2;

			PuntosPerfil h2;
			h2.x = (perfilSubdividido[i].x + perfilSubdividido[i + 1].x) / 2;
			h2.y = (perfilSubdividido[i].y + perfilSubdividido[i + 1].y) / 2;

			PuntosPerfil pi;
			pi.x = ((perfilSubdividido[i].x / 2) + (h1.x / 4) + (h2.x / 4));
			pi.y = ((perfilSubdividido[i].y / 2) + (h1.y / 4) + (h2.y / 4));

			perfiltemporal[(i * 2) - 1] = h1;
			perfiltemporal[i * 2] = pi;
			if(i == numPuntos - 2)perfiltemporal[(i * 2) + 1] = h2;

		}
		for (int i = 0; i < expectedNumberOfPoints; i++) {
			std::cout << "Tanda de puntos " << j + 1 << std::endl;
			std::cout << perfiltemporal[i].x << " " << perfiltemporal[i].y << std::endl;
		}
		numPuntos = expectedNumberOfPoints;
		perfilSubdividido = perfiltemporal;
		expectedNumberOfPoints = (2 * expectedNumberOfPoints) - 1;

		numPuntosPerfilSubdividido = numPuntos;
	}
}

PagSubdivisionProfile::~PagSubdivisionProfile(){}