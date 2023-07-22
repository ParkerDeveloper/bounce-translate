#include "VerticalLayout.h"

CVerticalLayout::CVerticalLayout( QObject *parent, POINT pos ) : CNode( parent, pos )
{
	if (parent == nullptr)
		throw "Parent for CVerticalLayout can't be null";
	_height = 0;
	_width = 0;

	_Init = false;
}

void CVerticalLayout::onDraw( int so_V, int so_H )
{
	if ( !isInizialize() )
		return;

	if ( _Init )
		return __drawLayout( so_V, so_H );

	if ( !CNode::isInizialize() )
		return;

	for ( int i = 0; i < _nodes.size(); ++i ){
		POINT pos = _nodes[i].node->position();
		pos.y = _height;
		_nodes[i].node->setPosition( pos );
		_height += _nodes[i].node->height() + 3;
		if ( _nodes[i].node->width() > _width )
			_width = _nodes[i].node->width();
	}

	CNode::setSize( { _width, _height } );

	_Init = true;
	__drawLayout(so_V, so_H);
}

void CVerticalLayout::setPosition( POINT pos )
{
	_pos.x = pos.x;
}

bool CVerticalLayout::addChield( CWidgetBase* node, QString name )
{
	if ( name.length() > 1 )
		for ( int i = 0; i < _nodes.size(); ++i )
			if ( _nodes[i].name == name )
				return false;

	POINT pos = node->position();
	pos.y = _height;
	node->setPosition( pos );
	if ( _Init ){
		_height += node->height() + 3;
		if ( node->width() > _width )
			_width = node->width();
		CNode::setSize( { _width, _height } );
	}

	_nodes.push_back( { node, name } );
	node->__setMenu( _menu );
	return true;
}
bool CVerticalLayout::delChield( CWidgetBase* node )
{
	int offset = -1;
	_width = 0;
	bool ret = false;
	for ( int i = 0; i < _nodes.size(); ++i ){
		if ( _nodes[i].node == node ){
			offset = _nodes[i].node->height();
			//if ( node->parent() == this ){
			delete node;
			ret = true;
			//}
		}
		else if ( _Init ){
			if ( offset != -1 ){
				POINT pos = _nodes[i].node->position();
				pos.y -= offset;
				_nodes[i].node->setPosition( pos );
			}

			if ( _nodes[i].node->width() > _width )
				_width = _nodes[i].node->width();
		}
	}
	if ( offset != -1 )
		_height -= offset;
	if ( _Init )
		CNode::setSize( { _width, _height } );
	return ret;
}

bool CVerticalLayout::delChield( QString name )
{
	if ( name.isEmpty() )
		return false;

	int offset = -1;
	_width = 0;
	bool ret = false;
	for ( int i = 0; i < _nodes.size(); ++i ){
		if ( _nodes[i].name == name ){
			offset = _nodes[i].node->height();
			if ( _nodes[i].node->parent() == this ){
				delete _nodes[i].node;
				ret = true;
			}
		}
		else if ( _Init ){
			if ( offset != -1 ){
				POINT pos = _nodes[i].node->position();
				pos.y -= offset;
				_nodes[i].node->setPosition( pos );
			}

			if ( _nodes[i].node->width() > _width )
				_width = _nodes[i].node->width();
		}
	}
	if ( offset != -1 )
		_height -= offset;
	if ( _Init )
		CNode::setSize( { _width, _height } );
	return ret;
}

bool CVerticalLayout::operator ==( CWidgetBase *widget )
{
	return this == (CVerticalLayout*)widget;
}

bool CVerticalLayout::operator ==( CNode *node )
{
	return this == (CVerticalLayout*)node;
}

void CVerticalLayout::setSize( POINT sz )
{
	// Размеры считаются сами!
}

void CVerticalLayout::__drawLayout( int so_V, int so_H )
{
	// Все кроме скроллбаров скопипизженно из CNode
	if ( g_class.DirectX->d3d9_device() == nullptr )
		return;

	if (__isMouseOnWidget(so_V, so_H)){
		__drawTexture( so_V, so_H );
	}
	_texture->Render( _pos.x - so_H, _pos.y - so_V );
	CWidgetBase::onDraw( so_V, so_H );
}

void CVerticalLayout::__drawTexture( int so_V, int so_H )
{
	_texture->Begin();
	_texture->Clear( _colorBkg );

	for ( int i = 0; i < _nodes.size(); ++i ){
		if ( _nodes[i].node->isShowed() ){

			if ( __isMouseInNode(so_V, so_H) )
				_nodes[i].node->__setMousePos( { _MP.x - _pos.x + so_H, _MP.y - _pos.y + so_V } );
			else _nodes[i].node->__setMousePos( { -1, -1 } );
			_nodes[i].node->onDraw( _scrollOffsetVertical, _scrollOffsetHorizontal );
		}
	}

	_texture->End();
}

eLockEvent CVerticalLayout::onEvents( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	// Тоже скопипизжено из CNode, и то же выпелины скроллбары
	if ( !__isMouseInNode( _SO.y, _SO.x ) )
		return eLe_noLock;
	for ( int i = 0; i < _nodes.size(); ++i ){
		if ( _nodes[i].node->isShowed() ){
			eLockEvent nodeEv = _nodes[i].node->onEvents( hwnd, uMsg, wParam, lParam );
			if ( nodeEv != eLe_noLock )
				return nodeEv;
		}
	}

	return CWidgetBase::onEvents( hwnd, uMsg, wParam, lParam );
}
