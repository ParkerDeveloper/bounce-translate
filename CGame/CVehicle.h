#ifndef CVEHICLE_H
#define CVEHICLE_H

#include "CGame/Types.h"
#include "CGame/CPhysical.h"

#pragma pack(push, 1)
class CVehicle : public CPhysical
{
public:
	//CPhysical				   physical;
	void						*__unknown_316;			/* 316 - pointer to this something in this classure */
	uint8_t						__unknown_320[157];		/* 320 */
	uint8_t						in_vehicle;			/* 477 */
	uint8_t						__unknown_478[422]; /* 478 */

	void						*pHandlingData;		/* 900 */
	class physicalFlyParams	*pFlyData;			/* 904 */
	uint8_t						__unknown_908[96];	/* 908 */
	uint32_t					hFlagsLocal;		/* 1004 */
	uint8_t						__unknown_1008[56]; /* 1008 - AutoPilot */
	uint8_t						m_nVehicleFlags[8];	/* 1064 - 60 bits/flags */
	uint32_t					m_TimeOfCreation;	/* 1072 - GetTimeInMilliseconds when this vehicle was created. */

	uint8_t						color[4];			/* 1076 - as in carcolors.dat - body, stripe, body2, stripe2 */
	uint8_t						modding[2];			/* 1080 - modding data */
	unsigned short				UpgradeModelID[15];	/* 1082 - attached upgrades */
	float						wheel_size;			/* 1112 */
	unsigned short				CarAlarmState;		/* 1116 - time left for car alarm to sound in ms */
	unsigned short				ForcedRandomSeed;	/* 1118 - if this is non-zero the random wander gets deterministic */

	class CPed					*driver;
	class CPed					*passenger_FrontRight; //Переднее правое сиденье
	class CPed					*passenger_RearLeft; //Заднее левое сиденье
	class CPed					*passenger_RearRight; //Заднее правое сиденье
	class CPed					*passengers_additional[5]; //Для автобусов

	unsigned char				m_nNumPassengers;	/* 1156 */
	unsigned char				m_nNumGettingIn;	/* 1157 */
	unsigned char				m_nGettingInFlags;	/* 1158 */
	unsigned char				m_nGettingOutFlags; /* 1159 */
	unsigned char				m_nMaxPassengers;	/* 1160 */
	unsigned char				m_windowsOpenFlags; /* 1161 */
	char						m_nNitroBoosts;		/* 1162 */
	char						m_nSpecialColModel; /* 1163 */
	DWORD						*pEntityWeAreOnForVisibilityCheck;	/* 1164 - we need a CEntity */
	DWORD						*m_pFire;			/* 1168 - CFire*/

	float						steer_angles[2];	/* 1172 - steer angles */
	float						gas_pedal;			/* 1180 - gas pedal */
	float						break_pedal;		/* 1184 - break pedal */

	// 1188
	unsigned char				VehicleCreatedBy;	// Contains information on whether this vehicle can be deleted or not. Probably only need this or IsLocked.
	short						ExtendedRemovalRange;

	// this padding probably isn't in the right place.
	uint8_t						__unknown_1191;

	//1192
	unsigned char				car_bomb : 3;		// 0 = None. 1 = Timed. 2 = On ignition, 3 = remotely set ? 4 = Timed Bomb has been activated. 5 = On ignition has been activated.
	unsigned char				OverrideLights : 2; // uses enum NO_CAR_LIGHT_OVERRIDE, FORCE_CAR_LIGHTS_OFF, FORCE_CAR_LIGHTS_ON
	unsigned char				WinchType : 2;		// Does this vehicle use a winch?

	// this padding probably isn't in the right place.
	uint8_t						__unknown_1193;

	//1194
	unsigned char				m_GunsCycleIndex : 2;		// Cycle through alternate gun hardpoints on planes/helis
	unsigned char				m_OrdnanceCycleIndex : 2;	// Cycle through alternate ordnance hardpoints on planes/helis

	// 1195
	unsigned char				nUsedForCover;			// Has n number of cops hiding/attempting to hid behind it
	unsigned char				AmmoInClip;				// Used to make the guns on boat do a reload.
	unsigned char				PacMansCollected;
	unsigned char				PedsPositionForRoadBlock;
	unsigned char				NumPedsForRoadBlock;

	//1200
	float						nBodyDirtLevel;			// Dirt level of vehicle body texture: 0.0f=fully clean, 15.0f=maximum dirt visible, it may be altered at any time while vehicle's cycle of lige

	// values used by transmission
	unsigned char				m_nCurrentGear;			/* 1204 */
	float						m_fGearChangeCount;		/* 1205 */
	float						m_fWheelSpinForAudio;	/* 1209 */
	uint8_t						__unknown_1213[3];		/* 1213 */

	float						hitpoints;			/* 1216 */
	void						*pulling_truck;		/* 1220 - vehicle_info - pulling truck */
	class vehicle_info			*trailer;			/* 1224 - pointer to the currently attached trailer; 0 if theres no trailer */
	uint8_t						__unknown_1228[44]; /* 1228 */
	uint32_t					door_status;		/* 1272 - car door status (1:Opened 2:Locked) */
	uint8_t						__unknown_1276[148];	/* 1276 */
	uint8_t						vehicle_type;			/* 1424 - VEHICLE_TYPE_* */
	uint8_t						__unknown_1425[19];		/* 1425 */

	union
	{
		struct
		{
			float	m_fTrainSpeed;			/* 1444 - Train speed along rails */
			float	m_fTrainRailDistance;	/* 1448 - Distance along rail starting from first rail node (determines train position when on rails) -max 18106 */
			float	m_fDistanceToNextCarriage;		/* 1452 - Distance to Carriage being infront of this */
		};
		struct
		{
			uint8_t boat_sound_level;				/* 1444 */
			uint8_t car_tire_status[4];				/* 1445 - LF, LR, RF, RR, 0 = ok, 1 = flat, 2 = landing gear up */
			uint8_t door_damage_status[6];			/* 1449 - damage status of doors, 0 = ok, 2 = damaged, 3 = open free, 4 = lost */
		};
	};

	// light damage states
	//uint8_t			lights;						/* 1456 - Light status, 0 = no dmg, 1 = front left dmg, 4 = front right dmg, 5 = front dmg, ...+0x40 = ...+back dmg */
	unsigned char		lights_status_frontLeft : 1;
	unsigned char		__unknown_lights_status_2 : 1;
	unsigned char		lights_status_frontRight : 1;
	unsigned char		__unknown_lights_status_4 : 3;
	unsigned char		lights_status_rear : 1;

	// end of light damage states
	uint8_t				__unknown_1457[3];			/* 1457 - 1475 related to doorHood (byte??)*/

	// misc damage states
	unsigned char		car_status_left : 4;		/* 1460 - 0 = ok, 1 = damaged, 2 = free movement, 3 = lost - same status codes for following bumper/windshield */
	unsigned char		car_status_right : 4;
	uint8_t				car_bumper_status;			/* 1461 - unknown */
	unsigned char		car_windshield_status : 4;
	unsigned char		car_bumper_status_front : 4;
	uint8_t				car_bumper_status_rear;
	// end of misc damage states

	uint8_t				m_trainFlags[4];			/* 1464 */
	uint8_t				__unknown_1468[8];			/* 1468 */
	float				doorHood_dist;				/* 1476 - positive = open */
	uint8_t				__unknown_1480[4];			/* 1480 - detachable related*/
	float				doorHood_dist_two;			/* 1484 - positive = open*/
	uint8_t				__unknown_1488[4];			/* 1488 */
	class vehicle_info *m_train_next_carriage;		/* 1492 */
	uint8_t				__unknown_1496[4];			/* 1496 */
	float				doorTrunk_dist;				/* 1500 - negative = open */
	uint8_t				__unknown_1504[4];			/* 1504 */
	float				doorTrunk_dist_two;			/* 1508 - negative = open */
	uint8_t				__unknown_1512[12];			/* 1512 */
	float				doorOne_dist;				/* 1524 - also for movable part of boats (marquis)*/
	uint8_t				__unknown_1528[4];			/* 1528 */
	union
	{
		struct Detachable	detachable_bike1[1];	/* 1532 - bike/motorcycle/car part */
		struct
		{
			float	doorOne_dist_two;			/* 1532 - negative = open */
			uint8_t __unknown_1536[12];			/* 1536 */
			float	doorTwo_dist;				/* 1548 - positive = open */
			uint8_t __unknown_1552[4];			/* 1552 */
			float	doorTwo_dist_two;			/* 1556  - positive = open */
			uint8_t __unknown_1560[12];			/* 1560 */
			float	doorThree_dist;				/* 1572 - negative = open */
			uint8_t __unknown_1576[4];			/* 1576 */
			float	doorThree_dist_two;			/* 1580 - negative = open */
			uint8_t __unknown_1584[12];			/* 1584 */
			float	doorFour_dist;				/* 1596 - positive = open */
			uint8_t __unknown_1600[6];			/* 1600 */
			float	doorFour_dist_two;			/* 1606 - positive = open */
		};
	};
	uint8_t				__unknown_1610[18];		/* 1610 */
	uint8_t				bike_tire_status[2];	/* 1628 Front, Rear, 0 = ok, 1 = flat */
	uint8_t				__unknown_1630[2];		/* 1630 */

	//maybe also door positions in here, like in 15xx?
	struct Detachable	detachable_bike2[4];	/* 1632 - bike/motorcycle and boat parts */
	uint8_t				__unknown_1808[8];		/* 1808 */
	float				fPos_FireCarLadder[3];	/* 1816 - train ladder positioning (part of detachables?) */
	struct Detachable	detachable_car[4];		/* 1828 - car/helicopter/airplane parts */
	uint8_t				__unknown_2004[12];		/* 2004 */
	float				suspension[4];			/* 2016 - FL, RL, FR, RR suspension height */
	uint8_t				__unknown_2032[92];	/* 2032 */
	float				fHeliRotorSpeed;	/* 2124 */
	uint8_t				__unknown_2128[84];	/* 2128 */
	float			   fNitroValue;			/* 2212 */
	uint8_t				__unknown_2216[60];	 /* 2216 */
	float				burn_timer;				/* 2276 - burn timer counting up from 0.0f */
	uint8_t				__unknown_2280[100];	/* 2280 */
	float				fCannonAimX_Y[2];		/* 2380 - cannon offset (x/y) */
	uint8_t				__unknown_2388[48];		/* 2388 */
	float				fHeliDistanceToGround;	/* 2436 - (between 0.9 and 1 = touching ground) */
	uint8_t				__unknown_2440[24];		/* 2440 */
	float				fHeliMainRotorDistance;	/* 2464 - distance/rotation */
	float				fHeliSecRotorDistance;	/* 2468 - distance/rotation secondary rotor */
	uint8_t				__unknown_2472[88];		/* 2472 */
	uint8_t				SmokeTrailEnabled;		/* 2560 */
	uint8_t				__unknown_2561[23];		/* 2561 */
	/* 2584 */

	virtual void _processControlCollisionCheck(char a1) = 0;
	virtual void _processControlInputs(bool a2) = 0;
	virtual void getComponentWorldPosition(int id, RwV3D *pos) = 0;
	virtual bool isComponentPresent(int id) = 0;
	virtual bool _openDoor(int a2, int a3, int a4, float a5, char a6) = 0;
	virtual void _processOpenDoor(int a2, float a3, float a4, float a5, float a6) = 0;
	virtual long double getDoorAngleOpenRatio(int id) = 0;
	virtual void _getDoorAngleOpenRatio(int id) = 0;
	virtual bool isDoorReady(int id) = 0;
	virtual bool _isDoorReady(int id) = 0;
	virtual bool isDoorFullyOpen(int id) = 0;
	virtual bool _isDoorFullyOpen(int id) = 0;
	virtual bool isDoorClosed(int id) = 0;
	virtual bool _isDoorClosed(int id) = 0;
	virtual bool isDoorMissing(int id) = 0;
	virtual bool _isDoorMissing(int id) = 0;
	virtual bool isOpenTopCar() = 0;
	virtual void _removeRefsToVehicle(int a1) = 0;
	virtual void _blowUpCar(int frame, bool a2) = 0;
	virtual void _blowUpCarCutSceneNoExtras(int a1, int a2, int a3, int a4) = 0;
	virtual bool _setUpWheelColModel(int a1) = 0;
	virtual bool _burstTyre(byte nWheel, bool a3) = 0;
	virtual bool __isRoomForPedToLeaveCar() = 0;
	virtual void _processDrivingAnims(class CPed* ped, bool a3) = 0;
	virtual char* getRideAnimData() = 0;
	virtual void setupSuspensionLines() = 0;
	virtual RwV3D* _addMovingCollisionSpeed(RwV3D *a2, RwV3D *a3) = 0;
	virtual void fix() = 0;
	virtual int setupDamageAfterLoad() = 0;
	virtual void doBurstAndSoftGroundRatios() = 0;
	virtual long double getHeightAboveRoad() = 0;
	virtual bool playCarHorn() = 0;
	virtual int getNumContactWheels() = 0;
	virtual void _vehicleDamage(int a1, int a2, int a3, int a4, int a5, int a6) = 0;
	virtual bool _canPedStepOutCar(char a2) = 0;
	virtual bool canPedJumpOutCar(byte passengerId) = 0;
	virtual bool getTowHitchPos(RwV3D* pos, bool get, CEntity *pEntity) = 0;
	virtual bool getTowBarPos(RwV3D* pos, bool get, CEntity *pEntity) = 0;
	virtual bool SetTowLink(CEntity *pEntity, bool set) = 0;
	virtual bool breakTowLink() = 0;
	virtual long double _findWheelWidth(bool a1) = 0;
	virtual bool save() = 0;
	virtual bool load() = 0;

	void repair();

	bool isBoat();
	bool isCar();
	bool isTrain();
	bool isHeli();
	bool isPlane();
	bool isBike();
	bool isFakePlane();
	bool isMonsterTruck();
	bool isQuadBike();
	bool isBmx();
	bool isTrailer();

	bool lock();
	float setAngularVelocity(RwV3D angularVelocity);
};
#pragma pack(pop)

#define LOCAL_VEHICLE (CPed*)*(DWORD*)0xBA18FC
#define CVEHICLE_POOL_START 0xC502AA0
#define CVEHICLE_SIZE 0xA18

#endif // CVEHICLE_H
