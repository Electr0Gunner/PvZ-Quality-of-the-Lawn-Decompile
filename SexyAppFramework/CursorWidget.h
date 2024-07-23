#ifndef __CURSORWIDGET_H__
#define __CURSORWIDGET_H__

#include "Widget.h"
#include "Point.h"
#include "../ConstEnums.h"

namespace Sexy
{

class Image;

class CursorWidget : public Widget
{
public:
	Image*					mImage;
	CursorMode				mCursorMode;

public:
	CursorWidget();

	virtual void			Draw(Graphics* g);
	void					SetImage(Image* theImage);
	void					Update();
	Point					GetHotspot();
	
};

}

#endif //__CURSORWIDGET_H__