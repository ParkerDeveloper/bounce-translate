#ifndef CAUTOMOBILE_H
#define CAUTOMOBILE_H

#include "CVehicle.h"

class CAutomobile : public CVehicle
{
public:
	virtual int _01();
	virtual int ResetSuspension();
	virtual int _03();
	virtual int _04();
	virtual int _05();

	int fixTire(int nWheel);
	int setTaxiLight(bool enable);
	void setAllTaxiLights(bool enable);
	void createNitroParticle(float a2);
	void processNitro(byte slot);
	bool hydraulicControl();
};

#endif // CAUTOMOBILE_H
