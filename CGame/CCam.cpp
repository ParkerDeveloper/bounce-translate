#include "CCam.h"

CEntity *CCam::GetTargetEntity() const
{
	CEntity* pReturn = NULL;

	if ( CamTargetEntity )
	{
		switch ( CamTargetEntity->nType )
		{
			case ENTITY_TYPE_PED:
				pReturn = CamTargetEntity;
				break;
			case ENTITY_TYPE_VEHICLE:
				pReturn = CamTargetEntity;
				break;
			case ENTITY_TYPE_OBJECT:
				pReturn = CamTargetEntity;
				break;
			default:
				break;
		}
	}
	return pReturn;
}
