#include "methods.h"
#include <cmath>

CU IS_LINE_OF_SIGHT_CLEAR_FUNC = 0x56A490;
CU FIND_PLAYER_PED_FUNC = 0x56E210;
CU IS_SPHERE_VISIBLE_FUNC = 0x420D40;
CU REQUEST_MODEL_FUNC = 0x4087e0;
CU LOAD_ALL_REQUESTED_MODELS = 0x40ea10;

void GetMatrixForGravity ( CVector& vecGravity, CMatrix& mat )
{
	// Calculates a basis where the z axis is the inverse of the gravity
	if ( vecGravity.length() > 0.0001f )
	{
		mat.up = -vecGravity;
		mat.up.normalize ();
		if ( fabs(mat.up.fX) > 0.0001f || fabs(mat.up.fZ) > 0.0001f )
		{
			CVector y ( 0.0f, 1.0f, 0.0f );
			mat.at = vecGravity;
			mat.at.CrossProduct ( &y );
			mat.at.CrossProduct ( &vecGravity );
			mat.at.normalize ();
		}
		else
		{
			mat.at = CVector ( 0.0f, 0.0f, vecGravity.fY );
		}
		mat.right = mat.at;
		mat.right.CrossProduct ( &mat.up );
	}
	else
	{
		// No gravity, use default axes
		mat.right = CVector ( 1.0f, 0.0f, 0.0f );
		mat.at = CVector ( 0.0f, 1.0f, 0.0f );
		mat.up	= CVector ( 0.0f, 0.0f, 1.0f );
	}
}

bool IsLineOfSightClear(RwV3D start, RwV3D end, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool seeThroughStuff, bool ignoreSomeObjectsForCamera)
{
	typedef bool(__cdecl *_IsLineOfSightClear)(RwV3D *start, RwV3D *end, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool seeThroughStuff, bool ignoreSomeObjectsForCamera);
	return (_IsLineOfSightClear(IS_LINE_OF_SIGHT_CLEAR_FUNC))(&start, &end, buildings, vehicles, peds, objects, dummies, seeThroughStuff, ignoreSomeObjectsForCamera);
}

class CPed *findPlayerPed(int handle)
{
	typedef class CPed*(__cdecl *__findOlayerPed)(int id);
	return (__findOlayerPed(FIND_PLAYER_PED_FUNC))(handle);
}

bool isSphereVisible(RwV3D pos, float range)
{
	typedef bool (__thiscall *CCamera__isSphereVisible)(void* _this, RwV3D *pos, float radius);
	return (CCamera__isSphereVisible(IS_SPHERE_VISIBLE_FUNC))((void*)*(uint32_t*)0xB6F028, &pos, range);
}

int isModelLoaded(eModelIndex modelID)
{
	int *ModelsLoadStateArray = (int *)0x8E4CD0;
	return ModelsLoadStateArray[5 * modelID];
}

bool requestModelLoad(eModelIndex modelID)
{
	if (isModelLoaded(modelID))
		return false;
	typedef void(__cdecl *CStreaming__requestModel)(int modelId, int a2);
	(CStreaming__requestModel(REQUEST_MODEL_FUNC))(modelID, 2);
	return true;
}

void loadRequestedModels()
{
	typedef void(__cdecl *CStreaming__loadRequestedModels)(int a1);
	(CStreaming__loadRequestedModels(LOAD_ALL_REQUESTED_MODELS))(0);
}

void loadModel(eModelIndex modelID)
{
	if (requestModelLoad(modelID))
		loadRequestedModels();
}

eModelIndex getWeaponModel(int weaponId)
{
	if (weaponId == 1)
		return weapon_BrassKnuckles;
	else if (weaponId >= 2 && weaponId <= 8)
		return eModelIndex(weaponId + 331);
	else if (weaponId == 9)
		return weapon_Chainsaw;
	else if (weaponId >= 22 && weaponId <= 29)
		return eModelIndex(weaponId + 324);
	else if (weaponId == 32)
		return weapon_Tech9;
	else if (weaponId >= 30 && weaponId <= 31)
		return eModelIndex(weaponId + 325);
	else if (weaponId >= 33 && weaponId <= 38)
		return eModelIndex(weaponId + 324);
	else if (weaponId >= 16 && weaponId <= 18)
		return eModelIndex(weaponId + 326);
	else if (weaponId == 39)
		return weapon_RemoteExplosives;
	else if (weaponId >= 41 && weaponId <= 43)
		return eModelIndex(weaponId + 324);
	else if (weaponId >= 10 && weaponId <= 15)
		return eModelIndex(weaponId + 311);
	else if (weaponId >= 44 && weaponId <= 45)
		return eModelIndex(weaponId + 324);
	else if (weaponId == 46)
		return weapon_Parachute;
	else if (weaponId == 40)
		return weapon_Detonator;
	return eModelIndex(-1);
}

void loadWeaponModel(int weaponId)
{
	loadModel(getWeaponModel(weaponId));
}

void loadAllWeaponModels()
{
	requestModelLoad(weapon_BrassKnuckles);
	requestModelLoad(weapon_GolfClub);
	requestModelLoad(weapon_Nitestick);
	requestModelLoad(weapon_Knife);
	requestModelLoad(weapon_BaseballBat);
	requestModelLoad(weapon_Shovel);
	requestModelLoad(weapon_PoolCue);
	requestModelLoad(weapon_Katana);
	requestModelLoad(weapon_Chainsaw);
	requestModelLoad(weapon_Pistol);
	requestModelLoad(weapon_SilencedPistol);
	requestModelLoad(weapon_DesertEagle);
	requestModelLoad(weapon_Shotgun);
	requestModelLoad(weapon_SawnOffShotgun);
	requestModelLoad(weapon_SPAZ12);
	requestModelLoad(weapon_MicroUZI);
	requestModelLoad(weapon_MP5);
	requestModelLoad(weapon_Tech9);
	requestModelLoad(weapon_AK47);
	requestModelLoad(weapon_M4);
	requestModelLoad(weapon_CountryRifle);
	requestModelLoad(weapon_SniperRifle);
	requestModelLoad(weapon_RocketLauncher);
	requestModelLoad(weapon_HeatSeekingRPG);
	requestModelLoad(weapon_FlameThrower);
	requestModelLoad(weapon_Minigun);
	requestModelLoad(weapon_Grenade);
	requestModelLoad(weapon_Teargas);
	requestModelLoad(weapon_MolotovCocktail);
	requestModelLoad(weapon_RemoteExplosives);
	requestModelLoad(weapon_SprayCan);
	requestModelLoad(weapon_FireExtinguisher);
	requestModelLoad(weapon_Camera);
	requestModelLoad(weapon_Dildo1);
	requestModelLoad(weapon_Dildo2);
	requestModelLoad(weapon_Vibe1);
	requestModelLoad(weapon_Vibe2);
	requestModelLoad(weapon_Flowers);
	requestModelLoad(weapon_Cane);
	requestModelLoad(weapon_NVGoggles);
	requestModelLoad(weapon_IRGoggles);
	requestModelLoad(weapon_Parachute);
	requestModelLoad(weapon_Detonator);
	loadRequestedModels();
}
