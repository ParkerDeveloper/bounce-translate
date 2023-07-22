#ifndef LOADER_H
#define LOADER_H

#include "llmo/ccallhook.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <wingdi.h>
#include <d3dx9core.h>
#include "d3d9/directx.h"

#include "CGame/Types.h"
#include "CGame/CPlaceable.h"
#include "CGame/CEntity.h"
#include "CGame/CPhysical.h"
#include "CGame/CObject.h"
#include "CGame/CHAnimIFrame.h"
#include "CGame/CBone.h"
#include "CGame/CPedIK.h"
#include "CGame/CParticleData.h"
#include "CGame/CWeaponSlot.h"
#include "CGame/CPed.h"
#include "CGame/CVehicle.h"
#include "CGame/CAutomobile.h"
#include "CGame/CMonsterTruck.h"
#include "CGame/CBike.h"
#include "CGame/CQuad.h"
#include "CGame/CBmx.h"
#include "CGame/CHeli.h"
#include "CGame/CPlane.h"
#include "CGame/CBoat.h"
#include "CGame/CTrailer.h"
#include "CGame/samp.h"
#include "CGame/sampfuncs.h"
#include "sys/SRKeys.h"

enum eCursorType{
	System,
	SAMP,
	Girl
};

const HANDLE INVALID_HANDLE = reinterpret_cast<HANDLE>(-1);
const char PROJECT_NAME[]   = "translator";
const eCursorType cursorType = eCursorType::SAMP;

struct stGlobalHandles{
	union{
		HANDLE samp;
		DWORD dwSAMP;
	};
	union{
		HANDLE d3d9;
		DWORD dwD3D9;
	};
};
struct stGlobalClasses{
	IDirect3D9& d3d = *reinterpret_cast<IDirect3D9*>(0xC97C20);
	D3DPRESENT_PARAMETERS* params = reinterpret_cast<D3DPRESENT_PARAMETERS*>(0xC9C040);
	stSAMP* samp = static_cast<stSAMP*>(nullptr);
	CDirectX* DirectX = static_cast<CDirectX*>(nullptr);
	SAMPFUNCS* SF = static_cast<SAMPFUNCS*>(nullptr);
	SRKeys keys;
};
struct stGlobalPVars{
	uint& gameSatate = *reinterpret_cast<uint*>(0xC8D4C0);
	bool& isMenuOpened = *reinterpret_cast<bool*>(0xBA67A4);
	byte& activeMenuID = *reinterpret_cast<byte*>(0xBA68A5);
	HWND& hwnd = *reinterpret_cast<HWND*>(0xC97C1C);

	// Vars by this plugin
	bool isLocalCursorShowed = false;
};

extern stGlobalHandles g_handle;
extern stGlobalClasses g_class;
extern stGlobalPVars g_vars;

int MessageBox(QString text, QString title = QString(PROJECT_NAME), UINT type = MB_OK);

#endif // LOADER_H
