#include "WidgetBase.h"
#include "Menu.h"
#include "../proxydirectx.h"

CWidgetBase::CWidgetBase( QObject *parent, POINT pos, CD3DFont *font, bool deleteOnDestructor ) : QObject( parent )
{
	_pos = pos;
	_show = true;
	_menu = nullptr;
	_parent = (CNode*)parent;
	_SO = { 0, 0 };
	_selectable = true;

	if ( font != nullptr ){
		_font = font;
		_deleteFont = deleteOnDestructor;
	}
	else {
		_font = g_class.DirectX->d3d9_CreateFont( "Arial", 10, FCR_BORDER );
		_deleteFont = true;
	}
	_draw = g_class.DirectX->d3d9_CreateRender( 40 );

	_Init = false;
}

CWidgetBase::~CWidgetBase()
{
	if ( _deleteFont )
		g_class.DirectX->d3d9_ReleaseFont( _font );
	g_class.DirectX->d3d9_ReleaseRender( _draw );
}
void CWidgetBase::onDraw( int so_V, int so_H )
{
	if ( !isInizialize() )
		return;

	_SO.x = so_H;
	_SO.y = so_V;

	if ( __isMouseOnWidget( so_V, so_H ) && _menu != nullptr ){

		if ( ((CMenu*)_menu)->isActive() ){

			if ( _menu != this && _selectable && _parent != _menu )
				_draw->D3DBoxBorder( _pos.x - so_H - 1, _pos.y - so_V - 1, _width + 2, _height + 2, ((CNode*)_parent)->colorBkg().invert(), 0 );

			if ( !_description.isEmpty() )
				((CMenu*)_menu)->__setMenuHelper( _description );
		}
	}
}

eLockEvent CWidgetBase::onEvents( HWND, UINT uMsg, WPARAM, LPARAM )
{
	if ( !__isMouseOnWidget( _SO.y, _SO.x ) )
		return eLe_noLock;

	switch ( uMsg )
	{
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
			emit eventClick( this, uMsg );
			return eLe_lockMouseClick;
		default:
			break;
	}

	return eLe_noLock;
}

bool CWidgetBase::isInizialize()
{
	if ( _Init )
		return true;

	if ( g_class.DirectX->d3d9_device() == nullptr )
		return false;

	_Init = true;
	return true;
}

void CWidgetBase::setPosition( POINT pos )
{
	_pos = pos;
	emit eventMove( this, _pos );
}

POINT CWidgetBase::position()
{
	return _pos;
}

bool CWidgetBase::isShowed()
{
	return _show;
}

void CWidgetBase::setShow( bool show )
{
	_show = show;
	emit eventShow(this, show);
}

bool CWidgetBase::isSelectable()
{
	return _selectable;
}

void CWidgetBase::setSelectable( bool selectable )
{
	_selectable = selectable;
}

int CWidgetBase::height()
{
	return _height;
}

int CWidgetBase::width()
{
	return _width;
}

POINT CWidgetBase::__getMousePos()
{
	POINT M;
	GetCursorPos( &M );
	ScreenToClient( *(HWND*)0xC97C1C, &M );
	return M;
}

void CWidgetBase::__setMousePos( POINT MP )
{
	_MP = MP;
}

bool CWidgetBase::__isMouseOnWidget( int so_V, int so_H )
{
	POINT M = _MP;
	int PX = _pos.x - so_H;
	int PY = _pos.y - so_V;
	if ( M.x > PX && M.x < PX + _width && M.y > PY && M.y < PY + _height )
		return true;
	return false;
}

void CWidgetBase::setDescription( QString description )
{
	_description = description;
}

QString CWidgetBase::description()
{
	return _description;
}

void CWidgetBase::__setMenu( CWidgetBase *menu )
{
	_menu = menu;
	_parent = ((CMenu*)_menu)->node();
}
