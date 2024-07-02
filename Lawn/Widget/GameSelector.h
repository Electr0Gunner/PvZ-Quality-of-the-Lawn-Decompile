#ifndef __GAMESELECTOR_H__
#define __GAMESELECTOR_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/ButtonListener.h"

class LawnApp;
class ToolTipWidget;
class AchievementScreen;
namespace Sexy
{
    class DialogButton;
}

using namespace Sexy;

enum SelectorAnimState
{
    SELECTOR_OPEN,
    SELECTOR_NEW_USER,
    SELECTOR_SHOW_SIGN,
    SELECTOR_SUB_MENU,
    SELECTOR_IDLE,
};

class GameSelector : public Widget, public ButtonListener
{
private:
    enum
    {
        GameSelector_Adventure = 100,
        GameSelector_Minigame = 101,
        GameSelector_Puzzle = 102,
        GameSelector_Options = 103,
        GameSelector_Help = 104,
        GameSelector_Quit = 105,
        GameSelector_ChangeUser = 106,
        GameSelector_Store = 107,
        GameSelector_Almanac = 108,
        GameSelector_ZenGarden = 109,
        GameSelector_Survival = 110,
        GameSelector_Achievement = 111,
        GameSelector_QuickPlay = 112,
        GameSelector_Credits = 113
    };

public:
    LawnApp*                    mApp;                       
    NewLawnButton*              mAdventureButton;           
    NewLawnButton*              mMinigameButton;            
    NewLawnButton*              mPuzzleButton;              
    NewLawnButton*              mOptionsButton;             
    NewLawnButton*              mQuitButton;                
    NewLawnButton*              mHelpButton;                
    NewLawnButton*              mStoreButton;               
    NewLawnButton*              mAlmanacButton;             
    NewLawnButton*              mZenGardenButton;           
    NewLawnButton*              mAchievementButton;                
    NewLawnButton*              mQuickPlayButton;
    NewLawnButton*              mCreditsButton;
    NewLawnButton*              mSurvivalButton;            
    NewLawnButton*              mChangeUserButton;          
    Widget*                     mOverlayWidget;             
    bool                        mStartingGame;              
    int                         mStartingGameCounter;       
    bool                        mMinigamesLocked;           
    bool                        mPuzzleLocked;              
    bool                        mSurvivalLocked;            
    bool                        mShowStartButton;           
    ParticleSystemID            mTrophyParticleID;          
    ReanimationID               mSelectorReanimID;          
    ReanimationID               mCloudReanimID[6];          
    int                         mCloudCounter[6];           
    ReanimationID               mFlowerReanimID[3];         
    ReanimationID               mLeafReanimID;              
    ReanimationID               mHandReanimID;              
    int                         mLeafCounter;               
    SelectorAnimState           mSelectorState;             
    int                         mLevel;                     
    bool                        mLoading;                   
    ToolTipWidget*              mToolTip;                   
    bool                        mHasTrophy;                 
    bool                        mUnlockSelectorCheat;       
    bool                        mDebugText;
    int                         mMovementTimer;
    int                         mCurrentY;
    int                         mDestinationY;
    int                         mCurrentX;
    int                         mDestinationX;
    bool                        mEnableButtonsTransition;

public:
    GameSelector(LawnApp* theApp);
    virtual ~GameSelector();

    void                        SyncProfile(bool theShowLoading);
    virtual void                Draw(Graphics* g);
    virtual void                DrawOverlay(Graphics* g);
    virtual void                Update();
    virtual void                AddedToManager(WidgetManager* theWidgetManager);
    virtual void                RemovedFromManager(WidgetManager* theWidgetManager);
    virtual void                OrderInManagerChanged();
    virtual void                ButtonMouseEnter(int theId);
    virtual void                ButtonPress(int theId, int theClickCount);
    virtual void                ButtonDepress(int theId);
    virtual void                KeyDown(KeyCode theKey);
    virtual void                KeyChar(char theChar);
    virtual void                MouseDown(int x, int y, int theClickCount);
    void                        TrackButton(DialogButton* theButton, const char* theTrackName, float theOffsetX, float theOffsetY);
    void                        SyncButtons();
    void                        AddTrophySparkle();
    void                        ClickedAdventure();
    void                        UpdateTooltip();
    /*inline*/ bool             ShouldDoZenTuturialBeforeAdventure();
    void                        AddPreviewProfiles();
    void                        KeyChar();
    int                         CalcYPos(int ogY, int newY);
    int                         CalcXPos(int ogX, int newX);
};

class GameSelectorOverlay : public Widget
{
public:
    GameSelector*               mParent;                    

public:
    GameSelectorOverlay(GameSelector* theGameSelector);
    virtual ~GameSelectorOverlay() { }

    virtual void Draw(Graphics* g);
};

#endif
