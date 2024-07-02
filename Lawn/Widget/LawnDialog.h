#ifndef __LAWNDIALOG_H__
#define __LAWNDIALOG_H__

#include "../../Sexy.TodLib/TodCommon.h"
#include "../../SexyAppFramework/Dialog.h"

constexpr const int DIALOG_HEADER_OFFSET = 45;

class LawnApp;
class LawnDialog;
class Reanimation;
class LawnStoneButton;
class ReanimationWidget;
namespace Sexy
{
	class Checkbox;
	class DialogButton;
	class CheckboxListener;
}

using namespace std;
using namespace Sexy;

class ReanimationWidget : public Widget
{
public:
    LawnApp*				mApp;					
    Reanimation*			mReanim;				
    LawnDialog*				mLawnDialog;			
    float					mPosX;					
    float					mPosY;					

public:
	ReanimationWidget();
	virtual ~ReanimationWidget();

	/*inline*/ void			Dispose();
	virtual void			Draw(Graphics*);
	virtual void			Update();
	void					AddReanimation(float x, float y, ReanimationType theReanimationType);
};

class LawnDialog : public Dialog
{
public:
	LawnApp*				mApp;					
	int						mButtonDelay;			
	ReanimationWidget*		mReanimation;			
	bool					mDrawStandardBack;		
	LawnStoneButton*		mLawnYesButton;			
	LawnStoneButton*		mLawnNoButton;			
	bool					mTallBottom;			
	bool					mVerticalCenterText;	

public:
	LawnDialog(LawnApp* theApp, int theId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode);
	~LawnDialog();

	int						GetLeft();
	int						GetWidth();
	int						GetTop();
	virtual void			SetButtonDelay(int theDelay);
	virtual void			Update();
	virtual void			ButtonPress(int theId);
	virtual void			ButtonDepress(int theId);
	virtual void			CheckboxChecked(int theId, bool theChecked);
	virtual void			KeyDown(KeyCode theKey);
	virtual void			AddedToManager(WidgetManager* theWidgetManager);
	virtual void			RemovedFromManager(WidgetManager* theWidgetManager);
	virtual void			Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void			Draw(Graphics* g);
	void					CalcSize(int theExtraX, int theExtraY);
};

class GameOverDialog : public LawnDialog
{
public:
	DialogButton*			mMenuButton;

public:
	GameOverDialog(const SexyString& theMessage, bool theShowChallengeName);
	virtual ~GameOverDialog();

	virtual void			ButtonDepress(int theId);
	virtual void			AddedToManager(WidgetManager* theWidgetManager);
	virtual void			RemovedFromManager(WidgetManager* theWidgetManager);
	virtual void			MouseDrag(int x, int y);
};

#endif
