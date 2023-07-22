#ifndef Text_H
#define Text_H

#include "WidgetBase.h"
#include <QObject>

class CText : public CWidgetBase
{
	Q_OBJECT

	friend class CContextMenu;
	friend class CListing;
	friend class CMenu;
	friend class CNode;
	friend class CVerticalLayout;
	friend class CSlider;

	friend class proxyIDirect3DDevice9;
	friend LRESULT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CText( QString, SRColor, QObject *parent, POINT = { 0, 0 }, CD3DFont* = nullptr, bool = false );

	virtual bool isInizialize();

protected:
	virtual void onDraw( int = 0, int = 0 );

public:
	virtual void setText( QString );
	virtual QString text();

	virtual void setColor( SRColor );
	virtual SRColor color();

	virtual void setShadow( bool );
	virtual bool isShadow();

	bool operator ==( CWidgetBase* );

protected:
	QString _text;
	SRColor _color;
	bool	_shadow;

private:
	bool _Init;

signals:
	void eventTextChanged(CText*, QString);
	void eventColorChanged(CText*, SRColor);
};

#endif // Text_H
