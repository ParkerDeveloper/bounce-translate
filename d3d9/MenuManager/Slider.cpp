#include "Slider.h"

CSlider::CSlider(QObject *parent, POINT pos, uint length, float start, float end, float value, CD3DFont *text) : CWidgetBase(parent, pos, text)
{
	if (parent == nullptr)
		throw "Parent for CSlider can't be null";

	_length = length;
	_start = start;
	_end = end;
	_value = value;
	float range = end - start;
	float percent = (value - start) / (range / 100.0f);
	float len = length - length / 25.0f;
	_rollerX = (percent / (100.0f / len)) + length / 50.0f;

	_roller = eCdRed;
	_mat = eCdCyan;
	_text = eCdWhite;
	_moveRoller = false;
	_description = "";
	setSelectable(false);

	_init = false;
}

CSlider::~CSlider()
{
	g_class.DirectX->d3d9_ReleaseTexture(_texture);
}

bool CSlider::isInizialize()
{
	if ( _Init )
		return true;

	if ( g_class.DirectX->d3d9_device() == nullptr )
		return false;

	if ( !CWidgetBase::isInizialize() )
		return false;

	_height = _font->DrawHeight();
	_width = _length + _font->DrawLength(QString::number(_value));
	_texture = g_class.DirectX->d3d9_CreateTexture( _length, _height );
	connect(_texture, &SRTexture::eventInitialized, this, &CSlider::__textureInitialized);

	_Init = true;
	return true;
}

void CSlider::onDraw( int so_V, int so_H )
{
	if (!isInizialize())
		return;

	int posX = _pos.x - so_H;
	int posY = _pos.y - so_V;

	if (__isMouseOnWidget( so_V, so_H ))
		__drawTexture( so_V, so_H );
	_texture->Render(posX, posY);
	_font->PrintShadow(posX + _length, posY, _text, QString::number(_value));

	CWidgetBase::onDraw( so_V, so_H );
}

eLockEvent CSlider::onEvents(HWND, UINT uMsg, WPARAM, LPARAM)
{
	if (__isMouseOnWidget( _SO.y, _SO.x )){
		if (uMsg == WM_LBUTTONDOWN){
			_moveRoller = true;
			return eLe_lockMouseClick;
		} else if (uMsg == WM_LBUTTONUP){
			_moveRoller = false;
			if (__isMouseOnSlider(_SO.y, _SO.x)){
				emit eventValueChanged(this, _value);
				emit eventValueEdited(this, _value);
			}
			return eLe_lockMouseClick;
		}
	} else _moveRoller = false;

	if (_moveRoller){
		if (!__isMouseOnSlider(_SO.y, _SO.x)){
			emit eventValueChanged(this, _value);
			emit eventValueEdited(this, _value);
			_moveRoller = false;
			return eLe_noLock;
		}
		return eLe_lockMouseMove;
	}
	return eLe_noLock;
}

void CSlider::setValue( float value )
{
	_value = value;
	_width = _length + _font->DrawLength(QString::number(_value));
	emit eventValueChanged(this, value);
}

float CSlider::value()
{
	return _value;
}

void CSlider::setColors( SRColor mat, SRColor roller, SRColor text )
{
	if (mat.argb != 0)
		_mat = mat;
	if (roller.argb != 0)
		_roller = roller;
	if (text.argb != 0)
		_text = text;
}

void CSlider::getColors( SRColor *mat, SRColor *roller, SRColor *text )
{
	if (mat != nullptr)
		*mat = _mat;
	if (roller != nullptr)
		*roller = _roller;
	if (text != nullptr)
		*text = _text;
}

bool CSlider::operator ==( CWidgetBase *widget )
{
	return this == (CSlider*)widget;
}

bool CSlider::__isMouseOnSlider( int so_V, int so_H )
{
	POINT M = _MP;
	int PX = (_pos.x - so_H) + _length / 50.0f;
	int PY = _pos.y - so_V;
	int LEN = (_length - _length / 25.0f) + 1;
	if ( M.x >= PX && M.x <= PX + LEN && M.y > PY && M.y < PY + _height )
		return true;
	return false;
}

void CSlider::__drawTexture( int so_V, int so_H )
{
	_texture->Begin();
	_texture->Clear();

	_draw->D3DBox(_length / 50.0f, _height / 4.0f, _length - _length / 25.0f, _height / 2.0f, _mat);
	_draw->D3DBox(_rollerX, 0, _length / 25.0f, _height, _roller);
	if (__isMouseOnSlider(so_V, so_H) && _moveRoller){
		int rollerX = _MP.x - (_pos.x - so_H);

		if (rollerX >= _length / 50.0f && rollerX <= (_length / 50.0f) + (_length - _length / 25.0f)){
			_rollerX = rollerX;
			rollerX -= _length / 50.0f;
			float len = _length - _length / 25.0f;
			float percent = (100.0f / len) * rollerX;
			float range = _end - _start;
			_value = (range / 100.0f) * percent + _start;
			if (_value < _start)
				_value = _start;
			if (_value > _end)
				_value = _end;
			_width = _length + _font->DrawLength(QString::number(_value));
			emit eventValueChanging(this, _value);
			emit eventValueEditing(this, _value);
		}
	}

	_texture->End();
}

void CSlider::__textureInitialized()
{
	__drawTexture(_SO.y, _SO.x);
}
