#ifndef ContextMenu_H
#define ContextMenu_H

#include <QVector>
#include "WidgetBase.h"
#include "Text.h"
//#include "Menu.h"
#include <QObject>

class CContextMenu : public CWidgetBase
{
	Q_OBJECT

	friend class CListing;
	friend class CMenu;
	friend class CNode;
	friend class CText;
	friend class CVerticalLayout;
	friend class CSlider;

	friend class proxyIDirect3DDevice9;
	friend LRESULT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CContextMenu( QObject *parent, SRColor = 0xE8283848 );
	virtual ~CContextMenu();

protected:
	virtual void onDraw( int = 0, int = 0 );
	virtual eLockEvent onEvents( HWND, UINT, WPARAM, LPARAM );

public:
	virtual bool isInizialize();

	virtual void setPosition( POINT );

	virtual void addVariant( QString, SRColor = -1 );
	virtual void setDescription( QString );

	bool operator ==( CWidgetBase* );

protected:
	QVector<CText*> _vars;

	SRColor _color;

	bool __isMouseOnVariant( int );

private:
	bool _Init;

signals:
	void eventContextMenu(CContextMenu*, int);
};

#endif // ContextMenu_H
