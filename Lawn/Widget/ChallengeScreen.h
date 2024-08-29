#ifndef __CHALLENGESCREEN_H__
#define __CHALLENGESCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Dialog.h"
#include "../../SexyAppFramework/SliderListener.h"
#include "../../SexyAppFramework/Slider.h"
using namespace Sexy;

#define NUM_CHALLENGE_MODES GameMode::NUM_GAME_MODES - 1

class LawnApp;
class ToolTipWidget;
class NewLawnButton;
namespace Sexy
{
    class Slider;
};

class ChallengeScreen : public Widget, public ButtonListener, public Sexy::SliderListener
{
private:
    enum
    {
        ChallengeScreen_Back,
        ChallengeScreen_Selector,
        ChallengeScreen_Mode = 100
    };

public:
    NewLawnButton*              mBackButton;                                
    NewLawnButton*              mChallengesButton;
    ButtonWidget*               mChallengeButtons[NUM_CHALLENGE_MODES];     
    LawnApp*                    mApp;                                       
    ToolTipWidget*              mToolTip;                                   
    ChallengePage               mPageIndex;                                 
    bool                        mCheatEnableChallenges;                     
    UnlockingState              mUnlockState;                               
    int                         mUnlockStateCounter;                        
    int                         mUnlockChallengeIndex;                      
    float                       mLockShakeX;                                
    float                       mLockShakeY;                                
    float						mScrollPosition;
    float						mScrollAmount;
    const float					mBaseScrollSpeed = 1.0f;
    const float					mScrollAccel = 0.1f;
    float						mMaxScrollPosition;
    Sexy::Slider*               mSlider;
    int                         mButtonYOffset;
    int                         mButtonStartYOffset;

public:
    ChallengeScreen(LawnApp* theApp, ChallengePage thePage);
    virtual ~ChallengeScreen();
    void                        SetUnlockChallengeIndex(ChallengePage thePage, bool theIsIZombie = false);
    int                         MoreTrophiesNeeded(int theChallengeIndex);
    /*inline*/ bool             ShowPageButtons();
    void                        UpdateButtons();
    int                         AccomplishmentsNeeded(int theChallengeIndex);
    void                        DrawButton(Graphics* g, int theChallengeIndex);
    virtual void                Draw(Graphics* g);
    virtual void                Update();
    virtual void                AddedToManager(WidgetManager* theWidgetManager);
    virtual void                RemovedFromManager(WidgetManager* theWidgetManager);
    virtual void                ButtonPress(int theId);
    virtual void                ButtonDepress(int theId);
    void                        UpdateToolTip();
    virtual void                KeyChar(char theChar) { ; }
    void                        SliderVal(int theId, double theVal);
    virtual void			    MouseWheel(int theDelta);
    SexyString                  GetPageTitle(ChallengePage thePage);
    bool                        IsPageUnlocked(ChallengePage thePage);

    /*inline*/ bool             IsScaryPotterLevel(GameMode theGameMode);
    /*inline*/ bool             IsIZombieLevel(GameMode theGameMode);
};

class ChallengeDefinition
{
public:
    GameMode                    mChallengeMode; //identifier of the challenge ex: CHALLENGE_GAMEMODE_FINAL_BOSS
    int                         mChallengeIconIndex; // index of the thumbnail
    ChallengePage               mPage; //the page ex:  CHALLENGE_PAGE_PUZZLE
    int                         mRow; // the row in the specific page
    int                         mCol; // the same but the collumn
    const SexyChar*             mChallengeName; //the name
};
extern ChallengeDefinition gChallengeDefs[NUM_CHALLENGE_MODES];

ChallengeDefinition& GetChallengeDefinition(int theChallengeMode);

#endif