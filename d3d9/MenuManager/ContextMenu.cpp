#include "ContextMenu.h"
#include "Menu.h"

CContextMenu::CContextMenu(QObject *parent, SRColor color ) : CWidgetBase( parent )
{
	if (parent == nullptr)
		throw "Parent for CContextMenu can't be null";
	_color = color;
	_width = 0;
	_height = 0;
	_Init = false;
}

CContextMenu::~CContextMenu()
{
	for ( int i = 0; i < _vars.size(); ++i )
		delete _vars[i];
}

bool CContextMenu::isInizialize()
{
	if ( _Init )
		return true;

	if ( !CWidgetBase::isInizialize() )
		return false;

	if ( _menu == nullptr )
		return false;

	for ( int i = 0; i < _vars.size(); ++i ){
		_vars[i]->__setMenu( _menu );
		if ( !_vars[i]->isInizialize() )
			return false;
	}

	for ( int i = 0; i < _vars.size(); ++i ){
		if ( _vars[i]->width() + 3 > _width )
			_width = _vars[i]->width() + 3;
	}

	_height = _font->DrawHeight() * _vars.size() + 5;

	if ( _pos.y + _height > SCREEN_Y )
		_pos.y = SCREEN_Y - _height;
	if ( _pos.x + _width > SCREEN_X )
		_pos.x = SCREEN_X - _width;

	_Init = true;
	return true;
}

void CContextMenu::addVariant(QString text, SRColor color )
{
	auto var = new CText( text, color, this );
	var->__setMenu( _menu );
	_vars.push_back( var );

	if ( _Init ){
		if ( var->width() + 3 > _width )
			_width = var->width() + 3;
		_height = _font->DrawHeight() * _vars.size() + 5;
	}
}

void CContextMenu::setDescription( QString desc )
{
	_vars[_vars.size() - 1]->setDescription( desc );
}

bool CContextMenu::operator ==( CWidgetBase *widget )
{
	return this == (CContextMenu*)widget;
}

void CContextMenu::onDraw( int, int )
{
	if ( !isInizialize() )
		return;

	_draw->D3DBoxBorder( _pos.x - 1, _pos.y - 1, _width, _height, _color.invert(), _color );

	for ( int i = 0; i < _vars.size(); ++i ){
		if ( __isMouseOnVariant( i ) )
			_draw->D3DBox( _pos.x + 1, _pos.y + i * _font->DrawHeight() + 1,
						   _vars[i]->width() - 1, _vars[i]->height() + 1, _color.invert() );

		_vars[i]->setPosition( _pos );
		_vars[i]->onDraw( -(i * _font->DrawHeight()) );
	}
}

eLockEvent CContextMenu::onEvents( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if ( !isInizialize() )
		return eLe_noLock;

	__setMousePos( __getMousePos() );
	if ( uMsg == WM_LBUTTONDOWN ){
		for ( int i = 0; i < _vars.size(); ++i ){

			if ( __isMouseOnVariant(i) ){
				emit eventContextMenu( this, i );
				return eLe_lockMouseMove;
			}
		}
		if ( __isMouseOnWidget() )
			emit eventContextMenu( this, -1 );
		return eLe_lockMouseClick;
	}

	return eLe_noLock;
}

bool CContextMenu::__isMouseOnVariant( int id )
{
	if ( _MP.x > _pos.x &&
		 _MP.x < _pos.x + _vars[id]->width() &&
		 _MP.y > _pos.y + id * _font->DrawHeight() &&
		 _MP.y < (_pos.y + id * _font->DrawHeight()) + _vars[id]->height() )
		return true;
	return false;
}

void CContextMenu::setPosition( POINT pos )
{
	if ( pos.y + _height > SCREEN_Y )
		pos.y = SCREEN_Y - _height;
	if ( pos.x + _width > SCREEN_X )
		pos.x = SCREEN_X - _width;

	return CWidgetBase::setPosition( pos );
}
