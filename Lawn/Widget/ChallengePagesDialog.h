#ifndef __CHALLENGEPAGESDIALOG_H__
#define __CHALLENGEPAGESDIALOG_H__

#include "LawnDialog.h"
#include "../../SexyAppFramework/SliderListener.h"
#include "../../SexyAppFramework/Slider.h"

//Made by BULLETBOT

class ChallengePagesDialog : public LawnDialog, public Sexy::SliderListener
{
public:
	LawnApp* mApp;
	Sexy::Slider* mSlider;
	LawnStoneButton* mPageButtons[MAX_CHALLENGE_PAGES];
	Rect						mPageButtonRects[MAX_CHALLENGE_PAGES];
	float						mScrollPosition;
	float						mScrollAmount;
	const float					mBaseScrollSpeed = 1.0f;
	const float					mScrollAccel = 0.1f;
	float						mMaxScrollPosition;
	Rect						mClipRect;

public:
	ChallengePagesDialog(LawnApp* theApp);
	virtual ~ChallengePagesDialog();

	virtual void				AddedToManager(WidgetManager* theWidgetManager);
	virtual void				RemovedFromManager(WidgetManager* theWidgetManager);
	virtual void				Draw(Graphics* g);
	virtual void				Update();
	virtual void				ButtonDepress(int theId);
	virtual void                SliderVal(int theId, double theVal);
	virtual void			    MouseWheel(int theDelta);
	virtual void				KeyDown(KeyCode theKey);
};

#endif