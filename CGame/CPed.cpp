#include "CPed.h"
#include "CVehicle.h"
#include "methods.h"

CU BONE_POS_FUNC = 0x5E01C0;
CU GIVE_WEAPON_FUNC = 0x5E6080;
CU SET_AMMO_FUNC = 0x5DF290;
CU IS_AVAILABLE_FUNC = 0x5E0170;
CU SET_ACTIVE_WEAPON_SLOT_FUNC = 0x5E61F0;
CU SET_WEAPON_FUNC = 0x5E6280;
CU CLEAR_WEAPONS_FUNC = 0x5E6320;
CU GET_WEAPON_SKILL_INDEX_FUNC = 0x5E6580;
CU GET_WEAPON_SKILL_BY_TYPE_FUNC = 0x5E3B60;
CU REMOVE_WEAPON_MODEL_FUNC = 0x5E3990;
CU GRANT_AMMO_FUNC = 0x5DF220;
CU SET_MODEL_INDEX_FUNC = 0x5E4880;
CU IS_CONTROLABLE_FUNC = 0x609590;

bool CPed::isDriving()
{
	return state == 50;
}

bool CPed::isDriver()
{
	if (!isDriving())
		return false;
	return vehicle->driver == this;
}

bool CPed::isPassenger()
{
	return (isDriving() && !isDriver());
}

bool CPed::isLeavingCar()
{
	if (isDriving())
		return false;
	return state == 0;
}

bool CPed::isActorDead()
{
	return (state == 55 || state == 63 || hitpoints == 0.0f);
}

bool CPed::isAvailable()
{
	typedef bool(__thiscall *CPed__isAvailable)(CPed *_this);
	return (CPed__isAvailable(IS_AVAILABLE_FUNC))(this);
}

bool CPed::isControlable()
{
	typedef bool(__thiscall *CPed__isControlable)(CPed *_this);
	return (CPed__isControlable(IS_CONTROLABLE_FUNC))(this);
}

RwV3D CPed::getBonePos(byte boneId, bool includeAnim)
{
	RwV3D Position = {0.0, 0.0, 0.0};

	typedef int(__thiscall *CPed__getBonePositionWithOffset) (CPed *_this, RwV3D *_offset, int _bodeId, bool _includeAnim);
	(CPed__getBonePositionWithOffset(BONE_POS_FUNC))(this, &Position, boneId, includeAnim);

	return Position;
}

int CPed::giveWeapon(int weaponId, int ammo)
{
	loadWeaponModel(weaponId);
	typedef int(__thiscall *CPed__giveWeapon)(CPed *_this, int weapId, int ammo, int unk);
	return (CPed__giveWeapon(GIVE_WEAPON_FUNC))(this, weaponId, ammo, 0);
}

int CPed::setAmmo(int weaponId, int ammo)
{
	typedef int(__thiscall *CPed__setAmmo)(CPed *_this, int weaponId, int ammo);
	return (CPed__setAmmo(SET_AMMO_FUNC))(this, weaponId, ammo);
}

void CPed::setActiveWeaponSlot(int slotId)
{
	typedef void(__thiscall *CPed__setActiveWeaponSlot)(CPed *_this, int slotId);
	(CPed__setActiveWeaponSlot(SET_ACTIVE_WEAPON_SLOT_FUNC))(this, slotId);
}

unsigned CPed::setWeapon(int weaponId)
{
	typedef unsigned(__thiscall *CPed__setWeapon)(CPed *_this, int weaponId);
	return (CPed__setWeapon(SET_WEAPON_FUNC))(this, weaponId);
}

void CPed::clearWeapons()
{
	typedef void(__thiscall *CPed__clearWeapons)(CPed *_this);
	(CPed__clearWeapons(CLEAR_WEAPONS_FUNC))(this);
}

uint8_t CPed::getWeaponSkillIndex()
{
	typedef uint8_t(__thiscall *CPed__getWeaponSkillIndex)(CPed *_this);
	return (CPed__getWeaponSkillIndex(GET_WEAPON_SKILL_INDEX_FUNC))(this);
}

uint8_t CPed::getWeaponSkillByType(int weaponId)
{
	typedef uint8_t(__thiscall *CPed__getWeaponSkillByType)(CPed *_this, int wType);
	return (CPed__getWeaponSkillByType(GET_WEAPON_SKILL_BY_TYPE_FUNC))(this, weaponId);
}

void *CPed::removeWeaponModel(int model)
{
	typedef void*(__thiscall *CPed__removeWeaponModel)(CPed *_this, int model);
	return (CPed__removeWeaponModel(REMOVE_WEAPON_MODEL_FUNC))(this, model);
}

int CPed::grantAmmo(int weaponId, int ammo)
{
	typedef int(__thiscall *CPed__grantAmmo)(CPed *_this, int weaponId, int ammo);
	return (CPed__grantAmmo(GRANT_AMMO_FUNC))(this, weaponId, ammo);
}
