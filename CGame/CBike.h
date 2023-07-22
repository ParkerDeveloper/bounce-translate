#ifndef CBIKE_H
#define CBIKE_H

#include "CVehicle.h"

class CBike : public CVehicle
{
public:
	virtual int _01() = 0;

	bool _processFall(float mass, int unused_a3, int unused_a4, int unused_a5, RwV3D *a6);
	bool processUnderWater();
	int placeOnRoadProperly();
};

#endif // CBIKE_H
