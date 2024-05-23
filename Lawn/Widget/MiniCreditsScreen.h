#ifndef __MINICREDITSSCREEN_H__
#define __MINICREDITSSCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"
#include "../../SexyAppFramework/ButtonListener.h"

using namespace Sexy;

class LawnApp;
class GameButton;
class NewLawnButton;
class MiniCreditsScreen : public Widget, public Sexy::ButtonListener
{
public:
    NewLawnButton* mBackButton;
    NewLawnButton* mMusicButton;
    LawnApp* mApp;

public:
    MiniCreditsScreen(LawnApp* theApp);
    virtual ~MiniCreditsScreen();
    void                        DrawButton(Graphics* g);
    virtual void                Draw(Graphics* g);
    virtual void                Update();
    virtual void                AddedToManager(WidgetManager* theWidgetManager);
    virtual void                RemovedFromManager(WidgetManager* theWidgetManager);
    virtual void                ButtonPress(int theId);
    virtual void                ButtonDepress(int theId);
};
#endif