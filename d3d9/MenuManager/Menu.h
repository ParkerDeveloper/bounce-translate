#ifndef Menu_H
#define Menu_H

#define SCREEN_X *(int*)0x00C9C040
#define SCREEN_Y *(int*)0x00C9C044

#include "Node.h"
#include "ContextMenu.h"
#include <QRegExp>
#include <QVector>
#include <QObject>

template<typename T> void VectorErase( std::vector<T> &vec, T v );
template<typename T> void myswap( T &a, T &b );

class CMenu;
extern std::vector<CMenu*> MenuList;

class CMenu : public CWidgetBase
{
	Q_OBJECT

	friend class CWidgetBase;
	friend class CContextMenu;
	friend class CListing;
	friend class CNode;
	friend class CText;
	friend class CVerticalLayout;
	friend class CSlider;

	friend class proxyIDirect3DDevice9;
	friend LRESULT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CMenu( QString, POINT, QObject *parent = 0, CNode* = nullptr );
	~CMenu();

protected:
	virtual void onDraw( int = 0, int = 0 );
	virtual eLockEvent onEvents( HWND, UINT, WPARAM, LPARAM );

public:
	virtual bool isInizialize();

	virtual void setSize( POINT );
	virtual POINT size();

	virtual CNode* node();

	virtual void setContextMenu( CContextMenu* );

	virtual bool isActive();

	virtual void setSticked( bool );
	virtual bool isSticked();

	virtual void setStickedDistance( uint );
	virtual uint stickedDistance();

	bool operator ==( CWidgetBase* );

protected:
	CNode *_node;
	CContextMenu *_context;

	QString _title;
	POINT _size;
	int _header;
	int _titleLen;
	bool _hasStickBorder;
	int _stickDist;

	bool __isMouseOnHeader();
	bool __isMouseOnClose();
	void __correctPosition();

	virtual void __setMenuHelper( QString );

	QVector<QString> p_helper;

private:
	bool _Init;

	bool _move;
	POINT _mvOffset;
};

void SetForeground( CMenu* menu );
bool IsForeground( CMenu*menu );

template<typename T>
inline void VectorErase( std::vector<T> &vec, T v )
{
	for ( int i = 0; i < vec.size(); ++i ){
		if ( vec[i] == v ){
			vec.erase( vec.begin() + i );
			break;
		}
	}
}

template<typename T>
inline void myswap( T &a, T &b )
{
	T c = a;
	a = b;
	b = c;
}

#endif // Menu_H
