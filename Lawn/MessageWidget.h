#ifndef __MESSAGEWIDGET_H__
#define __MESSAGEWIDGET_H__

#include "../ConstEnums.h"
#include "../SexyAppFramework/Common.h"

#define MAX_MESSAGE_LENGTH 128
#define MAX_REANIM_LINES 5

class LawnApp;
namespace Sexy
{
	class Font;
	class Graphics;
}

class MessageWidget
{
public:
	LawnApp*			mApp;									
	SexyChar			mLabel[MAX_MESSAGE_LENGTH];				
	int					mDisplayTime;							
	int					mDuration;								
	MessageStyle		mMessageStyle;							
	ReanimationID		mTextReanimID[MAX_MESSAGE_LENGTH];		
	ReanimationType		mReanimType;							
	int					mSlideOffTime;							
	SexyChar			mLabelNext[MAX_MESSAGE_LENGTH];			
	MessageStyle		mMessageStyleNext;						

public:
	MessageWidget(LawnApp* theApp);
	~MessageWidget() { ClearReanim(); }

	/*inline*/ void		SetLabel(const SexyString& theNewLabel, MessageStyle theMessageStyle);
	void				Update();
	void				Draw(Sexy::Graphics* g);
	void				ClearReanim();
	/*inline*/ void		ClearLabel();
	inline bool			IsBeingDisplayed() { return mDuration != 0; }
	/*inline*/ Font*	GetFont();
	void				DrawReanimatedText(Sexy::Graphics* g, Sexy::Font* theFont, const Sexy::Color& theColor, float thePosY);
	void				LayoutReanimText();
};

#endif