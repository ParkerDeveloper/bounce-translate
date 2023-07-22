#include "Text.h"

CText::CText(QString text, SRColor color, QObject *parent, POINT pos, CD3DFont *font, bool deleteOnDestructor ) : CWidgetBase( parent, pos, font, deleteOnDestructor )
{
	if (parent == nullptr)
		throw "Parent for CText can't be null";
	_text = text;
	_color = color;
	_shadow = true;
	_description = "";
	setSelectable( false );

	_Init = false;
}

bool CText::isInizialize()
{
	if ( _Init )
		return true;

	if ( g_class.DirectX->d3d9_device() == nullptr )
		return false;

	if ( !CWidgetBase::isInizialize() )
		return false;

	_height = _font->DrawHeight();
	_width = _font->DrawLength( _text );

	_Init = true;
	return false;
}

void CText::onDraw( int so_V, int so_H )
{
	if ( !isInizialize() )
		return;

	if ( _shadow )
		_font->PrintShadow( _pos.x - so_H, _pos.y - so_V, _color, _text );
	else _font->Print( _text, _color, _pos.x - so_H, _pos.y - so_V);

	CWidgetBase::onDraw( so_V, so_H );
}

void CText::setText( QString text )
{
	_text = text;
	_width = _font->DrawLength( _text );
	emit eventTextChanged(this, text);
}

QString CText::text()
{
	return _text;
}

void CText::setColor( SRColor color )
{
	_color = color;
	emit eventColorChanged(this, color);
}

SRColor CText::color()
{
	return _color;
}

void CText::setShadow( bool shadow )
{
	_shadow = shadow;
}

bool CText::isShadow()
{
	return _shadow;
}

bool CText::operator ==( CWidgetBase *widget )
{
	return this == (CText*)widget;
}
