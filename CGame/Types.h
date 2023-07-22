#ifndef TYPES_H
#define TYPES_H

#include <windows.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef class RwV3D CVector;
typedef class RwV3D VECTOR;
typedef class RwMatrix CMatrix;
typedef const unsigned CU;

struct Quaternion;

class RwV3D
{
public:
	float fX, fY, fZ;

	RwV3D(float X = 0.0f, float Y = 0.0f, float Z = 0.0f);

	void clear();
	void normalize();

	float length();
	float angle();
	float angle(float X, float Y);
	float angle(RwV3D r);

	float DotProduct ( const CVector * param ) const;
	void CrossProduct ( const CVector * param );


	RwV3D operator + ( const RwV3D& vecRight ) const
	{
		return RwV3D ( fX + vecRight.fX, fY + vecRight.fY, fZ + vecRight.fZ );
	}
	RwV3D operator - ( const RwV3D& vecRight ) const
	{
		return RwV3D ( fX - vecRight.fX, fY - vecRight.fY, fZ - vecRight.fZ );
	}
	RwV3D operator * ( const RwV3D& vecRight ) const
	{
		return RwV3D ( fX * vecRight.fX, fY * vecRight.fY, fZ * vecRight.fZ );
	}
	RwV3D operator * ( float fRight ) const
	{
		return RwV3D ( fX * fRight, fY * fRight, fZ * fRight );
	}
	RwV3D operator / ( const RwV3D& vecRight ) const
	{
		return RwV3D ( fX / vecRight.fX, fY / vecRight.fY, fZ / vecRight.fZ );
	}
	RwV3D operator / ( float fRight ) const
	{
		return RwV3D ( fX / fRight, fY / fRight, fZ / fRight );
	}
	RwV3D operator - () const
	{
		return RwV3D ( -fX, -fY, -fZ );
	}

	void operator += ( float fRight )
	{
		fX += fRight;
		fY += fRight;
		fZ += fRight;
	}
	void operator += ( const RwV3D& vecRight )
	{
		fX += vecRight.fX;
		fY += vecRight.fY;
		fZ += vecRight.fZ;
	}
	void operator -= ( float fRight )
	{
		fX -= fRight;
		fY -= fRight;
		fZ -= fRight;
	}
	void operator -= ( const RwV3D& vecRight )
	{
		fX -= vecRight.fX;
		fY -= vecRight.fY;
		fZ -= vecRight.fZ;
	}
	void operator *= ( float fRight )
	{
		fX *= fRight;
		fY *= fRight;
		fZ *= fRight;
	}
	void operator *= ( const RwV3D& vecRight )
	{
		fX *= vecRight.fX;
		fY *= vecRight.fY;
		fZ *= vecRight.fZ;
	}
	void operator /= ( float fRight )
	{
		fX /= fRight;
		fY /= fRight;
		fZ /= fRight;
	}
	void operator /= ( const RwV3D& vecRight )
	{
		fX /= vecRight.fX;
		fY /= vecRight.fY;
		fZ /= vecRight.fZ;
	}

	bool operator== ( const RwV3D& param ) const
	{
		return ( fX == param.fX && fY == param.fY && fZ == param.fZ );
	}
	bool operator!= ( const RwV3D& param ) const
	{
		return !( fX == param.fX && fY == param.fY && fZ == param.fZ );
	}
};

class RwMatrix
{
public:
	RwV3D	right;
	DWORD	flags;
	RwV3D	up;
	float	pad_u;
	RwV3D	at; // front
	float	pad_a;
	RwV3D	pos;
	float	pad_p;

	RwMatrix();
	RwMatrix(const RwMatrix &);
	RwMatrix(Quaternion q);

	void setQuaternion(Quaternion quater);
	Quaternion quaternion();
	void invert ();
	RwMatrix rotate ( const RwV3D * param, float theta );


	RwMatrix operator+ ( const RwMatrix& other ) const
	{
		RwMatrix matResult;
		matResult.right = right + other.right;
		matResult.at = at + other.at;
		matResult.up	= up	+ other.up;
		matResult.pos   = pos   + other.pos;
		return matResult;
	}
	RwMatrix operator- ( const RwMatrix& other ) const
	{
		RwMatrix matResult;
		matResult.right = right - other.right;
		matResult.at = at - other.at;
		matResult.up	= up	- other.up;
		matResult.pos   = pos   - other.pos;
		return matResult;
	}
	RwMatrix operator* ( const RwMatrix& other ) const
	{
		RwMatrix matResult;
		matResult.right = (*this) * other.right;
		matResult.at = (*this) * other.at;
		matResult.up	= (*this) * other.up;
		matResult.pos   = (*this) * other.pos;
		return matResult;
	}
	RwMatrix operator/ ( RwMatrix other ) const
	{
		other.invert ();
		return (*this) * other;
	}
	RwV3D operator* ( const RwV3D& vec ) const
	{
		return CVector (
					right.fX*vec.fX + at.fX*vec.fY + up.fX*vec.fZ,
					right.fY*vec.fX + at.fY*vec.fY + up.fY*vec.fZ,
					right.fZ*vec.fX + at.fZ*vec.fY + up.fZ*vec.fZ
					);
	}

private:
	void QuaternionToMatrix(Quaternion &quater);
};

struct CompressedVector
{
	WORD wX, wY, wZ;
};

struct Quaternion
{
	float fW, fX, fY, fZ;
};

struct Detachable
{
	RwV3D	position;
	uint8_t __unknown_12[4];
	RwV3D	vector;
	uint8_t __unknown_28[16];
};

struct CRect
{
	float l;
	float t;
	float r;
	float b;
};

enum eModelIndex{
	ped_cj = 0,
	ped_male01 = 7,

	car_landstal = 400,
	car_bravura = 401,
	car_buffalo = 402,
	car_linerun = 403,
	car_peren = 404,
	car_sentinel = 405,
	spec_car_firetruk = 407, //Пожарка с водой
	car_trash = 408,
	car_stretch = 409,
	car_manana = 410,
	car_infernus = 411,
	car_voodoo = 412,
	car_pony = 413,
	car_mule = 414,
	car_cheetah = 415,
	spec_car_ambulan = 416,
	car_moonbeam = 418,
	car_esperant = 419,
	car_taxi = 420,
	car_washing = 421,
	car_bobcat = 422,
	car_mrwhoop = 423,
	car_bfinject = 424,
	car_premier = 426,
	spec_car_enforcer = 427,
	car_securica = 428,
	car_banshee = 429,
	car_bus = 431,
	spec_army_car_rhino = 432,
	car_barracks = 433,
	car_hotknife = 434,
	car_previon = 436,
	car_coach = 437,
	car_cabbie = 438,
	car_stallion = 439,
	car_rumpo = 440,
	mini_car_rcbandit = 441,
	car_romero = 442,
	car_packer = 443,
	car_admiral = 445,
	car_turismo = 451,
	car_flatbed = 455,
	car_yankee = 456,
	car_caddy = 457,
	car_solair = 458,
	car_topfun = 459,
	car_glendale = 466,
	car_oceanic = 467,
	car_patriot = 470,
	car_hermes = 474,
	car_sabre = 475,
	car_zr350 = 477,
	car_walton = 478,
	car_regina = 479,
	car_comet = 480,
	car_burrito = 482,
	car_camper = 483,
	car_baggage = 485,
	spec_car_dozer = 486,
	car_rancher = 489,
	spec_polici_car_fbiranch = 490,
	car_virgo = 491,
	car_greenwoo = 492,
	car_hotring = 494,
	car_sandking = 495,
	car_blistac = 496,
	car_boxville = 498,
	car_benson = 499,
	car_mesa = 500,
	car_hotrina = 502,
	car_hotrinb = 503,
	car_bloodra = 504,
	car_rnchlure = 505,
	car_supergt = 506,
	car_elegant = 507,
	car_journey = 508,
	car_petro = 514,
	car_rdtrain = 515,
	car_nebula = 516,
	car_majestic = 517,
	car_buccanee = 518,
	spec_car_cement = 524,
	spec_car_towtruck = 525,
	car_fortune = 526,
	car_cadrona = 527,
	spec_polici_car_fbitruck = 528,
	car_willard = 529,
	spec_car_forklift = 530,
	car_tractor = 531,
	spec_car_combine = 532,
	car_feltzer = 533,
	car_remingtn = 534,
	car_slamvan = 535,
	car_blade = 536,
	car_vincent = 540,
	car_bullet = 541,
	car_clover = 542,
	car_sadler = 543,
	car_firela = 544, //Пожарка
	car_hustler = 545,
	car_intruder = 546,
	car_primo = 547,
	car_cargobob = 548,
	car_tampa = 549,
	car_sunrise = 550,
	car_merit = 551,
	car_utility = 552,
	car_yosemite = 554,
	car_windsor = 555,
	car_uranus = 558,
	car_jester = 559,
	car_sultan = 560,
	car_stratum = 561,
	car_elegy = 562,
	mini_car_rctiger = 564, //Мини-танк
	car_flash = 565,
	car_tahoma = 566,
	car_savanna = 567,
	car_bandito = 568,
	spec_car_kart = 571,
	car_mower = 572, //Газонокосилка
	car_sweeper = 574,
	car_broadway = 575,
	car_tornado = 576,
	car_dft30 = 578,
	car_huntley = 579,
	car_stafford = 580,
	car_newsvan = 582,
	car_tug = 583,
	car_emperor = 585,
	car_euros = 587,
	car_hotdog = 588,
	car_club = 589,
	mini_polici_car_rccam = 594, //Ведро
	spec_polici_car_copcarla = 596,
	spec_polici_car_copcarsf = 597,
	spec_polici_car_copcarvg = 598,
	spec_polici_car_copcarru = 599,
	car_picador = 600,
	car_swatvan = 601,
	car_alpha = 602, //use
	car_phoenix = 603,
	car_glenshit = 604,
	car_sadlshit = 605,
	car_boxburg = 609,

	mtruck_dumper = 406,
	mtruck_monster = 444,
	mtruck_monstera = 556,
	mtruck_monsterb = 557,
	mtruck_duneride = 573,

	bike_pizzaboy = 448,
	bike_pcj600 = 461,
	bike_faggio = 462,
	bike_freeway = 463,
	bike_sanchez = 468,
	bike_fcr900 = 521,
	bike_nrg500 = 522,
	spec_polici_bike_copbike = 523,
	bike_bf400 = 581,
	bike_wayfarer = 586,

	quad_quad = 471,

	bmx_bmx = 481,
	bmx_bike = 509,
	bmx_mtbike = 510,

	heli_leviathn = 417,
	spec_army_heli_hunter = 425,
	spec_army_heli_seaspar = 447,
	mini_heli_rcraider = 465,
	heli_sparrow = 469,
	heli_maverick = 487,
	heli_vcnmav = 488,
	fuck_heli_polmav = 497,
	mini_heli_rcgoblin = 501,
	heli_cargobob = 548,
	heli_raindanc = 563,

	plane_skimmer = 460,
	mini_plane_rcbaron = 464,
	spec_army_plane_rustler = 476,
	plane_beagle = 511,
	spec_plane_cropdust = 512,
	spec_plane_stunt = 513,
	plane_shamal = 519,
	spec_army_plane_hydra = 520,
	plane_nevada = 553,
	plane_at400 = 577,
	plane_androm = 592,
	plane_dodo = 593,

	universal_vortex = 539,

	spec_polici_boat_predator = 430,
	boat_squalo = 446,
	boat_speeder = 452,
	boat_reefer = 453,
	boat_tropic = 454,
	boat_coastg = 472,
	boat_dinghy = 473,
	boat_marquis = 484,
	boat_jetmax = 493,
	boat_launch = 595,

	train_tram = 449,
	train_freight = 537,
	train_streak = 538,
	train_freiflat = 569,
	train_streakc = 570,
	train_freibox = 590,

	trailer_artict1 = 435,
	trailer_artict2 = 450,
	trailer_petrotr = 584,
	trailer_artict3 = 591,
	trailer_bagboxa = 606,
	trailer_bagboxb = 607,
	trailer_tugstair = 608,
	trailer_farmtr1 = 610,
	trailer_utiltr1 = 611,


	weapon_BrassKnuckles = 331,
	weapon_GolfClub = 333,
	weapon_Nitestick,
	weapon_Knife,
	weapon_BaseballBat,
	weapon_Shovel,
	weapon_PoolCue,
	weapon_Katana,
	weapon_Chainsaw = 341,
	weapon_Grenade,
	weapon_Teargas,
	weapon_MolotovCocktail,
	weapon_Pistol = 346,
	weapon_SilencedPistol,
	weapon_DesertEagle,
	weapon_Shotgun,
	weapon_SawnOffShotgun,
	weapon_SPAZ12,
	weapon_MicroUZI,
	weapon_MP5,
	weapon_AK47 = 355,
	weapon_M4,
	weapon_CountryRifle,
	weapon_SniperRifle,
	weapon_RocketLauncher,
	weapon_HeatSeekingRPG,
	weapon_FlameThrower,
	weapon_Minigun,
	weapon_RemoteExplosives,
	weapon_Detonator,
	weapon_SprayCan,
	weapon_FireExtinguisher,
	weapon_Camera,
	weapon_Dildo1 = 321,
	weapon_Dildo2,
	weapon_Vibe1,
	weapon_Vibe2,
	weapon_Flowers,
	weapon_Cane,
	weapon_NVGoggles = 368,
	weapon_IRGoggles,
	weapon_Parachute = 371,
	weapon_Tech9
};

#endif // TYPES_H
