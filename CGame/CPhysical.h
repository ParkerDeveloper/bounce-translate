#ifndef CPHYSICAL_H
#define CPHYSICAL_H

#include "CGame/Types.h"
#include "CGame/CEntity.h"

class CPhysical : public CEntity
{
public:
	//CEntity entity;
	union{
		struct{
			uint8_t __unk1_nImmunities : 1;
			uint8_t       bUsesGravity : 1;
			uint8_t __unk3_nImmunities : 1;
			uint8_t __unk4_nImmunities : 1;
			uint8_t __unk5_nImmunities : 1;
			uint8_t __unk6_nImmunities : 1;
			uint8_t __unk7_nImmunities : 1;
			uint8_t __unk8_nImmunities : 1;
		};
		uint8_t			nImmunities;			// 65
	};
	uint8_t		   __unknown_66;			// 66
	union{
		struct
		{
			uint8_t            soft : 1;
			uint8_t          freeze : 1;
			uint8_t    bullet_proof : 1;
			uint8_t      fire_proof : 1;
			uint8_t collision_proof : 1;
			uint8_t     melee_proof : 1;
			uint8_t     __unk7_flag : 1;
			uint8_t explosion_proof : 1;
		};
		uint8_t			  flags;			/* 66 immunities */
	};
	uint8_t		   __unknown_67;			/* 67 */
	RwV3D				  speed;
	RwV3D				   spin;
	RwV3D		   speed_rammed;
	RwV3D			spin_rammed;
	uint8_t	  __unknown_116[24];			/* 116 */
	float				   mass;
	float		massWhenTurning;
	float			gripDivider;
	// 1.0 = 1 x gGrip
	// 10.1 = 10 x gGrip
	// 100.0 = g / 100Grip
	float			 massToGrip;
	float			 Elasticity;
	float			   Buoyancy;
	RwV3D			 massCenter;
	void		 *__unknown_176;			/* 176 - pointer to a "entry node info" pool item */
	void		 *__unknown_180;			/* 180 - pointer to a "ptr node Double" pool item */
	byte		  __unknown_184;
	WORD		 collisionCount;
	byte		  __unknown_187;
	CPhysical  *last_collided_object;
	CPhysical  *last_collided_object2;
	CPhysical  *last_collided_object3;
	CPhysical  *last_collided_object4;
	CPhysical  *last_collided_object5;
	CPhysical  *last_collided_object6;
	float				 speed_z;			/* 212 */
	float			 damageValue;			/* 216 мб это таймер коллизии */
	CPhysical		  *damagedBy;			/* 220 он может быть CPed'ом */
	RwV3D	  collided_pos_local;
	RwV3D			collided_pos;
	WORD		   collided_part;
	// ѕримечание: ƒл€ автомобилей используютс€ следующие номера частей :
	// 		1 - капот ? (лева€ передн€€ фара ? )
	// 		2 - багажник ?
	// 		3 - передний бампер ?
	// 		4 - задний бампер ?
	// 		5 - лева€ передн€€ дверь
	// 		6 - права€ передн€€ дверь
	// 		7 - лева€ задн€€ дверь
	// 		8 - права€ задн€€ дверь
	// 		9 - левое крыло ?
	// 		10 - правое крыло ?
	// 		17 - права€ передн€€ фара ?
	CPhysical   *attachedSubject;
	RwV3D			  target_pos;
	RwV3D			target_angle;
	byte	   __unknown_280[16];
	CPhysical   *collide_ignored;
	float			  lightLevel;
	DWORD		   __unknown_304;
	DWORD			*CShadowData;

	virtual int processEntityCollision(CEntity *pEntity, char *pColPoint) = 0;

	float getSpeed();
	void setSpeed(RwV3D spd);

	void applyMoveForce(RwV3D mov);
	void applyGravityForce(RwV3D a, CVector b, char a4 = 1);

	void stickToPlace();
};

#endif // CPHYSICAL_H
