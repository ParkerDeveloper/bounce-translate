#ifndef NodeMenu_H
#define NodeMenu_H

#include <windows.h>
#include "../d3drender.h"
#include <QObject>
#define CALLBACK __stdcall

//template <class T>
//union bit32{
//	T v;
//	byte b[sizeof( T )];
//};

enum eLockEvent{
	eLe_noLock,
	eLe_lockAll,
	eLe_lockMouseMove,
	eLe_lockMouseClick,
	eLe_lockMouseScroll,
	eLe_lockKeyboard,
	eLe_lockChar
};

class CWidgetBase : public QObject
{
	Q_OBJECT

	friend class CContextMenu;
	friend class CListing;
	friend class CMenu;
	friend class CNode;
	friend class CText;
	friend class CVerticalLayout;
	friend class CSlider;

	friend class proxyIDirect3DDevice9;
	friend LRESULT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CWidgetBase( QObject *parent, POINT = { 0, 0 }, CD3DFont* = nullptr, bool = false );

	virtual ~CWidgetBase();

protected:
	virtual void onDraw( int, int );
	virtual eLockEvent onEvents( HWND, UINT, WPARAM, LPARAM );

public:
	virtual bool isInizialize();

	virtual void setPosition( POINT );
	virtual POINT position();

	virtual bool isShowed();
	virtual void setShow( bool );

	virtual bool isSelectable();
	virtual void setSelectable( bool );

	virtual int height();
	virtual int width();

	virtual void setDescription( QString );
	virtual QString description();

protected:
	CD3DFont *_font;
	CD3DRender *_draw;
	CWidgetBase *_menu;
	CWidgetBase *_parent;

	QString _description;
	POINT _pos;
	int _height; // Высота элемента, задается из наследников
	int _width; // Длина элемента, задается из наследников
	POINT _MP;
	POINT _SO;
	bool _selectable;

	POINT __getMousePos();
	virtual bool __isMouseOnWidget( int = 0, int = 0 );
	virtual void __setMousePos( POINT );
	virtual void __setMenu( CWidgetBase *menu );

private:
	bool _Init;
	bool _show;
	bool _deleteFont;

signals:
	void eventShow(CWidgetBase*, bool);
	void eventMove(CWidgetBase*, POINT);
	void eventClick(CWidgetBase*, UINT);
};

#endif // NodeMenu_H
