#ifndef __CREDITSCREEN_H__
#define __CREDITSCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/PerfTimer.h"
#include "../../SexyAppFramework/ButtonListener.h"

using namespace Sexy;

enum CreditsPhase
{
	CREDITS_MAIN1,
	CREDITS_MAIN2,
	CREDITS_MAIN3,
	CREDITS_END
};

enum CreditLayer
{
	CREDIT_LAYER_BACKGROUND,
	CREDIT_LAYER_ZOMBIE,
	CREDIT_LAYER_TOP
};

enum CreditWordType
{
	WORD_AA,
	WORD_EE,
	WORD_AW,
	WORD_OH,
	WORD_OFF
};

enum CreditBrainType
{
	BRAIN_FLY_ON,
	BRAIN_FAST_ON,
	BRAIN_NEXT_WORD,
	BRAIN_FAST_OFF,
	BRAIN_FLY_OFF,
	BRAIN_OFF
};

class CreditsTiming
{
public:
	float					mFrame;						
	CreditWordType			mWordType;					
	int						mWordX;						
	CreditBrainType			mBrainType;					
};

class TodsHackyUnprotectedPerfTimer : public PerfTimer
{
public:
	void					SetStartTime(int theTimeMillisecondsAgo);
};

class GameButton;
class LawnApp;
class LawnStoneButton;
class NewLawnButton;
class Reanimation;

class CreditScreen : public Widget, public ButtonListener
{
protected:
	enum
	{
		Credits_Button_Replay,
		Credits_Button_MainMenu
	};

public:
	GameButton*				mCloseButton;				
	LawnApp*				mApp;						
	CreditsPhase			mCreditsPhase;				
	int						mCreditsPhaseCounter;		
	ReanimationID			mCreditsReanimID;			
	ParticleSystemID		mFogParticleID;				
	int						mBlinkCountdown;			
	LawnStoneButton*		mMainMenuButton;			
	NewLawnButton*			mReplayButton;				
	Widget*					mOverlayWidget;				
	bool					mDrawBrain;					
	float					mBrainPosX;					
	float					mBrainPosY;					
	int						mUpdateCount;				
	int						mDrawCount;					
	PerfTimer				mTimerSinceStart;			
	bool					mDontSync;					
	bool					mCreditsPaused;				
	double					mOriginalMusicVolume;		
	bool					mPreloaded;					
	int						mLastDrawCount;				

public:
	CreditScreen(LawnApp* theApp);
	virtual ~CreditScreen();

	virtual void			Update();
	virtual void			Draw(Graphics* g);
	virtual void			KeyChar(SexyChar theChar);
	virtual void			KeyDown(KeyCode theKey);
	virtual void			MouseUp(int x, int y, int theClickCount);
	virtual void			AddedToManager(WidgetManager* theWidgetManager);
	virtual void			RemovedFromManager(WidgetManager* theWidgetManager);
	virtual void			ButtonPress(int theId);
	virtual void			ButtonDepress(int theId);
	Reanimation*			PlayReanim(int aIndex);
	void					JumpToFrame(CreditsPhase thePhase, float theFrame);
	void					GetTiming(CreditsTiming** theBeforeTiming, CreditsTiming** theAfterTiming, float* theFraction);
	static Reanimation*		FindSubReanim(Reanimation* theReanim, ReanimationType theReanimType);
	void					DrawFogEffect(Graphics* g, float theTime);
	void					UpdateBlink();
	void					TurnOffTongues(Reanimation* theReanim, int aParentTrack);
	void					DrawFinalCredits(Graphics* g);
	void					DrawOverlay(Graphics* g);
	void					UpdateMovie();
	void					PauseCredits();
	void					PreLoadCredits();
};

void						DrawDisco(Graphics* g, float aCenterX, float aCenterY, float theTime);
void						DrawReanimToPreload(Graphics* g, ReanimationType theReanimType);

class CreditsOverlay : public Widget
{
public:
	CreditScreen*			mParent;

public:
	CreditsOverlay(CreditScreen* theCreditScreen);

	void					Draw(Graphics* g);
};

#endif
