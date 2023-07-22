#ifndef Node_H
#define Node_H

#include "WidgetBase.h"
#include "../texture.h"
#include <QVector>
#include <QObject>

struct stNodeChield{
	CWidgetBase*	node;
	QString name;
};

class CNode : public CWidgetBase
{
	Q_OBJECT

	friend class CContextMenu;
	friend class CListing;
	friend class CMenu;
	friend class CText;
	friend class CVerticalLayout;
	friend class CSlider;

	friend class proxyIDirect3DDevice9;
	friend LRESULT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CNode( QObject *parent, POINT = { 0, 0 }, POINT = { 100, 100 } );
	virtual ~CNode();

protected:
	virtual void onDraw( int = 0, int = 0 );
	virtual eLockEvent onEvents( HWND, UINT, WPARAM, LPARAM );

public:
	virtual bool isInizialize();

	virtual void setSize( POINT );
	virtual POINT size();

	virtual int scrollVertical();
	virtual void setScrollVertical( int );
	virtual int scrollHorizontal();
	virtual void setScrollHorizontal( int );

	virtual void setScrollStep( int );
	virtual void scrollColor( SRColor&, SRColor&, SRColor& );
	virtual void setScrollColor( SRColor, SRColor, SRColor );

	virtual bool addChield( CWidgetBase*, QString = "" );
	virtual bool delChield( CWidgetBase* );
	virtual bool delChield( QString );
	virtual CWidgetBase* getChield( QString );

	virtual SRColor colorBkg();
	virtual void setColorBkg( SRColor );

	bool operator ==( CWidgetBase* );

protected:
	SRTexture *_texture;
	QVector<stNodeChield> _nodes;

	POINT _size;
	int _scrollOffsetVertical;
	int _scrollOffsetHorizontal;
	int _scrollSizeVertical;
	int _scrollSizeHorizontal;
	int _scrollStep;
	SRColor _scrollFrame;
	SRColor _scrollMat;
	SRColor _scrollRoller;

	SRColor _colorBkg;

	void __drawScrollBarVertical( int = 0, int = 0 );
	void __drawScrollBarHorizontal( int = 0, int = 0 );
	bool __isMouseInNode( int = 0, int = 0 );
	virtual void __drawTexture( int = 0, int = 0 );

private slots:
	void __textureInitialized();

private:
	bool _Init;
};

#endif // Node_H
