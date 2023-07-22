#include "Menu.h"
#include "../proxydirectx.h"

std::vector<CMenu*> MenuList;

CMenu::CMenu(QString title, POINT size, QObject *parent, CNode* node ) : CWidgetBase( parent )
{
	_title = title;
	_size = size;
	_description = "";
	_move = false;
	_context = nullptr;
	_menu = this;
	_hasStickBorder = false;
	_stickDist = 10;
	setSelectable( false );

	if ( node != nullptr ){
		_node = node;
	}
	else _node = new CNode( this, { 0, 0 }, size );
	_node->__setMenu( this );

	_Init = false;
	MenuList.push_back( this );
}

CMenu::~CMenu()
{
	VectorErase( MenuList, this );
}

bool CMenu::isInizialize()
{
	if ( _Init )
		return true;

	if ( g_class.DirectX->d3d9_device() == nullptr )
		return false;

	if ( !CWidgetBase::isInizialize() )
		return false;

	if ( !_node->isInizialize() )
		return false;

	_pos.x = (SCREEN_X - _size.x) / 2;
	_pos.y = (SCREEN_Y - _size.y) / 2;

	_header = _font->DrawHeight() + 3;
	_height = _size.y + _header + 6;
	_width = _size.x + 6;
	_titleLen = _size.x - (3 + _font->DrawLength( "X" ));

	_Init = true;
	return true;
}

void CMenu::onDraw( int so_V, int so_H )
{
	if ( !isInizialize() )
		return;

	if ( _move ){
		__setMousePos( __getMousePos() );
		_pos.x = _MP.x - _mvOffset.x;
		_pos.y = _MP.y - _mvOffset.y;
		__correctPosition();
	}
	else if ( __isMouseOnHeader() )
		__setMenuHelper( _description );

	_draw->BeginRender();
	_draw->D3DBox(_pos.x, _pos.y, _titleLen, _header, eCdBlack);
	_font->PrintShadow( _pos.x + 1, _pos.y, -1, _title );
	if ( __isMouseOnClose() && isActive() ){
		_draw->D3DBox( _pos.x + (_size.x - (3 + _font->DrawLength( "X" ))),
					   _pos.y, 10 + _font->DrawLength( "X" ), _header, 0xFFFF0000 );
		__setMenuHelper( "Close" );
	}
	else{
		_draw->D3DBox( _pos.x + (_size.x - (3 + _font->DrawLength( "X" ))),
					   _pos.y, 10 + _font->DrawLength( "X" ), _header, 0xFFFF6060 );
	}
	_font->PrintShadow( _pos.x + (_size.x - _font->DrawLength( "X" ) + 2), _pos.y, -1, "X" );
	_draw->D3DBox( _pos.x, _pos.y + _header - 1, _size.x + 6, 1, -1 );

	_node->setPosition( { _pos.x, _pos.y + _header } );
	POINT MP = __getMousePos();
	_node->__setMousePos( { MP.x - so_H, MP.y - so_V } );
	_node->onDraw( so_V, so_H );

	__setMousePos( __getMousePos() );

	if ( _context != nullptr ){
		p_helper.clear();
		if ( _context->isInizialize() )
			_context->onDraw();
	}

	if ( __isMouseOnWidget() && !p_helper.empty() && IsForeground(this) ){
		POINT M = __getMousePos();
		float length = _font->DrawLength( p_helper[0] );
		for ( int i = 1; i < p_helper.size(); ++i ){
			if ( _font->DrawLength( p_helper[i] ) > length )
				length = _font->DrawLength( p_helper[i] );
		}
		int x_offset = 0;
		int x_cursorOffset = 20;
		int y_cursorOffset = 20;
		if (cursorType == eCursorType::SAMP){
			x_cursorOffset = 32;
			y_cursorOffset = 32;
		}
		else if (cursorType == eCursorType::Girl){
			x_cursorOffset = 330 / 5;
			y_cursorOffset = 0;
		}
		if ( M.x + x_cursorOffset + length > SCREEN_X )
			x_offset = (M.x + x_cursorOffset + length) - SCREEN_X;
		int y_offset = 0;
		if ( M.y + y_cursorOffset + _font->DrawHeight() * p_helper.size() > SCREEN_Y )
			y_offset = (M.y + y_cursorOffset + _font->DrawHeight() * p_helper.size()) - SCREEN_Y;
		_draw->D3DBoxBorder( (M.x + (x_cursorOffset - 4)) - x_offset, M.y + (y_cursorOffset - 4) - y_offset, length + 3, _font->DrawHeight() * p_helper.size() + 3, -1, 0xF8000000 );
		for ( int i = 0; i < p_helper.size(); ++i )
			_font->PrintShadow( (M.x + (x_cursorOffset - 4) + 1) - x_offset, M.y + (y_cursorOffset - 4) + _font->DrawHeight() * i - y_offset, -1, p_helper[i] );
	}
	_draw->EndRender();
	p_helper.clear();
	//p_helper.shrink_to_fit();
}

eLockEvent CMenu::onEvents( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	__setMousePos(__getMousePos());

	if ( _context != nullptr ){
		if ( !_context->onEvents( hwnd, uMsg, wParam, lParam ) ){
			//			if ( _context->parent() == this )
			//				delete _context;
			_context = nullptr;
		}
		return eLe_lockAll;
	}

	if ( !__isMouseOnWidget() )
		return eLe_noLock;

	switch ( uMsg )
	{
		case WM_LBUTTONDOWN:
			if ( !IsForeground( this ) ){
				SetForeground( this );
				if ( __isMouseOnClose() )
					return eLe_lockMouseClick;
			}
			if ( __isMouseOnHeader() ){
				if ( !_move ){
					_mvOffset.x = _MP.x - _pos.x;
					_mvOffset.y = _MP.y - _pos.y;
					_move = true;
				}
				return eLe_lockMouseClick;
			}
			else if ( __isMouseOnClose() ){
				//setShow( false );
				return eLe_lockMouseClick;
			}
			break;
		case WM_LBUTTONUP:
			if ( _move ){
				_pos.x = _MP.x - _mvOffset.x;
				_pos.y = _MP.y - _mvOffset.y;
				__correctPosition();
				_move = false;
				emit eventMove( this, _pos );
			}
			if ( __isMouseOnClose() ){
				setShow( false );
				return eLe_lockMouseClick;
			}
			break;
		default:
			break;
	}

	if (_move)
		return eLe_lockMouseMove;

	if ( IsForeground( this ) )
		return _node->onEvents( hwnd, uMsg, wParam, lParam );
	return eLe_noLock;
}

void CMenu::setSize( POINT sz )
{
	//delete _texture;
	_size = sz;
	_height = sz.y + _header + 6;
	_width = sz.x + 6;
	_titleLen = sz.x - (3 + _font->DrawLength( "X" ));
	_node->setSize( _size );
}

POINT CMenu::size()
{
	return _size;
}

CNode* CMenu::node()
{
	return _node;
}

void CMenu::__setMenuHelper( QString help )
{
	if ( help.isEmpty() ){
		p_helper.clear();
		return;
	}
	while ( help.indexOf( "\n" ) != -1 ){
		QRegExp re(R"(.*(\n(.*)))");
		if (re.indexIn(help) >= 0)
			p_helper.push_front( re.cap(2) );
		help = help.remove(re.cap(1));
	}
	p_helper.push_front( help );
}

bool CMenu::__isMouseOnHeader()
{
	__setMousePos( __getMousePos() );
	if ( !__isMouseOnWidget() )
		return false;
	if ( _MP.x < _pos.x + (_size.x - (3 + _font->DrawLength( "X" ))) && _MP.y < _pos.y + _header )
		return true;
	return false;
}

bool CMenu::__isMouseOnClose()
{
	__setMousePos( __getMousePos() );
	if ( !__isMouseOnWidget() )
		return false;
	if ( _MP.x > _pos.x + (_size.x - (3 + _font->DrawLength( "X" ))) && _MP.y < _pos.y + _header )
		return true;
	return false;
}

void CMenu::__correctPosition()
{
	if (_hasStickBorder){
		if (_pos.x >= -_stickDist && _pos.x <= _stickDist)
			_pos.x = 0;
		if (_pos.y >= -_stickDist && _pos.y <= _stickDist)
			_pos.y = 0;
		if (_pos.x + _width >= SCREEN_X - _stickDist && _pos.x + _width <= SCREEN_X + _stickDist)
			_pos.x = SCREEN_X - _width;
		if (_pos.y + _height >= SCREEN_Y - _stickDist && _pos.y + _height <= SCREEN_Y + _stickDist)
			_pos.y = SCREEN_Y - _height;
	}

	// Disallow move menu out of the window
	if (_pos.x > SCREEN_X - 2)
		_pos.x = SCREEN_X - 2;
	if (_pos.y > SCREEN_Y - 2)
		_pos.y = SCREEN_Y - 2;
	if (_pos.x + _titleLen - 2 < 0 )
		_pos.x = -(_titleLen - 2);
	if (_pos.y + _header - 2 < 0)
		_pos.y = -(_header - 2);
}

void CMenu::setContextMenu( CContextMenu* contextMenu )
{
	_context = contextMenu;
	_context->setPosition( __getMousePos() );
	_context->__setMenu( this );
}

bool CMenu::isActive()
{
	if ( IsForeground( this ) && _context == nullptr )
		return true;
	return false;
}

void CMenu::setSticked( bool sticked )
{
	_hasStickBorder = sticked;
}

bool CMenu::isSticked()
{
	return _hasStickBorder;
}

void CMenu::setStickedDistance( uint distance )
{
	_stickDist = distance;
}

uint CMenu::stickedDistance()
{
	return _stickDist;
}

bool CMenu::operator ==( CWidgetBase *widget )
{
	return this == (CMenu*)widget;
}

void SetForeground( CMenu* menu )
{
	for ( size_t i = 0; i < MenuList.size() - 1; ++i ){
		if ( menu == MenuList[i] ){
			myswap( MenuList[i], MenuList[MenuList.size() - 1] );
			break;
		}
	}
}

bool IsForeground( CMenu* menu )
{
	if ( menu == MenuList[MenuList.size() - 1] )
		return true;
	return false;
}
