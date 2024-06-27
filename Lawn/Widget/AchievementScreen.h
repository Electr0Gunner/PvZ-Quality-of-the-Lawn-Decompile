#ifndef __ACHIEVEMENTSCREEN_H__
#define __ACHIEVEMENTSCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/ButtonListener.h"

using namespace Sexy;

class LawnApp;
class GameButton;
class NewLawnButton;

class AchievementScreen : public Widget, public Sexy::ButtonListener
{
public:
    LawnApp* mApp;
    NewLawnButton* mBackButton;
    NewLawnButton* mRockButton;
    float						mScrollPosition;
    float						mScrollAmount;
    const float					mBaseScrollSpeed = 5.5f;
    const float					mScrollAccel = 0.2f;
    float						mMaxScrollPosition;
    int						    mTweenTimer;
    bool						mGoesDown;

public:
    AchievementScreen(LawnApp* theApp);
    virtual ~AchievementScreen();
    void                        KeyDown(KeyCode theKey);
    void				        DoButtonMovement(int StartX, int FinalX);
    void                        ExitScreen();
    virtual void                Draw(Graphics* g);
    virtual void                Update();
    virtual void                AddedToManager(WidgetManager* theWidgetManager);
    virtual void                RemovedFromManager(WidgetManager* theWidgetManager);
    virtual void                ButtonPress(int theId);
    virtual void                ButtonDepress(int theId);
    virtual void				MouseWheel(int theDelta);
};
#endif