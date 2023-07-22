#include "CObject.h"

CU SET_TARGATABLE_FUNC = 0x59F300;
CU IS_TARGATABLE_FUNC = 0x59F320;
CU IS_DAMAGED_FUNC = 0x46A2F0;

int CObject::setTargatable(bool targatable)
{
	typedef int(__thiscall *CObject__setTargatable)(CObject *_this, uint8_t targatable);
	return (CObject__setTargatable(SET_TARGATABLE_FUNC))(this, targatable);
}

bool CObject::isTargatable()
{
	typedef int(__thiscall *CObject__isTargatable)(CObject *_this);
	return (CObject__isTargatable(IS_TARGATABLE_FUNC))(this);
}

bool CObject::isDamaged()
{
	typedef int(__thiscall *CObject__isDamafed)(CObject *_this);
	return (CObject__isDamafed(IS_DAMAGED_FUNC))(this);
}
