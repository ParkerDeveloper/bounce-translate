#ifndef CPED_H
#define CPED_H

#include "CGame/Types.h"
#include "CGame/CObject.h"
#include "CGame/CPhysical.h"
#include "CGame/CPedIK.h"
#include "CGame/CWeaponSlot.h"

class CPed : public CPhysical
{
public:
	//CPhysical					physical;
	uint8_t			   __unknown_316[32];		/* 316 */
	uint8_t				 animation_state;
	// 	0 = прыгает от земли
	// 	61 = ударяет
	// 	102 = остановился
	// 	154 = спринт(бежит с ускорением)
	// 	205 = бежит
	uint8_t				__unknown_349[7];		/* 349 */
	RwV3D						step_pos;		/* 356 - coordinates, last foot step */
	RwV3D				 step_pos_before;		/* 368 - coordinates, foot step before last one */
	uint8_t			  __unknown_380[280];		/* 380 */
	byte				CPedSound[0x100];
	uint8_t			  __unknown_916[216];		/* 916 */
	byte					playerStatus;
	// 	0 = в воздухе / воде
	// 	1 = в машине
	// 	2 = входит в интерьер
	// 	3 = пешком
	// 	18 = истекает кровью
	byte					  jumpStatus;
	// 	32 = приземлился / ожидает
	// 	33 = в машине(? )
	// 	34 = в воздухе
	// 	36 = приземление
	byte					  __unk_flag;
	byte					crouchStatus;
	// 	128 = стоит
	// 	132 = присел
	DWORD					  propirties;
	// 	3 = невидимость(не включая оружие)
	// 	12 = иммунитет к выстрелам в голову
	// 	20 = тонет в воде
	DWORD					 propirties2;		/* 1140 */
	// 	2 = невидимость(включая оружие)
	// 	9 = не создавать пикап оружия после смерти
	DWORD				  __unknown_1144;		/* 1144 */
	DWORD					  ptr_stAnim;		/* 1148 */
	void					*pPlayerData;		/* 1152 */

	uint8_t				__unknown_1156[8];		/* 1156 */

	// relative body-part-positions
	void						   *pNeck;		/* 1164 - void* pNeck
	(pChest?)
	- 4 unknown
	- float height
	- float front/back
	- float left/right
	- void* pObject
	(same class for the following body-part-pointers [except pLeft/RightArm])
	*/
	class CBone				   *boneHead;		/* 1168 */
	class CBone				*boneLeftArm;		/* 1172 */
	class CBone			   *boneRightArm;		/* 1176 */
	class CBone			 *pboneLeftLowArm;		/* 1180 */
	class CBone			*boneRightLowArm;		/* 1184 */
	class CBone				*boneLeftLeg;		/* 1188 */
	class CBone			   *boneRightLeg;		/* 1192 */
	class CBone			 *boneLeftLowLeg;		/* 1196 */
	class CBone			*boneRightLowLeg;		/* 1200 */
	class CBone			*boneRightMidLeg;		/* 1204 */
	class CBone			 *boneLeftMidLeg;		/* 1208 */
	class CBone			 *boneLeftMidArm;		/* 1212 */
	class CBone			*boneRightMidArm;		/* 1216 */
	class CBone		   *boneLeftShoulder;		/* 1220 */
	class CBone		  *boneRightShoulder;		/* 1224 */
	class CBone				  *boneChest;		/* 1228 */
	class CBone				  *boneMouth;		/* 1232 */
	DWORD						animGroup;
	uint8_t				__unknown_1240[4];		/* 1240 */
	float						 runspeed;		/* 1244 */
	byte				   animLoopStatus;
	// 	0 = ничего
	// 	61 = начало / остановка
	// 	62 = идёт цикл
	uint8_t			   __unknown_1249[19];		/* 1249 */
	DWORD					CurrentWeapon;		/* RpClump */
	DWORD					 muzzle_flash;		/* RpClump */
	DWORD						   Scores;		/* RpClump */
	DWORD					   ScoresType;
	DWORD		   AlphaBlendMuzzle_flash;
	DWORD		  AlphaBlendMuzzle_flash2;
	class CPedIK					PedIK;
	uint8_t				__unknown_1324[4];		/* 1324 */

	uint32_t						state;		/* 1328 - ACTOR_STATE_* */
	uint32_t					run_state;		/* 1332 - ACTOR_MSTATE_* */
	uint8_t				__unknown_1336[8];		/* 1336 */
	float						hitpoints;		/* 1344 */
	float					hitpoints_max;		/* 1348 - нужный_уровень_ХП * 5.69 */
	float							armor;		/* 1352 */
	RwV3D				   reset_position;		/* 1356 */
	float				 fCurrentRotation;		/* 1368 */
	float				  fTargetRotation;		/* 1372 */
	float				   fRotationSpeed;		/* 1376 */
	float			 fRotationCalculation;		/* 1380 - is 0.1 when target rotation reached */
	class CVehicle		 *pContactVehicle;		/* CVehicle */
	RwV3D			 vehicle_contact_dist;
	RwV3D		fPlaneAnglesContactEntity;
	CEntity					*item_contact;
	float					fUnknown_1416;		/* 1416 - only changing when slightly under map */
	union{
		class CVehicle			 *vehicle;		/* CVehicle */
		class CAutomobile	  *automobile;		/* CAutomobile */
		class CMonsterTruck       *mtruck;		/* CMonsterTruck */
		class CTrailer           *trailer;		/* CTrailer */
		class CBike                 *bike;		/* CBike */
		class CQuad                 *quad;		/* CQuad */
		class CBmx                   *bmx;		/* CBmx */
		class CHeli                 *heli;		/* CHeli */
		class CPlane               *plane;		/* CPlane */
		class CBoat                 *boat;		/* CBoat */
	};
	uint8_t				__unknown_1424[8];		/* 1424 */
	uint8_t					   actor_lock;		/* 1432 */
	uint8_t				__unknown_1433[7];		/* 1433 */
	CWeaponSlot			   WeaponSlot[13];		/* 1440 */
	DWORD				   turrelWeaponID;
	uint8_t			    __unknown_1808[8];		/* 1808 */
	uint8_t					  weapon_slot;		/* 1816 */
	uint8_t				   __unknown_1817;		/* 1817 */
	uint8_t				     AccuracyShot;
	uint8_t				   __unknown_1819;		/* 1819 */
	CObject					*targetObject;
	RwV3D				 fImpactPos_close;
	byte					 weaponSkills;
	byte					   fightStyle;
	byte					  fightStyle2;
	uint8_t				   __unknown_1839;		/* 1839 */
	DWORD						ptr_CFire;
	uint8_t			   __unknown_1836[12];		/* 1844 */
	uint32_t				 weapon_model;		/* 1856 */
	uint8_t			   __unknown_1860[18];		/* 1860 */
	WORD							money;
	uint8_t				__unknown_1880[8];		/* 1880 */
	DWORD				 killedByWeaponID;
	CPed						  *killer;
	uint8_t				__unknown_1896[4];		/* 1896 */
	RwV3D					 turrelOffset;
	float					 angleTurrelA;
	float					 angleTurrelB;
	DWORD				  vievPosInTurrel;
	DWORD					 ammoInTurrel;
	uint8_t			   __unknown_1928[20];		/* 1928 */
	CPed					 *TargetedPed;
	uint8_t			   __unknown_1952[36];		/* 1952 */

	//CPed();

	// Car methods
	bool isDriving();
	bool isDriver();
	bool isPassenger();
	bool isLeavingCar();

	bool isActorDead();
	bool isAvailable();
	bool isControlable();

	RwV3D getBonePos(byte boneId, bool includeAnim = true); // TODO: change to enumeration

	int giveWeapon(int weaponId, int ammo);
	int setAmmo(int weaponId, int ammo); // return slot
	void setActiveWeaponSlot(int slotId);
	unsigned setWeapon(int weaponId);
	void clearWeapons();
	uint8_t getWeaponSkillIndex();
	uint8_t getWeaponSkillByType(int weaponId);
	void* removeWeaponModel(int model);
	int grantAmmo(int weaponId, int ammo); // return slot
};

#define LOCAL_PLAYER (*reinterpret_cast<CPed**>(0xB6F5F0))
#define CPED_POOL_START 0xB7CD98
#define CPEDS_MAXIMUM 0xB74498
#define CPED_SIZE 0x7C4

#endif // CPED_H
