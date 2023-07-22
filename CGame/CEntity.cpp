#include "CEntity.h"

CU REMOVE_REF_TO_ENTITY_FUNC = 0x544280;

bool CEntity::isVehicle()
{
	return (modelID >= 400 && modelID <= 611);
}

bool CEntity::isPed()
{
	return modelID <= 311;
}

bool CEntity::_removeRefsToEntity(int a2)
{
	typedef bool(__thiscall *CEntity__removeRefToEntity)(CEntity *_this, int a2);
	return (CEntity__removeRefToEntity(REMOVE_REF_TO_ENTITY_FUNC))(this, a2);
}
