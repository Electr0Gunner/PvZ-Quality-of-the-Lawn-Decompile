#ifndef __TITLESCREEN_H__
#define __TITLESCREEN_H__

#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/ButtonListener.h"

using namespace Sexy;

enum TitleState
{
	TITLESTATE_WAITING_FOR_FIRST_DRAW,
	TITLESTATE_POPCAP_LOGO,
	TITLESTATE_PARTNER_LOGO,
	TITLESTATE_SCREEN
};

namespace Sexy
{
	class HyperlinkWidget;
}

class LawnApp;

class TitleScreen :public Sexy::Widget, public Sexy::ButtonListener
{
public:
	enum
	{
		TitleScreen_Start,
		TitleScreen_Register
	};

public:
	HyperlinkWidget*		mStartButton;				
	float					mCurBarWidth;				
	float					mTotalBarWidth; 			
	float					mBarVel;					
	float					mBarStartProgress;			
	bool					mRegisterClicked;			
	bool					mLoadingThreadComplete;		
	int						mTitleAge;					
	KeyCode					mQuickLoadKey;				
	bool					mNeedRegister;				
	bool					mNeedShowRegisterBox;		
	bool					mDrawnYet;					
	bool					mNeedToInit;				
	float					mPrevLoadingPercent;		
	TitleState				mTitleState;				
	int						mTitleStateCounter;			
	int						mTitleStateDuration;		
	bool					mDisplayPartnerLogo;		
	bool					mLoaderScreenIsLoaded;		
	LawnApp*				mApp;						

public:
	TitleScreen(LawnApp* theApp);
	virtual ~TitleScreen();

	virtual void			Update();
	virtual void			Draw(Graphics* g);
	virtual void			Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void			AddedToManager(WidgetManager* theWidgetManager);
	virtual void			RemovedFromManager(WidgetManager* theWidgetManager);
	virtual void			ButtonPress(int theId);
	virtual void			ButtonDepress(int theId);
	virtual void			MouseDown(int x, int y, int theClickCount);
	virtual void			KeyDown(KeyCode theKey);
	void					SetRegistered();
	void					DrawToPreload(Graphics* g);
};

#endif