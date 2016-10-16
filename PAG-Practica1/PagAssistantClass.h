#include <iostream>
#include "PagRevolutionObject.h"

class PagAssistantClass{
	PagRevolutionObject revolutionObject;
	void devolverDatos();
	std::string nombreAlumno;
public:
	PagAssistantClass(std::string archivoIN, int slices, std::string _nombreAlumno);
	~PagAssistantClass();
};

