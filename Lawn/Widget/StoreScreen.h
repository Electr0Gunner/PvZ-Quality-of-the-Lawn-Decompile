#ifndef __STORESCREEN_H__
#define __STORESCREEN_H__

#include "../../ConstEnums.h"
#include "../System/PlayerInfo.h"
#include "../../Sexy.TodLib/DataArray.h"
#include "../../SexyAppFramework/Dialog.h"
using namespace std;
using namespace Sexy;

#define MAX_PAGE_SPOTS 8
#define MAX_PURCHASES 80

class Coin;
class LawnApp;
class NewLawnButton;

class StoreScreen : public Dialog
{
private:
    enum
    {
        StoreScreen_Back = 100,
        StoreScreen_Prev = 101,
        StoreScreen_Next = 102
    };

public:
	LawnApp*					mApp;                           
	NewLawnButton*				mBackButton;                    
	NewLawnButton*				mPrevButton;                    
	NewLawnButton*				mNextButton;                    
    Widget*                     mOverlayWidget;                 
	int                         mStoreTime;                     
	string                      mBubbleText;                    
    int                         mBubbleCountDown;               
    bool                        mBubbleClickToContinue;         
    int                         mAmbientSpeechCountDown;        
    int                         mPreviousAmbientSpeechIndex;    
    StorePages                  mPage;                          
    StoreItem                   mMouseOverItem;                 
    int                         mHatchTimer;                    
    bool                        mHatchOpen;                     
    int                         mShakeX;                        
    int                         mShakeY;                        
    int                         mStartDialog;                   
    bool                        mEasyBuyingCheat;               
    bool                        mWaitForDialog;                 
    PottedPlant                 mPottedPlantSpecs;              
    DataArray<Coin>             mCoins;                         
    bool                        mDrawnOnce;                     
    bool                        mGoToTreeNow;                   
    bool                        mPurchasedFullVersion;          
    bool                        mTrialLockedWhenStoreOpened;    
    bool                        mInCutscene;

public:
    StoreScreen(LawnApp* theApp);
    virtual ~StoreScreen();

    /*inline*/ StoreItem        GetStoreItemType(int theSpotIndex);
    bool                        IsFullVersionOnly(StoreItem theStoreItem);
    static /*inline*/ bool      IsPottedPlant(StoreItem theStoreItem);
    bool                        IsComingSoon(StoreItem theStoreItem);
    bool                        IsItemSoldOut(StoreItem theStoreItem);
    bool                        IsItemUnavailable(StoreItem theStoreItem);
    static /*inline*/ void      GetStorePosition(int theSpotIndex, int& thePosX, int& thePosY);
    void                        DrawItemIcon(Graphics* g, int theItemPosition, StoreItem theItemType, bool theIsForHighlight);
    void                        DrawItem(Graphics* g, int theItemPosition, StoreItem theItemType);
    virtual void                Draw(Graphics* g);
    virtual void                DrawOverlay(Graphics* g);
    /*inline*/ void             SetBubbleText(int theCrazyDaveMessage, int theTime, bool theClickToContinue);
    void                        UpdateMouse();
    void                        StorePreload();
    /*inline*/ bool             CanInteractWithButtons();
    virtual void                Update();
    virtual void                AddedToManager(WidgetManager* theWidgetManager);
    virtual void                RemovedFromManager(WidgetManager* theWidgetManager);
    virtual void                ButtonPress(int theId);
    /*inline*/ bool             IsPageShown(StorePages thePage);
    virtual void                ButtonDepress(int theId);
    virtual void                KeyChar(char theChar);
    static /*inline*/ int		GetItemCost(StoreItem theStoreItem);
    /*inline*/ bool             CanAffordItem(StoreItem theStoreItem);
    void                        PurchaseItem(StoreItem theStoreItem);
    void                        AdvanceCrazyDaveDialog();
    virtual void                MouseDown(int x, int y, int theClickCount);
    /*inline*/ void             EnableButtons(bool theEnable);
    void                        SetupForIntro(int theDialogIndex);
};

class StoreScreenOverlay : public Widget
{
public:
    StoreScreen*                mParent;

public:
    StoreScreenOverlay(StoreScreen* theParent);
    virtual void                Draw(Graphics* g);
};


#endif
