#ifndef __QUICKPLAYSCREEN_H__
#define __QUICKPLAYSCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/ButtonListener.h"

using namespace Sexy;

class LawnApp;
class GameButton;
class NewLawnButton;
class Zombie;
class Plant;

class QuickPlayScreen : public Widget, public Sexy::ButtonListener
{
public:
    LawnApp*                    mApp;
    NewLawnButton*              mBackButton;
    NewLawnButton*              mLeftButton;
    NewLawnButton*              mRightButton;
    GameButton*                 mPlayButton;
    BackgroundType              mBackground;
    ZombieType                  mZombieType;
    int                         mLevel;
    Zombie*                     mDisplayZombie;
    Plant*                      mDisplayPlant;

public:
    QuickPlayScreen(LawnApp* theApp);
    virtual ~QuickPlayScreen();
    void                        DrawButton(Graphics* g);
    void                        KeyDown(KeyCode theKey);
    void                        DrawPool(Graphics* g, bool isNight);
    void                        ChooseBackground();
    void                  ChooseZombieType();
    void                        ResetZombie();
    virtual void                Draw(Graphics* g);
    virtual void                Update();
    virtual void                AddedToManager(WidgetManager* theWidgetManager);
    virtual void                RemovedFromManager(WidgetManager* theWidgetManager);
    virtual void                ButtonPress(int theId);
    virtual void                ButtonDepress(int theId);
    virtual void			    MouseUp(int x, int y, int theClickCount);
};
#endif