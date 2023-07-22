#ifndef CSLIDER_H
#define CSLIDER_H

#include "Text.h"
#include "../texture.h"
#include <QObject>

class CSlider : public CWidgetBase
{
	Q_OBJECT

	friend class CContextMenu;
	friend class CListing;
	friend class CMenu;
	friend class CNode;
	friend class CText;
	friend class CVerticalLayout;

	friend class proxyIDirect3DDevice9;
	friend LRESULT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CSlider(QObject *parent, POINT pos, uint length, float start = 1.0f, float end = 99.0f, float value = 1.0f, CD3DFont* = nullptr);

	virtual ~CSlider();

	virtual bool isInizialize();

protected:
	virtual void onDraw( int, int );
	virtual eLockEvent onEvents( HWND, UINT, WPARAM, LPARAM );

public:
	virtual void setValue( float );
	virtual float value();

	virtual void setColors( SRColor, SRColor, SRColor );
	virtual void getColors( SRColor*, SRColor*, SRColor* );

	bool operator ==( CWidgetBase* );

protected:
	SRColor _roller;
	SRColor _mat;
	SRColor _text;
	SRTexture *_texture;
	uint _length;
	float _start;
	float _end;
	float _value;
	bool _moveRoller;
	int _rollerX;

	virtual bool __isMouseOnSlider( int = 0, int = 0 );
	void __drawTexture( int = 0, int = 0 );

private slots:
	void __textureInitialized();

private:
	bool _init;

signals:
	void eventValueChanging(CSlider*, float);
	void eventValueChanged(CSlider*, float);
	void eventValueEditing(CSlider*, float);
	void eventValueEdited(CSlider*, float);
};

#endif // CSLIDER_H
