#include "GameButton.h"
#include "../../LawnApp.h"
#include "../System/Music.h"
#include "MiniCreditsScreen.h"
#include "../../Resources.h"
#include "../../Sexy.TodLib/TodDebug.h"
#include "../../Sexy.TodLib/TodFoley.h"
#include "../../Sexy.TodLib/TodCommon.h"
#include "../../SexyAppFramework/Debug.h"
#include "../../Sexy.TodLib/TodStringFile.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "../../GameConstants.h"

MiniCreditsScreen::MiniCreditsScreen(LawnApp* theApp)
{
	mApp = theApp;
	mApp->mMusic->MakeSureMusicIsPlaying(MUSIC_TUNE_CHOOSE_YOUR_SEEDS);
	TodLoadResources("DelayLoad_ChallengeScreen");
	TodLoadResources("DelayLoad_Credits");

	mBackButton = MakeNewButton(0, this, _S("[BACK_TO_MENU]"), nullptr, Sexy::IMAGE_SEEDCHOOSER_BUTTON2,
		Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW, Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW);
	mBackButton->mTextDownOffsetX = 1;
	mBackButton->mTextDownOffsetY = 1;
	mBackButton->mColors[ButtonWidget::COLOR_LABEL] = Color(42, 42, 90);
	mBackButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color(42, 42, 90);
	mBackButton->Resize(18, 568, 111, 26);

	mMusicButton = MakeNewButton(1, this, _S("[CREDITS_BUTTON]"), nullptr, Sexy::IMAGE_CREDITS_PLAYBUTTON,
		Sexy::IMAGE_CREDITS_PLAYBUTTON, Sexy::IMAGE_CREDITS_PLAYBUTTON);
	mMusicButton->SetFont(Sexy::FONT_HOUSEOFTERROR20);
	mMusicButton->mColors[ButtonWidget::COLOR_LABEL] = Color(255, 255, 255);
	mMusicButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color(213, 159, 43);
	mMusicButton->Resize(500, 520, 400, 73);
	mMusicButton->mTextOffsetX = -30;
	mMusicButton->mTextOffsetY = -2;
	mMusicButton->mButtonOffsetY = 8;

	mApp->mDetails = "In the Credits Screen";
}
MiniCreditsScreen::~MiniCreditsScreen()
{
	delete mBackButton;
	if(mMusicButton)
		delete mMusicButton;
}

void MiniCreditsScreen::Draw(Graphics* g)
{
	//g->SetLinearBlend(true);
	g->DrawImage(Sexy::IMAGE_CREDITS_BG, 0, 0);
	TodDrawString(g, "CREDITS", 400, 58, Sexy::FONT_HOUSEOFTERROR28, Color(220, 220, 220), DS_ALIGN_CENTER);

	Color TextColor = Color(255, 255, 255);

	TodDrawString(g, "'insert your mod name' Team \n", 400, 120, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);
	TodDrawString(g, "Insert Name\n", 400, 140, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);
	TodDrawString(g, "Insert Name\n", 400, 160, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);
	TodDrawString(g, "Insert Name\n", 400, 180, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);
	TodDrawString(g, "Insert Name\n", 400, 200, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);

	TodDrawString(g, "Plants Vs. Zombies Team \n", 120, 420, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);
	TodDrawString(g, "George Fan\n", 120, 440, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);
	TodDrawString(g, "Rich Werner\n", 120, 460, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);
	TodDrawString(g, "Stephen Notley\n", 120, 480, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);
	TodDrawString(g, "Laura Shigihara", 120, 500, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);
	TodDrawString(g, "Tod Semple", 120, 520, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);

	TodDrawString(g, "Quality of The Lawn Team \n", 400, 380, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);
	TodDrawString(g, "Electr0Gunner\n", 400, 400, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);
	TodDrawString(g, "BULLETBOT\n", 400, 420, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);

	TodDrawString(g, "Special Thanks \n", 630, 420, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);
	TodDrawString(g, "InLiothixie\n", 630, 440, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);
	TodDrawString(g, "PvZ Modding Association Members\n", 630, 460, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);
	TodDrawString(g, "Yukinonon\n", 630, 480, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);
	TodDrawString(g, "timoox_\n", 630, 500, Sexy::FONT_HOUSEOFTERROR16, TextColor, DS_ALIGN_CENTER);

	//mMusicButton->Draw(g);
}
void MiniCreditsScreen::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
	AddWidget(mBackButton);
	if(mApp->HasFinishedAdventure())
		AddWidget(mMusicButton);
}

void MiniCreditsScreen::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
	RemoveWidget(mBackButton);
	if (mApp->HasFinishedAdventure())
		RemoveWidget(mMusicButton);
}

void MiniCreditsScreen::ButtonPress(int theId)
{
	mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
}

void MiniCreditsScreen::Update()
{
	Widget::Update();
	mBackButton->Update();
	if (mApp->HasFinishedAdventure())
		mMusicButton->Update();

	MarkDirty();
}

void MiniCreditsScreen::ButtonDepress(int theId)
{
	if (theId == 0)
	{
		mApp->KillMiniCreditScreen();
		mApp->DoBackToMain();
	}
	if (theId == 1)
	{
		mApp->KillMiniCreditScreen();
		mApp->ShowCreditScreen();
	}
}