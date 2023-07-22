#include "CPhysical.h"
#include "methods.h"

CU APPLY_MOVE_FORCE_FUNC = 0x542A07;
CU APPLY_GRAVITY_FORCE_FUNC = 0x542B50;

float CPhysical::getSpeed()
{
	return speed.length();
}

void CPhysical::setSpeed(RwV3D spd)
{
	speed.fX = spd.fX;
	speed.fY = spd.fY;
	speed.fZ = spd.fZ;
}

void CPhysical::applyMoveForce(RwV3D mov)
{
	typedef void(__thiscall *CPhysical__applyMoveForce)(CPhysical *_this, CVector vec);
	(CPhysical__applyMoveForce(APPLY_MOVE_FORCE_FUNC))(this, mov);
}

void CPhysical::applyGravityForce(RwV3D a, CVector b, char a4)
{
	typedef void(__thiscall *CPhysical__applyGravityForce)(CPhysical *_this, RwV3D a, CVector b, char a4);
	(CPhysical__applyGravityForce(APPLY_GRAVITY_FORCE_FUNC))(this, a, b, a4);
}

void CPhysical::stickToPlace()
{
	float grav = *reinterpret_cast<float*>(0x863984);
	RwV3D place = getOffsetUnder() * (mass * grav);
	RwV3D standard(0.0f, 0.0f, -(mass * grav));
	if (!IsLineOfSightClear(matrix->pos, matrix->pos + getOffsetUnder() * 3.0f, 1, 0, 0, 1, 1, 0, 0))
		applyGravityForce(place, place, 1);
	else applyGravityForce(standard, standard, 1);
}
