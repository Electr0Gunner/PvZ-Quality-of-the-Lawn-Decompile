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
	TodLoadResources("DelayLoad_AwardScreen");
    TodLoadResources("DelayLoad_ChallengeScreen");

    mBackButton = MakeNewButton(0, this, _S("[BACK_TO_MENU]"), nullptr, Sexy::IMAGE_SEEDCHOOSER_BUTTON2,
        Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW, Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW);
    mBackButton->mTextDownOffsetX = 1;
    mBackButton->mTextDownOffsetY = 1;
    mBackButton->mColors[ButtonWidget::COLOR_LABEL] = Color(42, 42, 90);
    mBackButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color(42, 42, 90);
    mBackButton->Resize(18, 568, 111, 26);
}
AchievementScreen::~AchievementScreen()
{
    delete mBackButton;
}

void AchievementScreen::Draw(Graphics* g)
{
    int yPosIndex = 0;
    g->DrawImage(Sexy::IMAGE_CHALLENGE_BACKGROUND, 0, 0);
    for (int i = 0; i < TOTAL_ACHIEVEMENTS; i++)
    {
            yPosIndex++;
            SexyString aAchievementName = StrFormat(_S("[%s]"), mApp->mAchievement->ReturnAchievementName(i).c_str());
            SexyString aAchievementDesc = StrFormat(_S("[%s_DESCRIPTION]"), mApp->mAchievement->ReturnAchievementName(i).c_str());
            int yPos = 90 + (yPosIndex * 100);
            TodDrawString(g, aAchievementName, 150, yPos + 20, Sexy::FONT_DWARVENTODCRAFT24, Color(255, 200, 0, 255), DS_ALIGN_LEFT);
            //TodDrawString(g, aAchievementDesc, 150, yPos + 50, Sexy::FONT_DWARVENTODCRAFT24, Color(255, 255, 255, 255), DS_ALIGN_LEFT);
            TodDrawStringWrapped(g, aAchievementDesc, Rect(150, yPos + 30, 258, 230), Sexy::FONT_DWARVENTODCRAFT12, Color(255, 255, 255), DS_ALIGN_LEFT);
            g->DrawImageCel(Sexy::IMAGE_ACHIEVEMENTS_PORTRAITS, 60, yPos, 1);
    }


}
void AchievementScreen::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
    AddWidget(mBackButton);
}

//0x42F6B0
void AchievementScreen::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
    RemoveWidget(mBackButton);
}

//0x42F720
void AchievementScreen::ButtonPress(int theId)
{
	mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
}

void AchievementScreen::Update()
{
	mApp->UpdateDiscordRPC("In The Achievement Screen");
}

//0x42F740
void AchievementScreen::ButtonDepress(int theId)
{
    if (theId == 0)
    {
        mApp->mGameSelector->mAchievementTimer = 75;
        mApp->mGameSelector->mDestinationY = 0;
        mApp->mGameSelector->mSelectorState = SELECTOR_IDLE;
        mApp->mWidgetManager->BringToFront(mApp->mGameSelector);
        //mApp->KillAchievementScreen();
        //mApp->DoBackToMain();
    }
}