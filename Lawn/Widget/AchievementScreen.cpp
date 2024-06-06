#include "GameButton.h"
#include "../Achievements.h"
#include "../../LawnApp.h"
#include "../System/Music.h"
#include "../System/PlayerInfo.h"
#include "AchievementScreen.h"
#include "GameSelector.h"
#include "../../Resources.h"
#include "../../Sexy.TodLib/TodDebug.h"
#include "../../Sexy.TodLib/TodFoley.h"
#include "../../Sexy.TodLib/TodCommon.h"
#include "../../SexyAppFramework/Debug.h"
#include "../../Sexy.TodLib/TodStringFile.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "../../GameConstants.h"

AchievementScreen::AchievementScreen(LawnApp* theApp)
{
	mApp = theApp;
	TodLoadResources("DelayLoad_Achievements");
    TodLoadResources("DelayLoad_AwardScreen");
    mScrollAmount = 0;
    mScrollPosition = 0;
    mTweenTimer = 0;
    mGoesDown = false;

    mBackButton = MakeNewButton(0, this, "", nullptr, Sexy::IMAGE_BLANK,
        Sexy::IMAGE_ACHIEVEMENT_BACK_GLOW, Sexy::IMAGE_ACHIEVEMENT_BACK_GLOW);
    mBackButton->Resize(18, 568 + mScrollPosition, 111, 26);

    mRockButton = MakeNewButton(1, this, "", nullptr, Sexy::IMAGE_ACHIEVEMENT_MORE,
        Sexy::IMAGE_ACHIEVEMENT_MORE_HIGHLIGHT, Sexy::IMAGE_ACHIEVEMENT_MORE_HIGHLIGHT);
    mRockButton->Resize(710, 470 + mScrollPosition, IMAGE_ACHIEVEMENT_MORE->mWidth, IMAGE_ACHIEVEMENT_MORE->mHeight);
}
AchievementScreen::~AchievementScreen()
{
    delete mBackButton;
    delete mRockButton;
}

void AchievementScreen::Draw(Graphics* g)
{
    int yPosIndex = 0;

    g->DrawImage(Sexy::IMAGE_ACHIEVEMENT_SELECTOR_TILE, 0, 0 + mScrollPosition);
   for (int i = 1; i <= 70; i++)
    {
       if (i == 70)
       {
           g->DrawImage(Sexy::IMAGE_ACHIEVEMENT_TILE_CHINA, 0, Sexy::IMAGE_ACHIEVEMENT_TILE_CHINA->mHeight * i + mScrollPosition - 30);
       }
       else
            g->DrawImage(Sexy::IMAGE_ACHIEVEMENT_TILE, 0, Sexy::IMAGE_ACHIEVEMENT_TILE->mHeight * i + mScrollPosition);
    }
   g->DrawImage(Sexy::IMAGE_ACHIEVEMENT_ROCK, mRockButton->mX, mRockButton->mY);

    g->SetScale(0.9f, 0.9f,0,0);
    for (int i = 0; i < TOTAL_ACHIEVEMENTS; i++)
    {
            yPosIndex++;
            SexyString aAchievementName = StrFormat(_S("[%s]"), mApp->mAchievement->ReturnAchievementName(i).c_str());
            SexyString aAchievementDesc = StrFormat(_S("[%s_DESCRIPTION]"), mApp->mAchievement->ReturnAchievementName(i).c_str());
            int yPos = 178 + (72 * (i / 2)) + mScrollPosition;
            int xPos = 120;
            if (i % 2 != 0)
            {
                xPos = 429;
            }
            xPos += 120;
            TodDrawString(g, aAchievementName, xPos - 10, yPos + 17, Sexy::FONT_DWARVENTODCRAFT15, Color(21, 175, 0) , DS_ALIGN_LEFT);
            //TodDrawString(g, aAchievementDesc, 150, yPos + 50, Sexy::FONT_DWARVENTODCRAFT24, Color(255, 255, 255, 255), DS_ALIGN_LEFT);
            TodDrawStringWrapped(g, aAchievementDesc, Rect(xPos - 10, yPos + 19, 230, 260), Sexy::FONT_DWARVENTODCRAFT12, Color(255, 255, 255, 255), DS_ALIGN_LEFT);
            g->SetColorizeImages(true);
            g->SetColor(mApp->mPlayerInfo->mEarnedAchievements[i] ? Color(255, 255, 255) : Color(255, 255, 255, 32));
            g->DrawImageCel(Sexy::IMAGE_ACHIEVEMENTS_PORTRAITS, xPos - 90, yPos, i);
            g->SetColorizeImages(false);
    }
    g->SetScale(1.0f, 1.0f, 0, 0);

}
void AchievementScreen::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
    AddWidget(mBackButton);
    AddWidget(mRockButton);
}

//0x42F6B0
void AchievementScreen::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
    RemoveWidget(mBackButton);
    RemoveWidget(mRockButton);
}

//0x42F720
void AchievementScreen::ButtonPress(int theId)
{
	mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
}

void AchievementScreen::Update()
{
    if (mTweenTimer > 0)
    {
        int direction;
        if (mGoesDown)
            direction = -234;
        else
            direction = 0;
        DoButtonMovement(mScrollPosition, direction);
    }


    mBackButton->Resize(128, 55 + mScrollPosition, 130, 80);
    mRockButton->Resize(710, 470 + mScrollPosition, IMAGE_ACHIEVEMENT_MORE->mWidth, IMAGE_ACHIEVEMENT_MORE->mHeight);
    mMaxScrollPosition = 15342;//Sexy::IMAGE_ACHIEVEMENT_TILE->mHeight * 69 + Sexy::IMAGE_ACHIEVEMENT_TILE_CHINA->mHeight;
    float aScrollSpeed = mBaseScrollSpeed + abs(mScrollAmount) * mScrollAccel;
    mScrollPosition = ClampFloat(mScrollPosition -= mScrollAmount * aScrollSpeed, -mMaxScrollPosition, 0);
    mScrollAmount *= (1.0f - mScrollAccel);
}

//0x42F740
void AchievementScreen::ButtonDepress(int theId)
{
    if (theId == 0)
    {
        mScrollPosition = 0;
        mApp->mGameSelector->mAchievementTimer = 75;
        mApp->mGameSelector->mDestinationY = 0;
        mApp->mGameSelector->mSelectorState = SELECTOR_IDLE;
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
    }
    if (theId == 1)
    {
        mTweenTimer = 110;
        mGoesDown = !mGoesDown;
        if (mGoesDown)
        {
            mRockButton->mButtonImage = IMAGE_ACHIEVEMENT_TOP;
            mRockButton->mDownImage = IMAGE_ACHIEVEMENT_TOP_HIGHLIGHT;
            mRockButton->mOverImage = IMAGE_ACHIEVEMENT_TOP_HIGHLIGHT;
        }
        else
        {
            mRockButton->mButtonImage = IMAGE_ACHIEVEMENT_MORE;
            mRockButton->mDownImage = IMAGE_ACHIEVEMENT_MORE_HIGHLIGHT;
            mRockButton->mOverImage = IMAGE_ACHIEVEMENT_MORE_HIGHLIGHT;
        }
    }
}

void AchievementScreen::DoButtonMovement(int StartX, int FinalX)
{
    mScrollPosition = TodAnimateCurve(200, 0, mTweenTimer, StartX, FinalX, TodCurves::CURVE_EASE_IN_OUT);
    mTweenTimer--;
}

void AchievementScreen::MouseWheel(int theDelta)
{
    mScrollAmount -= mBaseScrollSpeed * theDelta;
    mScrollAmount -= mScrollAmount * mScrollAccel;
}
