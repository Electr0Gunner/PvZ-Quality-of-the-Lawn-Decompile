#include "../Board.h"
#include "GameButton.h"
#include "../Cutscene.h"
#include "AlmanacDialog.h"
#include "../LawnCommon.h"
#include "../../LawnApp.h"
#include "../System/Music.h"
#include "../../Resources.h"
#include "NewOptionsDialog.h"
#include "../../ConstEnums.h"
#include "../../Sexy.TodLib/TodFoley.h"
#include "../../SexyAppFramework/Slider.h"
#include "../../SexyAppFramework/Checkbox.h"
#include "../../Sexy.TodLib/TodStringFile.h"

using namespace Sexy;

NewOptionsDialog::NewOptionsDialog(LawnApp* theApp, bool theFromGameSelector, bool theAdvanced) :
    Dialog(nullptr, nullptr, Dialogs::DIALOG_NEWOPTIONS, true, _S("Options"), _S(""), _S(""), Dialog::BUTTONS_NONE)
{
    TodLoadResources("DelayLoad_QuickPlay");
    mApp = theApp;
    mFromGameSelector = theFromGameSelector;
    mAdvancedMode = theAdvanced;
    SetColor(Dialog::COLOR_BUTTON_TEXT, Color(255, 255, 100));
    mAlmanacButton = MakeButton(NewOptionsDialog::NewOptionsDialog_Almanac, this, _S("[VIEW_ALMANAC_BUTTON]"));
    mRestartButton = MakeButton(NewOptionsDialog::NewOptionsDialog_Restart, this, _S("[RESTART_LEVEL]"));
    mBackToMainButton = MakeButton(NewOptionsDialog::NewOptionsDialog_MainMenu, this, _S("[MAIN_MENU_BUTTON]"));
    mAdvancedButton = MakeButton(NewOptionsDialog::NewOptionsDialog_Advanced, this, _S("[ADVANCED_OPTIONS]"));

    mBackToGameButton = MakeNewButton(
        Dialog::ID_OK,
        this,
        _S("[BACK_TO_GAME]"),
        nullptr,
        IMAGE_OPTIONS_BACKTOGAMEBUTTON0,
        IMAGE_OPTIONS_BACKTOGAMEBUTTON0,
        IMAGE_OPTIONS_BACKTOGAMEBUTTON2
    );
    mBackToGameButton->mTranslateX = 0;
    mBackToGameButton->mTranslateY = 0;
    mBackToGameButton->mTextOffsetX = -2;
    mBackToGameButton->mTextOffsetY = -5;
    mBackToGameButton->mTextDownOffsetX = 0;
    mBackToGameButton->mTextDownOffsetY = 1;
    mBackToGameButton->SetFont(FONT_DWARVENTODCRAFT36GREENINSET);
    mBackToGameButton->SetColor(ButtonWidget::COLOR_LABEL, Color::White);
    mBackToGameButton->SetColor(ButtonWidget::COLOR_LABEL_HILITE, Color::White);
    mBackToGameButton->mHiliteFont = FONT_DWARVENTODCRAFT36BRIGHTGREENINSET;

    mMusicVolumeSlider = new Sexy::Slider(IMAGE_OPTIONS_SLIDERSLOT, IMAGE_OPTIONS_SLIDERKNOB2, NewOptionsDialog::NewOptionsDialog_MusicVolume, this);
    double aMusicVolume = theApp->GetMusicVolume();
    aMusicVolume = max(0.0, min(1.0, aMusicVolume));
    mMusicVolumeSlider->SetValue(aMusicVolume);

    mSfxVolumeSlider = new Sexy::Slider(IMAGE_OPTIONS_SLIDERSLOT, IMAGE_OPTIONS_SLIDERKNOB2, NewOptionsDialog::NewOptionsDialog_SoundVolume, this);
    mSfxVolumeSlider->SetValue(theApp->GetSfxVolume() / 0.65);

    mFullscreenCheckbox = MakeNewCheckbox(NewOptionsDialog::NewOptionsDialog_Fullscreen, this, !theApp->mIsWindowed);
    mHardwareAccelerationCheckbox = MakeNewCheckbox(NewOptionsDialog::NewOptionsDialog_HardwareAcceleration, this, theApp->Is3dAccel());
    mDebugModeBox = MakeNewCheckbox(-1, this, mApp->mTodCheatKeys);
    mDebugModeBox->SetVisible(false);

    mDiscordBox = MakeNewCheckbox(-1, this, mApp->mDiscordPresence);
    mDiscordBox->SetVisible(false);

    mBankKeybindsBox = MakeNewCheckbox(-1, this, mApp->mBankKeybinds);
    mBankKeybindsBox->SetVisible(false);

    m09FormatBox = MakeNewCheckbox(-1, this, mApp->mZeroNineBankFormat);
    m09FormatBox->SetVisible(false);

    mAutoCollectSunsBox = MakeNewCheckbox(-1, this, mApp->mAutoCollectSuns);
    mAutoCollectSunsBox->SetVisible(false);

    mAutoCollectCoinsBox = MakeNewCheckbox(-1, this, mApp->mAutoCollectCoins);
    mAutoCollectCoinsBox->SetVisible(false);

    mZombieHealthbarsBox = MakeNewCheckbox(-1, this, mApp->mZombieHealthbars);
    mZombieHealthbarsBox->SetVisible(false);
    

    mPlantHealthbarsBox = MakeNewCheckbox(-1, this, mApp->mPlantHealthbars);
    mPlantHealthbarsBox->SetVisible(false);

    mLeftPageButton = MakeNewButton(NewOptionsDialog::NewOptionsDialog_LeftPage, this, "", nullptr, Sexy::IMAGE_QUICKPLAY_LEFT_BUTTON,
        Sexy::IMAGE_QUICKPLAY_LEFT_BUTTON_HIGHLIGHT, Sexy::IMAGE_QUICKPLAY_LEFT_BUTTON_HIGHLIGHT);
    mLeftPageButton->SetVisible(false);

    mRightPageButton = MakeNewButton(NewOptionsDialog::NewOptionsDialog_RightPage, this, "", nullptr, Sexy::IMAGE_QUICKPLAY_RIGHT_BUTTON,
        Sexy::IMAGE_QUICKPLAY_RIGHT_BUTTON_HIGHLIGHT, Sexy::IMAGE_QUICKPLAY_RIGHT_BUTTON_HIGHLIGHT);
    mRightPageButton->SetVisible(false);

    mSpeedEditWidget = CreateEditWidget(-1, this, this);
    mSpeedEditWidget->mMaxChars = 1;
    mSpeedEditWidget->SetFont(FONT_DWARVENTODCRAFT18GREENINSET);
    mSpeedEditWidget->AddWidthCheckFont(FONT_DWARVENTODCRAFT18GREENINSET, IMAGE_OPTIONS_CHECKBOX0->mWidth);
    mSpeedEditWidget->SetText(StrFormat(_S("%d"), mApp->mSpeedModifier), true);
    mSpeedEditWidget->SetColor(ButtonWidget::COLOR_LIGHT_OUTLINE, Color(1, 233, 1));
    mSpeedEditWidget->SetVisible(false);

    mGameAdvancedButton = MakeNewButton(NewOptionsDialog::NewOptionsDialog_Advanced, this, "A", nullptr, Sexy::IMAGE_BUTTON_SMALL,
        Sexy::IMAGE_BUTTON_SMALL, Sexy::IMAGE_BUTTON_DOWN_SMALL);
    mGameAdvancedButton->SetFont(FONT_DWARVENTODCRAFT18GREENINSET);
    mGameAdvancedButton->SetColor(ButtonWidget::COLOR_LABEL, Color::White);
    mGameAdvancedButton->SetColor(ButtonWidget::COLOR_LABEL_HILITE, Color::White);
    mGameAdvancedButton->mHiliteFont = FONT_DWARVENTODCRAFT18BRIGHTGREENINSET;
    mGameAdvancedButton->SetVisible(false);

    mRealHardwareAccelerationCheckbox = MakeNewCheckbox(NewOptionsDialog::NewOptionsDialog_Real_HardwareAcceleration, this, theApp->Is3DAccelerated());
    mRealHardwareAccelerationCheckbox->SetVisible(false);

    if (mFromGameSelector)
    {
        mRestartButton->SetVisible(false);
        mBackToGameButton->SetLabel(_S("[DIALOG_BUTTON_OK]"));
        if (mApp->HasFinishedAdventure() && !mApp->IsTrialStageLocked())
        {
            mBackToMainButton->SetVisible(false);
            mBackToMainButton->SetLabel(_S("[CREDITS]"));
        }
    }
    else
    {
        mAdvancedButton->SetVisible(false);
        mGameAdvancedButton->SetVisible(true);
    }

    if (mAdvancedMode)
    {
        mAdvancedPage = 1;
        mRestartButton->SetVisible(false);
        mAlmanacButton->SetVisible(false);
        mBackToMainButton->SetVisible(false);
        mAdvancedButton->SetVisible(false);
        mGameAdvancedButton->SetVisible(false);
        mBackToGameButton->SetLabel(_S("BACK"));
        mBackToGameButton->mId = NewOptionsDialog::NewOptionsDialog_Back;
    }

    if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ICE ||
        mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN ||
        mApp->mGameMode == GameMode::GAMEMODE_TREE_OF_WISDOM)
    {
        mRestartButton->SetVisible(false);
    }
    if (mApp->mGameScene == GameScenes::SCENE_LEVEL_INTRO && !mApp->mBoard->mCutScene->IsSurvivalRepick())
    {
        mRestartButton->SetVisible(false);
    }
    if (!mApp->CanShowAlmanac() ||
        mApp->mGameScene == GameScenes::SCENE_LEVEL_INTRO ||
        mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN ||
        mApp->mGameMode == GameMode::GAMEMODE_TREE_OF_WISDOM ||
        mFromGameSelector)
    {
        mAlmanacButton->SetVisible(false);
    }
    if ((!mRestartButton->mVisible || !mAlmanacButton->mVisible) && !mFromGameSelector && !mAdvancedMode)
    {
        mAdvancedButton->SetVisible(true);
        mGameAdvancedButton->SetVisible(false);
    }
}

NewOptionsDialog::~NewOptionsDialog()
{
    delete mMusicVolumeSlider;
    delete mSfxVolumeSlider;
    delete mFullscreenCheckbox;
    delete mHardwareAccelerationCheckbox;
    delete mDebugModeBox;
    delete mDiscordBox;
    delete m09FormatBox;
    delete mBankKeybindsBox;
    delete mAlmanacButton;
    delete mRestartButton;
    delete mBackToMainButton;
    delete mAdvancedButton;
    delete mBackToGameButton;
    delete mLeftPageButton;
    delete mRightPageButton;
    delete mSpeedEditWidget;
    delete mGameAdvancedButton;
    delete mAutoCollectSunsBox;
    delete mAutoCollectCoinsBox;
    delete mZombieHealthbarsBox;
    delete mRealHardwareAccelerationCheckbox;
}

int NewOptionsDialog::GetPreferredHeight(int theWidth)
{
    return IMAGE_OPTIONS_MENUBACK->mWidth;
}

void NewOptionsDialog::AddedToManager(Sexy::WidgetManager* theWidgetManager)
{
    Dialog::AddedToManager(theWidgetManager);
    AddWidget(mAlmanacButton);
    AddWidget(mRestartButton);
    AddWidget(mBackToMainButton);
    AddWidget(mAdvancedButton);
    AddWidget(mMusicVolumeSlider);
    AddWidget(mSfxVolumeSlider);
    AddWidget(mHardwareAccelerationCheckbox);
    AddWidget(mDebugModeBox);
    AddWidget(mDiscordBox);
    AddWidget(mBankKeybindsBox);
    AddWidget(m09FormatBox);
    AddWidget(mFullscreenCheckbox);
    AddWidget(mBackToGameButton);
    AddWidget(mLeftPageButton);
    AddWidget(mRightPageButton);
    AddWidget(mSpeedEditWidget);
    AddWidget(mGameAdvancedButton);
    AddWidget(mAutoCollectSunsBox);
    AddWidget(mAutoCollectCoinsBox);
    AddWidget(mZombieHealthbarsBox);
    AddWidget(mPlantHealthbarsBox);
    AddWidget(mRealHardwareAccelerationCheckbox);
}

void NewOptionsDialog::RemovedFromManager(Sexy::WidgetManager* theWidgetManager)
{
    Dialog::RemovedFromManager(theWidgetManager);
    RemoveWidget(mAlmanacButton);
    RemoveWidget(mMusicVolumeSlider);
    RemoveWidget(mSfxVolumeSlider);
    RemoveWidget(mFullscreenCheckbox);
    RemoveWidget(mHardwareAccelerationCheckbox);
    RemoveWidget(mDebugModeBox);
    RemoveWidget(mDiscordBox);
    RemoveWidget(mBankKeybindsBox);
    RemoveWidget(m09FormatBox);
    RemoveWidget(mBackToMainButton);
    RemoveWidget(mAdvancedButton);
    RemoveWidget(mBackToGameButton);
    RemoveWidget(mRestartButton);
    RemoveWidget(mLeftPageButton);
    RemoveWidget(mRightPageButton);
    RemoveWidget(mSpeedEditWidget);
    RemoveWidget(mGameAdvancedButton);
    RemoveWidget(mAutoCollectSunsBox);
    RemoveWidget(mAutoCollectCoinsBox);
    RemoveWidget(mZombieHealthbarsBox);
    RemoveWidget(mPlantHealthbarsBox);
    RemoveWidget(mRealHardwareAccelerationCheckbox);
}

void NewOptionsDialog::Resize(int theX, int theY, int theWidth, int theHeight)
{
    Dialog::Resize(theX, theY, theWidth, theHeight);
    mMusicVolumeSlider->Resize(199, 116, 135, 40);
    mSfxVolumeSlider->Resize(199, 143, 135, 40);
    mHardwareAccelerationCheckbox->Resize(284, 175, 46, 45);
    mDebugModeBox->Resize(284, 148, 46, 45);
    mFullscreenCheckbox->Resize(284, 206, 46, 45);
    mDiscordBox->Resize(mDebugModeBox->mX, mDebugModeBox->mY + 40, 46, 45);
    mBankKeybindsBox->Resize(mDiscordBox->mX, mDiscordBox->mY + 40, 46, 45);
    m09FormatBox->Resize(mBankKeybindsBox->mX, mBankKeybindsBox->mY + 40, 46, 45);
    mAutoCollectSunsBox->Resize(mDiscordBox->mX, mDiscordBox->mY, 46, 45);
    mAutoCollectCoinsBox->Resize(mBankKeybindsBox->mX, mBankKeybindsBox->mY, 46, 45);
    mZombieHealthbarsBox->Resize(m09FormatBox->mX, m09FormatBox->mY, 46, 45);
    mPlantHealthbarsBox->Resize(mZombieHealthbarsBox->mX, mZombieHealthbarsBox->mY + 40, 46, 45);
    mAlmanacButton->Resize(107, 241, 209, 46);
    mRestartButton->Resize(mAlmanacButton->mX, mAlmanacButton->mY + 43, 209, 46);
    mBackToMainButton->Resize(mRestartButton->mX, mRestartButton->mY + 43, 209, 46);
    mAdvancedButton->Resize(mRestartButton->mX, mRestartButton->mY + 43, 209, 46);
    mBackToGameButton->Resize(30, 381, mBackToGameButton->mWidth, mBackToGameButton->mHeight);
    mLeftPageButton->Resize(100, ADVANCED_PAGE_Y - 25, IMAGE_QUICKPLAY_LEFT_BUTTON->mWidth, IMAGE_QUICKPLAY_LEFT_BUTTON->mHeight);
    mRightPageButton->Resize(280, ADVANCED_PAGE_Y - 25, IMAGE_QUICKPLAY_RIGHT_BUTTON->mWidth, IMAGE_QUICKPLAY_RIGHT_BUTTON->mHeight);
    mSpeedEditWidget->Resize(ADVANCED_SPEED_X + 9, ADVANCED_SPEED_Y - 4, IMAGE_OPTIONS_CHECKBOX0->mWidth, IMAGE_OPTIONS_CHECKBOX0->mHeight + 4);
    mGameAdvancedButton->Resize(mWidth - Sexy::IMAGE_BUTTON_SMALL->mWidth - 9, mRestartButton->mY, Sexy::IMAGE_BUTTON_SMALL->mWidth, Sexy::IMAGE_BUTTON_SMALL->mHeight);
    mRealHardwareAccelerationCheckbox->Resize(310, 148, 46, 45);

    if ((!mRestartButton->mVisible || !mAlmanacButton->mVisible) && !mFromGameSelector && !mAdvancedMode)
    {
        LawnStoneButton* button;
        if (!mRestartButton->mVisible)
            button = mRestartButton;
        else if (!mAlmanacButton->mVisible)
            button = mAlmanacButton;
        mAdvancedButton->Resize(button->mX, button->mY, button->mWidth, button->mHeight);
    }
    if (mFromGameSelector)
    {
        mMusicVolumeSlider->mY += 5;
        mSfxVolumeSlider->mY += 10;
        mHardwareAccelerationCheckbox->mY += 15;
        mFullscreenCheckbox->mY += 20;
    }
    if (mAdvancedMode)
    {
        mMusicVolumeSlider->SetVisible(false);
        mSfxVolumeSlider->SetVisible(false);
        mHardwareAccelerationCheckbox->SetVisible(false);
        mFullscreenCheckbox->SetVisible(false);
        mLeftPageButton->SetVisible(true);
        mRightPageButton->SetVisible(true);
        UpdateAdvancedPage();
    }

    if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN || mApp->mGameMode == GameMode::GAMEMODE_TREE_OF_WISDOM)
    {
        mAlmanacButton->mY += 43;
    }
}

void NewOptionsDialog::Draw(Sexy::Graphics* g)
{
    g->DrawImage(IMAGE_OPTIONS_MENUBACK, 0, 0);

    int aMusicOffset = 0;
    int aSfxOffset = 0;
    int a3DAccelOffset = 0;
    int aFullScreenOffset = 0;
    if (mFromGameSelector)
    {
        aMusicOffset = 5;
        aSfxOffset = 10;
        a3DAccelOffset = 15;
        aFullScreenOffset = 20;
    }
    Sexy::Color aTextColor(107, 109, 145);

    if (!mAdvancedMode)
    {
        TodDrawString(g, _S("Music"), 186, 140 + aMusicOffset, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_RIGHT);
        TodDrawString(g, _S("Sound FX"), 186, 167 + aSfxOffset, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_RIGHT);
        TodDrawString(g, _S("3D Acceleration"), 274, 197 + a3DAccelOffset, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_RIGHT);
        TodDrawString(g, _S("Full Screen"), 274, 229 + aFullScreenOffset, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_RIGHT);
    }
    else
    {
        if (mAdvancedPage == 1)
        {
            TodDrawString(g, mApp->mReconVersion, mWidth / 2, 137, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_CENTER);
            TodDrawString(g, _S("Debug Mode"), mDebugModeBox->mX - 6, mDebugModeBox->mY + 22, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_RIGHT);
            TodDrawString(g, _S("Discord Presence"), mDiscordBox->mX - 6, mDiscordBox->mY + 22, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_RIGHT);
            TodDrawString(g, _S("Seed Bank Keybinds"), mBankKeybindsBox->mX - 6, mBankKeybindsBox->mY + 22, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_RIGHT);
            TodDrawString(g, StrFormat(_S("Keybind: '%s'"), m09FormatBox->mChecked ? "1-0" : "0-9"), m09FormatBox->mX - 6, m09FormatBox->mY + 22, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_RIGHT);
            TodDrawString(g, _S("Shovel Keybind: 'S'"), mWidth / 2, m09FormatBox->mY + 55, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_CENTER);
        }
        else if (mAdvancedPage == 2)
        {
            TodDrawString(g, _S("Speed Multiplier"), ADVANCED_SPEED_X - 6, ADVANCED_SPEED_Y + 22, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_RIGHT);
            TodDrawString(g, _S("Auto-Collect Suns"), mAutoCollectSunsBox->mX - 6, mAutoCollectSunsBox->mY + 22, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_RIGHT);
            TodDrawString(g, _S("Auto-Collect Coins"), mAutoCollectCoinsBox->mX - 6, mAutoCollectCoinsBox->mY + 22, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_RIGHT);
            TodDrawString(g, _S("Zombie Healthbars"), mZombieHealthbarsBox->mX - 6, mZombieHealthbarsBox->mY + 22, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_RIGHT);
            TodDrawString(g, _S("Plant Healthbars"), mPlantHealthbarsBox->mX - 6, mPlantHealthbarsBox->mY + 22, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_RIGHT);
            g->DrawImage(Sexy::IMAGE_OPTIONS_CHECKBOX0, ADVANCED_SPEED_X, ADVANCED_SPEED_Y);
        }
        else if (mAdvancedPage == 3)
        {
            TodDrawString(g, _S("Actual 3D Acceleration"), mRealHardwareAccelerationCheckbox->mX - 6, mRealHardwareAccelerationCheckbox->mY + 22, FONT_DWARVENTODCRAFT18, aTextColor, DrawStringJustification::DS_ALIGN_RIGHT);
        }
        TodDrawString(g, StrFormat(_S("Page %d"), mAdvancedPage), mWidth / 2, ADVANCED_PAGE_Y, FONT_DWARVENTODCRAFT18GREENINSET, Color::White, DrawStringJustification::DS_ALIGN_CENTER);
    }
}

void NewOptionsDialog::SliderVal(int theId, double theVal)
{
    switch (theId)
    {
    case NewOptionsDialog::NewOptionsDialog_MusicVolume:
        mApp->SetMusicVolume(theVal);
        mApp->mSoundSystem->RehookupSoundWithMusicVolume();
        break;

    case NewOptionsDialog::NewOptionsDialog_SoundVolume:
        mApp->SetSfxVolume(theVal * 0.65);
        mApp->mSoundSystem->RehookupSoundWithMusicVolume();
        if (!mSfxVolumeSlider->mDragging)
        {
            mApp->PlaySample(SOUND_BUTTONCLICK);
        }
        break;
    }
}

void NewOptionsDialog::CheckboxChecked(int theId, bool checked)
{
    switch (theId)
    {
    case NewOptionsDialog::NewOptionsDialog_Fullscreen:
        if (!checked && mApp->mForceFullscreen)
        {
            mApp->DoDialog(
                Dialogs::DIALOG_COLORDEPTH_EXP,
                true,
                _S("No Windowed Mode"),
                _S("Windowed mode is only available if your desktop was running in either\n"
                    "16 bit or 32 bit color mode when you started the game.\n\n"
                    "If you'd like to run in Windowed mode then you need to quit the game and switch your desktop to 16 or 32 bit color mode."),
                _S("OK"),
                Dialog::BUTTONS_FOOTER
            );

            mFullscreenCheckbox->SetChecked(true, false);
        }
        break;

    case NewOptionsDialog::NewOptionsDialog_HardwareAcceleration:
        if (checked)
        {
            if (!mApp->Is3DAccelerationRecommended())
            {
                mApp->DoDialog(
                    Dialogs::DIALOG_INFO,
                    true,
                    _S("Warning"),
                    _S("Your video card may not fully support this feature.\n\n"
                        "If you experience slower performance, please disable Hardware Acceleration.\n"),
                    _S("OK"),
                    Dialog::BUTTONS_FOOTER
                );
            }
        }
        break;
    case NewOptionsDialog::NewOptionsDialog_Real_HardwareAcceleration:
        if (checked)
        {
            if (!mApp->Is3DAccelerationRecommended())
            {
                mApp->DoDialog(
                    Dialogs::DIALOG_INFO,
                    true,
                    _S("Warning"),
                    _S("Your video card may not fully support this feature.\n\n"
                        "If you experience slower performance, please disable Hardware Acceleration.\n"),
                    _S("OK"),
                    Dialog::BUTTONS_FOOTER
                );
            }
        }
        break;
    }
}

void NewOptionsDialog::KeyDown(Sexy::KeyCode theKey)
{
    if (mApp->mBoard)
    {
        mApp->mBoard->DoTypingCheck(theKey);
    }

    if (theKey == KeyCode::KEYCODE_SPACE || theKey == KeyCode::KEYCODE_RETURN)
    {
        if (mAdvancedMode)
            ButtonDepress(NewOptionsDialog::NewOptionsDialog_Back);
        else
        {
            Dialog::ButtonDepress(Dialog::ID_OK);
            mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
        }
    }
    else if (theKey == KeyCode::KEYCODE_ESCAPE)
    {
        Dialog::ButtonDepress(Dialog::ID_CANCEL);
    }
}

void NewOptionsDialog::UpdateAdvancedPage()
{
    if (mAdvancedPage == 1)
        mLeftPageButton->SetVisible(false);
    else
        mLeftPageButton->SetVisible(true);
    if (mAdvancedPage == ADVANCED_MAX_PAGES)
        mRightPageButton->SetVisible(false);
    else
        mRightPageButton->SetVisible(true);

    mDebugModeBox->SetVisible(false);
    mDiscordBox->SetVisible(false);
    mBankKeybindsBox->SetVisible(false);
    m09FormatBox->SetVisible(false);
    mSpeedEditWidget->SetVisible(false);
    mAutoCollectSunsBox->SetVisible(false);
    mAutoCollectCoinsBox->SetVisible(false);
    mZombieHealthbarsBox->SetVisible(false);
    mPlantHealthbarsBox->SetVisible(false);
    mRealHardwareAccelerationCheckbox->SetVisible(false);

    switch (mAdvancedPage)
    {
        case 1:
            mDebugModeBox->SetVisible(true);
            mDiscordBox->SetVisible(true);
            mBankKeybindsBox->SetVisible(true);
            m09FormatBox->SetVisible(true);
            break;
        case 2:
            mSpeedEditWidget->SetVisible(true);
            mAutoCollectSunsBox->SetVisible(true);
            mAutoCollectCoinsBox->SetVisible(true);
            mZombieHealthbarsBox->SetVisible(true);
            mPlantHealthbarsBox->SetVisible(true);
            break;
        case 3:
            mRealHardwareAccelerationCheckbox->SetVisible(true);
            break;
        break;
    }
}

void NewOptionsDialog::Update()
{
    bool isGameAdvancedDown = mGameAdvancedButton->mIsDown;
    mGameAdvancedButton->mTextDownOffsetX = isGameAdvancedDown;
    mGameAdvancedButton->mTextDownOffsetY = isGameAdvancedDown;
    if (mAdvancedMode)
    {
        if (mSpeedEditWidget->mHasFocus && mSpeedEditWidget->mFont != FONT_DWARVENTODCRAFT18BRIGHTGREENINSET)
            mSpeedEditWidget->SetFont(FONT_DWARVENTODCRAFT18BRIGHTGREENINSET);
        if (mSpeedEditPrevText != mSpeedEditWidget->mString)
        {
            if ((mSpeedEditWidget->mString == "" || mSpeedEditWidget->mString == " ") && (mSpeedEditPrevText != "" || mSpeedEditPrevText != " "))
                mSpeedEditWidget->mString = mSpeedEditPrevText;
            int num;
            try
            {
                num = stoi(mSpeedEditWidget->mString);
            }
            catch (exception)
            {
                mSpeedEditWidget->mString = mSpeedEditPrevText;
                return;
            }
            if (num < ADVANCED_SPEED_MIN)
                mSpeedEditWidget->mString = StrFormat(_S("%d"), ADVANCED_SPEED_MIN);
            else if (num > ADVANCED_SPEED_MAX)
                mSpeedEditWidget->mString = StrFormat(_S("%d"), ADVANCED_SPEED_MAX);
            mSpeedEditPrevText = mSpeedEditWidget->mString;
        }
    }
}

void NewOptionsDialog::ButtonPress(int theId)
{
    mApp->PlaySample(SOUND_GRAVEBUTTON);
}

void NewOptionsDialog::ButtonDepress(int theId)
{
    Dialog::ButtonDepress(theId);

    switch (theId)
    {
    case NewOptionsDialog::NewOptionsDialog_Almanac:
    {
        AlmanacDialog* aDialog = mApp->DoAlmanacDialog(SeedType::SEED_NONE, ZombieType::ZOMBIE_INVALID);
        aDialog->WaitForResult(true);
        break;
    }
    case NewOptionsDialog::NewOptionsDialog_Advanced:
    {
        mApp->KillNewOptionsDialog();
        mApp->DoAdvancedOptions(mFromGameSelector, mX, mY);
        mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
        break;
    }
    case NewOptionsDialog::NewOptionsDialog_MainMenu:
    {
        if (mApp->mBoard && mApp->mBoard->NeedSaveGame())
        {
            mApp->DoConfirmBackToMain();
        }
        else if (mApp->mBoard && mApp->mBoard->mCutScene && mApp->mBoard->mCutScene->IsSurvivalRepick())
        {
            mApp->DoConfirmBackToMain();
        }
        else
        {
            mApp->mBoardResult = BoardResult::BOARDRESULT_QUIT;
            mApp->DoBackToMain(true);
        }
        break;
    }

    case NewOptionsDialog::NewOptionsDialog_Restart:
    {
        if (mApp->mBoard)
        {
            SexyString aDialogTitle;
            SexyString aDialogMessage;
            if (mApp->IsPuzzleMode())
            {
                aDialogTitle = _S("[RESTART_PUZZLE_HEADER]");
                aDialogMessage = _S("[RESTART_PUZZLE_BODY]");
            }
            else if (mApp->IsChallengeMode())
            {
                aDialogTitle = _S("[RESTART_CHALLENGE_HEADER]");
                aDialogMessage = _S("[RESTART_CHALLENGE_BODY]");
            }
            else if (mApp->IsSurvivalMode())
            {
                aDialogTitle = _S("[RESTART_SURVIVAL_HEADER]");
                aDialogMessage = _S("[RESTART_SURVIVAL_BODY]");
            }
            else
            {
                aDialogTitle = _S("[RESTART_LEVEL_HEADER]");
                aDialogMessage = _S("[RESTART_LEVEL_BODY]");
            }

            LawnDialog* aDialog = (LawnDialog*)mApp->DoDialog(Dialogs::DIALOG_CONFIRM_RESTART, true, aDialogTitle, aDialogMessage, _S(""), Dialog::BUTTONS_YES_NO);
            aDialog->mLawnYesButton->mLabel = TodStringTranslate(_S("RESTART"/*[RESTART_LABEL]*/));
            aDialog->mLawnNoButton->mLabel = TodStringTranslate(_S("[DIALOG_BUTTON_CANCEL]"));

            if (aDialog->WaitForResult(true) == Dialog::ID_YES)
            {
                mApp->mMusic->StopAllMusic();
                mApp->mSoundSystem->CancelPausedFoley();
                mApp->KillNewOptionsDialog();
                mApp->mBoardResult = BoardResult::BOARDRESULT_RESTART;
                mApp->mSawYeti = mApp->mBoard->mKilledYeti;
                if (mApp->mPlayedQuickplay)
                    mApp->StartQuickPlay();
                else
                    mApp->PreNewGame(mApp->mGameMode, false);
                mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
            }
        }
        break;
    }

    case NewOptionsDialog::NewOptionsDialog_LeftPage:
        mAdvancedPage--;
        UpdateAdvancedPage();
        break;

    case NewOptionsDialog::NewOptionsDialog_RightPage:
        mAdvancedPage++;
        UpdateAdvancedPage();
        break;

    case NewOptionsDialog::NewOptionsDialog_Back:
        mApp->KillNewOptionsDialog();
        mApp->DoNewOptions(mFromGameSelector, mX, mY);
        mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
        break;

    case Dialog::ID_OK:
        mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
        break;
    }
}