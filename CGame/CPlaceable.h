#ifndef CPLACEABLE_H
#define CPLACEABLE_H

#include "CGame/Types.h"

class CPlaceable
{
public:
	//uint32_t*	vtbl;   // Указатель на виртуальную таблицу методов для этого объекта
	virtual void _destruct() = 0;
	RwV3D		pos;	// Позиция RwV3D
	float		angle;   // Угол по оси Z
	RwMatrix	 *matrix; // Указатель на матрицу позиции и вращения

	float setRotation(float X, float Y, float Z);
	float setRotation(RwV3D rot);
	int setHeading(float Zangle);
	long double getRotation();
	RwV3D getOffset(RwV3D offset);
	RwV3D getOffsetUnder();
	RwV3D getPosition();
	void setPosition(RwV3D pos);
};

#endif // CPLACEABLE_H
