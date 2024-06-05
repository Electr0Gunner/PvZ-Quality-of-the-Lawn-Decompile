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

public:
    AchievementScreen(LawnApp* theApp);
    virtual ~AchievementScreen();
    void                        DrawButton(Graphics* g);
    virtual void                Draw(Graphics* g);
    virtual void                Update();
    virtual void                AddedToManager(WidgetManager* theWidgetManager);
    virtual void                RemovedFromManager(WidgetManager* theWidgetManager);
    virtual void                ButtonPress(int theId);
    virtual void                ButtonDepress(int theId);
};
#endif