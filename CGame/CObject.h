#ifndef COBJECT_H
#define COBJECT_H

#include "CGame/Types.h"
#include "CGame/CPhysical.h"

class CObject : public CPhysical
{
public:
	//CPhysical				   physical;
	uint8_t			   __unknown_312[8];		/* 312 */
	DWORD						  flags;
	// 	бит 10 = обьект сломан
	// 	бит 11 = включен сигнал поезда
	// 	бит 12 = обьект сфотографирован камерой
	// 	бит 13 = обьект можно поднимать, переносить
	// 	бит 18 = обьект можно прицепить к магниту
	// 	бит 22 = иммунитет к педам(не включая игрока)
	byte				   EffectDamage;
	// 	0 = нет эффекта
	// 	1 = происходит смена модели
	// 	20 = разрушается
	// 	21 = изменяется модель, затем разрушается
	// 	200 = ломается
	// 	202 = ломается и удаляется
	uint8_t			   __unknown_325[3];		/* 325 */
	byte				DamagByWeaponID;
	uint8_t			  __unknown_327[11];		/* 327 */
	float					  hitpoints;
	float						   size;
	DWORD				ptr_CObjectInfo;

	int setTargatable(bool targatable);
	bool isTargatable();
	bool isDamaged();
};

#endif // COBJECT_H
