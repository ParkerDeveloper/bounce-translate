#include "CPlaceable.h"

CU SET_ROTATION_FUNC = 0x439A80;
CU SET_HEADING_FUNC = 0x43E0C0;
CU GET_ROTATION_FUNC = 0x441DB0;

float CPlaceable::setRotation(float X, float Y, float Z)
{
	typedef float(__thiscall *CPlaceable__setRotation)(CPlaceable *_this, float rotX, float rotY, float rotZ);
	return (CPlaceable__setRotation(SET_ROTATION_FUNC))(this, X, Y, Z);
}

float CPlaceable::setRotation(RwV3D rot)
{
	return setRotation(rot.fX, rot.fY, rot.fZ);
}

int CPlaceable::setHeading(float Zangle)
{
	typedef int(__thiscall *CPlaceable__setHeading)(CPlaceable *_this, float rotZ);
	return (CPlaceable__setHeading(SET_HEADING_FUNC))(this, Zangle);
}

long double CPlaceable::getRotation()
{
	typedef long double(__thiscall *CPlaceable__getRotation)(CPlaceable *_this);
	return (CPlaceable__getRotation(SET_HEADING_FUNC))(this);
}

RwV3D CPlaceable::getOffset(RwV3D offset)
{
	CVector offsetVector;
	offsetVector.fX = (offset.fX * matrix->right.fX) + (offset.fY * matrix->up.fX) + (offset.fZ * matrix->at.fX);
	offsetVector.fY = (offset.fX * matrix->right.fY) + (offset.fY * matrix->up.fY) + (offset.fZ * matrix->at.fY);
	offsetVector.fZ = (offset.fX * matrix->right.fZ) + (offset.fY * matrix->up.fZ) + (offset.fZ * matrix->at.fZ);
	return offsetVector;
}

RwV3D CPlaceable::getOffsetUnder()
{
	return getOffset({0.0f, 0.0f, -1.0f});
}

RwV3D CPlaceable::getPosition()
{
	return matrix->pos;
}

void CPlaceable::setPosition(RwV3D pos)
{
	matrix->pos = pos;
}
