#ifndef VerticalLayout_H
#define VerticalLayout_H

#include "Node.h"
#include <QObject>

class CVerticalLayout : public CNode
{
	Q_OBJECT

	friend class CContextMenu;
	friend class CListing;
	friend class CMenu;
	friend class CText;
	friend class CSlider;

	friend class proxyIDirect3DDevice9;
	friend LRESULT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CVerticalLayout( QObject *parent, POINT = { 0, 0 } );

protected:
	virtual void onDraw( int = 0, int = 0 );
	virtual eLockEvent onEvents( HWND, UINT, WPARAM, LPARAM );

public:
	virtual void setPosition( POINT );
	virtual void setSize( POINT );

	virtual bool addChield( CWidgetBase*, QString = "" );
	virtual bool delChield( CWidgetBase* );
	virtual bool delChield( QString );

	bool operator ==( CWidgetBase* );
	bool operator ==( CNode* );

protected:
	void __drawLayout( int = 0, int = 0 );
	virtual void __drawTexture( int = 0, int = 0 );

private:
	bool _Init;
};

#endif // VerticalLayout_H
