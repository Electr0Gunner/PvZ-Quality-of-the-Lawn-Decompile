#include "GameButton.h"
#include "../Achievements.h"
#include "../../LawnApp.h"
#include "../System/Music.h"
#include "../System/PoolEffect.h"
#include "../System/PlayerInfo.h"
#include "QuickPlayScreen.h"
#include "GameSelector.h"
#include "../../Resources.h"
#include "../../Sexy.TodLib/TodDebug.h"
#include "../../Sexy.TodLib/TodFoley.h"
#include "../../Sexy.TodLib/TodCommon.h"
#include "../../SexyAppFramework/Debug.h"
#include "../../Sexy.TodLib/TodStringFile.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "../../GameConstants.h"
#include "../Zombie.h"
#include "../Plant.h"

QuickPlayScreen::QuickPlayScreen(LawnApp* theApp)
{
    mApp = theApp;
    TodLoadResources("DelayLoad_QuickPlay");
    TodLoadResources("DelayLoad_AwardScreen");
    TodLoadResources("DelayLoad_Background1");
    TodLoadResources("DelayLoad_BackgroundUnsodded");
    TodLoadResources("DelayLoad_Background2");
    TodLoadResources("DelayLoad_Background3");
    TodLoadResources("DelayLoad_Background4");
    TodLoadResources("DelayLoad_Background5");
    TodLoadResources("DelayLoad_Background6");

    mBackground = BackgroundType::BACKGROUND_1_DAY;
    mZombieType = ZombieType::ZOMBIE_NORMAL;
    mSeedType = SeedType::SEED_PEASHOOTER;
    mLevel = 1;

    mBackButton = MakeNewButton(0, this, "", nullptr, Sexy::IMAGE_BLANK,
        Sexy::IMAGE_QUICKPLAY_BACK_HIGHLIGHT, Sexy::IMAGE_QUICKPLAY_BACK_HIGHLIGHT);
    mBackButton->Resize(278, 528, IMAGE_QUICKPLAY_BACK_HIGHLIGHT->mWidth, IMAGE_QUICKPLAY_BACK_HIGHLIGHT->mHeight);

    mLeftButton = MakeNewButton(1, this, "", nullptr, Sexy::IMAGE_QUICKPLAY_LEFT_BUTTON,
        Sexy::IMAGE_QUICKPLAY_LEFT_BUTTON_HIGHLIGHT, Sexy::IMAGE_QUICKPLAY_LEFT_BUTTON_HIGHLIGHT);
    mLeftButton->Resize(240, 380, IMAGE_QUICKPLAY_LEFT_BUTTON->mWidth, IMAGE_QUICKPLAY_LEFT_BUTTON->mHeight);

    mRightButton = MakeNewButton(2, this, "", nullptr, Sexy::IMAGE_QUICKPLAY_RIGHT_BUTTON,
        Sexy::IMAGE_QUICKPLAY_RIGHT_BUTTON_HIGHLIGHT, Sexy::IMAGE_QUICKPLAY_RIGHT_BUTTON_HIGHLIGHT);
    mRightButton->Resize(510, 380, IMAGE_QUICKPLAY_RIGHT_BUTTON->mWidth, IMAGE_QUICKPLAY_RIGHT_BUTTON->mHeight);

    mPlayButton = new GameButton(3);
    mPlayButton->mDrawStoneButton = true;
    mPlayButton->Resize(310, 380, 163, 46);
    mPlayButton->SetLabel("PLAY");

    mDisplayZombie = new Zombie();
    mDisplayZombie->mBoard = nullptr;
    mDisplayZombie->ZombieInitialize(0, mZombieType, false, nullptr, Zombie::ZOMBIE_WAVE_UI);

    mDisplayPlant = new Plant();
    mDisplayPlant->mIsOnBoard = false;
    mDisplayPlant->PlantInitialize(0, 0, mSeedType, SEED_NONE);

    mFlowerPot = new Plant();
    mFlowerPot->mIsOnBoard = false;
    mFlowerPot->PlantInitialize(0, 0, SEED_FLOWERPOT, SEED_NONE);
}
QuickPlayScreen::~QuickPlayScreen()
{
    delete mLeftButton;
    delete mRightButton;
    delete mBackButton;
    delete mPlayButton;
    delete mDisplayZombie;
    delete mDisplayPlant;
    delete mFlowerPot;
}

void QuickPlayScreen::Draw(Graphics* g)
{
    g->DrawImage(Sexy::IMAGE_QUICKPLAY_BACKGROUND, 0, 0);
    g->SetClipRect(130, 30, 530, 370);
    switch (mBackground)
    {
    case BackgroundType::BACKGROUND_1_DAY:				g->DrawImage(Sexy::IMAGE_BACKGROUND1, -130, 0);                       break;
    case BackgroundType::BACKGROUND_2_NIGHT:			g->DrawImage(Sexy::IMAGE_BACKGROUND2, -130, 0);						break;
    case BackgroundType::BACKGROUND_3_POOL:				
        g->DrawImage(Sexy::IMAGE_BACKGROUND3, -130, 0);
        DrawPool(g, false);
        break;
    case BackgroundType::BACKGROUND_4_FOG:				        
        g->DrawImage(Sexy::IMAGE_BACKGROUND4, -130, 0);
        DrawPool(g, true);
        break;
    case BackgroundType::BACKGROUND_5_ROOF:				g->DrawImage(Sexy::IMAGE_BACKGROUND5, -130, 0);						break;
    case BackgroundType::BACKGROUND_6_BOSS:				g->DrawImage(Sexy::IMAGE_BACKGROUND6BOSS, -130, 0);					break;
    default:											TOD_ASSERT();											break;
    }
    g->ClearClipRect();
    if (mDisplayZombie)
    {
        Graphics aZombieGraphics = Graphics(*g);
        mDisplayZombie->BeginDraw(&aZombieGraphics);
        mDisplayZombie->Draw(&aZombieGraphics);
        mDisplayZombie->DrawShadow(&aZombieGraphics);
        mDisplayZombie->mPosX = 340;
        mDisplayZombie->mPosY = 240;
        if (mBackground == BACKGROUND_3_POOL || mBackground == BACKGROUND_4_FOG)
        {
            mDisplayZombie->mPosY -= 120;
        }
    }
    if (mFlowerPot)
    {
        if (mBackground == BACKGROUND_5_ROOF || mBackground == BACKGROUND_6_BOSS)
        {
            Graphics aPotGraphics = Graphics(*g);
            mFlowerPot->BeginDraw(&aPotGraphics);
            mFlowerPot->Draw(&aPotGraphics);
            mFlowerPot->mX = 280;
            mFlowerPot->mY = 280;
        }
    }
    if (mDisplayPlant)
    {
        Graphics aPlantGraphics = Graphics(*g);
        mDisplayPlant->BeginDraw(&aPlantGraphics);
        //mDisplayPlant->DrawShadow(&aPlantGraphics, 0, 0);
        mDisplayPlant->Draw(&aPlantGraphics);
        mDisplayPlant->mX = 280;
        mDisplayPlant->mY = 280;
        if ((mBackground == BACKGROUND_3_POOL || mBackground == BACKGROUND_4_FOG) && !mDisplayPlant->IsAquatic(mDisplayPlant->mSeedType))
        {
            mDisplayPlant->mY -= 120;
        }
        if(mBackground == BACKGROUND_5_ROOF || mBackground == BACKGROUND_6_BOSS)
        {
            mDisplayPlant->mY -= 10;
        }
    }
    g->DrawImage(Sexy::IMAGE_QUICKPLAY_WIDGET, 100, 0);
    int aStage = ClampInt((mLevel - 1) / 10 + 1, 1, ADVENTURE_AREAS);
    int aSub = mLevel - (aStage - 1) * 10;
    SexyString curLevel = to_string(aStage);
    curLevel += "-";
    curLevel += to_string(aSub);
    TodDrawString(g, curLevel, 380, 30, Sexy::FONT_DWARVENTODCRAFT18GREENINSET, Color(0, 255, 0), DS_ALIGN_CENTER);
    mPlayButton->Draw(g);
}

void QuickPlayScreen::KeyDown(KeyCode theKey) {
    if (theKey == KEYCODE_LEFT) {
        mLevel--;
        mLevel = ClampInt(mLevel, 1, NUM_LEVELS);
        ChooseBackground();
        ResetZombie();
        ResetPlant(true);
    }
    if (theKey == KEYCODE_RIGHT)
    {
        mLevel++;
        mLevel = ClampInt(mLevel, 1, NUM_LEVELS);
        ChooseBackground();
        ResetZombie();
        ResetPlant(false);
    }

}

void QuickPlayScreen::DrawPool(Graphics* g, bool isNight)
{
    g->SetClipRect(140, 30, 500, 370);
    mApp->mPoolEffect->PoolEffectDraw(g, isNight);
    g->ClearClipRect();
}

void QuickPlayScreen::ChooseBackground()
{
    if (mLevel <= 1 * LEVELS_PER_AREA)
    {
        mBackground = BackgroundType::BACKGROUND_1_DAY;
    }
    else if (mLevel <= 2 * LEVELS_PER_AREA)
    {
        mBackground = BackgroundType::BACKGROUND_2_NIGHT;
    }
    else if (mLevel <= 3 * LEVELS_PER_AREA)
    {
        mBackground = BackgroundType::BACKGROUND_3_POOL;
    }
    else if (mLevel <= 4 * LEVELS_PER_AREA)
    {
        mBackground = BackgroundType::BACKGROUND_4_FOG;
    }
    else if (mLevel < FINAL_LEVEL)
    {
        mBackground = BackgroundType::BACKGROUND_5_ROOF;
    }
    else if (mLevel == FINAL_LEVEL)
    {
        mBackground = BackgroundType::BACKGROUND_6_BOSS;
    }
    else
    {
        mBackground = BackgroundType::BACKGROUND_1_DAY;
    }

}

void QuickPlayScreen::ChooseZombieType()
{
    if (mLevel == 3)
        mZombieType = ZOMBIE_TRAFFIC_CONE;
    else if (mLevel == 6)
        mZombieType = ZOMBIE_POLEVAULTER;
    else if (mLevel == 8)
        mZombieType = ZOMBIE_PAIL;
    else if (mLevel == 11)
        mZombieType = ZOMBIE_NEWSPAPER;
}

void QuickPlayScreen::AddedToManager(WidgetManager* theWidgetManager)
{
    Widget::AddedToManager(theWidgetManager);
    AddWidget(mBackButton);
    AddWidget(mLeftButton);
    AddWidget(mRightButton);
}

//0x42F6B0
void QuickPlayScreen::RemovedFromManager(WidgetManager* theWidgetManager)
{
    Widget::RemovedFromManager(theWidgetManager);
    RemoveWidget(mBackButton);
    RemoveWidget(mLeftButton);
    RemoveWidget(mRightButton);
}

//0x42F720
void QuickPlayScreen::ButtonPress(int theId)
{
    mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
}

void QuickPlayScreen::Update()
{
    mPlayButton->Update();
    mApp->mPoolEffect->PoolEffectUpdate();
    TOD_ASSERT(mLevel < 51);
    if (mDisplayZombie) mDisplayZombie->Update();
    if (mDisplayPlant) mDisplayPlant->Update();
    if (mFlowerPot) mFlowerPot->Update();
}

//0x42F740
void QuickPlayScreen::ButtonDepress(int theId)
{
    if (theId == 0)
    {
        mApp->mGameSelector->mMovementTimer = 75;
        mApp->mGameSelector->mSelectorState = SELECTOR_IDLE;
        mApp->mGameSelector->mDestinationX = 0;
        mApp->mWidgetManager->SetFocus(mApp->mGameSelector);
        mApp->mGameSelector->mAdventureButton->SetDisabled(false);
        mApp->mGameSelector->mMinigameButton->SetDisabled(false);
        mApp->mGameSelector->mPuzzleButton->SetDisabled(false);
        mApp->mGameSelector->mOptionsButton->SetDisabled(false);
        mApp->mGameSelector->mQuitButton->SetDisabled(false);
        mApp->mGameSelector->mHelpButton->SetDisabled(false);
        mApp->mGameSelector->mChangeUserButton->SetDisabled(false);
        mApp->mGameSelector->mStoreButton->SetDisabled(false);
        mApp->mGameSelector->mAlmanacButton->SetDisabled(false);
        mApp->mGameSelector->mSurvivalButton->SetDisabled(false);
        mApp->mGameSelector->mZenGardenButton->SetDisabled(false);
        mApp->mGameSelector->mAchievementButton->SetDisabled(false);
        mApp->mGameSelector->mQuickPlayButton->SetDisabled(false);
        mApp->mGameSelector->mCreditsButton->SetDisabled(false);
    }
    if (theId == 1)
    {
        mLevel--;
        mLevel = ClampInt(mLevel, 1, NUM_LEVELS);
        ChooseBackground();
        ResetZombie();
        ResetPlant(true);
    }
    if (theId == 2)
    {
        mLevel++;
        mLevel = ClampInt(mLevel, 1, NUM_LEVELS);
        ChooseBackground();
        ResetZombie();
        ResetPlant(false);
    }
}

void QuickPlayScreen::MouseUp(int x, int y, int theClickCount)
{
    if (mPlayButton->IsMouseOver())
    {
        mApp->mQuickLevel = mLevel;
        mApp->mPlayedQuickplay = true;
        mApp->KillGameSelector();
        mApp->KillQuickPlayScreen();
        mApp->StartQuickPlay(GameMode::GAMEMODE_ADVENTURE, true);
        return;
    }
}

void QuickPlayScreen::ResetZombie()
{
    ZombieType aPrevType = mZombieType;
    ChooseZombieType();
    if (aPrevType == mZombieType)
        return;
    mDisplayZombie = nullptr;
    mDisplayZombie = new Zombie();
    mDisplayZombie->mBoard = nullptr;
    mDisplayZombie->ZombieInitialize(0, mZombieType, false, nullptr, Zombie::ZOMBIE_WAVE_UI);
}

void QuickPlayScreen::ResetPlant(bool decrease)
{
    if (mLevel % 10 == 0)
        return;
    if (mApp->GetAwardSeedForLevel(mLevel - 1) == SEED_FLOWERPOT)
        return;
    SeedType aSeedType = mDisplayPlant->mSeedType;
    mDisplayPlant = nullptr;
    mDisplayPlant = new Plant();
    mDisplayPlant->mIsOnBoard = false;
    if(decrease)
        mDisplayPlant->PlantInitialize(0, 0, mApp->GetAwardSeedForLevel(mLevel - 1), SEED_NONE);
    else
    {
        mDisplayPlant->PlantInitialize(0, 0, mApp->GetAwardSeedForLevel(mLevel -1 ), SEED_NONE);
    }
}