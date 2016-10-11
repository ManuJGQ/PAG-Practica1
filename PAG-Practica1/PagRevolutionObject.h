#include <iostream>
#include "PagSubdivisionProfile.h"

class PagRevolutionObject{
	bool flagBottomTape;
	bool flagTopTape;
	PagSubdivisionProfile subdivisionProfiles;
public:
	void set_flagBottomTape(bool flag);
	void set_flagTopTape(bool flag);
	PagRevolutionObject();
	~PagRevolutionObject();
};

