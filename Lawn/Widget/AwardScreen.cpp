#include "../Plant.h"
#include "../Board.h"
#include "GameButton.h"
#include "StoreScreen.h"
#include "AwardScreen.h"
#include "../ZenGarden.h"
#include "../SeedPacket.h"
#include "../Achievements.h"
#include "../../LawnApp.h"
#include "AlmanacDialog.h"
#include "../System/Music.h"
#include "../../Resources.h"
#include "../../GameConstants.h"
#include "../System/PlayerInfo.h"
#include "../../Sexy.TodLib/TodFoley.h"
#include "../../Sexy.TodLib/TodCommon.h"
#include "../../Sexy.TodLib/TodStringFile.h"

const Rect cAchievementClipRect = Rect(0, 95, BOARD_WIDTH, 405);

AwardScreen::AwardScreen(LawnApp* theApp, AwardType theAwardType, bool hasAchievement)
{
    mApp = theApp;
    mClip = false;
    mFadeInCounter = 180;
    mAchievementCounter = 360;
    mScrollAmount = 0;
    mScrollPosition = 0;
    mMaxScrollPosition = 0;

    mAwardType = theAwardType;
    mShowAchievements = hasAchievement;
    LoadAchievements();
    TodLoadResources("DelayLoad_AwardScreen");
    TodLoadResources("DelayLoad_Achievements");

    int aLevel = mApp->mPlayerInfo->mLevel;
    if (mAwardType == AWARD_CREDITS_ZOMBIENOTE)
    {
        TodLoadResources("DelayLoad_Background6");
        TodLoadResources("DelayLoad_ZombieNote");
        TodLoadResources("DelayLoad_Credits");
    }
    else if (mAwardType == AWARD_HELP_ZOMBIENOTE)
    {
        TodLoadResources("DelayLoad_Background1");
        TodLoadResources("DelayLoad_ZombieNote");
        TodLoadResources("DelayLoad_ZombieNoteHelp");
    }
    else if (mApp->IsAdventureMode())
    {
        if (aLevel == 10)
        {
            TodLoadResources("DelayLoad_Background1");
            TodLoadResources("DelayLoad_ZombieNote");
            TodLoadResources("DelayLoad_ZombieNote1");
        }
        else if (aLevel == 20)
        {
            TodLoadResources("DelayLoad_Background2");
            TodLoadResources("DelayLoad_ZombieNote");
            TodLoadResources("DelayLoad_ZombieNote2");
        }
        else if (aLevel == 30)
        {
            TodLoadResources("DelayLoad_Background1");
            TodLoadResources("DelayLoad_ZombieNote");
            TodLoadResources("DelayLoad_ZombieNote3");
        }
        else if (aLevel == 40)
        {
            TodLoadResources("DelayLoad_Background2");
            TodLoadResources("DelayLoad_ZombieNote");
            TodLoadResources("DelayLoad_ZombieNote4");
        }
        else if (aLevel == 50)
        {
            TodLoadResources("DelayLoad_Background1");
            TodLoadResources("DelayLoad_ZombieNote");
            TodLoadResources("DelayLoad_ZombieFinalNote");
        }
    }

    mStartButton = new GameButton(AwardScreen::AwardScreen_Start);
    mStartButton->mButtonImage = Sexy::IMAGE_SEEDCHOOSER_BUTTON;
    mStartButton->mOverImage = nullptr;
    mStartButton->mDownImage = nullptr;
    mStartButton->mDisabledImage = Sexy::IMAGE_SEEDCHOOSER_BUTTON_DISABLED;
    mStartButton->mOverOverlayImage = Sexy::IMAGE_SEEDCHOOSER_BUTTON_GLOW;
    mStartButton->SetFont(Sexy::FONT_DWARVENTODCRAFT15);
    mStartButton->mColors[ButtonWidget::COLOR_LABEL] = Color(213, 159, 43);
    mStartButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color(213, 159, 43);
    mStartButton->Resize(324, 500, 156, 42);
    mStartButton->mTextOffsetY = -1;

    mMenuButton = new GameButton(AwardScreen::AwardScreen_Menu);
    mMenuButton->SetLabel("[AWARD_MAIN_MENU_BUTTON]");
    mMenuButton->mButtonImage = Sexy::IMAGE_SEEDCHOOSER_BUTTON2;
    mMenuButton->mOverImage = Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW;
    mMenuButton->mDownImage = nullptr;
    mMenuButton->SetFont(Sexy::FONT_BRIANNETOD12);
    mMenuButton->mColors[ButtonWidget::COLOR_LABEL] = Color(42, 42, 90);
    mMenuButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color(42, 42, 90);
    mMenuButton->mParentWidget = this;
    mMenuButton->Resize(677, 16, 111, 26);
    mMenuButton->mTextOffsetY = 1;
    if (!mApp->HasFinishedAdventure() && aLevel <= 3)
    {
        mMenuButton->mBtnNoDraw = true;
        mMenuButton->mDisabled = true;
    }

    if (mAwardType == AWARD_CREDITS_ZOMBIENOTE)
    {
        mStartButton->SetLabel("[ROLL_CREDITS]");
        mStartButton->mButtonImage = Sexy::IMAGE_CREDITS_PLAYBUTTON;
        mStartButton->mOverImage = nullptr;
        mStartButton->mDownImage = nullptr;
        mStartButton->mDisabledImage = nullptr;
        mStartButton->mOverOverlayImage = nullptr;
        mStartButton->SetFont(Sexy::FONT_HOUSEOFTERROR20);
        mStartButton->mColors[ButtonWidget::COLOR_LABEL] = Color(255, 255, 255);
        mStartButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color(213, 159, 43);
        mStartButton->Resize(325, 505, 190, 73);
        mStartButton->mTextOffsetX = 33;
        mStartButton->mTextOffsetY = -2;
        mStartButton->mButtonOffsetX = -2;
        mStartButton->mButtonOffsetY = 8;
        mStartButton->mParentWidget = this;
    }
    else if (mAwardType == AWARD_HELP_ZOMBIENOTE)
    {
        mStartButton->SetLabel("[MAIN_MENU_BUTTON]");
        mMenuButton->mBtnNoDraw = true;
        mMenuButton->mDisabled = true;
    }
    else if (!mApp->IsAdventureMode())
    {
        mStartButton->SetLabel("[MAIN_MENU_BUTTON]");
        mMenuButton->mBtnNoDraw = true;
        mMenuButton->mDisabled = true;
    }
    else if (aLevel == 1)
    {
        mStartButton->SetLabel("[CONTINUE_BUTTON]");
        mMenuButton->mBtnNoDraw = true;
        mMenuButton->mDisabled = true;
    }
    else if (aLevel == 15)
        mStartButton->SetLabel("[VIEW_ALMANAC_BUTTON]");
    else if (aLevel == 25 || aLevel == 35 || aLevel == 45)
        mStartButton->SetLabel("[CONTINUE_BUTTON]");
    else
        mStartButton->SetLabel("[NEXT_LEVEL_BUTTON]");

    if (mApp->IsAdventureMode() && mApp->EarnedGoldTrophy()) {
        mApp->GetAchievement(ACHIEVEMENT_NOBEL_PEAS_PRIZE);
    }

    if (mApp->IsFirstTimeAdventureMode() && aLevel == 25 && mApp->IsTrialStageLocked() && !mApp->mPlayerInfo->mHasSeenUpsell)
    {
        mMenuButton->mBtnNoDraw = true;
        mMenuButton->mDisabled = true;
    }
    else if (mApp->HasFinishedAdventure())
    {
        mStartButton->SetLabel("[CONTINUE_BUTTON]");
        mMenuButton->mBtnNoDraw = true;
        mMenuButton->mDisabled = true;
    }

    if (IsPaperNote())
    {
        mApp->mMusic->StopAllMusic();
        mStartButton->mY += 20;
        mApp->PlayFoley(FOLEY_PAPER);
    }
    else
        mApp->mMusic->MakeSureMusicIsPlaying(MUSIC_TUNE_ZEN_GARDEN);

    mWasDrawn = mMenuButton->mBtnNoDraw;
    mApp->mDetails = "In the Award Screen";
    if (!mShowAchievements)
        StartSounds();

    mSlider = new Sexy::Slider(IMAGE_OPTIONS_SLIDERSLOT_PLANT, IMAGE_OPTIONS_SLIDERKNOB_PLANT, AwardScreen::AwardScreen_Slider, this);
    mSlider->SetValue(max(0.0, min(mMaxScrollPosition, mScrollPosition)));
    mSlider->mHorizontal = false;
    mSlider->Resize(180, cAchievementClipRect.mY, 20, cAchievementClipRect.mHeight);
    mSlider->mThumbOffsetX = -5;
    mSlider->mNoDraw = true;
}

AwardScreen::~AwardScreen()
{
    if (mStartButton) delete mStartButton;
    if (mMenuButton) delete mMenuButton;
    delete mSlider;
    mApp->UpdateDiscordState();
}

void AwardScreen::LoadAchievements()
{
    TodLoadResources("DelayLoad_ChallengeScreen");
    if (mShowAchievements)
    {
        for (int i = 0; i < NUM_ACHIEVEMENTS; i++)
        {
            if (mApp->mPlayerInfo->mEarnedAchievements[i] && !mApp->mPlayerInfo->mShownedAchievements[i] && mApp->mAchievements->ReturnShowInAwards(i))
            {
                mShowAchievements = true;
                break;
            }
            else
            {
                mShowAchievements = false;
            }
        }
        mApp->WriteCurrentUserConfig();
    }
}

bool AwardScreen::IsPaperNote()
{
    if (mAwardType == AWARD_CREDITS_ZOMBIENOTE || mAwardType == AWARD_HELP_ZOMBIENOTE)
        return true;

    int aLevel = mApp->mPlayerInfo->mLevel;
    return mApp->IsAdventureMode() && (aLevel == 10 || aLevel == 20 || aLevel == 30 || aLevel == 40 || aLevel == 50);
}

void AwardScreen::DrawBottom(Graphics* g, SexyString theTitle, SexyString theAward, SexyString theMessage)
{
    g->DrawImage(Sexy::IMAGE_AWARDSCREEN_BACK, 0, 0);
    TodDrawString(g, theTitle, BOARD_WIDTH / 2, 58, Sexy::FONT_DWARVENTODCRAFT24, Color(213, 159, 43), DS_ALIGN_CENTER);
    TodDrawString(g, theAward, BOARD_WIDTH / 2, 326, Sexy::FONT_DWARVENTODCRAFT18YELLOW, Color::White, DS_ALIGN_CENTER);
    TodDrawStringWrapped(g, theMessage, Rect(285, 360, 230, 90), Sexy::FONT_BRIANNETOD16, Color(40, 50, 90), DS_ALIGN_CENTER_VERTICAL_MIDDLE);
    mState = TodStringTranslate(theAward);
}

void AwardScreen::DrawAwardSeed(Graphics* g)
{
    SeedType aSeedType = mApp->GetAwardSeedForLevel(mApp->mPlayerInfo->mLevel - 1);
    SexyString aAward = Plant::GetNameString(aSeedType, SEED_NONE);
    SexyString aMessage;
    if (mApp->IsTrialStageLocked() && aSeedType >= SEED_SQUASH && aSeedType != SEED_TANGLEKELP)
        aMessage = _S("[AVAILABLE_IN_FULL_VERSION]");
    else
        aMessage = Plant::GetToolTip(aSeedType);
    DrawBottom(g, _S("[NEW_PLANT]"), aAward, aMessage);

    g->SetScale(2, 2, 350, 129);
    DrawSeedPacket(g, 350, 129, aSeedType, SEED_NONE, 0, 255, true, false);
    g->SetScale(1, 1, 0, 0);
}

void AwardScreen::Draw(Graphics* g)
{
    g->SetLinearBlend(true);
    
    int aLevel = mApp->mPlayerInfo->mLevel;
    if (mAwardType == AWARD_CREDITS_ZOMBIENOTE)
    {
        g->SetColor(Color(125, 200, 255, 255));
        g->SetColorizeImages(true);
        g->DrawImage(Sexy::IMAGE_BACKGROUND6BOSS, -900, -400, 2800, 1200);
        g->SetColorizeImages(false);
        g->SetColor(Color(0, 0, 0, 64));
        g->FillRect(0, 525, BOARD_WIDTH, BOARD_HEIGHT);
        g->DrawImage(Sexy::IMAGE_ZOMBIE_NOTE, 75, 60);
        g->DrawImage(Sexy::IMAGE_CREDITS_ZOMBIENOTE, 149, 103, 475, 325);
        mState = "Credits Note";
    }
    else if (mAwardType == AWARD_HELP_ZOMBIENOTE)
    {
        g->DrawImage(Sexy::IMAGE_BACKGROUND1, -700, -300, 2800, 1200);
        g->DrawImage(Sexy::IMAGE_ZOMBIE_NOTE, 80, 80);
        g->DrawImage(Sexy::IMAGE_ZOMBIE_NOTE_HELP, 131, 132);
        mState = "Help Note";
    }
    else
    {
        if (!mApp->IsAdventureMode())
        {
            if (mApp->EarnedGoldTrophy())
            {
                DrawBottom(g, _S("[BEAT_GAME_MESSAGE1]"), _S("[GOLD_SUNFLOWER_TROPHY]"), _S("[BEAT_GAME_MESSAGE2]"));
                TodDrawImageCelCenterScaledF(g, Sexy::IMAGE_SUNFLOWER_TROPHY, 325, 65, 1, 0.6f, 0.6f);
            }
            else
            {
                const char* aMsgChar;
                if (mApp->IsSurvivalMode())
                {
                    int aNumTrophies = mApp->GetNumTrophies(CHALLENGE_PAGE_SURVIVAL);
                    aMsgChar =
                        aNumTrophies <= 7 ? _S("[YOU_UNLOCKED_A_SURVIVAL]") :
                        aNumTrophies == 10 ? _S("[YOU_UNLOCKED_ENDLESS_SURVIVAL]") : _S("[EARN_MORE_TROPHIES_FOR_ENDLESS_SURVIVAL]");

                }
                else if (mApp->IsScaryPotterLevel())
                    aMsgChar = _S("[UNLOCKED_VASEBREAKER_LEVEL]");
                else if (mApp->IsPuzzleMode())
                    aMsgChar = _S("[UNLOCKED_I_ZOMBIE_LEVEL]");
                else
                    aMsgChar = mApp->GetNumTrophies(CHALLENGE_PAGE_CHALLENGE) <= 17 ? _S("[CHALLENGE_UNLOCKED]") : _S("[GET_MORE_TROPHIES]");

                DrawBottom(g, _S("[GOT_TROPHY]"), _S("[TROPHY]"), aMsgChar);
                g->DrawImage(Sexy::IMAGE_TROPHY_HI_RES, BOARD_WIDTH / 2 - Sexy::IMAGE_TROPHY_HI_RES->mWidth / 2, 137);
            }
        }
        else if (aLevel == 5)
        {
            DrawBottom(g, _S("[GOT_SHOVEL]"), _S("[SHOVEL]"), _S("[SHOVEL_DESCRIPTION]"));
            g->DrawImage(Sexy::IMAGE_SHOVEL_HI_RES, BOARD_WIDTH / 2 - Sexy::IMAGE_SHOVEL_HI_RES->mWidth / 2, 137);
        }
        else if (aLevel == 10)
        {
            g->DrawImage(Sexy::IMAGE_BACKGROUND1, -700, -300, 2800, 1200);
            g->DrawImage(Sexy::IMAGE_ZOMBIE_NOTE, 80, 80);
            g->DrawImage(Sexy::IMAGE_ZOMBIE_NOTE1, 131, 132);
            TodDrawString(g, _S("[FOUND_NOTE]"), BOARD_WIDTH / 2, 70, Sexy::FONT_DWARVENTODCRAFT24, Color(255, 200, 0, 255), DS_ALIGN_CENTER);
            mState = "Zombie Note (" + mApp->GetStageString(aLevel).erase(0, 1) + ")";
        }
        else if (aLevel == 15)
        {
            DrawBottom(g, _S("[FOUND_SUBURBAN_ALMANAC]"), _S("[SUBURBAN_ALMANAC]"), _S("[SUBURBAN_ALMANAC_DESCRIPTION]"));
            g->DrawImage(Sexy::IMAGE_ALMANAC, BOARD_WIDTH / 2 - Sexy::IMAGE_ALMANAC->mWidth / 2, 160);
        }
        else if (aLevel == 20)
        {
            g->DrawImage(Sexy::IMAGE_BACKGROUND2, -700, -300, 2800, 1200);
            g->DrawImage(Sexy::IMAGE_ZOMBIE_NOTE, 80, 80);
            g->DrawImage(Sexy::IMAGE_ZOMBIE_NOTE2, 133, 127);
            TodDrawString(g, _S("[FOUND_NOTE]"), BOARD_WIDTH / 2, 70, Sexy::FONT_DWARVENTODCRAFT24, Color(255, 200, 0, 255), DS_ALIGN_CENTER);
            mState = "Zombie Note (" + mApp->GetStageString(aLevel).erase(0, 1) + ")";
        }
        else if (aLevel == 25)
        {
            DrawBottom(g, _S("[FOUND_KEYS]"), _S("[KEYS]"), _S("[KEYS_DESCRIPTION]"));
            g->DrawImage(Sexy::IMAGE_CARKEYS, BOARD_WIDTH / 2 - Sexy::IMAGE_CARKEYS->mWidth / 2, 160);
        }
        else if (aLevel == 30)
        {
            g->DrawImage(Sexy::IMAGE_BACKGROUND1, -700, -300, 2800, 1200);
            g->DrawImage(Sexy::IMAGE_ZOMBIE_NOTE, 80, 80);
            g->DrawImage(Sexy::IMAGE_ZOMBIE_NOTE3, 120, 117);
            TodDrawString(g, _S("[FOUND_NOTE]"), BOARD_WIDTH / 2, 70, Sexy::FONT_DWARVENTODCRAFT24, Color(255, 200, 0, 255), DS_ALIGN_CENTER);
            mState = "Zombie Note (" + mApp->GetStageString(aLevel).erase(0, 1) + ")";
        }
        else if (aLevel == 35)
        {
            DrawBottom(g, _S("[FOUND_TACO]"), _S("[TACO]"), _S("[TACO_DESCRIPTION]"));
            g->DrawImage(Sexy::IMAGE_TACO, BOARD_WIDTH / 2 - Sexy::IMAGE_TACO->mWidth / 2, 160);
        }
        else if (aLevel == 40)
        {
            g->DrawImage(Sexy::IMAGE_BACKGROUND2, -700, -300, 2800, 1200);
            g->DrawImage(Sexy::IMAGE_ZOMBIE_NOTE, 80, 80);
            g->DrawImage(Sexy::IMAGE_ZOMBIE_NOTE4, 102, 117);
            TodDrawString(g, _S("[FOUND_NOTE]"), BOARD_WIDTH / 2, 70, Sexy::FONT_DWARVENTODCRAFT24, Color(255, 200, 0, 255), DS_ALIGN_CENTER);
            mState = "Zombie Note (" + mApp->GetStageString(aLevel).erase(0, 1) + ")";
        }
        else if (aLevel == 45)
        {
            DrawBottom(g, _S("[FOUND_WATERING_CAN]"), _S("[WATERING_CAN]"), _S("[WATERING_CAN_DESCRIPTION]"));
            g->DrawImage(Sexy::IMAGE_WATERINGCAN, BOARD_WIDTH / 2 - Sexy::IMAGE_WATERINGCAN->mWidth / 2, 160);
        }
        else if (aLevel == 50)
        {
            g->DrawImage(Sexy::IMAGE_BACKGROUND1, -700, -300, 2800, 1200);
            g->DrawImage(Sexy::IMAGE_ZOMBIE_NOTE, 80, 80);
            g->DrawImage(Sexy::IMAGE_ZOMBIE_FINAL_NOTE, 114, 138);
            TodDrawString(g, _S("[FOUND_NOTE]"), BOARD_WIDTH / 2, 70, Sexy::FONT_DWARVENTODCRAFT24, Color(255, 200, 0, 255), DS_ALIGN_CENTER);
            mState = "Zombie Note (" + mApp->GetStageString(aLevel).erase(0, 1) + ")";
        }
        else if (aLevel == 1 && mApp->HasFinishedAdventure())
        {
            DrawBottom(g, _S("[WIN_MESSAGE1]"), _S("[SILVER_SUNFLOWER_TROPHY]"), _S("[WIN_MESSAGE2]"));
            TodDrawImageCelCenterScaledF(g, Sexy::IMAGE_SUNFLOWER_TROPHY, 325, 65, 0, 0.6f, 0.6f);
        }
        else
        {
            DrawAwardSeed(g);
        }
    }

    if (mShowAchievements)
    {
        g->DrawImage(Sexy::IMAGE_CHALLENGE_BACKGROUND, 0, 0);
        mStartButton->SetLabel("[CONTINUE_BUTTON]");
        SexyString aTitleString = _S("ACHIEVEMENTS");
        TodDrawString(g, aTitleString, 400, 58, Sexy::FONT_HOUSEOFTERROR28, Color(220, 220, 220), DS_ALIGN_CENTER);
        mMenuButton->mBtnNoDraw = true;
        g->SetClipRect(cAchievementClipRect);
        int totalShown = 0;
        int maxScroll = 0;
        for (int i = 0; i < NUM_ACHIEVEMENTS; i++)
        {
            if (mApp->mPlayerInfo->mEarnedAchievements[i] && !mApp->mPlayerInfo->mShownedAchievements[i] && mApp->mAchievements->ReturnShowInAwards(i)) 
            {
                totalShown++;
                SexyString aAchievementName = StrFormat(_S("[ACHIEVEMENT_%s_TITLE]"), mApp->mAchievements->ReturnAchievementName(i).c_str());
                SexyString aAchievementDesc = StrFormat(_S("[ACHIEVEMENT_%s_DESCRIPTION]"), mApp->mAchievements->ReturnAchievementName(i).c_str());
                Rect textRect = Rect(80, 30, 320, 230);
                int xPos = BOARD_WIDTH / 2 - textRect.mWidth / 2 - 35;
                int offset = 75;
                int yPos = 20 + (totalShown * offset) - mScrollPosition;
                textRect.mX += xPos;
                textRect.mY += yPos - 2;
                g->DrawImageCel(Sexy::IMAGE_ACHIEVEMENTS_PORTRAITS, xPos, yPos, i);
                TodDrawString(g, aAchievementName, textRect.mX, yPos + 23, Sexy::FONT_DWARVENTODCRAFT24, Color(255, 200, 0, 255), DS_ALIGN_LEFT);
                TodDrawStringWrapped(g, aAchievementDesc, textRect, Sexy::FONT_DWARVENTODCRAFT12, Color(255, 255, 255), DS_ALIGN_LEFT);
                maxScroll += offset;
            }
        }
        mMaxScrollPosition = max(0, maxScroll - cAchievementClipRect.mHeight - 5);
        g->ClearClipRect();
        mSlider->SliderDraw(g);

    }
    else
    {
        if (mAwardType == AWARD_HELP_ZOMBIENOTE)
        {
            mStartButton->SetLabel("[MAIN_MENU_BUTTON]");
        }
        else if (!mApp->IsAdventureMode())
        {
            mStartButton->SetLabel("[MAIN_MENU_BUTTON]");
        }
        else if (aLevel == 1)
        {
            mStartButton->SetLabel("[CONTINUE_BUTTON]");
        }
        else if (aLevel == 15)
            mStartButton->SetLabel("[VIEW_ALMANAC_BUTTON]");
        else if (aLevel == 25 || aLevel == 35 || aLevel == 45)
            mStartButton->SetLabel("[CONTINUE_BUTTON]");
        else
            mStartButton->SetLabel("[NEXT_LEVEL_BUTTON]");

        if (mApp->HasFinishedAdventure())
        {
            mStartButton->SetLabel("[CONTINUE_BUTTON]");
        }
        mMenuButton->mBtnNoDraw = mWasDrawn;
    }
    mMenuButton->Draw(g);
    mStartButton->Draw(g);


    int aFadeInAlpha = TodAnimateCurve(180, 0, mFadeInCounter, 255, 0, CURVE_LINEAR);
    g->SetColor(IsPaperNote() ? Color(0, 0, 0, aFadeInAlpha) : Color(255, 255, 255, aFadeInAlpha));
    g->FillRect(0, 0, BOARD_WIDTH, BOARD_HEIGHT);
}

void AwardScreen::Update()
{
    Widget::Update();
    if (mApp->GetDialogCount() > 0) return;
    if (!(mSlider->mIsOver || mSlider->mDragging))
        mApp->SetCursor(mStartButton->IsMouseOver() || mMenuButton->IsMouseOver() ? CURSOR_HAND : CURSOR_POINTER);
    mStartButton->Update();
    mMenuButton->Update();
    mApp->SetCursor(mStartButton->IsMouseOver() || mMenuButton->IsMouseOver() ? CURSOR_HAND : CURSOR_POINTER);
    MarkDirty();
    if (mFadeInCounter > 0) mFadeInCounter--;
    if (mAchievementCounter > 0) mAchievementCounter--;
    mApp->UpdateDiscordState(mState);
    mScrollPosition = ClampFloat(mScrollPosition += mScrollAmount * (mBaseScrollSpeed + abs(mScrollAmount) * mScrollAccel), 0, mMaxScrollPosition);
    mScrollAmount *= (1.0f - mScrollAccel);
    mSlider->SetValue(max(0.0, min(mMaxScrollPosition, mScrollPosition)) / mMaxScrollPosition);
    mSlider->mVisible = mMaxScrollPosition != 0 && mShowAchievements;
    MarkDirty();
}

void AwardScreen::AddedToManager(WidgetManager* theWidgetManager)
{
    Widget::AddedToManager(theWidgetManager);
    AddWidget(mSlider);
}

void AwardScreen::RemovedFromManager(WidgetManager* theWidgetManager)
{
    Widget::RemovedFromManager(theWidgetManager);
    RemoveWidget(mSlider);
}

void AwardScreen::KeyChar(char theChar)
{
    if (theChar == ' ' || theChar == '\r' || theChar == '\u001B')
        StartButtonPressed();
}

void AwardScreen::ExitScreen()
{
    if (mApp->mPlayedQuickplay)
    {
        mApp->KillAwardScreen();
        mApp->KillGameSelector();
        mApp->ShowGameSelector();
        return;
    }
    else if (mAwardType == AWARD_CREDITS_ZOMBIENOTE)
    {
        mApp->KillAwardScreen();
        mApp->ShowCreditScreen();
    }
    else if (mAwardType == AWARD_HELP_ZOMBIENOTE)
    {
        mApp->KillAwardScreen();
        mApp->ShowGameSelector();
    }
    else if (mApp->IsSurvivalMode())
    {
        mApp->KillAwardScreen();
        mApp->ShowChallengeScreen(CHALLENGE_PAGE_SURVIVAL);
    }
    else if (mApp->IsPuzzleMode())
    {
        mApp->KillAwardScreen();
        mApp->ShowChallengeScreen(CHALLENGE_PAGE_PUZZLE);
    }
    else if (mApp->IsChallengeMode())
    {
        mApp->KillAwardScreen();
        mApp->ShowChallengeScreen(CHALLENGE_PAGE_CHALLENGE);
    }
    else
    {
        int aLevel = mApp->mPlayerInfo->mLevel;
        if (aLevel == 1)
        {
            mApp->KillAwardScreen();
            if (mApp->HasFinishedAdventure())
            {
                mApp->ShowAwardScreen(AWARD_CREDITS_ZOMBIENOTE, true);
            }
            else
            {
                mApp->PreNewGame(GAMEMODE_ADVENTURE, false);
            }
        }
        else
        {
            if (aLevel == 15)
            {
                mApp->DoAlmanacDialog()->WaitForResult();
            }
            else if (aLevel == 25)
            {
                StoreScreen* aStore = mApp->ShowStoreScreen();
                aStore->SetupForIntro(301);
                aStore->WaitForResult(true);

                if (aStore->mPurchasedFullVersion)
                {
                    mApp->KillAwardScreen();
                    mApp->ShowGameSelector();
                    return;
                }
                if (mApp->IsTrialStageLocked())
                {
                    mApp->KillAwardScreen();
                    mApp->PreNewGame(GAMEMODE_UPSELL, false);
                    if (!mApp->mPlayerInfo->mHasSeenUpsell)
                    {
                        mApp->mBoard->mStoreButton->mBtnNoDraw = true;
                        mApp->mPlayerInfo->mHasSeenUpsell = true;
                    }
                    return;
                }
            }
            else if (aLevel == 35)
            {
                StoreScreen* aStore = mApp->ShowStoreScreen();
                aStore->SetupForIntro(601);
                aStore->WaitForResult(true);
            }
            else if (aLevel == 42)
            {
                StoreScreen* aStore = mApp->ShowStoreScreen();
                aStore->SetupForIntro(3100);
                aStore->WaitForResult(true);
            }
            else if (aLevel == 45)
            {
                mApp->KillAwardScreen();
                mApp->PreNewGame(GAMEMODE_CHALLENGE_ZEN_GARDEN, false);
                mApp->mZenGarden->SetupForZenTutorial();
                return;
            }

            mApp->KillAwardScreen();
            mApp->PreNewGame(GAMEMODE_ADVENTURE, false);
        }
    }
}

void AwardScreen::StartButtonPressed()
{
    if (mApp->GetDialog(DIALOG_STORE))
        return;

    if (mShowAchievements)
    {
        for (int i = 0; i < NUM_ACHIEVEMENTS; i++) {
            if (mApp->mPlayerInfo->mEarnedAchievements[i] && !mApp->mPlayerInfo->mShownedAchievements[i]) {
                mApp->mPlayerInfo->mShownedAchievements[i] = true;
            }
        }
        mShowAchievements = false;
        mFadeInCounter = 180;
        if (mAwardType == AWARD_ACHIEVEMENTONLY)
        {
            ExitScreen();
        }
        else
            StartSounds();
        return;
    }
    ExitScreen();
}

void AwardScreen::MouseDown(int x, int y, int theClickCount)
{
    if (theClickCount == 1 && (mStartButton->IsMouseOver() || mMenuButton->IsMouseOver()))
        mApp->PlaySample(Sexy::SOUND_TAP);
}

void AwardScreen::MouseUp(int x, int y, int theClickCount)
{
    if (theClickCount == 1)
    {
        if (mStartButton->IsMouseOver())
            StartButtonPressed();
        if (mMenuButton->IsMouseOver())
        {
            for (int i = 0; i < NUM_ACHIEVEMENTS; i++) {
                if (mApp->mPlayerInfo->mEarnedAchievements[i] && !mApp->mPlayerInfo->mShownedAchievements[i]) {
                    mApp->mPlayerInfo->mShownedAchievements[i] = true;
                }
            }
            mApp->KillAwardScreen();
            mApp->ShowGameSelector();
            
        }
    }
}

void AwardScreen::SliderVal(int theId, double theVal)
{
    if (!mShowAchievements)
        return;
    switch (theId)
    {
    case AwardScreen::AwardScreen_Slider:
        mScrollPosition = theVal * mMaxScrollPosition;
        break;
    }
}

void AwardScreen::MouseWheel(int theDelta)
{
    if (!mShowAchievements)
        return;
    mScrollAmount -= mBaseScrollSpeed * theDelta;
    mScrollAmount -= mScrollAmount * mScrollAccel;
}

void AwardScreen::StartSounds()
{
    if (IsPaperNote())
    {
        mApp->mMusic->StopAllMusic();
        mStartButton->mY += 20;
        mApp->PlayFoley(FOLEY_PAPER);
    }
    else
        mApp->mMusic->MakeSureMusicIsPlaying(MUSIC_TUNE_ZEN_GARDEN);
}