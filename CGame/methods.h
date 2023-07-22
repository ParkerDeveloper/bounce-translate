#ifndef METHODS_H
#define METHODS_H

#include "Types.h"

void GetMatrixForGravity ( CVector& vecGravity, CMatrix& mat );
bool IsLineOfSightClear(RwV3D start, RwV3D end, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool seeThroughStuff, bool ignoreSomeObjectsForCamera);
class CPed* findPlayerPed(int handle);
bool isSphereVisible(RwV3D pos, float range);

int isModelLoaded(eModelIndex modelID);
bool requestModelLoad(eModelIndex modelID);
void loadRequestedModels(void);
void loadModel(eModelIndex modelID);
eModelIndex getWeaponModel(int weaponId);
void loadWeaponModel(int weaponId);
void loadAllWeaponModels();

#endif // METHODS_H
