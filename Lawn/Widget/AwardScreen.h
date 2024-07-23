#ifndef __AWARDSCREEN_H__
#define __AWARDSCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/SliderListener.h"
#include "../../SexyAppFramework/Slider.h"

using namespace Sexy;

class LawnApp;
class GameButton;
class AwardScreen : public Widget, public SliderListener
{
private:
	enum
	{
		AwardScreen_Start,
		AwardScreen_Menu,
		AwardScreen_Slider
	};

public:
	GameButton* mStartButton;
	GameButton* mMenuButton;
	LawnApp* mApp;
	int					mFadeInCounter;
	int					mAchievementCounter;
	AwardType			mAwardType;
	bool				mShowAchievements;
	bool				mWasDrawn;
	SexyString			mState;
	Sexy::Slider* mSlider;
	float				mScrollPosition;
	float				mScrollAmount;
	const float			mBaseScrollSpeed = 1.75f;
	const float			mScrollAccel = 0.1f;
	float				mMaxScrollPosition;

public:
	AwardScreen(LawnApp* theApp, AwardType theAwardType, bool hasAchievement);
	virtual ~AwardScreen();

	/*inline*/ bool		IsPaperNote();
	void				LoadAchievements();
	void				DrawBottom(Graphics* g, SexyString theTitle, SexyString theAward, SexyString theMessage);
	void				DrawAwardSeed(Graphics* g);
	virtual void		Draw(Graphics* g);
	virtual void		Update();
	virtual void		AddedToManager(WidgetManager* theWidgetManager);
	virtual void		RemovedFromManager(WidgetManager* theWidgetManager);
	virtual void		KeyChar(char theChar);
	void				StartButtonPressed();
	void				ExitScreen();
	virtual void		MouseDown(int x, int y, int theClickCount);
	virtual void		MouseUp(int x, int y, int theClickCount);
	virtual void        SliderVal(int theId, double theVal);
	virtual void		MouseWheel(int theDelta);
	void				StartSounds();
};

#endif