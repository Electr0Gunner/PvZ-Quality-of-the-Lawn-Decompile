#include "Slider.h"
#include "Graphics.h"
#include "Image.h"
#include "SliderListener.h"
#include "WidgetManager.h"
#include "SexyAppBase.h"

using namespace Sexy;

Slider::Slider(Image* theTrackImage, Image* theThumbImage, int theId, SliderListener* theListener) : 		
	mTrackImage(theTrackImage),
	mThumbImage(theThumbImage),
	mId(theId),
	mListener(theListener),
	mVal(0.0)
{
	mDragging = false;
	mHorizontal = true;
	mRelX = mRelY = 0;
	mThumbOffsetX = 0;
	mNoDraw = false;
}

void Slider::SetValue(double theValue)
{	
	mVal = theValue;
	if (mVal < 0.0)
		mVal = 0.0;
	else if (mVal > 1.0)
		mVal = 1.0;

	MarkDirtyFull();
}

bool Slider::HasTransparencies()
{
	return true;
}

void Slider::Draw(Graphics* g)
{	
	if (mNoDraw)
		return;
	SliderDraw(g);
}

void Slider::SliderDraw(Graphics* g)
{
	if (mNoDraw)
	{
		if (!mVisible)
			return;
		g->mTransX += mX;
		g->mTransY += mY;
	}
	if (mTrackImage != NULL)
	{
		int cw = mHorizontal ? mTrackImage->GetWidth() / 3 : mTrackImage->GetWidth();
		int ch = mHorizontal ? mTrackImage->GetHeight() : mTrackImage->GetHeight() / 3;
		if (mHorizontal)
		{
			int ty = (mHeight - ch) / 2;
			g->DrawImage(mTrackImage, 0, ty, Rect(0, 0, cw, ch));
			Graphics aClipG(*g);
			aClipG.ClipRect(cw, ty, mWidth - cw * 2, ch);
			for (int i = 0; i < (mWidth - cw * 2 + cw - 1) / cw; i++)
				aClipG.DrawImage(mTrackImage, cw + i * cw, ty, Rect(cw, 0, cw, ch));
			g->DrawImage(mTrackImage, mWidth - cw, ty, Rect(cw * 2, 0, cw, ch));
		}
		else
		{
			g->DrawImage(mTrackImage, 0, 0, Rect(0, 0, cw, ch));
			Graphics aClipG(*g);
			aClipG.ClipRect(0, ch, cw, mHeight - ch * 2);
			for (int i = 0; i < (mHeight - ch * 2 + ch - 1) / ch; i++)
				aClipG.DrawImage(mTrackImage, 0, ch + i * ch, Rect(0, ch, cw, ch));
			g->DrawImage(mTrackImage, 0, mHeight - ch, Rect(0, ch * 2, cw, ch));
		}
	}
	g->ClearClipRect();
	if (mHorizontal && (mThumbImage != NULL))
		g->DrawImage(mThumbImage, (int)(mVal * (mWidth - mThumbImage->GetWidth())) + mThumbOffsetX, (mHeight - mThumbImage->GetHeight()) / 2);
	else if (!mHorizontal && (mThumbImage != NULL))
		g->DrawImage(mThumbImage, (mWidth - mThumbImage->GetWidth()) / 2 + mThumbOffsetX, (int)(mVal * (mHeight - mThumbImage->GetHeight())));
	g->Translate(-mX, -mY);
}

void Slider::MouseDown(int x, int y, int theClickCount)
{
	if (mHorizontal)
	{
		int aThumbX = (int) (mVal * (mWidth - mThumbImage->GetWidth())) + mThumbOffsetX;;
		if ((x >= aThumbX) && (x < aThumbX + mThumbImage->GetWidth()))
		{
			mWidgetManager->mApp->SetCursor(CURSOR_DRAGGING);
			mDragging = true;
			mRelX = x - aThumbX;
		}
		else
			SetValue((double)x / mWidth);
	}
	else
	{
		int aThumbY = (int) (mVal * (mHeight - mThumbImage->GetHeight()));
		int aThumbCenterX = (mWidth - mThumbImage->GetWidth()) / 2 + mThumbOffsetX;
		if ((x >= aThumbCenterX) && (x < aThumbCenterX + mThumbImage->GetWidth()) && (y >= aThumbY) && (y < aThumbY + mThumbImage->GetHeight()))
		{
			mWidgetManager->mApp->SetCursor(CURSOR_DRAGGING);
			mDragging = true;
			mRelY = y - aThumbY;
		}
		else
			SetValue((double)y / mHeight);
	}
}

void Slider::MouseMove(int x, int y)
{
	if (mHorizontal)
	{
		int aThumbX = (int) (mVal * (mWidth - mThumbImage->GetWidth())) + mThumbOffsetX;
		if ((x >= aThumbX) && (x < aThumbX + mThumbImage->GetWidth()))
			mWidgetManager->mApp->SetCursor(CURSOR_DRAGGING);
		else
			mWidgetManager->mApp->SetCursor(CURSOR_POINTER);
	}
	else
	{
		int aThumbY = (int)(mVal * (mHeight - mThumbImage->GetHeight()));
		int aThumbCenterX = (mWidth - mThumbImage->GetWidth()) / 2 + mThumbOffsetX;
		if ((x >= aThumbCenterX) && (x < aThumbCenterX + mThumbImage->GetWidth()) && (y >= aThumbY) && (y < aThumbY + mThumbImage->GetHeight()))
			mWidgetManager->mApp->SetCursor(CURSOR_DRAGGING);
		else
			mWidgetManager->mApp->SetCursor(CURSOR_POINTER);
	}
}

void Slider::MouseDrag(int x, int y)
{
	if (mDragging)
	{	
		double anOldVal = mVal;

		if (mHorizontal)
			mVal = (x - mRelX) / (double) (mWidth - mThumbImage->GetWidth());
		else
			mVal = (y - mRelY) / (double) (mHeight - mThumbImage->GetHeight());

		if (mVal < 0.0)
			mVal = 0.0;
		if (mVal > 1.0)
			mVal = 1.0;

		if (mVal != anOldVal)
		{
			mListener->SliderVal(mId, mVal);
			MarkDirtyFull();
		}
	}
}

void Slider::MouseUp(int x, int y)
{
	mDragging = false;
	mWidgetManager->mApp->SetCursor(CURSOR_POINTER);
	mListener->SliderVal(mId, mVal);
}

void Slider::MouseLeave()
{
	if (!mDragging)
		mWidgetManager->mApp->SetCursor(CURSOR_POINTER);
}