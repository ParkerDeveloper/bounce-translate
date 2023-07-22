#ifndef Listing_H
#define Listing_H

#include "VerticalLayout.h"
#include <QObject>

class CListing : public CNode
{
	Q_OBJECT

	friend class CContextMenu;
	friend class CMenu;
	friend class CText;
	friend class CVerticalLayout;
	friend class CSlider;

	friend class proxyIDirect3DDevice9;
	friend LRESULT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CListing( POINT, POINT, QObject *parent );
	~CListing();

protected:
	virtual void onDraw( int = 0, int = 0 );
	virtual eLockEvent onEvents( HWND, UINT, WPARAM, LPARAM );

public:
	virtual bool isInizialize();

	virtual void setSize( POINT );

	virtual bool addChield( CWidgetBase*, QString = "" );
	virtual bool delChield( CWidgetBase* );
	virtual bool delChield( QString );
	virtual CWidgetBase* getChield( QString );

	bool operator ==( CWidgetBase* );
	bool operator ==( CNode* );

protected:
	CVerticalLayout* _layout;

	virtual void __drawTexture( int = 0, int = 0 );

private:
	bool _Init;
};

#endif // Listing_H
