#ifndef CBONE_H
#define CBONE_H

#include "CGame/Types.h"
#include "CGame/CHAnimIFrame.h"

class CBone
{
public:
	BYTE          m_bFlags;
	RwV3D         m_vOffset;  // Статичное смещение относительно родительской кости
	CHAnimIFrame *m_pIFrame;  // Указатель на структуру, которая содержит интерполированные данные о положении кости
	DWORD         m_dwNodeId; // Специальный идентификатор кости
};

#endif // CBONE_H
