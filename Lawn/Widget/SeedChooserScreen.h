#ifndef __SEEDCHOOSERSCREEN_H__
#define __SEEDCHOOSERSCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/ScrollListener.h"
#include "../../SexyAppFramework/ScrollbarWidget.h"
#include "../../SexyAppFramework/SliderListener.h"
#include "../../SexyAppFramework/Slider.h"

const int IMITATER_POS_X = 459;
const int IMITATER_POS_Y = 503;

using namespace Sexy;

class Board;
class Slider;
class LawnApp;
class GameButton;
class ToolTipWidget;
namespace Sexy
{
    class MTRand;
}

class ChosenSeed
{
public:
    int                     mX;                                
    int                     mY;                                
    int                     mTimeStartMotion;                  
    int                     mTimeEndMotion;                    
    int                     mStartX;                           
    int                     mStartY;                           
    int                     mEndX;                             
    int                     mEndY;                             
    SeedType                mSeedType;                         
    ChosenSeedState         mSeedState;                        
    int                     mSeedIndexInBank;                  
    bool                    mRefreshing;                       
    int                     mRefreshCounter;                   
    SeedType                mImitaterType;                     
    bool                    mCrazyDavePicked;                  
};

class SeedChooserScreen : public Widget, public Sexy::SliderListener
{
private:
    enum
    {
        SeedChooserScreen_Start = 100,
        SeedChooserScreen_Random = 101,
        SeedChooserScreen_ViewLawn = 102,
        SeedChooserScreen_Almanac = 103,
        SeedChooserScreen_Menu = 104,
        SeedChooserScreen_Store = 105,
        SeedChooserScreen_Imitater = 106,
        SeedChooserScreen_Scrollbar = 107
    };

public:
    GameButton*             mStartButton;                       
    GameButton*             mRandomButton;                      
    GameButton*             mViewLawnButton;                    
    GameButton*             mStoreButton;                       
    GameButton*             mAlmanacButton;                     
    GameButton*             mMenuButton;
    ChosenSeed              mChosenSeeds[NUM_SEED_TYPES];
    LawnApp*                mApp;                               
    Board*                  mBoard;                             
    int                     mNumSeedsToChoose;                  
    int                     mSeedChooserAge;                    
    int                     mSeedsInFlight;                     
    int                     mSeedsInBank;                       
    ToolTipWidget*          mToolTip;                           
    int                     mToolTipSeed;                       
    int                     mLastMouseX;                        
    int                     mLastMouseY;                        
    SeedChooserState        mChooseState;                       
    int                     mViewLawnTime;                      
    float                   mScrollPosition;
    float                   mScrollAmount;
    Sexy::Slider*           mSlider;
    const float             mBaseScrollSpeed = 1.0f;
    const float             mScrollAccel = 0.1f;
    float					mMaxScrollPosition;
    SeedType                mPreviousType;


public:
    SeedChooserScreen();
    ~SeedChooserScreen();

    static /*inline*/ int   PickFromWeightedArrayUsingSpecialRandSeed(TodWeightedArray* theArray, int theCount, MTRand& theLevelRNG);
    void                    CrazyDavePickSeeds();
    bool                    Has7Rows();
    void                    GetSeedPositionInChooser(int theIndex, int& x, int& y);
    /*inline*/ void         GetSeedPositionInBank(int theIndex, int& x, int& y);
    /*inline*/ unsigned int SeedNotRecommendedToPick(SeedType theSeedType);
    /*inline*/ bool         SeedNotAllowedToPick(SeedType theSeedType);
    /*inline*/ bool         SeedNotAllowedDuringTrial(SeedType theSeedType);
    virtual void            Draw(Graphics* g);
    void                    UpdateViewLawn();
    void                    LandFlyingSeed(ChosenSeed& theChosenSeed);
    void                    UpdateCursor();
    virtual void            Update();
    /*inline*/ bool         DisplayRepickWarningDialog(const SexyChar* theMessage);
    bool                    FlyersAreComming();
    bool                    FlyProtectionCurrentlyPlanted();
    bool                    CheckSeedUpgrade(SeedType theSeedTypeTo, SeedType theSeedTypeFrom);
    void                    OnStartButton();
    void                    PickRandomSeeds();
    virtual void            ButtonDepress(int theId);
    SeedType                SeedHitTest(int x, int y);
    Zombie*                 ZombieHitTest(int x, int y);
    SeedType                FindSeedInBank(int theIndexInBank);
    /*inline*/ void         EnableStartButton(bool theEnabled);
    void                    ClickedSeedInBank(ChosenSeed& theChosenSeed);
    void                    ClickedSeedInChooser(ChosenSeed& theChosenSeed);
    void                    ShowToolTip();
    /*inline*/ void         RemoveToolTip();
    /*inline*/ void         CancelLawnView();
    virtual void            MouseUp(int x, int y, int theClickCount);
    bool                    IsImitaterUnselectable(SeedType seedType);
    bool                    IsOverImitater(int x, int y);
    virtual void            MouseDown(int x, int y, int theClickCount);
    /*inline*/ bool         PickedPlantType(SeedType theSeedType);
    void                    CloseSeedChooser();
    virtual void            KeyDown(KeyCode theKey);
    virtual void            KeyChar(SexyChar theChar);
    virtual void			MouseWheel(int theDelta);
    void                    UpdateAfterPurchase();
    void                    SliderVal(int theId, double theVal);
    virtual void			RemovedFromManager(WidgetManager* theWidgetManager);
    virtual void			AddedToManager(WidgetManager* theWidgetManager);
    void                    ResizeSlider();
};

#endif
