#ifndef __NEWOPTIONSDIALOG_H__
#define __NEWOPTIONSDIALOG_H__

#include "../../SexyAppFramework/Dialog.h"
#include "../../SexyAppFramework/SliderListener.h"
#include "../../SexyAppFramework/CheckboxListener.h"
#include "../../SexyAppFramework/EditListener.h"

const int ADVANCED_PAGE_Y = 355;
const int ADVANCED_MAX_PAGES = 3;
const int ADVANCED_SPEED_MIN = 2;
const int ADVANCED_SPEED_MAX = 9;
const int ADVANCED_SPEED_X = 284;
const int ADVANCED_SPEED_Y = 148;

class LawnApp;
class LawnStoneButton;
class NewLawnButton;
namespace Sexy
{
	class Slider;
	class Checkbox;
};

class NewOptionsDialog : public Sexy::Dialog, public Sexy::SliderListener, public Sexy::CheckboxListener, public EditListener
{
protected:
	enum
	{
		NewOptionsDialog_Almanac,
		NewOptionsDialog_MainMenu,
		NewOptionsDialog_Restart,
		NewOptionsDialog_MusicVolume,
		NewOptionsDialog_SoundVolume,
		NewOptionsDialog_Fullscreen,
		NewOptionsDialog_HardwareAcceleration,
		NewOptionsDialog_Advanced,
		NewOptionsDialog_LeftPage,
		NewOptionsDialog_RightPage,
		NewOptionsDialog_Back,
		NewOptionsDialog_Real_HardwareAcceleration
	};

public:
	LawnApp*				mApp;								
	Sexy::Slider*			mMusicVolumeSlider;					
	Sexy::Slider*			mSfxVolumeSlider;					
	Sexy::Checkbox*			mFullscreenCheckbox;				
	Sexy::Checkbox*			mHardwareAccelerationCheckbox;		
	Sexy::Checkbox*			mRealHardwareAccelerationCheckbox;		
	Sexy::Checkbox*			mDebugModeBox;
	Sexy::Checkbox*			mDiscordBox;
	Sexy::Checkbox*			mBankKeybindsBox;
	Sexy::Checkbox*			m09FormatBox;
	Sexy::Checkbox*			mAutoCollectSunsBox;
	Sexy::Checkbox*			mAutoCollectCoinsBox;
	Sexy::Checkbox*			mZombieHealthbarsBox;
	Sexy::Checkbox*			mPlantHealthbarsBox;
	LawnStoneButton*		mAlmanacButton;						
	LawnStoneButton*		mBackToMainButton;					
	LawnStoneButton*		mRestartButton;						
	NewLawnButton*			mBackToGameButton;					
	LawnStoneButton*		mAdvancedButton;
	NewLawnButton*			mGameAdvancedButton;
	NewLawnButton*			mLeftPageButton;
	NewLawnButton*			mRightPageButton;
	bool					mFromGameSelector;					
	bool					mAdvancedMode;
	int						mAdvancedPage;
	EditWidget*				mSpeedEditWidget;
	SexyString				mSpeedEditPrevText;

public:
	NewOptionsDialog(LawnApp* theApp, bool theFromGameSelector, bool theAdvanced);
	~NewOptionsDialog();

	int						GetPreferredHeight(int theWidth);
	void					AddedToManager(Sexy::WidgetManager* theWidgetManager);
	void					RemovedFromManager(Sexy::WidgetManager* theWidgetManager);
	void					Resize(int theX, int theY, int theWidth, int theHeight);
	void					Draw(Sexy::Graphics* g);
	void					SliderVal(int theId, double theVal);
	void					CheckboxChecked(int theId, bool checked);
	void					ButtonPress(int theId);
	void					ButtonDepress(int theId);
	void					KeyDown(Sexy::KeyCode theKey);
	void					UpdateAdvancedPage();
	void					Update();
};

#endif
