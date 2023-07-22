#include "Node.h"
#include "../proxydirectx.h"

CNode::CNode( QObject *parent, POINT pos, POINT size ) : CWidgetBase( parent, pos )
{
	if (parent == nullptr)
		throw "Parent for CNode can't be null";
	_size = size;
	_height = _size.y + 6;
	_width = _size.x + 6;
	_scrollOffsetVertical = 0;
	_scrollOffsetHorizontal = 0;
	_scrollSizeVertical = _size.y;
	_scrollSizeHorizontal = _size.x;
	_scrollStep = 10;
	_scrollFrame = eCdGreen;
	_scrollMat = eCdBlue;
	_scrollRoller = eCdRed;
	_colorBkg = eCdBlack;
	setSelectable(false);

	_Init = false;
}

CNode::~CNode()
{
	for ( int i = 0; i < _nodes.size(); ++i )
		if ( _nodes[i].node->parent() == this )
			delete _nodes[i].node;

	g_class.DirectX->d3d9_ReleaseTexture(_texture);
}

bool CNode::isInizialize()
{
	if ( _Init )
		return true;

	if ( g_class.DirectX->d3d9_device() == nullptr )
		return false;

	if ( !CWidgetBase::isInizialize() )
		return false;

	if ( _menu == nullptr )
		return false;

	for ( int i = 0; i < _nodes.size(); ++i ){
		_nodes[i].node->__setMenu( _menu );
		if ( !_nodes[i].node->isInizialize() )
			return false;
	}
	_texture = g_class.DirectX->d3d9_CreateTexture( _size.x, _size.y );
	connect(_texture, &SRTexture::eventInitialized, this, &CNode::__textureInitialized);

	_Init = true;
	return true;
}

void CNode::onDraw( int so_V, int so_H )
{
	if ( !isInizialize() )
		return;

	if (__isMouseOnWidget(so_V, so_H)){
		__drawTexture( so_V, so_H );
	}
	_texture->Render( _pos.x - so_H, _pos.y - so_V );
	__drawScrollBarVertical( so_V, so_H );
	__drawScrollBarHorizontal( so_V, so_H );
	CWidgetBase::onDraw( so_V, so_H );
}

void CNode::__drawScrollBarVertical( int so_V, int so_H )
{
	int fullScroll = _size.y - 4;
	float rollerSize = (float)_size.y / ((float)_scrollSizeVertical) * (float)fullScroll;
	float rollerOffset = (float)_size.y / ((float)_scrollSizeVertical) * (float)_scrollOffsetVertical;

	_draw->D3DBox( _pos.x + _size.x - so_H, _pos.y - so_V, 6, _size.y, _scrollFrame );
	_draw->D3DBox( _pos.x + _size.x + 2 - so_H, (_pos.y + 2) - so_V, 2, fullScroll, _scrollMat );
	_draw->D3DBox( _pos.x + _size.x + 2 - so_H, (_pos.y + 2 + rollerOffset) - so_V, 2, rollerSize, _scrollRoller );
}

void CNode::__drawScrollBarHorizontal( int so_V, int so_H )
{
	float rollerSize = (float)_size.x / ((float)_scrollSizeHorizontal) * (float)_size.x;
	float rollerOffset = (float)_size.x / ((float)_scrollSizeHorizontal) * (float)_scrollOffsetHorizontal;

	_draw->D3DBox( _pos.x - so_H, (_pos.y + _size.y) - so_V, _size.x + 6, 6, _scrollFrame );
	_draw->D3DBox( _pos.x + 3 - so_H, (_pos.y + _size.y + 2) - so_V, _size.x, 2, _scrollMat );
	_draw->D3DBox( _pos.x + 3 + rollerOffset - so_H, (_pos.y + _size.y + 2) - so_V, rollerSize, 2, _scrollRoller );
}

eLockEvent CNode::onEvents( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	if ( !__isMouseInNode( _SO.y, _SO.x ) )
		return eLe_noLock;
	for ( int i = 0; i < _nodes.size(); ++i ){
		if ( _nodes[i].node->isShowed() ){
			eLockEvent nodeEv = _nodes[i].node->onEvents( hwnd, uMsg, wParam, lParam );
			if ( nodeEv != eLe_noLock )
				return nodeEv;
		}
	}
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
				case VK_LEFT:
					_scrollOffsetHorizontal -= _scrollStep;
					if ( _scrollOffsetHorizontal < 0 )
						_scrollOffsetHorizontal = 0;
					return eLe_lockKeyboard;
				case VK_RIGHT:
					_scrollOffsetHorizontal += _scrollStep;
					if ( _scrollOffsetHorizontal + _size.x > _scrollSizeHorizontal )
						_scrollOffsetHorizontal = _scrollSizeHorizontal - _size.x;
					return eLe_lockKeyboard;
				case VK_PRIOR:
					_scrollOffsetVertical = 0;
					return eLe_lockKeyboard;
				case VK_NEXT:
					_scrollOffsetVertical = _scrollSizeVertical - _size.y;
					return eLe_lockKeyboard;
				case VK_HOME:
					_scrollOffsetHorizontal = 0;
					return eLe_lockKeyboard;
				case VK_END:
					_scrollOffsetHorizontal = _scrollSizeHorizontal - _size.x;
					return eLe_lockKeyboard;
				default:
					break;
			}
			break;
		default:
			break;
	}

	return CWidgetBase::onEvents(hwnd, uMsg, wParam, lParam);
}

void CNode::setSize( POINT sz )
{
	//delete _texture;
	_size = sz;
	_height = sz.y + 6;
	_width = sz.x + 6;
	//_texture = new SRTexture( sz.x, sz.y );
	_texture->ReInit( sz.x, sz.y );
}

POINT CNode::size()
{
	return _size;
}

int CNode::scrollVertical()
{
	return _scrollOffsetVertical - _size.y;
}

void CNode::setScrollVertical( int scroll )
{
	_scrollOffsetVertical = scroll;
	if ( _scrollOffsetVertical + _size.y > _scrollSizeVertical )
		_scrollOffsetVertical = _scrollSizeVertical - _size.y;
	else if ( _scrollOffsetVertical < 0 )
		_scrollOffsetVertical = 0;
}

int CNode::scrollHorizontal()
{
	return _scrollOffsetHorizontal - _size.y;
}

void CNode::setScrollHorizontal( int scroll )
{
	_scrollOffsetHorizontal = scroll;
	if ( _scrollOffsetHorizontal + _size.x > _scrollSizeHorizontal )
		_scrollOffsetHorizontal = _scrollSizeHorizontal - _size.x;
	else if ( _scrollOffsetHorizontal < 0 )
		_scrollOffsetHorizontal = 0;
}

void CNode::setScrollStep( int step )
{
	_scrollStep = step;
}

void CNode::scrollColor(SRColor &frame, SRColor &mat, SRColor &roller )
{
	frame = _scrollFrame;
	mat = _scrollMat;
	roller = _scrollRoller;
}

void CNode::setScrollColor(SRColor frame, SRColor mat, SRColor roller )
{
	_scrollFrame = frame;
	_scrollMat = mat;
	_scrollRoller = roller;
}

bool CNode::addChield( CWidgetBase* node, QString name )
{
	if (name.length() > 1)
		for ( int i = 0; i < _nodes.size(); ++i )
			if ( _nodes[i].name == name )
				return false;

	_nodes.push_back( { node, name } );
	node->__setMenu( _menu );
	return true;
}

bool CNode::delChield( CWidgetBase* node )
{
	for ( int i = 0; i < _nodes.size(); ++i ){
		if ( _nodes[i].node == node ){
			if ( node->parent() == this )
				delete node;
			_nodes.erase( _nodes.begin() + i );
			return true;
		}
	}
	return false;
}

bool CNode::delChield( QString name )
{
	if ( name.isEmpty() )
		return false;

	for ( int i = 0; i < _nodes.size(); ++i ){
		if ( _nodes[i].name == name ){
			if ( _nodes[i].node->parent() == this )
				delete _nodes[i].node;
			_nodes.erase( _nodes.begin() + i );
			return true;
		}
	}
	return false;
}

CWidgetBase* CNode::getChield( QString name )
{
	if ( name.isEmpty() )
		throw "MenuManager error: name of chield can not be empty";

	for ( int i = 0; i < _nodes.size(); ++i )
		if ( _nodes[i].name == name )
			return _nodes[i].node;

	throw "MenuManager error: Chield "" + name + "" has not defined";
}

bool CNode::__isMouseInNode( int so_V, int so_H )
{
	POINT M = _MP;
	int PX = _pos.x - so_H;
	int PY = _pos.y - so_V;
	if ( M.x > PX && M.x < PX + _size.x && M.y > PY && M.y < PY + _size.y )
		return true;
	return false;
}

void CNode::__drawTexture( int so_V, int so_H )
{
	_texture->Begin();
	_texture->Clear( _colorBkg );

	for ( int i = 0; i < _nodes.size(); ++i ){
		if ( _nodes[i].node->isShowed() ){

			int sd = _nodes[i].node->position().y + _nodes[i].node->height();
			if ( sd > _scrollSizeVertical )
				_scrollSizeVertical = sd;

			sd = _nodes[i].node->position().x + _nodes[i].node->width();
			if ( sd > _scrollSizeHorizontal )
				_scrollSizeHorizontal = sd;

			if ( __isMouseInNode(so_V, so_H) )
				_nodes[i].node->__setMousePos( { _MP.x - _pos.x + so_H, _MP.y - _pos.y + so_V } );
			else _nodes[i].node->__setMousePos( { -1, -1 } );
			_nodes[i].node->onDraw( _scrollOffsetVertical, _scrollOffsetHorizontal );
		}
	}

	_texture->End();
}

void CNode::__textureInitialized()
{
	__drawTexture(_SO.y, _SO.x);
}

SRColor CNode::colorBkg()
{
	return _colorBkg;
}

void CNode::setColorBkg(SRColor color )
{
	_colorBkg = color;
}

bool CNode::operator ==( CWidgetBase *widget )
{
	return this == (CNode*)widget;
}
