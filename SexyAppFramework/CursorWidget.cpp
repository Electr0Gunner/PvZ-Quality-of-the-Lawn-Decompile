#include "CursorWidget.h"
#include "WidgetManager.h"
#include "../GameConstants.h"
#include "../LawnApp.h"
#include "Image.h"

using namespace Sexy;

CursorWidget::CursorWidget()
{
	mImage = NULL;
	mMouseVisible = false;
	mCursorMode = CursorMode::CURSOR_MODE_NORMAL;
}

void CursorWidget::Draw(Graphics* g)
{
	Widget::Draw(g);
	if (mImage != NULL && mCursorMode == CursorMode::CURSOR_MODE_NORMAL)
		g->DrawImage(mImage, 0, 0);
}

void CursorWidget::SetImage(Image* theImage)
{
	mImage = theImage;
	if (mImage != NULL)
		Resize(mX, mY, theImage->mWidth, theImage->mHeight);
}

void CursorWidget::Update()
{
	mX = gSexyAppBase->mWidgetManager->mLastMouseX - 30;
	mY = gSexyAppBase->mWidgetManager->mLastMouseY - 25;
}

Point CursorWidget::GetHotspot()
{
	if (mImage == NULL)
		return Point(0, 0);
	return Point(mImage->GetWidth()/2, mImage->GetHeight()/2);
}
