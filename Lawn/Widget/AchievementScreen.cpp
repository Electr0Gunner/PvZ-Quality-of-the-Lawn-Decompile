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
    mApp->mDetails = "In the Achievement Screen";
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

   //positions from re-plants-vs-zombies (by @Patoke)
   g->DrawImage(Sexy::IMAGE_ACHIEVEMENT_BOOKWORM, 0, 1125 + mScrollPosition);
   g->DrawImage(Sexy::IMAGE_ACHIEVEMENT_BEJEWELED, 0, 2250 + mScrollPosition);
   g->DrawImage(Sexy::IMAGE_ACHIEVEMENT_CHUZZLE, 0, 4500 + mScrollPosition);
   g->DrawImage(Sexy::IMAGE_ACHIEVEMENT_PEGGLE, 0, 6750 + mScrollPosition);
   g->DrawImage(Sexy::IMAGE_ACHIEVEMENT_PIPE, 0, 9000 + mScrollPosition);
   g->DrawImage(Sexy::IMAGE_ACHIEVEMENT_ZUMA, 0, 11250 + mScrollPosition);

    for (int i = 0; i < NUM_ACHIEVEMENTS; i++)
    {
        yPosIndex++;
        SexyString aAchievementName = StrFormat(_S("[ACHIEVEMENT_%s_TITLE]"), mApp->mAchievements->ReturnAchievementName(i).c_str());
        SexyString aAchievementDesc = StrFormat(_S("[ACHIEVEMENT_%s_DESCRIPTION]"), mApp->mAchievements->ReturnAchievementName(i).c_str());
        int yPos = 178 + (57 * (i / 2)) + mScrollPosition;
        int xPos = 90;
        if (i % 2 != 0)
        {
            xPos = 380;
        }
        xPos += 120;
        TodDrawString(g, aAchievementName, xPos - 20, yPos + 16, Sexy::FONT_DWARVENTODCRAFT15, Color(21, 175, 0), DS_ALIGN_LEFT);
        g->SetColor(Color::White);
        g->SetFont(Sexy::FONT_DWARVENTODCRAFT12);
        g->DrawStringWordWrapped(TodStringTranslate(aAchievementDesc), xPos - 20, yPos + 30, 215, 12);
        g->SetColorizeImages(true);
        g->SetColor(mApp->mPlayerInfo->mEarnedAchievements[i] ? Color(255, 255, 255) : Color(255, 255, 255, 32));
        int imagePosX = xPos - 90;
        g->SetScale(0.8f, 0.8f, imagePosX, yPos);
        g->DrawImageCel(Sexy::IMAGE_ACHIEVEMENTS_PORTRAITS, imagePosX, yPos, i);
        g->SetScale(1, 1, 0, 0);
        g->SetColorizeImages(false);
    }
}

void AchievementScreen::KeyDown(KeyCode theKey) {
    if (mApp->mWidgetManager->mFocusWidget != this)
        return;
    if (theKey == KEYCODE_UP) {
        mScrollPosition += 15;
    }
    else if (theKey == KEYCODE_DOWN) {
        mScrollPosition -= 15;
    }
    else if (theKey == KEYCODE_ESCAPE)
    {
        ExitScreen();
    }
}

void AchievementScreen::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
    AddWidget(mBackButton);
    AddWidget(mRockButton);
}

void AchievementScreen::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
    RemoveWidget(mBackButton);
    RemoveWidget(mRockButton);
}

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

    mMaxScrollPosition = 15342;//Sexy::IMAGE_ACHIEVEMENT_TILE->mHeight * 69 + Sexy::IMAGE_ACHIEVEMENT_TILE_CHINA->mHeight;
    float aScrollSpeed = mBaseScrollSpeed + abs(mScrollAmount) * mScrollAccel;
    mScrollPosition = ClampFloat(mScrollPosition -= mScrollAmount * aScrollSpeed, -mMaxScrollPosition, 0);
    mScrollAmount *= (1.0f - mScrollAccel);
    mBackButton->Resize(128, 55 + mScrollPosition, 130, 80);
    mRockButton->Resize(710, 470 + mScrollPosition, IMAGE_ACHIEVEMENT_MORE->mWidth, IMAGE_ACHIEVEMENT_MORE->mHeight);
}

void AchievementScreen::ButtonDepress(int theId)
{
    if (theId == 0)
    {
        ExitScreen();
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

void AchievementScreen::ExitScreen()
{
    mScrollPosition = 0;
    mApp->mGameSelector->mMovementTimer = 75;
    mApp->mGameSelector->mDestinationY = 0;
    mApp->mGameSelector->mSelectorState = SELECTOR_IDLE;
    mApp->mGameSelector->mEnableButtonsTransition = true;
    mApp->mWidgetManager->SetFocus(mApp->mGameSelector);
    mBackButton->SetDisabled(true);
    mRockButton->SetDisabled(true);
}

void AchievementScreen::MouseWheel(int theDelta)
{
    if (mApp->mGameSelector->mMovementTimer > 0)
        return;
    mScrollAmount -= mBaseScrollSpeed * theDelta;
    mScrollAmount -= mScrollAmount * mScrollAccel;
}
