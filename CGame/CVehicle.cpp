#include "CVehicle.h"
#include "CPed.h"
#include "CCamera.h"
#include "methods.h"

typedef bool(__cdecl *CVehicle__isType)(int modelId);
CU IS_BOAT_FUNC = 0x4c5a70;
CU IS_CAR_FUNC = 0x4c5aa0;
CU IS_TRAIN_FUNC = 0x4c5ad0;
CU IS_HELI_FUNC = 0x4c5b00;
CU IS_PLANE_FUNC = 0x4c5b30;
CU IS_BIKE_FUNC = 0x4c5b60;
CU IS_FAKE_PLANE_FUNC = 0x4c5b90;
CU IS_MONSTER_TRUCK_FUNC = 0x4c5bc0;
CU IS_QUAD_BIKE_FUNC = 0x4c5bf0;
CU IS_BMX_FUNC = 0x4c5c20;
CU IS_TRAILER_FUNC = 0x4c5c50;
CU LOCK_VEHICLE_FUNC = 0x5433B0;
CU SET_ANGULAR_VELOCITY_FUNC = 0x45AFB0;

void CVehicle::repair()
{
	fix();
	hitpoints = 1000.0f;
}

bool CVehicle::isBoat()
{
	return (CVehicle__isType(IS_BOAT_FUNC))(modelID);
}

bool CVehicle::isCar()
{
	return (CVehicle__isType(IS_CAR_FUNC))(modelID);
}

bool CVehicle::isTrain()
{
	return (CVehicle__isType(IS_TRAIN_FUNC))(modelID);
}

bool CVehicle::isHeli()
{
	return (CVehicle__isType(IS_HELI_FUNC))(modelID);
}

bool CVehicle::isPlane()
{
	return (CVehicle__isType(IS_PLANE_FUNC))(modelID);
}

bool CVehicle::isBike()
{
	return (CVehicle__isType(IS_BIKE_FUNC))(modelID);
}

bool CVehicle::isFakePlane()
{
	return (CVehicle__isType(IS_FAKE_PLANE_FUNC))(modelID);
}

bool CVehicle::isMonsterTruck()
{
	return (CVehicle__isType(IS_MONSTER_TRUCK_FUNC))(modelID);
}

bool CVehicle::isQuadBike()
{
	return (CVehicle__isType(IS_QUAD_BIKE_FUNC))(modelID);
}

bool CVehicle::isBmx()
{
	return (CVehicle__isType(IS_BMX_FUNC))(modelID);
}

bool CVehicle::isTrailer()
{
	return (CVehicle__isType(IS_TRAILER_FUNC))(modelID);
}

bool CVehicle::lock()
{
	typedef bool(__thiscall *CVehicle__lock)(CVehicle *_this);
	return (CVehicle__lock(LOCK_VEHICLE_FUNC))(this);
}

float CVehicle::setAngularVelocity(RwV3D angularVelocity)
{
	typedef float(__thiscall *CVehicle__setAngularVelocity)(CVehicle *_this, float X, float Y, float Z);
	return (CVehicle__setAngularVelocity(SET_ANGULAR_VELOCITY_FUNC))(this,
																	 angularVelocity.fX,
																	 angularVelocity.fY,
																	 angularVelocity.fZ);
}
