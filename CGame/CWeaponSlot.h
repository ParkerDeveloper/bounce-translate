#ifndef CWEAPONSLOT_H
#define CWEAPONSLOT_H

#include "CGame/Types.h"

class CWeaponSlot
{
public:
	DWORD  m_Type;              // Тип оружия
	DWORD        m_dwState;           // Статус: 0 - ожидание, 1 - стреляет, 2 - перезарядка
	DWORD        m_dwAmmoInClip;      // Патронов в обойме
	DWORD        m_dwTotalAmmo;       // Патронов всего
	DWORD        m_dwTimeForNextShot; // Время для следующего выстрела (время последнего выстрела + время ожидания)
	uint32_t	 __goggle;			/* 0 off, 256 on */
	void		 *m_pParticle;    // Прикреплённый эффект
};

#endif // CWEAPONSLOT_H
