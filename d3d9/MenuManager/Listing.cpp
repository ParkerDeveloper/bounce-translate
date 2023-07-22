#include "Listing.h"

CListing::CListing( POINT pos, POINT size, QObject *parent ) : CNode( parent, pos, size )
{
	if (parent == nullptr)
		throw "Parent for CListing can't be null";
	_height = size.y;
	_width = size.x + 6;
	_size = size;
	_Init = false;
	_layout = new CVerticalLayout(this);
}

CListing::~CListing()
{
	//delete _layout;
}

void CListing::onDraw( int so_V, int so_H )
{
	if ( !isInizialize() )
		return;

	if (__isMouseOnWidget(so_V, so_H)){
		__drawTexture( so_V, so_H );
	}
	_texture->Render( _pos.x - so_H, _pos.y - so_V );
	__drawScrollBarVertical( so_V, so_H );
	CWidgetBase::onDraw( so_V, so_H );
}

eLockEvent CListing::onEvents( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if ( !__isMouseInNode( _SO.y, _SO.x ) )
		return eLe_noLock;

	eLockEvent layoutEv = _layout->onEvents( hwnd, uMsg, wParam, lParam );
	if ( layoutEv != eLe_noLock )
		return layoutEv;

	switch ( uMsg )
	{
		case WM_MOUSEWHEEL:
			if ( GET_WHEEL_DELTA_WPARAM( wParam ) < 0 ){
				_scrollOffsetVertical += _scrollStep;
				if ( _scrollOffsetVertical + _size.y > _scrollSizeVertical )
					_scrollOffsetVertical = _scrollSizeVertical - _size.y;
			}
			else{
				_scrollOffsetVertical -= _scrollStep;
				if ( _scrollOffsetVertical < 0 )
					_scrollOffsetVertical = 0;
			}
			return eLe_lockMouseScroll;
		case WM_KEYDOWN:
			switch ( wParam )
			{
				case VK_UP:
					_scrollOffsetVertical -= _scrollStep;
					if ( _scrollOffsetVertical < 0 )
						_scrollOffsetVertical = 0;
					return eLe_lockKeyboard;
				case VK_DOWN:
					_scrollOffsetVertical += _scrollStep;
					if ( _scrollOffsetVertical + _size.y > _scrollSizeVertical )
						_scrollOffsetVertical = _scrollSizeVertical - _size.y;
					return eLe_lockKeyboard;
				case VK_PRIOR:
					_scrollOffsetVertical = 0;
					return eLe_lockKeyboard;
				case VK_NEXT:
					_scrollOffsetVertical = _scrollSizeVertical - _size.y;
					return eLe_lockKeyboard;
				default:
					break;
			}
			break;
		default:
			break;
	}

	return CWidgetBase::onEvents( hwnd, uMsg, wParam, lParam );
}

bool CListing::isInizialize()
{
	if ( _Init )
		return true;

	if ( !CNode::isInizialize() )
		return false;

	if ( _menu == nullptr )
		return false;

	_layout->__setMenu( _menu );

	_Init = true;
	return true;
}

void CListing::setSize( POINT size )
{
	size.x = _width - 6;
	CNode::setSize( size );
}

bool CListing::addChield( CWidgetBase* node, QString name )
{
	return _layout->addChield( node, name );
}

bool CListing::delChield( CWidgetBase* node )
{
	return _layout->delChield( node );
}

bool CListing::delChield( QString name )
{
	return _layout->delChield( name );
}

CWidgetBase* CListing::getChield( QString name )
{
	return _layout->getChield( name );
}

bool CListing::operator ==( CWidgetBase *widget )
{
	return this == (CListing*)widget;
}

bool CListing::operator ==( CNode *node )
{
	return this == (CListing*)node;
}

void CListing::__drawTexture( int so_V, int so_H )
{
	_texture->Begin();
	_texture->Clear( _colorBkg );

	int sd = _layout->position().y + _layout->height();
	if ( sd > _scrollSizeVertical )
		_scrollSizeVertical = sd;

	sd = _layout->position().x + _layout->width();
	if ( sd > _width - 6 ){
		_width = sd + 6;
		setSize( { _width, _height } );
	}

	if ( __isMouseInNode( so_V, so_H ) )
		_layout->__setMousePos( { _MP.x - _pos.x + so_H, _MP.y - _pos.y + so_V } );
	else _layout->__setMousePos( { -1, -1 } );

	_layout->onDraw( _scrollOffsetVertical, _scrollOffsetHorizontal );

	_texture->End();
}
