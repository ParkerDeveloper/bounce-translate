#ifndef CENTITY_H
#define CENTITY_H

#include "CGame/Types.h"
#include "CGame/CPlaceable.h"

enum eEntityType
{
	ENTITY_TYPE_NOTHING,
	ENTITY_TYPE_BUILDING,
	ENTITY_TYPE_VEHICLE,
	ENTITY_TYPE_PED,
	ENTITY_TYPE_OBJECT,
	ENTITY_TYPE_DUMMY,
	ENTITY_TYPE_NOTINPOOLS
};

enum eEntityStatus
{
	STATUS_PLAYER,
	STATUS_PLAYER_PLAYBACKFROMBUFFER,
	STATUS_SIMPLE,
	STATUS_PHYSICS,
	STATUS_ABANDONED,
	STATUS_WRECKED,
	STATUS_TRAIN_MOVING,
	STATUS_TRAIN_NOT_MOVING,
	STATUS_HELI,
	STATUS_PLANE,
	STATUS_PLAYER_REMOTE,
	STATUS_PLAYER_DISABLED,
	STATUS_TRAILER,
	STATUS_SIMPLE_TRAILER
};

class CEntity : public CPlaceable
{
public:
	//CPlaceable		placeable;
	DWORD			ptr_RwObject;
	/********** BEGIN CFLAGS **************/
	unsigned long	bUsesCollision : 1;			// does entity use collision
	unsigned long	bCollisionProcessed : 1;	// has object been processed by a ProcessEntityCollision function
	unsigned long	bIsStatic : 1;			// is entity static
	unsigned long	bHasContacted : 1;		// has entity processed some contact forces
	unsigned long	bIsStuck : 1;			// is entity stuck
	unsigned long	bIsInSafePosition : 1;	// is entity in a collision free safe position
	unsigned long	bWasPostponed : 1;		// was entity control processing postponed
	unsigned long	bIsVisible : 1;			//is the entity visible
	unsigned long	bIsBIGBuilding : 1;		// Set if this entity is a big building
	unsigned long	bRenderDamaged : 1;		// use damaged LOD models for objects with applicable damage
	unsigned long	bStreamingDontDelete : 1;	// Dont let the streaming remove this
	unsigned long	bRemoveFromWorld : 1;		// remove this entity next time it should be processed
	unsigned long	bHasHitWall : 1;			// has collided with a building (changes subsequent collisions)
	unsigned long	bImBeingRendered : 1;		// don't delete me because I'm being rendered
	unsigned long	bDrawLast : 1;			// draw object last
	unsigned long	bDistanceFade : 1;		// Fade entity because it is far away
	unsigned long	bDontCastShadowsOn : 1; // Dont cast shadows on this object
	unsigned long	bOffscreen : 1;			// offscreen flag. This can only be trusted when it is set to true
	unsigned long	bIsStaticWaitingForCollision : 1;	// this is used by script created entities - they are static until the collision is loaded below them
	unsigned long	bDontStream : 1;			// tell the streaming not to stream me
	unsigned long	bUnderwater : 1;			// this object is underwater change drawing order
	unsigned long	bHasPreRenderEffects : 1;	// Object has a prerender effects attached to it
	unsigned long	bIsTempBuilding : 1;		// whether or not the building is temporary (i.e. can be created and deleted more than once)
	unsigned long	bDontUpdateHierarchy : 1;	// Don't update the aniamtion hierarchy this frame
	unsigned long	bHasRoadsignText : 1;		// entity is roadsign and has some 2deffect text stuff to be rendered
	unsigned long	bDisplayedSuperLowLOD : 1;
	unsigned long	bIsProcObject : 1;			// set object has been generate by procedural object generator
	unsigned long	bBackfaceCulled : 1;		// has backface culling on
	unsigned long	bLightObject : 1;			// light object with directional lights
	unsigned long	bUnimportantStream : 1;		// set that this object is unimportant, if streaming is having problems
	unsigned long	bTunnel : 1;			// Is this model part of a tunnel
	unsigned long	bTunnelTransition : 1;	// This model should be rendered from within and outside of the tunnel
	/********** END CFLAGS **************/

	uint8_t			wSeedColFlags;			// 0x20
	uint8_t			wSeedVisibleFlags;		// 0x21
	WORD			modelID;
	uint8_t			__unknown_36[4];		// 36 - collision related (objects only?)

	//CReferences *pReferences; //36
	uint32_t		*m_pLastRenderedLink;	// 40 CLink<CEntity*>* m_pLastRenderedLink;
	uint16_t		timer;			// 44
	uint8_t			m_iplIndex;		// 46 used to define which IPL file object is in
	uint8_t			interior_id;	// 47
	uint8_t			__unknown_48[6];		// 48

	//********* BEGIN CEntityInfo **********//
	uint8_t			nType : 3;				// 54 what type is the entity (2 == Vehicle)
	uint8_t			nStatus : 5;			// 54 control status

	// 55 alignment
	//********* END CEntityInfo **********//
	uint8_t			__unknown_56[8];		// 56
	uint8_t			quantumPhysics;			// 64 // this really needs to be figured out cos it's probably a bit field

	virtual int __add_CRect() = 0;
	virtual void add() = 0;
	virtual int /*unk, mb it void*/ remove() = 0;
	virtual void setIsStatic(bool state) = 0;
	virtual void setModelIndex(eModelIndex index) = 0;
	virtual void /*BaseModelInfo*/ *setModelIndexNoCreate(eModelIndex index) = 0;
	virtual int createRwObject() = 0;
	virtual void deleteRwObject() = 0;
	virtual CRect *getBoundRect(CRect*rect) = 0;
	virtual int processControl() = 0;
	virtual int __processCollision() = 0;
	virtual int processShift() = 0;
	virtual bool _testCollision(char a2) = 0;
	virtual bool teleport(float X, float Y, float Z, bool lockRotate = true) = 0;
	virtual bool _specialEntityPreCollisionStuff(int a1, int a2, int a3, int a4, int a5, int a6) = 0;
	virtual bool _SpecialEntityCalcCollisionSteps(int a1, int a2) = 0;
	virtual void preRender() = 0;
	virtual void render() = 0;
	virtual bool setupLighting() = 0;
	virtual bool _removeLighting(bool a2 = true) = 0;
	virtual void flagToDestroyWhenNextProcessed() = 0;

	bool isVehicle();
	bool isPed();

	bool _removeRefsToEntity(int a2);
};

#endif // CENTITY_H
