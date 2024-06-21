#ifndef __QUICKPLAYSCREEN_H__
#define __QUICKPLAYSCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/ButtonListener.h"
#include "../../SexyAppFramework/CheckboxListener.h"

using namespace Sexy;

namespace Sexy
{
    class Checkbox;
};

class LawnApp;
class GameButton;
class NewLawnButton;
class Zombie;
class Plant;

class QuickPlayScreen : public Widget, public Sexy::ButtonListener, public Sexy::CheckboxListener
{
public:
    LawnApp* mApp;
    NewLawnButton* mBackButton;
    NewLawnButton* mLeftButton;
    NewLawnButton* mRightButton;
    LawnStoneButton* mPlayButton;
    BackgroundType              mBackground;
    ZombieType                  mZombieType;
    SeedType                    mSeedType;
    int                         mLevel;
    Zombie* mDisplayZombie;
    Plant* mDisplayPlant;
    Plant* mFlowerPot;
    ReanimationID			    mHammerID;
    Checkbox*         mCrazySeedsCheck;

public:
    QuickPlayScreen(LawnApp* theApp);
    virtual ~QuickPlayScreen();
    void                        KeyDown(KeyCode theKey);
    void                        DrawPool(Graphics* g, bool isNight);
    void                        ChooseBackground();
    void                        ChooseZombieType();
    void                        ResetZombie();
    void                        ResetPlant();
    void                        StartLevel();
    void                        ExitScreen();
    void                        PreviousLevel();
    void                        NextLevel();
    ZombieType                  GetZombieType(int ID);
    virtual void                Draw(Graphics* g);
    virtual void                Update();
    virtual void                AddedToManager(WidgetManager* theWidgetManager);
    virtual void                RemovedFromManager(WidgetManager* theWidgetManager);
    virtual void                ButtonPress(int theId);
    virtual void                ButtonDepress(int theId);
};
#endif
