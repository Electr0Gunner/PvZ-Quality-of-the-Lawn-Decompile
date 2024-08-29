#include <time.h>
#include "LawnApp.h"
#include "Lawn/Board.h"
#include "Lawn/Plant.h"
#include "Lawn/Zombie.h"
#include "Lawn/Cutscene.h"
#include "GameConstants.h"
#include "Lawn/Challenge.h"
#include "Lawn/ZenGarden.h"
#include "Sexy.TodLib/Trail.h"
#include "Lawn/System/Music.h"
#include "Lawn/System/SaveGame.h"
#include "Sexy.TodLib/TodDebug.h"
#include "Sexy.TodLib/TodFoley.h"
#include "Sexy.TodLib/Attachment.h"
#include "Lawn/System/PlayerInfo.h"
#include "Lawn/System/PoolEffect.h"
#include "Lawn/System/ProfileMgr.h"
#include "Lawn/System/PopDRMComm.h"
#include "Lawn/Widget/GameButton.h"
#include "Sexy.TodLib/Reanimator.h"
#include "Lawn/Widget/UserDialog.h"
#include "Lawn/System/TypingCheck.h"
#include "Sexy.TodLib/TodParticle.h"
#include "Lawn/Widget/AwardScreen.h"
#include "Lawn/Widget/TitleScreen.h"
#include "Lawn/Widget/StoreScreen.h"
#include "Lawn/Widget/CheatDialog.h"
#include "Lawn/Widget/GameSelector.h"
#include "Lawn/Widget/CreditScreen.h"
#include "Sexy.TodLib/EffectSystem.h"
#include "Sexy.TodLib/FilterEffect.h"
#include "SexyAppFramework/Graphics.h"
#include "Sexy.TodLib/TodStringFile.h"
#include "Lawn/Widget/AlmanacDialog.h"
#include "Lawn/Widget/NewUserDialog.h"
#include "Lawn/Widget/MiniCreditsScreen.h"
#include "Lawn/Widget/AchievementScreen.h"
#include "Lawn/Widget/QuickPlayScreen.h"
#include "Lawn/Widget/ContinueDialog.h"
#include "Lawn/System/ReanimationLawn.h"
#include "Lawn/Widget/ChallengeScreen.h"
#include "Lawn/Widget/NewOptionsDialog.h"
#include "Lawn/Widget/SeedChooserScreen.h"
#include "Lawn/Widget/ChallengePagesDialog.h"
#include "SexyAppFramework/WidgetManager.h"
#include "SexyAppFramework/CursorWidget.h"
#include "SexyAppFramework/ResourceManager.h"
#include "Lawn/Achievements.h"

#include "Lawn/System/discord_rpc.h"
#include "SexyAppFramework/Checkbox.h"
#include "SexyAppFramework/BassMusicInterface.h"
#include "SexyAppFramework/Dialog.h"
#include "SexyAppFramework/resource.h"

bool gIsPartnerBuild = false;
bool gSlowMo = false;  
bool gFastMo = false;  
LawnApp* gLawnApp = nullptr;  
int gSlowMoCounter = 0;  
bool isFastMode = false;  //the ingame fast mode


const char* CLIENT_ID = "1243252904878542908";

bool LawnGetCloseRequest()
{
	if (gLawnApp == nullptr)
		return false;

	return gLawnApp->mCloseRequest;
}

bool LawnHasUsedCheatKeys()
{
	return gLawnApp && gLawnApp->mPlayerInfo && gLawnApp->mPlayerInfo->mHasUsedCheatKeys;
}

LawnApp::LawnApp()
{
	mBoard = nullptr;
	mGameSelector = nullptr;
	mChallengeScreen = nullptr;
	mSeedChooserScreen = nullptr;
	mAwardScreen = nullptr;
	mCreditScreen = nullptr;
	mTitleScreen = nullptr;
	mQuickPlayScreen = nullptr;
	mMiniCreditsScreen = nullptr;
	mAchievementScreen = nullptr;
	mCursor = nullptr;
	mSoundSystem = nullptr;
	mKonamiCheck = nullptr;
	mMustacheCheck = nullptr;
	mMoustacheCheck = nullptr;
	mSuperMowerCheck = nullptr;
	mSuperMowerCheck2 = nullptr;
	mFutureCheck = nullptr;
	mPinataCheck = nullptr;
	mDanceCheck = nullptr;
	mDaisyCheck = nullptr;
	mSukhbirCheck = nullptr;
	mMustacheMode = false;
	mSuperMowerMode = false;
	mFutureMode = false;
	mPinataMode = false;
	mDanceMode = false;
	mDaisyMode = false;
	mSukhbirMode = false;
	mGameScene = GameScenes::SCENE_LOADING;
	mPoolEffect = nullptr;
	mZenGarden = nullptr;
	mEffectSystem = nullptr;
	mReanimatorCache = nullptr;
	mCloseRequest = false;
	mAchievements = nullptr;
	mWidth = BOARD_WIDTH;
	mHeight = BOARD_HEIGHT;
	mFullscreenBits = 32;
	mAppCounter = 0;
	mAppRandSeed = _time64(nullptr);
	mTrialType = TrialType::TRIALTYPE_NONE;
	mDebugTrialLocked = false;
	mMuteSoundsForCutscene = false;
	mMusicVolume = 0.85;
	mSfxVolume = 0.5525;
	mAutoStartLoadingThread = false;
	mDebugKeysEnabled = false;
	isFastMode = false;
	mProdName = "PlantsVsZombies";
	mVersion = "v2.1";
	mReconVersion = "PvZ: QoTL " + mVersion;
	std::string aTitleName = "Plants vs. Zombies";
#ifdef _DEBUG
	aTitleName += " DEBUG";
#endif

	mTitle = StringToSexyStringFast(aTitleName);
	mCustomCursorsEnabled = false;
	mPlayerInfo = nullptr;
	mLastLevelStats = new LevelStats();
	mFirstTimeGameSelector = true;
	mGameMode = GameMode::GAMEMODE_ADVENTURE;
	mEasyPlantingCheat = false;
	mAutoEnable3D = true;
	Tod_SWTri_AddAllDrawTriFuncs();
	mLoadingZombiesThreadCompleted = true;
	mGamesPlayed = 0;
	mMaxExecutions = 0;
	mMaxPlays = 0;
	mMaxTime = 0;
	mCompletedLoadingThreadTasks = 0;
	mProfileMgr = new ProfileMgr();
	mRegisterResourcesLoaded = false;
	mTodCheatKeys = false;
	mCrazyDaveReanimID = ReanimationID::REANIMATIONID_NULL;
	mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_OFF;
	mCrazyDaveBlinkCounter = 0;
	mCrazyDaveBlinkReanimID = ReanimationID::REANIMATIONID_NULL;
	mCrazyDaveMessageIndex = -1;
	mBigArrowCursor = LoadCursor(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDC_CURSOR1));
	mDRM = nullptr;
	mPlayedQuickplay = false;
	StartDiscord();
}

LawnApp::~LawnApp()
{
	Discord_Shutdown();
	if (mBoard)
	{
		WriteCurrentUserConfig();
	}

	if (mBoard)
	{
		mBoardResult = BoardResult::BOARDRESULT_QUIT_APP;
		mBoard->TryToSaveGame();
		mWidgetManager->RemoveWidget(mBoard);
		delete mBoard;
		mBoard = nullptr;
	}

	if (mTitleScreen)
	{
		mWidgetManager->RemoveWidget(mTitleScreen);
		delete mTitleScreen;
	}

	delete mSoundSystem;
	delete mMusic;


	if (mKonamiCheck)
	{
		delete mKonamiCheck;
	}
	if (mMustacheCheck)
	{
		delete mMustacheCheck;
	}
	if (mMoustacheCheck)
	{
		delete mMoustacheCheck;
	}
	if (mSuperMowerCheck)
	{
		delete mSuperMowerCheck;
	}
	if (mSuperMowerCheck2)
	{
		delete mSuperMowerCheck2;
	}
	if (mFutureCheck)
	{
		delete mFutureCheck;
	}
	if (mPinataCheck)
	{
		delete mPinataCheck;
	}
	if (mDanceCheck)
	{
		delete mDanceCheck;
	}
	if (mDaisyCheck)
	{
		delete mDaisyCheck;
	}
	if (mSukhbirCheck)
	{
		delete mSukhbirCheck;
	}

	if (mGameSelector)
	{
		mWidgetManager->RemoveWidget(mGameSelector);
		delete mGameSelector;
	}
	if (mChallengeScreen)
	{
		mWidgetManager->RemoveWidget(mChallengeScreen);
		delete mChallengeScreen;
	}
	if (mMiniCreditsScreen)
	{
		mWidgetManager->RemoveWidget(mMiniCreditsScreen);
		delete mMiniCreditsScreen;
	}
	if (mSeedChooserScreen)
	{
		mWidgetManager->RemoveWidget(mSeedChooserScreen);
		delete mSeedChooserScreen;
	}
	if (mAwardScreen)
	{
		mWidgetManager->RemoveWidget(mAwardScreen);
		delete mAwardScreen;
	}
	if (mCreditScreen)
	{
		mWidgetManager->RemoveWidget(mCreditScreen);
		delete mCreditScreen;
	}
	if (mAchievementScreen)
	{
		mWidgetManager->RemoveWidget(mAchievementScreen);
		delete mAchievementScreen;
	}
	if (mQuickPlayScreen)
	{
		mWidgetManager->RemoveWidget(mQuickPlayScreen);
		delete mQuickPlayScreen;
	}
	if (mCursor)
	{
		mWidgetManager->RemoveWidget(mCursor);
		delete mCursor;
	}

	delete mProfileMgr;
	delete mLastLevelStats;

	mResourceManager->DeleteResources("");
#ifdef _DEBUG
	BetaSubmit(true);
#endif
}

void LawnApp::Shutdown()
{
	if (!mLoadingThreadCompleted)
	{
		mLoadingFailed = true;
		return;
	}

	if (!mShutdown)
	{
		for (int i = 0; i < Dialogs::NUM_DIALOGS; i++)
		{
			KillDialog(i);
		}

		if (mBoard)
		{
			mBoardResult = BoardResult::BOARDRESULT_QUIT_APP;
			mBoard->TryToSaveGame();
			KillBoard();
			WriteCurrentUserConfig();
		}

		ProcessSafeDeleteList();

		if (mPoolEffect)
		{
			mPoolEffect->PoolEffectDispose();
			delete mPoolEffect;
			mPoolEffect = nullptr;
		}

		if (mZenGarden)
		{
			delete mZenGarden;
			mZenGarden = nullptr;
		}

		if (mEffectSystem)
		{
			mEffectSystem->EffectSystemDispose();
			delete mEffectSystem;
			mEffectSystem = nullptr;
		}

		if (mReanimatorCache)
		{
			mReanimatorCache->ReanimatorCacheDispose();
			delete mReanimatorCache;
			mReanimatorCache = nullptr;
		}

		FilterEffectDisposeForApp();
		TodParticleFreeDefinitions();
		ReanimatorFreeDefinitions();
		TrailFreeDefinitions();
		FreeGlobalAllocators();
		UpdateRegisterInfo();
		SexyAppBase::Shutdown();

		if (mDRM)
		{
			delete mDRM;
		}
		mDRM = nullptr;
	}
}

void LawnApp::KillBoard()
{
	FinishModelessDialogs();
	KillSeedChooserScreen();
	if (mBoard)
	{
#ifdef _DEBUG
		BetaRecordLevelStats();
#endif
		mBoard->DisposeBoard();
		mWidgetManager->RemoveWidget(mBoard);
		SafeDeleteWidget(mBoard);
		mBoard = nullptr;
	}

	SetCursor(CURSOR_POINTER);
}

bool LawnApp::CanPauseNow()
{
	if (mBoard == nullptr)  
		return false;

	if (mSeedChooserScreen && mSeedChooserScreen->mMouseVisible)  
		return false;

	if (mBoard->mBoardFadeOutCounter >= 0)  
		return false;

	if (mCrazyDaveState != CrazyDaveState::CRAZY_DAVE_OFF)  
		return false;

	if (mGameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN || mGameMode == GameMode::GAMEMODE_TREE_OF_WISDOM)  
		return false;

	return GetDialogCount() <= 0;  
}

void LawnApp::GotFocus()
{
}

void LawnApp::LostFocus()
{
	if (!mTodCheatKeys && CanPauseNow())
	{
		DoPauseDialog();
	}
}

void LawnApp::WriteToRegistry()
{
	if (mPlayerInfo)
	{
		RegistryWriteString("CurUser", SexyStringToStringFast(mPlayerInfo->mName));
		mPlayerInfo->SaveDetails();
	}

	SexyAppBase::WriteToRegistry();
}

void LawnApp::ReadFromRegistry()
{
	SexyApp::ReadFromRegistry();
}

bool LawnApp::WriteCurrentUserConfig()
{
	if (mPlayerInfo)
		mPlayerInfo->SaveDetails();

	return true;
}

void LawnApp::PreNewGame(GameMode theGameMode, bool theLookForSavedGame)
{
	//if (NeedRegister())
	//{
	//	ShowGameSelector();
	//	return;
	//}

	mGameMode = theGameMode;
	if (theLookForSavedGame && TryLoadGame())
		return;

	std::string aFileName = GetSavedGameName(mGameMode, mPlayerInfo->mId);
	EraseFile(aFileName);
	NewGame();
}

void LawnApp::StartQuickPlay()
{
	mPlayedQuickplay = true;
	mGameMode = GameMode::GAMEMODE_ADVENTURE;
	NewGame();
}

void LawnApp::MakeNewBoard()
{
	KillBoard();
	mBoard = new Board(this);
	mBoard->Resize(0, 0, mWidth, mHeight);
	mWidgetManager->AddWidget(mBoard);
	mWidgetManager->BringToBack(mBoard);
	mWidgetManager->SetFocus(mBoard);
}

void LawnApp::StartPlaying()
{
	KillSeedChooserScreen();
	mBoard->StartLevel();
	mGameScene = GameScenes::SCENE_PLAYING;
}

bool LawnApp::SaveFileExists()
{
	std::string aFileName = GetSavedGameName(GameMode::GAMEMODE_ADVENTURE, mPlayerInfo->mId);
	return this->FileExists(aFileName);
}

bool LawnApp::TryLoadGame()
{
	std::string aSaveName = GetSavedGameName(mGameMode, mPlayerInfo->mId);
	mMusic->StopAllMusic();

	if (this->FileExists(aSaveName))
	{
		MakeNewBoard();
		if (mBoard->LoadGame(aSaveName))
		{
			mFirstTimeGameSelector = false;
			DoContinueDialog();
			return true;
		}
		KillBoard();
	}

	return false;
}

void LawnApp::NewGame()
{
	mFirstTimeGameSelector = false;

	MakeNewBoard();
	mBoard->InitLevel();
	mBoardResult = BoardResult::BOARDRESULT_NONE;
	mGameScene = GameScenes::SCENE_LEVEL_INTRO;

	ShowSeedChooserScreen();
	mBoard->mCutScene->StartLevelIntro();
}

void LawnApp::ShowGameSelector()
{
	KillBoard();
	mPlayedQuickplay = false;
	//UpdateRegisterInfo();
	if (mGameSelector)
	{
		mWidgetManager->RemoveWidget(mGameSelector);
		SafeDeleteWidget(mGameSelector);
	}

	mGameScene = GameScenes::SCENE_MENU;
	mGameSelector = new GameSelector(this);
	mGameSelector->Resize(0, 0, mWidth, mHeight);
	mWidgetManager->AddWidget(mGameSelector);
	mWidgetManager->BringToBack(mGameSelector);
	mWidgetManager->SetFocus(mGameSelector);

	//if (NeedRegister())
	//{
	//	DoNeedRegisterDialog();
	//}
}

void LawnApp::KillGameSelector()
{
	if (mGameSelector)
	{
		mWidgetManager->RemoveWidget(mGameSelector);
		SafeDeleteWidget(mGameSelector);
		mGameSelector = nullptr;
	}
}

void LawnApp::ShowAwardScreen(AwardType theAwardType, bool theShowAchievements)
{
	mGameScene = GameScenes::SCENE_AWARD;
	mAwardScreen = new AwardScreen(this, theAwardType, theShowAchievements);
	mAwardScreen->Resize(0, 0, mWidth, mHeight);
	mWidgetManager->AddWidget(mAwardScreen);
	mWidgetManager->BringToBack(mAwardScreen);
	mWidgetManager->SetFocus(mAwardScreen);
}

void LawnApp::KillAwardScreen()
{
	if (mAwardScreen)
	{
		mWidgetManager->RemoveWidget(mAwardScreen);
		SafeDeleteWidget(mAwardScreen);
		mAwardScreen = nullptr;
	}
}

void LawnApp::ShowCreditScreen()
{
	mCreditScreen = new CreditScreen(this);
	mCreditScreen->Resize(0, 0, mWidth, mHeight);
	mWidgetManager->AddWidget(mCreditScreen);
	mWidgetManager->BringToBack(mCreditScreen);
	mWidgetManager->SetFocus(mCreditScreen);
}

void LawnApp::KillCreditScreen()
{
	if (mCreditScreen)
	{
		mWidgetManager->RemoveWidget(mCreditScreen);
		SafeDeleteWidget(mCreditScreen);
		mCreditScreen = nullptr;
	}
}

void LawnApp::ShowMiniCreditScreen()
{
	mGameScene = GameScenes::SCENE_CREDIT;
	mMiniCreditsScreen = new MiniCreditsScreen(this);
	mMiniCreditsScreen->Resize(0, 0, mWidth, mHeight);
	mWidgetManager->AddWidget(mMiniCreditsScreen);
	mWidgetManager->BringToBack(mMiniCreditsScreen);
	mWidgetManager->SetFocus(mMiniCreditsScreen);
}

void LawnApp::KillMiniCreditScreen()
{
	if (mMiniCreditsScreen)
	{
		mWidgetManager->RemoveWidget(mMiniCreditsScreen);
		SafeDeleteWidget(mMiniCreditsScreen);
		mMiniCreditsScreen = nullptr;
	}
}

void LawnApp::ShowAchievementScreen()
{
	if (mAchievementScreen)
		KillAchievementScreen();
	mGameScene = GameScenes::SCENE_MENU;
	mAchievementScreen = new AchievementScreen(this);
	mAchievementScreen->Resize(0, 0, mWidth, mHeight + 1);
	mWidgetManager->AddWidget(mAchievementScreen);
	mWidgetManager->BringToFront(mAchievementScreen);
	mWidgetManager->SetFocus(mAchievementScreen);
}

void LawnApp::KillAchievementScreen()
{
	if (mAchievementScreen)
	{
		mWidgetManager->RemoveWidget(mAchievementScreen);
		SafeDeleteWidget(mAchievementScreen);
		mAchievementScreen = nullptr;
	}
}

void LawnApp::ShowQuickPlayScreen()
{
	if (mQuickPlayScreen)
		KillQuickPlayScreen();
	mGameScene = GameScenes::SCENE_MENU;
	mQuickPlayScreen = new QuickPlayScreen(this);
	mQuickPlayScreen->Resize(0, 0, mWidth, mHeight);
	mWidgetManager->AddWidget(mQuickPlayScreen);
	mWidgetManager->BringToFront(mQuickPlayScreen);
	mWidgetManager->SetFocus(mQuickPlayScreen);
}

void LawnApp::KillQuickPlayScreen()
{
	if (mQuickPlayScreen)
	{
		mWidgetManager->RemoveWidget(mQuickPlayScreen);
		SafeDeleteWidget(mQuickPlayScreen);
		mQuickPlayScreen = nullptr;
	}
}

void LawnApp::ShowChallengeScreen(ChallengePage thePage)
{
	mGameScene = GameScenes::SCENE_CHALLENGE;
	mChallengeScreen = new ChallengeScreen(this, thePage);
	mChallengeScreen->Resize(0, 0, mWidth, mHeight);
	mWidgetManager->AddWidget(mChallengeScreen);
	mWidgetManager->BringToBack(mChallengeScreen);
	mWidgetManager->SetFocus(mChallengeScreen);
}

void LawnApp::KillChallengeScreen()
{
	if (mChallengeScreen)
	{
		mWidgetManager->RemoveWidget(mChallengeScreen);
		SafeDeleteWidget(mChallengeScreen);
		mChallengeScreen = nullptr;
	}
}

StoreScreen* LawnApp::ShowStoreScreen()
{
	//FinishModelessDialogs();
	TOD_ASSERT(!GetDialog((int)Dialogs::DIALOG_STORE));

	StoreScreen* aStoreScreen = new StoreScreen(this);
	AddDialog(aStoreScreen);
	mWidgetManager->SetFocus(aStoreScreen);

	return aStoreScreen;
}

void LawnApp::KillStoreScreen()
{
	if (GetDialog(Dialogs::DIALOG_STORE))
	{
		KillDialog(Dialogs::DIALOG_STORE);
		ClearUpdateBacklog(false);
	}
}

void LawnApp::ShowSeedChooserScreen()
{
	TOD_ASSERT(mSeedChooserScreen == nullptr);

	mSeedChooserScreen = new SeedChooserScreen();
	mSeedChooserScreen->Resize(0, 0, mWidth, mHeight);
	mWidgetManager->AddWidget(mSeedChooserScreen);
	mWidgetManager->BringToBack(mSeedChooserScreen);
}

void LawnApp::KillSeedChooserScreen()
{
	if (mSeedChooserScreen)
	{
		mWidgetManager->RemoveWidget(mSeedChooserScreen);
		SafeDeleteWidget(mSeedChooserScreen);
		mSeedChooserScreen = nullptr;
	}
}

void LawnApp::EndLevel()
{
	KillBoard();
	if (IsAdventureMode())
	{
		NewGame();
	}

	mFirstTimeGameSelector = true;

	MakeNewBoard();
	mBoard->InitLevel();
	mBoardResult = BoardResult::BOARDRESULT_NONE;
	mGameScene = GameScenes::SCENE_LEVEL_INTRO;
	ShowSeedChooserScreen();
	mBoard->mCutScene->StartLevelIntro();
}

void LawnApp::DoBackToMain(bool hasSound)
{
	mMusic->StopAllMusic();
	mSoundSystem->CancelPausedFoley();
	WriteCurrentUserConfig();
	KillNewOptionsDialog();
	KillBoard();
	mPlayedQuickplay = false;
	ShowGameSelector();
	if (hasSound)
		PlaySample(Sexy::SOUND_BUTTONCLICK);
}

void LawnApp::DoConfirmBackToMain()
{
	LawnDialog* aDialog = (LawnDialog*)DoDialog(
		Dialogs::DIALOG_CONFIRM_BACK_TO_MAIN, 
		true, 
		_S("Leave Game?"/*"[LEAVE_GAME]"*/),
		_S("Do you want to return\nto the main menu?\n\nYour game will be saved."/*"[LEAVE_GAME_HEADER]"*/), 
		"", 
		Dialog::BUTTONS_YES_NO
	);

	aDialog->mLawnYesButton->mLabel = TodStringTranslate("[LEAVE_BUTTON]");
	aDialog->mLawnNoButton->mLabel = TodStringTranslate("[DIALOG_BUTTON_CANCEL]");
	//aDialog->CalcSize(0, 0);
}

void LawnApp::DoNewOptions(bool theFromGameSelector, int x, int y)
{
	NewOptionsDialog* aDialog = new NewOptionsDialog(this, theFromGameSelector, false);
	CenterDialog(aDialog, IMAGE_OPTIONS_MENUBACK->mWidth, IMAGE_OPTIONS_MENUBACK->mHeight);
	if (x != -1 && y != -1)
		aDialog->Resize(x, y, aDialog->mWidth, aDialog->mHeight);
	AddDialog(Dialogs::DIALOG_NEWOPTIONS, aDialog);
	mWidgetManager->SetFocus(aDialog);
}

void LawnApp::DoAdvancedOptions(bool theFromGameSelector, int x, int y)
{
	NewOptionsDialog* aDialog = new NewOptionsDialog(this, theFromGameSelector, true);
	CenterDialog(aDialog, IMAGE_OPTIONS_MENUBACK->mWidth, IMAGE_OPTIONS_MENUBACK->mHeight);
	aDialog->Resize(x, y, aDialog->mWidth, aDialog->mHeight);
	AddDialog(Dialogs::DIALOG_NEWOPTIONS, aDialog);
	mWidgetManager->SetFocus(aDialog);
}

AlmanacDialog* LawnApp::DoAlmanacDialog(SeedType theSeedType, ZombieType theZombieType)
{
	PerfTimer mTimer;
	mTimer.Start();

	//FinishModelessDialogs();

	AlmanacDialog* aDialog = new AlmanacDialog(this);
	AddDialog(Dialogs::DIALOG_ALMANAC, aDialog);
	mWidgetManager->SetFocus(aDialog);

	if (theSeedType != SeedType::SEED_NONE)
	{
		aDialog->ShowPlant(theSeedType);
	}
	else if (theZombieType != ZombieType::ZOMBIE_INVALID)
	{
		aDialog->ShowZombie(theZombieType);
	}

	int aDuration = mTimer.GetDuration();
	TodTrace("almanac load time: %d ms", aDuration);

	return aDialog;
}

void LawnApp::DoContinueDialog()
{
	ContinueDialog* aDialog = new ContinueDialog(this);
	CenterDialog(aDialog, aDialog->mWidth, aDialog->mHeight);
	AddDialog(Dialogs::DIALOG_CONTINUE, aDialog);
}

void LawnApp::DoPauseDialog()
{
	mBoard->Pause(true);
	//FinishModelessDialogs();
	LawnDialog* aDialog = (LawnDialog*)DoDialog(
		Dialogs::DIALOG_PAUSED,
		true,
		_S("GAME PAUSED"/*"[GAME_PAUSED]"*/),
		_S("Click to resume game"), 
		_S("Resume Game"/*"[RESUME_GAME]"*/),
		Dialog::BUTTONS_FOOTER
	);

	aDialog->mReanimation->AddReanimation(72.0f, 42.0f, ReanimationType::REANIM_ZOMBIE_NEWSPAPER);
	aDialog->mSpaceAfterHeader = 155;
	aDialog->CalcSize(0, 10);
	CenterDialog(aDialog, aDialog->mWidth, aDialog->mHeight);
}

int LawnApp::LawnMessageBox(int theDialogId, const SexyChar* theHeaderName, const SexyChar* theLinesName, const SexyChar* theButton1Name, const SexyChar* theButton2Name, int theButtonMode)
{
	Widget* aOldFocus = mWidgetManager->mFocusWidget;

	LawnDialog* aDialog = (LawnDialog*)DoDialog(theDialogId, true, theHeaderName, theLinesName, theButton1Name, theButtonMode);
	if (aDialog->mYesButton)
	{
		aDialog->mYesButton->mLabel = TodStringTranslate(theButton1Name);
	}
	if (aDialog->mNoButton)
	{
		aDialog->mNoButton->mLabel = TodStringTranslate(theButton2Name);
	}
	//aDialog->CalcSize(0, 0);

	mWidgetManager->SetFocus(aDialog);
	int aResult = aDialog->WaitForResult(true);
	mWidgetManager->SetFocus(aOldFocus);

	return aResult;
}

Dialog* LawnApp::DoDialog(int theDialogId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode)
{
	SexyString aHeader = TodStringTranslate(theDialogHeader);
	SexyString aLines = TodStringTranslate(theDialogLines);
	SexyString aFooter = TodStringTranslate(theDialogFooter);
	SetCursorMode(CURSOR_MODE_NORMAL);
	Dialog* aDialog = SexyAppBase::DoDialog(theDialogId, isModal, aHeader, aLines, aFooter, theButtonMode);
	if (mWidgetManager->mFocusWidget == nullptr)
	{
		mWidgetManager->mFocusWidget = aDialog;
	}

	return aDialog;
}

Dialog* LawnApp::DoDialogDelay(int theDialogId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode)
{
	LawnDialog* aDialog = (LawnDialog*)SexyAppBase::DoDialog(theDialogId, isModal, theDialogHeader, theDialogLines, theDialogFooter, theButtonMode);
	aDialog->SetButtonDelay(30);
	return aDialog;
}

void LawnApp::DoUserDialog()
{
	KillDialog(Dialogs::DIALOG_USERDIALOG);

	UserDialog* aDialog = new UserDialog(this);
	CenterDialog(aDialog, aDialog->mWidth, aDialog->mHeight);
	AddDialog(Dialogs::DIALOG_USERDIALOG, aDialog);
	mWidgetManager->SetFocus(aDialog);
}

float LawnApp::GetSpeedVal()
{
	return mSpeedModifier;
}

void LawnApp::FinishUserDialog(bool isYes)
{
	UserDialog* aUserDialog = (UserDialog*)GetDialog(Dialogs::DIALOG_USERDIALOG);
	if (aUserDialog)
	{
		if (isYes)
		{
			PlayerInfo* aProfile = mProfileMgr->GetProfile(StringToSexyStringFast(aUserDialog->GetSelName()));
			if (aProfile)
			{
				mPlayerInfo = aProfile;
				mWidgetManager->MarkAllDirty();

				if (mGameSelector)
				{
					mGameSelector->SyncProfile(true);
				}
			}
		}

		KillDialog(Dialogs::DIALOG_USERDIALOG);
	}
}

void LawnApp::DoCreateUserDialog()
{
	KillDialog(Dialogs::DIALOG_CREATEUSER);

	NewUserDialog* aDialog = new NewUserDialog(this, false);
	CenterDialog(aDialog, aDialog->mWidth, aDialog->mHeight);
	AddDialog(Dialogs::DIALOG_CREATEUSER, aDialog);
}

void LawnApp::FinishCreateUserDialog(bool isYes)
{
	NewUserDialog* aNewUserDialog = (NewUserDialog*)GetDialog(Dialogs::DIALOG_CREATEUSER);
	if (aNewUserDialog == nullptr)
		return;

	SexyString aName = aNewUserDialog->GetName();

	if (isYes && aName.empty())
	{
		DoDialog(
			Dialogs::DIALOG_CREATEUSERERROR,
			true,
			_S("Enter Your Name"),
			_S("Please enter your name to create a new user profile for storing high score data and game progress"),
			_S("OK"),
			Dialog::BUTTONS_FOOTER
		);
	}
	else if (mPlayerInfo == nullptr && (!isYes || aName.empty()))
	{
		DoDialog(
			Dialogs::DIALOG_CREATEUSERERROR,
			true,
			_S("Enter Your Name"/*"[ENTER_YOUR_NAME]"*/),
			_S("Please enter your name to create a new user profile for storing high score data and game progress"/*"[ENTER_NEW_USER]"*/),
			_S("OK"/*"[DIALOG_BUTTON_OK]"*/),
			Dialog::BUTTONS_FOOTER
		);
	}
	else if (!isYes)
	{
		KillDialog(Dialogs::DIALOG_CREATEUSER);
	}
	else
	{
		PlayerInfo* aProfile = mProfileMgr->AddProfile(aName);
		if (aProfile == nullptr)
		{
			DoDialog(
				Dialogs::DIALOG_CREATEUSERERROR,
				true,
				_S("Name Conflict"/*"[NAME_CONFLICT]"*/),
				_S("The name you entered is already being used.  Please enter a unique player name"/*"[ENTER_UNIQUE_PLAYER_NAME]"*/),
				_S("OK"/*"[DIALOG_BUTTON_OK]"*/),
				Dialog::BUTTONS_FOOTER
			);
		}
		else
		{
			mProfileMgr->Save();
			mPlayerInfo = aProfile;

			KillDialog(Dialogs::DIALOG_USERDIALOG);
			KillDialog(Dialogs::DIALOG_CREATEUSER);
			mWidgetManager->MarkAllDirty();

			if (mGameSelector)
			{
				mGameSelector->SyncProfile(true);
			}
		}
	}
}

void LawnApp::DoConfirmDeleteUserDialog(const SexyString& theName)
{
	KillDialog(Dialogs::DIALOG_CONFIRMDELETEUSER);
	DoDialog(
		Dialogs::DIALOG_CONFIRMDELETEUSER, 
		true, 
		_S("Are You Sure"/*"[ARE_YOU_SURE]"*/), 
		// StrFormat(TodStringTranslate(_S("[DELETE_USER_WARNING]")).c_str(), StringToSexyStringFast(theName))
		StrFormat(_S("This will permanently remove '%s' from the player roster!"), theName.c_str()),
		_S(""), 
		Dialog::BUTTONS_YES_NO
	);
}

void LawnApp::FinishConfirmDeleteUserDialog(bool isYes)
{
	KillDialog(Dialogs::DIALOG_CONFIRMDELETEUSER);
	UserDialog* aUserDialog = (UserDialog*)GetDialog(Dialogs::DIALOG_USERDIALOG);
	if (aUserDialog == nullptr)
		return;

	mWidgetManager->SetFocus(aUserDialog);

	if (!isYes)
		return;

	SexyString aCurName = mPlayerInfo ? mPlayerInfo->mName : _S("");
	SexyString aName = aUserDialog->GetSelName();
	if (aName == aCurName)
	{
		mPlayerInfo = nullptr;
	}

	mProfileMgr->DeleteProfile(aName);
	aUserDialog->FinishDeleteUser();
	if (mPlayerInfo == nullptr)
	{
		mPlayerInfo = mProfileMgr->GetProfile(aUserDialog->GetSelName());
		if (mPlayerInfo == nullptr)
		{
			mPlayerInfo = mProfileMgr->GetAnyProfile();
		}
	}

	mProfileMgr->Save();
	if (mPlayerInfo == nullptr)
	{
		DoCreateUserDialog();
	}

	mWidgetManager->MarkAllDirty();
	if (mGameSelector != nullptr)
	{
		mGameSelector->SyncProfile(true);
	}
}

void LawnApp::DoRenameUserDialog(const SexyString& theName)
{
	KillDialog(Dialogs::DIALOG_RENAMEUSER);

	NewUserDialog* aDialog = new NewUserDialog(this, true);
	CenterDialog(aDialog, aDialog->mWidth, aDialog->mHeight);
	aDialog->SetName(theName);
	AddDialog(Dialogs::DIALOG_RENAMEUSER, aDialog);
}

void LawnApp::FinishRenameUserDialog(bool isYes)
{
	UserDialog* aUserDialog = (UserDialog*)GetDialog(Dialogs::DIALOG_USERDIALOG);
	if (!isYes)
	{
		KillDialog(Dialogs::DIALOG_RENAMEUSER);
		mWidgetManager->SetFocus(aUserDialog);
		return;
	}

	NewUserDialog* aNewUserDialog = (NewUserDialog*)GetDialog(Dialogs::DIALOG_RENAMEUSER);
	if (aUserDialog == nullptr || aNewUserDialog == nullptr)
		return;

	SexyString anOldName = aUserDialog->GetSelName();
	SexyString aNewName = aNewUserDialog->GetName();
	if (aNewName.empty())
		return;
	
	bool isCurrentUser = mProfileMgr->GetProfile(anOldName) == mPlayerInfo;
	if (!mProfileMgr->RenameProfile(anOldName, aNewName))
	{
		DoDialog(
			Dialogs::DIALOG_RENAMEUSERERROR,
			true,
			_S("Name Conflict"/*"[NAME_CONFLICT]"*/),
			_S("The name you entered is already being used.  Please enter a unique player name"/*"[ENTER_UNIQUE_PLAYER_NAME]"*/),
			_S("OK"/*"[DIALOG_BUTTON_OK]"*/),
			Dialog::BUTTONS_FOOTER
		);
		return;
	}

	mProfileMgr->Save();
	if (isCurrentUser)
	{
		mPlayerInfo = mProfileMgr->GetProfile(aNewName);
	}

	aUserDialog->FinishRenameUser(aNewName);
	mWidgetManager->MarkAllDirty();
	KillDialog(Dialogs::DIALOG_RENAMEUSER);
	mWidgetManager->SetFocus(aUserDialog);
}

void LawnApp::FinishNameError(int theId)
{
	KillDialog(theId);

	NewUserDialog* aNewUserDialog = (NewUserDialog*)GetDialog(theId == Dialogs::DIALOG_CREATEUSERERROR ? Dialogs::DIALOG_CREATEUSER : Dialogs::DIALOG_RENAMEUSER);
	if (aNewUserDialog)
	{
		mWidgetManager->SetFocus(aNewUserDialog->mNameEditWidget);
	}
}

void LawnApp::FinishRestartConfirmDialog()
{
	mSawYeti = mBoard->mKilledYeti;

	KillDialog(Dialogs::DIALOG_CONTINUE);
	KillDialog(Dialogs::DIALOG_RESTARTCONFIRM);
	KillBoard();

	PreNewGame(mGameMode, false);
}

void LawnApp::DoCheatDialog()
{
	KillDialog(Dialogs::DIALOG_CHEAT);

	CheatDialog* aDialog = new CheatDialog(this);
	CenterDialog(aDialog, aDialog->mWidth, aDialog->mHeight);
	AddDialog(Dialogs::DIALOG_CHEAT, aDialog);
}

void LawnApp::FinishCheatDialog(bool isYes)
{
	CheatDialog* aCheatDialog = (CheatDialog*)GetDialog(Dialogs::DIALOG_CHEAT);
	if (aCheatDialog == nullptr)
		return;

	if (isYes && !aCheatDialog->ApplyCheat())
		return;

	KillDialog(Dialogs::DIALOG_CHEAT);
	if (isYes)
	{
		mMusic->StopAllMusic();
		mBoardResult = BoardResult::BOARDRESULT_CHEAT;
		PreNewGame(mGameMode, false);
	}
}

void LawnApp::FinishTimesUpDialog()
{
	KillDialog(Dialogs::DIALOG_TIMESUP);
}

void LawnApp::DoChallengePagesDialog()
{
	if (mChallengeScreen == nullptr)
		return;

	KillDialog(Dialogs::DIALOG_CHALLENGE_PAGES);

	ChallengePagesDialog* aDialog = new ChallengePagesDialog(this);
	CenterDialog(aDialog, aDialog->mWidth, aDialog->mHeight);
	AddDialog(Dialogs::DIALOG_CHALLENGE_PAGES, aDialog);
	mWidgetManager->SetFocus(aDialog);
}

void LawnApp::DoConfirmSellDialog(const SexyString& theMessage)
{
	Dialog* aConfirmDialog = DoDialog(Dialogs::DIALOG_ZEN_SELL, true, _S("[ZEN_SELL_HEADER]"), theMessage, _S(""), Dialog::BUTTONS_YES_NO);
	aConfirmDialog->mYesButton->mLabel = TodStringTranslate(_S("[DIALOG_BUTTON_YES]"));
	aConfirmDialog->mNoButton->mLabel = TodStringTranslate(_S("[DIALOG_BUTTON_NO]"));
}

void LawnApp::DoConfirmPurchaseDialog(const SexyString& theMessage)
{
	LawnDialog* aComfirmDialog = (LawnDialog*)DoDialog(Dialogs::DIALOG_STORE_PURCHASE, true, _S("买下这个物品？"), theMessage, _S(""), Dialog::BUTTONS_YES_NO);
	aComfirmDialog->mLawnYesButton->mLabel = TodStringTranslate(_S("[DIALOG_BUTTON_YES]"));
	aComfirmDialog->mLawnNoButton->mLabel = TodStringTranslate(_S("[DIALOG_BUTTON_NO]"));
}

Dialog* LawnApp::NewDialog(int theDialogId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode)
{
	LawnDialog* aDialog = new LawnDialog(
		this, 
		theDialogId, 
		isModal, 
		SexyStringToStringFast(theDialogHeader), 
		SexyStringToStringFast(theDialogLines), 
		SexyStringToStringFast(theDialogFooter), 
		theButtonMode
	);

	CenterDialog(aDialog, aDialog->mWidth, aDialog->mHeight);
	return aDialog;
}

bool LawnApp::KillNewOptionsDialog()
{
	NewOptionsDialog* aNewOptionsDialog = (NewOptionsDialog*)GetDialog(Dialogs::DIALOG_NEWOPTIONS);
	if (aNewOptionsDialog == nullptr)
		return false;
	bool want3D = aNewOptionsDialog->mRealHardwareAccelerationCheckbox->IsChecked();
	if (aNewOptionsDialog->mAdvancedMode)
	{
		mDiscordPresence = aNewOptionsDialog->mDiscordBox->IsChecked();
		mBankKeybinds = aNewOptionsDialog->mBankKeybindsBox->IsChecked();
		mZeroNineBankFormat = aNewOptionsDialog->m09FormatBox->IsChecked();
		mSpeedModifier = stoi(aNewOptionsDialog->mSpeedEditWidget->mString.c_str());
		mAutoCollectSuns = aNewOptionsDialog->mAutoCollectSunsBox->IsChecked();
		mAutoCollectCoins = aNewOptionsDialog->mAutoCollectCoinsBox->IsChecked();
		mZombieHealthbars = aNewOptionsDialog->mZombieHealthbarsBox->IsChecked();
		mPlantHealthbars = aNewOptionsDialog->mPlantHealthbarsBox->IsChecked();
		ToggleDebugMode();
		bool wantWindowed = !aNewOptionsDialog->mFullscreenCheckbox->IsChecked();
		SwitchScreenMode(wantWindowed, want3D, false);
	}
	else
	{
		bool wantWindowed = !aNewOptionsDialog->mFullscreenCheckbox->IsChecked();
		bool wantFake3D = aNewOptionsDialog->mHardwareAccelerationCheckbox->IsChecked();
		mIs3dAccel = wantFake3D;
		SwitchScreenMode(wantWindowed, want3D, false);
	}

	KillDialog(Dialogs::DIALOG_NEWOPTIONS);
	ClearUpdateBacklog();
	return true;
}

bool LawnApp::KillAlmanacDialog()
{
	if (GetDialog(Dialogs::DIALOG_ALMANAC))
	{
		KillDialog(Dialogs::DIALOG_ALMANAC);
		ClearUpdateBacklog(false);
		return true;
	}

	return false;
}

bool LawnApp::NeedPauseGame()
{
	if (mDialogList.size() == 0)
		return false;

	if (mDialogList.size() == 1 && mDialogList.front()->mId != Dialogs::DIALOG_NEW_GAME)
	{
		int anId = mDialogList.front()->mId;
		if (anId == Dialogs::DIALOG_CHOOSER_WARNING || anId == Dialogs::DIALOG_PURCHASE_PACKET_SLOT || anId == Dialogs::DIALOG_IMITATER)
		{
			return false;
		}
	}

	return (mBoard == nullptr || mGameMode != GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN) && (mBoard == nullptr || mGameMode != GameMode::GAMEMODE_TREE_OF_WISDOM);
}

void LawnApp::ModalOpen()
{
	if (mBoard && NeedPauseGame())
	{
		mBoard->Pause(true);
	}
}

void LawnApp::ModalClose()
{
}

bool LawnApp::KillDialog(int theDialogId)
{
	if (SexyAppBase::KillDialog(theDialogId))
	{
		if (mDialogMap.size() == 0)
		{
			if (mSeedChooserScreen)
				mWidgetManager->SetFocus(mSeedChooserScreen);
			else if (mBoard)
				mWidgetManager->SetFocus(mBoard);
			else if (mGameSelector)
				mWidgetManager->SetFocus(mGameSelector);
			else if (mChallengeScreen)
				mWidgetManager->SetFocus(mChallengeScreen);
		}

		if (mBoard && !NeedPauseGame())
		{
			mBoard->Pause(false);
		}

		return true;
	}

	return false;
}

void LawnApp::ShowResourceError(bool doExit)
{
	SexyAppBase::ShowResourceError(doExit);
}

void BetaSubmitFunc()
{
	if (gLawnApp)
	{
		gLawnApp->BetaSubmit(false);
	}
}

void LawnApp::Init()
{
	DoParseCmdLine();
	if (!mTodCheatKeys)
	{
		mOnlyAllowOneCopyToRun = true;
	}

	//if (!gSexyCache->Connected() &&
	//	gLawnApp->mTodCheatKeys &&
	//	MessageBox(gLawnApp->mHWnd, _S("Start SexyCache now?"), _S("SexyCache"), MB_YESNO) == IDYES &&
	//	WinExec("SexyCache.exe", SW_MINIMIZE) >= 32)
	//{
	//	gSexyCache = SexyCache();
	//}
	//if (gSexyCache->Connected() && !gLawnApp->mTodCheatKeys)
	//{
	//	gSexyCache->Disconnect();
	//}

	mSessionID = _time32(nullptr);
	mPlayTimeActiveSession = 0;
	mPlayTimeInactiveSession = 0;
	mBoardResult = BoardResult::BOARDRESULT_NONE;
	mSawYeti = false;

	SexyApp::Init();
#ifdef _DEBUG
	TodAssertInitForApp();
	gBetaSubmitFunc = BetaSubmitFunc;
	bool is3dRecomended = SexyAppBase::Is3DAccelerationRecommended();
	bool is3dSupported = SexyAppBase::Is3DAccelerationSupported();
	TodLog("session id: %u", mSessionID);
	TodLog("3d recommended: %u", is3dRecomended);
	TodLog("3d supported: %u", is3dSupported);
#endif

	mStartTime = time(NULL);
	mDetails = "Starting the Game";
	UpdateDiscordState();

	if (!mResourceManager->ParseResourcesFile("properties\\resources.xml"))
	{
		ShowResourceError(true);
		return;
	}

	if (!TodLoadResources("Init"))
	{
		return;
	}

	PerfTimer mTimer;
	mTimer.Start();

	mProfileMgr->Load();

	std::string aCurUser;
	if (mPlayerInfo == nullptr && RegistryReadString("CurUser", &aCurUser))
	{
		mPlayerInfo = mProfileMgr->GetProfile(StringToSexyStringFast(aCurUser));
	}
	if (mPlayerInfo == nullptr)
	{
		mPlayerInfo = mProfileMgr->GetAnyProfile();
	}

	mMaxExecutions = GetInteger("MaxExecutions", 0);
	mMaxPlays = GetInteger("MaxPlays", 0);
	mMaxTime = GetInteger("MaxTime", 60);

	mTitleScreen = new TitleScreen(this);
	mTitleScreen->Resize(0, 0, mWidth, mHeight);
	mWidgetManager->AddWidget(mTitleScreen);
	mWidgetManager->SetFocus(mTitleScreen);
	mAchievements = new Achievements(this);
	mAchievements->InitAchievement();
	if (HAS_CUSTOM_CURSOR)
	{
		mCursor = new CursorWidget();
		mWidgetManager->AddWidget(mCursor);
		mWidgetManager->BringToFront(mCursor);
	}
#ifdef _DEBUG
	int aDuration = mTimer.GetDuration();
	TodTrace("loading: 'profiles' %d ms", aDuration);
#endif
	mTimer.Start();

	mMusic = new Music();
	mSoundSystem = new TodFoley();
	mEffectSystem = new EffectSystem();
	mEffectSystem->EffectSystemInitialize();

	mKonamiCheck = new TypingCheck();
	mKonamiCheck->AddKeyCode(KeyCode::KEYCODE_UP);
	mKonamiCheck->AddKeyCode(KeyCode::KEYCODE_UP);
	mKonamiCheck->AddKeyCode(KeyCode::KEYCODE_DOWN);
	mKonamiCheck->AddKeyCode(KeyCode::KEYCODE_DOWN);
	mKonamiCheck->AddKeyCode(KeyCode::KEYCODE_LEFT);
	mKonamiCheck->AddKeyCode(KeyCode::KEYCODE_RIGHT);
	mKonamiCheck->AddKeyCode(KeyCode::KEYCODE_LEFT);
	mKonamiCheck->AddKeyCode(KeyCode::KEYCODE_RIGHT);
	mKonamiCheck->AddChar('b');
	mKonamiCheck->AddChar('a');
	mMustacheCheck = new TypingCheck("mustache");
	mMoustacheCheck = new TypingCheck("moustache");
	mSuperMowerCheck = new TypingCheck("trickedout");
	mSuperMowerCheck2 = new TypingCheck("tricked out");
	mFutureCheck = new TypingCheck("future");
	mPinataCheck = new TypingCheck("pinata");
	mDanceCheck = new TypingCheck("dance");
	mDaisyCheck = new TypingCheck("daisies");
	mSukhbirCheck = new TypingCheck("sukhbir");

#ifdef _DEBUG
	aDuration = mTimer.GetDuration();
	TodTrace("loading: 'system' %d ms", aDuration);
#endif
	mTimer.Start();

	ReanimatorLoadDefinitions(gLawnReanimationArray, ReanimationType::NUM_REANIMS);
	ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_LOADBAR_SPROUT, true);
	ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_LOADBAR_ZOMBIEHEAD, true);

#ifdef _DEBUG
	aDuration = mTimer.GetDuration();
	TodTrace("loading: 'loaderbar' %d ms", aDuration);
#endif
	mTimer.Start();

	if ((!Is3DAccelerationSupported() || !Is3DAccelerationRecommended()) && mIs3dAccel)
		mIs3dAccel = false;
}

bool LawnApp::ChangeDirHook(const char* theIntendedPath)
{
	return false;
}

void LawnApp::Start()
{
	if (mLoadingFailed)
		return;

	SexyAppBase::Start();
}

void LawnApp::StartDiscord()
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	handlers.ready = [](const DiscordUser* connectedUser) {
		TodTraceAndLog("Discord: connected to user");
	};
	handlers.disconnected = [](int errcode, const char* message) {
		std::string s = std::to_string(errcode);
		char const* errchar = s.c_str();  //use char const* as target type

		TodTraceAndLog("Discord: disconnected from user");
		TodTraceAndLog(errchar);
	};
	handlers.errored = [](int errcode, const char* message) {
		std::string s = std::to_string(errcode);
		char const* errchar = s.c_str();  //use char const* as target type

		TodTraceAndLog("Discord: error");
		TodTraceAndLog(errchar);
	};

	Discord_Initialize(CLIENT_ID, &handlers, 1, NULL);
}

bool LawnApp::DebugKeyDown(int theKey)
{
	return SexyAppBase::DebugKeyDown(theKey);
}

void LawnApp::HandleCmdLineParam(const std::string& theParamName, const std::string& theParamValue)
{
	if (theParamName == "-tod")
	{
#ifdef _DEBUG
		mTodCheatKeys = true;
		mDebugKeysEnabled = true;
#endif
	}
	else
	{
		SexyApp::HandleCmdLineParam(theParamName, theParamValue);
	}
}

bool LawnApp::UpdatePlayerProfileForFinishingLevel()
{
	bool aUnlockedNewChallenge = false;

	if (IsAdventureMode())
	{
		if (mBoard->mLevel == FINAL_LEVEL)
		{
			mPlayerInfo->mLevel = 1;  
			mPlayerInfo->mFinishedAdventure++;  
			if (mPlayerInfo->mFinishedAdventure == 1)
			{
				mPlayerInfo->mNeedsMessageOnGameSelector = 1;
			}
		}
		else
		{
			mPlayerInfo->mLevel = mBoard->mLevel + 1;  
		}

		if (!HasFinishedAdventure() && mBoard->mLevel == 34)
		{
			mPlayerInfo->mNeedsMagicTacoReward = 1;
		}

		bool isChallengeLevel = IsWallnutBowlingLevel() || IsWhackAZombieLevel() || IsLittleTroubleLevel() || IsBungeeBlitzLevel() || IsStormyNightLevel() || mBoard->HasConveyorBeltSeedBank();
		if (mBoard->mBackground == BACKGROUND_3_POOL && !mBoard->mPeashootersUsed && !isChallengeLevel) {
			GetAchievement(ACHIEVEMENT_DONT_PEA_IN_POOL);
		}
		if (mBoard->StageHasRoof() && !mBoard->mCatapultsUsed && !isChallengeLevel) {
			GetAchievement(ACHIEVEMENT_GROUNDED);
		}
		if (mBoard->StageIsNight() && !mBoard->mMushroomsUsed && !isChallengeLevel) {
			GetAchievement(ACHIEVEMENT_NO_FUNGUS_AMONG_US);
		}
		if (mBoard->mBackground == BACKGROUND_1_DAY && mBoard->mMushroomsNCoffeeUsed && !mBoard->mUsedNonMushrooms && !isChallengeLevel) {
			GetAchievement(ACHIEVEMENT_GOOD_MORNING);
		}
	}
	else if (IsSurvivalMode())
	{
		if (mBoard->IsFinalSurvivalStage())
		{
			aUnlockedNewChallenge = !HasBeatenChallenge(mGameMode);
			mBoard->SurvivalSaveScore();

			if (aUnlockedNewChallenge && HasFinishedAdventure())
			{
				int aNumTrophies = GetNumTrophies(ChallengePage::CHALLENGE_PAGE_SURVIVAL);
				if (aNumTrophies != 8 && aNumTrophies != 9)
				{
					mPlayerInfo->mHasNewSurvival = true;
				}
			}
		}
	}
	else if (IsPuzzleMode())
	{
		aUnlockedNewChallenge = !HasBeatenChallenge(mGameMode);
		mPlayerInfo->mChallengeRecords[GetCurrentChallengeIndex()]++;

		if (!HasFinishedAdventure() && (mGameMode == GameMode::GAMEMODE_SCARY_POTTER_3 || mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_3))
		{
			aUnlockedNewChallenge = false;
		}

		if (aUnlockedNewChallenge)
		{
			if (IsScaryPotterLevel())
			{
				mPlayerInfo->mHasNewScaryPotter = 1;
			}
			else
			{
				mPlayerInfo->mHasNewIZombie = 1;
			}
		}
	}
	else
	{
		aUnlockedNewChallenge = !HasBeatenChallenge(mGameMode);
		mPlayerInfo->mChallengeRecords[GetCurrentChallengeIndex()]++;

		if (aUnlockedNewChallenge && HasFinishedAdventure())
		{
			int aNumTrophies = GetNumTrophies(ChallengePage::CHALLENGE_PAGE_CHALLENGE);
			if (aNumTrophies <= 17)
			{
				mPlayerInfo->mHasNewMiniGame = 1;
			}
			else if (aNumTrophies >= GetTotalTrophies(ChallengePage::CHALLENGE_PAGE_CHALLENGE))
			{
				GetAchievement(ACHIEVEMENT_BEYOND_THE_GRAVE);
			}
		}
	}

	WriteCurrentUserConfig();

	return aUnlockedNewChallenge;
}

void LawnApp::CheckForGameEnd()
{
	if (mBoard == nullptr || !mBoard->mLevelComplete)
		return;
	isFastMode = false;

	if (mPlayedQuickplay)
	{
		KillBoard();
		ShowGameSelector();
		int result = Dialog::ID_NO;
		if (mQuickLevel != FINAL_LEVEL)
		{
			LawnDialog* dialog = (LawnDialog*)DoDialog(DIALOG_MESSAGE, true, "Continue?", "Would you like to go to the next level in Quick Play?", "", Dialog::BUTTONS_YES_NO);
			result = dialog->WaitForResult(true);
		}

		if (result == Dialog::ID_YES)
		{
			mQuickLevel++;
			KillGameSelector();
			StartQuickPlay();
		}
		return;
	}

	bool aUnlockedNewChallenge = UpdatePlayerProfileForFinishingLevel();

	bool forceAchievements = false;
	for (int aAchivement = 0; aAchivement < NUM_ACHIEVEMENTS; aAchivement++)
	{
		if (mPlayerInfo->mEarnedAchievements[aAchivement] && !mPlayerInfo->mShownedAchievements[aAchivement] && mAchievements->ReturnShowInAwards(aAchivement))
			forceAchievements = true;
	}

	if (IsAdventureMode())
	{

		int aLevel = mBoard->mLevel;
		KillBoard();

		if (IsFirstTimeAdventureMode() && aLevel < 50)
		{
			ShowAwardScreen(AwardType::AWARD_FORLEVEL, true);
		}
		else if (aLevel == FINAL_LEVEL)
		{
			GetAchievement(ACHIEVEMENT_HOME_SECURITY);
			if (mPlayerInfo->mFinishedAdventure == 1)
			{
				ShowAwardScreen(AwardType::AWARD_FORLEVEL, true);
			}
			else
			{
				ShowAwardScreen(AwardType::AWARD_CREDITS_ZOMBIENOTE, true);
			}
		}
		else if (aLevel == 9 || aLevel == 19 || aLevel == 29 || aLevel == 39 || aLevel == 49)
		{
			ShowAwardScreen(AwardType::AWARD_FORLEVEL, true);
		}
		else
		{
			PreNewGame(mGameMode, false);
		}
	}
	else if (IsSurvivalMode())
	{
		if (mBoard->IsFinalSurvivalStage())
		{
			KillBoard();

			if (aUnlockedNewChallenge && HasFinishedAdventure())
			{
				ShowAwardScreen(AwardType::AWARD_FORLEVEL, true);
			}
			else
			{
				if (!forceAchievements)
					ShowChallengeScreen(ChallengePage::CHALLENGE_PAGE_SURVIVAL);
				else
					ShowAwardScreen(AwardType::AWARD_ACHIEVEMENTONLY, true);
			}
		}
		else
		{
			mBoard->mChallenge->mSurvivalStage++;
			KillGameSelector();
			mBoard->InitSurvivalStage();
		}
	}
	else if (IsPuzzleMode())
	{
		KillBoard();

		if (aUnlockedNewChallenge)
		{
			ShowAwardScreen(AwardType::AWARD_FORLEVEL, true);
		}
		else
		{
			if (!forceAchievements)
				ShowChallengeScreen(ChallengePage::CHALLENGE_PAGE_PUZZLE);
			else
				ShowAwardScreen(AwardType::AWARD_ACHIEVEMENTONLY, true);
		}
	}
	else
	{
		KillBoard();

		if (aUnlockedNewChallenge && HasFinishedAdventure())
		{
			ShowAwardScreen(AwardType::AWARD_FORLEVEL, true);
		}
		else
		{
			if (!forceAchievements)
				ShowChallengeScreen(ChallengePage::CHALLENGE_PAGE_CHALLENGE);
			else
				ShowAwardScreen(AwardType::AWARD_ACHIEVEMENTONLY, true);
		}
	}
}

void LawnApp::UpdatePlayTimeStats()
{
	static int aLastTime = -1;

	int aTickCount = GetTickCount();
	int aSession = (aTickCount - aLastTime) / 1000;

	if (mPlayerInfo && !mPlayerInfo->mHasUsedCheatKeys && !mDebugKeysEnabled && mTodCheatKeys)
	{
		mPlayerInfo->mHasUsedCheatKeys = 1;
	}

	if (aLastTime == -1)
	{
		aLastTime = aTickCount;
		return;
	}

	if (aSession > 0)
	{
		aLastTime = aTickCount;

		if ((mBoard == nullptr || !mBoard->mPaused) && mHasFocus && mLastTimerTime - mLastUserInputTick <= 10000)
		{
			mPlayTimeActiveSession += aSession;

			if (mBoard)
			{
				mBoard->mPlayTimeActiveLevel += aSession;
			}

			if (mPlayerInfo)
			{
				mPlayerInfo->mPlayTimeActivePlayer += aSession;
			}
		}
		else
		{
			mPlayTimeInactiveSession += aSession;

			if (mBoard)
			{
				mBoard->mPlayTimeInactiveLevel += aSession;
			}

			if (mPlayerInfo)
			{
				mPlayerInfo->mPlayTimeInactivePlayer += aSession;
			}
		}
	}
}

void LawnApp::UpdateFrames()
{
	if ((!mActive || mMinimized) && mBoard)
	{
		mBoard->ResetFPSStats();
	}

#ifdef _DEBUG
	UpdatePlayTimeStats();
#endif

	int aUpdateCount = 1;
	if (gSlowMo)
	{
		++gSlowMoCounter;
		if (gSlowMoCounter < 4)
		{
			aUpdateCount = 0;
		}
		else
		{
			gSlowMoCounter = 0;
		}
	}
	else if (gFastMo)
	{
		aUpdateCount = 20;
	}
	else if (isFastMode)
	{
		aUpdateCount = mSpeedModifier;
	}

	for (int i = 0; i < aUpdateCount; i++)
	{
		mAppCounter++;
		
		if (mBoard)
		{
			mBoard->ProcessDeleteQueue();
		}

		SexyApp::UpdateFrames();

		mMusic->MusicUpdate();
		if (mLoadingThreadCompleted && mEffectSystem)
		{
			mEffectSystem->ProcessDeleteQueue();
		}

		CheckForGameEnd();

		if (mCursor && HAS_CUSTOM_CURSOR)
		{
			mCursor->SetImage(IMAGE_MOUSE_CURSOR);
			mWidgetManager->BringToFront(mCursor);
		}
	}

	static time_t lastUpdateTime = time(NULL);
	time_t now = time(NULL);
	if (difftime(now, lastUpdateTime) >= 1) {

		if (!mDiscordPresence)
		{
			Discord_ClearPresence();
		}
		else
		{
			DiscordRichPresence discordPresence;
			memset(&discordPresence, 0, sizeof(discordPresence));
			discordPresence.state = mState.c_str();
			discordPresence.details = mDetails.c_str();
			discordPresence.largeImageKey = "logo";
			discordPresence.largeImageText = mVersion.c_str();
			discordPresence.startTimestamp = mStartTime;
			Discord_UpdatePresence(&discordPresence);
		}
		lastUpdateTime = now;
		Discord_RunCallbacks();
	}
}

void LawnApp::ToggleSlowMo()
{
	gSlowMoCounter = 0;
	gSlowMo = !gSlowMo;
	gFastMo = false;
}

void LawnApp::ToggleFastMo()
{
	gSlowMo = false;
	gFastMo = !gFastMo;
}

void LawnApp::LoadGroup(const char* theGroupName, int theGroupAveMsToLoad)
{
	PerfTimer aTimer;
	aTimer.Start();

	mResourceManager->StartLoadResources(theGroupName);
	while (!mShutdown && !mCloseRequest && !mLoadingFailed && TodLoadNextResource())
	{
		mCompletedLoadingThreadTasks += theGroupAveMsToLoad;
	}

	if (mShutdown || mCloseRequest)
		return;

	if (mResourceManager->HadError() || !ExtractResourcesByName(mResourceManager, theGroupName))
	{
		ShowResourceError();
		mLoadingFailed = true;
	}

	int aTotalGroupWeight = mResourceManager->GetNumResources(theGroupName) * theGroupAveMsToLoad;
	int aGroupTime = max(aTimer.GetDuration(), 0);
	TraceLoadGroup(theGroupName, aGroupTime, aTotalGroupWeight, theGroupAveMsToLoad);
}

void LawnApp::LoadingThreadProc()
{
	if (!TodLoadResources("LoaderBar"))
		return;

	TodStringListLoad("Properties\\LawnStrings.txt");

	if (mTitleScreen)
	{
		mTitleScreen->mLoaderScreenIsLoaded = true;
	}

	const char* groups[] = { "LoadingFonts", "LoadingImages", "LoadingSounds" };
	int group_ave_ms_to_load[] = { 54, 9, 54 };
	for (int i = 0; i < 3; i++)
	{
		mNumLoadingThreadTasks += mResourceManager->GetNumResources(groups[i]) * group_ave_ms_to_load[i];
	}
	mNumLoadingThreadTasks += 636;
	mNumLoadingThreadTasks += GetNumPreloadingTasks();
	mNumLoadingThreadTasks += mMusic->GetNumLoadingTasks();

	PerfTimer aTimer;
	aTimer.Start();

	TodHesitationTrace("start loading");
	TodHesitationBracket aHesitationResources("Resources");
	TodHesitationTrace("loading thread start");

	LoadGroup("LoadingImages", 9);
	LoadGroup("LoadingFonts", 54);
	if (mLoadingFailed || mShutdown || mCloseRequest)
		return;

	aHesitationResources.EndBracket();
	TodTrace("loading '%s' %d ms", "resources", (int)aTimer.GetDuration());

	mMusic->MusicInit();
	int aDuration = max(aTimer.GetDuration(), 0);
	aTimer.Start();

	mPoolEffect = new PoolEffect();
	mPoolEffect->PoolEffectInitialize();
	mZenGarden = new ZenGarden();
	mReanimatorCache = new ReanimatorCache();
	mReanimatorCache->ReanimatorCacheInitialize();
	TodFoleyInitialize(gLawnFoleyParamArray, LENGTH(gLawnFoleyParamArray));

	TodTrace("loading '%s' %d ms", "stuff", (int)aTimer.GetDuration());
	aTimer.Start();

	TrailLoadDefinitions(gLawnTrailArray, LENGTH(gLawnTrailArray));
	TodTrace("loading '%s' %d ms", "trail", (int)aTimer.GetDuration());
	aTimer.Start();
	TodHesitationTrace("trail");
	
	TodParticleLoadDefinitions(gLawnParticleArray, LENGTH(gLawnParticleArray));
	aDuration = max(aTimer.GetDuration(), 0);
	aTimer.Start();

	PreloadForUser();
	if (mLoadingFailed || mShutdown || mCloseRequest)
		return;

	aDuration = max(aTimer.GetDuration(), 0);
	aTimer.Start();

	GetNumPreloadingTasks();
	LoadGroup("LoadingSounds", 54);
	TodHesitationTrace("finished loading");
}

void LawnApp::FastLoad(GameMode theGameMode)
{
	if (!mShutdown)
	{
		mWidgetManager->RemoveWidget(mTitleScreen);
		SafeDeleteWidget(mTitleScreen);
		mTitleScreen = nullptr;

		PreNewGame(theGameMode, false);
	}
}

void LawnApp::LoadingThreadCompleted()
{
}

void LawnApp::LoadingCompleted()
{
	mWidgetManager->RemoveWidget(mTitleScreen);
	SafeDeleteWidget(mTitleScreen);
	mTitleScreen = nullptr;

	mResourceManager->DeleteImage("IMAGE_TITLESCREEN");

	ShowGameSelector();
}

void LawnApp::URLOpenFailed(const std::string& theURL)
{
	SexyAppBase::URLOpenFailed(theURL);
	KillDialog(Dialogs::DIALOG_OPENURL_WAIT);
	CopyToClipboard(theURL);

	std::string aString = 
		"Please open the following URL in your browser\n\n" + 
		theURL + 
		"\n\nFor your convenience, this URL has already been copied to your clipboard.";

	DoDialog(Dialogs::DIALOG_OPENURL_WAIT, true, _S("Open Browser"), _S("OK"), StringToSexyStringFast(aString), Dialog::BUTTONS_FOOTER);
}

void LawnApp::URLOpenSucceeded(const std::string& theURL)
{
	SexyAppBase::URLOpenSucceeded(theURL);
	KillDialog(Dialogs::DIALOG_OPENURL_WAIT);
}

bool LawnApp::OpenURL(const std::string& theURL, bool shutdownOnOpen)
{
	DoDialog(
		Dialogs::DIALOG_OPENURL_WAIT, 
		true, 
		_S("Opening Browser"), 
		_S("Opening Browser"), 
		_S(""), 
		Dialog::BUTTONS_NONE
	);

	DrawDirtyStuff();

	return SexyAppBase::OpenURL(theURL, shutdownOnOpen);
}

void LawnApp::ConfirmQuit()
{
	SexyString aBody = TodStringTranslate(_S("[QUIT_MESSAGE]"));
	SexyString aHeader = TodStringTranslate(_S("[QUIT_HEADER]"));
	LawnDialog* aDialog = (LawnDialog*)DoDialog(Dialogs::DIALOG_QUIT, true, aHeader, aBody, _S(""), Dialog::BUTTONS_OK_CANCEL);
	aDialog->mLawnYesButton->mLabel = TodStringTranslate(_S("[QUIT_BUTTON]"));
	CenterDialog(aDialog, aDialog->mWidth, aDialog->mHeight);
}

void LawnApp::PreDisplayHook()
{
	SexyApp::PreDisplayHook();
}

void LawnApp::ButtonPress(int theId)
{
}

void LawnApp::ButtonDepress(int theId)
{
	if (theId % 10000 >= 2000 && theId % 10000 < 3000)  
	{
		switch (theId - 2000)
		{
		case Dialogs::DIALOG_NEW_GAME:
			KillDialog(Dialogs::DIALOG_NEW_GAME);
			ShowGameSelector();
			return;

		case Dialogs::DIALOG_NEWOPTIONS:
			KillNewOptionsDialog();
			return;

		case Dialogs::DIALOG_PREGAME_NAG:
			DoRegister();
			return;

		case Dialogs::DIALOG_LOAD_GAME:
			return;

		case Dialogs::DIALOG_CONFIRM_UPDATE_CHECK:
			KillDialog(Dialogs::DIALOG_CONFIRM_UPDATE_CHECK);
			CheckForUpdates();
			return;

		case Dialogs::DIALOG_QUIT:
			KillDialog(Dialogs::DIALOG_QUIT);
			SendMessage(mHWnd, WM_CLOSE, NULL, NULL);
			return;

		case Dialogs::DIALOG_NAG:
			KillDialog(Dialogs::DIALOG_NAG);
			DoRegister();
			return;

		case Dialogs::DIALOG_INFO:
			KillDialog(Dialogs::DIALOG_INFO);
			return;

		case Dialogs::DIALOG_PAUSED:
			KillDialog(Dialogs::DIALOG_PAUSED);
			return;

		case Dialogs::DIALOG_NO_MORE_MONEY:
			KillDialog(Dialogs::DIALOG_NO_MORE_MONEY);
			mBoard->AddSunMoney(100);
			return;

		case Dialogs::DIALOG_BONUS:
			KillDialog(Dialogs::DIALOG_BONUS);
			return;

		case Dialogs::DIALOG_CONFIRM_BACK_TO_MAIN:
			KillDialog(Dialogs::DIALOG_CONFIRM_BACK_TO_MAIN);
			mBoardResult = BoardResult::BOARDRESULT_QUIT;
			mBoard->TryToSaveGame();
			DoBackToMain(true);
			return;

		case Dialogs::DIALOG_USERDIALOG:
			FinishUserDialog(true);
			return;

		case Dialogs::DIALOG_CREATEUSER:
			FinishCreateUserDialog(true);
			return;

		case Dialogs::DIALOG_CONFIRMDELETEUSER:
			FinishConfirmDeleteUserDialog(true);
			return;

		case Dialogs::DIALOG_RENAMEUSER:
			FinishRenameUserDialog(true);
			return;

		case Dialogs::DIALOG_CREATEUSERERROR:
		case Dialogs::DIALOG_RENAMEUSERERROR:
			FinishNameError(theId - 2000);
			return;

		case Dialogs::DIALOG_CHEAT:
			FinishCheatDialog(true);
			return;

		case Dialogs::DIALOG_RESTARTCONFIRM:
			FinishRestartConfirmDialog();
			return;

		case Dialogs::DIALOG_TIMESUP:
			FinishTimesUpDialog();
			return;

		case 20008:
			KillDialog(20008);
			KillDialog(Dialogs::DIALOG_CHECKING_UPDATES);
			return;

		default:
			KillDialog(theId - 2000);
			return;
		}
	}

	if (theId % 10000 >= 3000 && theId < 4000)  
	{
		switch (theId - 3000)
		{
		case Dialogs::DIALOG_PREGAME_NAG:
			KillDialog(Dialogs::DIALOG_PREGAME_NAG);
			Shutdown();
			return;

		case Dialogs::DIALOG_LOAD_GAME:
			KillDialog(Dialogs::DIALOG_LOAD_GAME);
			return;

		case Dialogs::DIALOG_USERDIALOG:
			FinishUserDialog(false);
			return;

		case Dialogs::DIALOG_CREATEUSER:
			FinishCreateUserDialog(false);
			return;

		case Dialogs::DIALOG_CONFIRMDELETEUSER:
			FinishConfirmDeleteUserDialog(false);
			return;

		case Dialogs::DIALOG_RENAMEUSER:
			FinishRenameUserDialog(false);
			return;

		case Dialogs::DIALOG_CHEAT:
			FinishCheatDialog(false);
			return;

		case Dialogs::DIALOG_TIMESUP:
			FinishTimesUpDialog();
			return;

		case 10008:
			KillDialog(10008);
			KillDialog(Dialogs::DIALOG_CHECKING_UPDATES);
			return;

		default:
			KillDialog(theId - 3000);
			return;
		}
	}
}

void LawnApp::CenterDialog(Dialog* theDialog, int theWidth, int theHeight)
{
	theDialog->Resize((BOARD_WIDTH - theWidth) / 2, (BOARD_HEIGHT - theHeight) / 2, theWidth, theHeight);
}

void LawnApp::PlayFoley(FoleyType theFoleyType)
{
	if (!mMuteSoundsForCutscene)
	{
		mSoundSystem->PlayFoley(theFoleyType);
	}
}

void LawnApp::PlayFoleyPitch(FoleyType theFoleyType, float thePitch)
{
	if (!mMuteSoundsForCutscene)
	{
		mSoundSystem->PlayFoleyPitch(theFoleyType, thePitch);
	}
}

SexyString LawnApp::GetStageString(int theLevel)
{
	int aArea = ClampInt((theLevel - 1) / LEVELS_PER_AREA + 1, 1, ADVENTURE_AREAS + 1);
	int aSub = theLevel - (aArea - 1) * LEVELS_PER_AREA;
	return StrFormat(" %d-%d", aArea, aSub);
} 

bool LawnApp::IsAdventureMode()
{
	return mGameMode == GameMode::GAMEMODE_ADVENTURE;
}

bool LawnApp::IsSurvivalMode()
{
	return mGameMode >= GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_1 && mGameMode <= GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_5;
}

bool LawnApp::IsPuzzleMode()
{
	return
		(mGameMode >= GameMode::GAMEMODE_SCARY_POTTER_1 && mGameMode <= GameMode::GAMEMODE_SCARY_POTTER_ENDLESS) ||
		(mGameMode >= GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_1 && mGameMode <= GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS);
}

bool LawnApp::IsChallengeMode()
{
	return !IsAdventureMode() && !IsPuzzleMode() && !IsSurvivalMode();
}

bool LawnApp::IsSurvivalNormal(GameMode theGameMode)
{
	int aLevel = theGameMode - GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_1;
	return aLevel >= 0 && aLevel <= 4;
}

bool LawnApp::IsSurvivalHard(GameMode theGameMode)
{
	int aLevel = theGameMode - GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_1;
	return aLevel >= 0 && aLevel <= 4;
}

bool LawnApp::IsSurvivalEndless(GameMode theGameMode)
{
	int aLevel = theGameMode - GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_1;
	return aLevel >= 0 && aLevel <= 4;
}

bool LawnApp::IsEndlessScaryPotter(GameMode theGameMode)
{
	return theGameMode == GameMode::GAMEMODE_SCARY_POTTER_ENDLESS;
}

bool LawnApp::IsEndlessIZombie(GameMode theGameMode)
{
	return theGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS;
}

bool LawnApp::IsContinuousChallenge()
{
	return 
		IsArtChallenge() || 
		IsSlotMachineLevel() || 
		IsFinalBossLevel() || 
		mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED || 
		mGameMode == GameMode::GAMEMODE_UPSELL || 
		mGameMode == GameMode::GAMEMODE_INTRO || 
		mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST;
}

bool LawnApp::IsArtChallenge()
{
	if (mBoard == nullptr)
		return false;

	return 
		mGameMode == GameMode::GAMEMODE_CHALLENGE_ART_CHALLENGE_WALLNUT || 
		mGameMode == GameMode::GAMEMODE_CHALLENGE_ART_CHALLENGE_SUNFLOWER || 
		mGameMode == GameMode::GAMEMODE_CHALLENGE_SEEING_STARS;
}

bool LawnApp::IsSquirrelLevel()
{
	return mBoard && mGameMode == GameMode::GAMEMODE_CHALLENGE_SQUIRREL;
}

bool LawnApp::IsIZombieLevel()
{
	if (mBoard == nullptr)
		return false;

	return
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_1 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_2 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_3 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_4 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_5 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_6 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_7 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_8 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_9 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS;
}

bool LawnApp::IsShovelLevel()
{
	return mBoard && mGameMode == GameMode::GAMEMODE_CHALLENGE_SHOVEL;
}

bool LawnApp::IsWallnutBowlingLevel()
{
	if (mBoard == nullptr)
		return false;

	if (mGameMode == GameMode::GAMEMODE_CHALLENGE_WALLNUT_BOWLING || mGameMode == GameMode::GAMEMODE_CHALLENGE_WALLNUT_BOWLING_2)
		return true;

	if (mPlayedQuickplay)
		return mQuickLevel == 5;

	return IsAdventureMode() && mPlayerInfo->mLevel == 5;
}

bool LawnApp::IsSlotMachineLevel()
{
	return (mBoard && mGameMode == GameMode::GAMEMODE_CHALLENGE_SLOT_MACHINE);
}

bool LawnApp::IsWhackAZombieLevel()
{
	if (mBoard == nullptr)
		return false;

	if (mGameMode == GameMode::GAMEMODE_CHALLENGE_WHACK_A_ZOMBIE)
		return true;

	if (mPlayedQuickplay)
		return mQuickLevel == 15;

	return IsAdventureMode() && mPlayerInfo->mLevel == 15;
}

bool LawnApp::IsLittleTroubleLevel()
{
	if (mBoard == nullptr)
		return false;

	if (mGameMode == GameMode::GAMEMODE_CHALLENGE_LITTLE_TROUBLE)
		return true;

	if (mPlayedQuickplay)
		return mQuickLevel == 25;

	return IsAdventureMode() && mPlayerInfo->mLevel == 25;
}

bool LawnApp::IsScaryPotterLevel()
{
	if (mGameMode >= GameMode::GAMEMODE_SCARY_POTTER_1 && mGameMode <= GameMode::GAMEMODE_SCARY_POTTER_ENDLESS)
		return true;

	if (mPlayedQuickplay)
		return mQuickLevel == 35;

	return IsAdventureMode() && mPlayerInfo->mLevel == 35;
}

bool LawnApp::IsStormyNightLevel()
{
	if (mBoard == nullptr)
		return false;

	if (mGameMode == GameMode::GAMEMODE_CHALLENGE_STORMY_NIGHT)
		return true;

	if (mPlayedQuickplay)
		return mQuickLevel == 40;

	return IsAdventureMode() && mPlayerInfo->mLevel == 40;
}

bool LawnApp::IsBungeeBlitzLevel()
{
	if (mBoard == nullptr)
		return false;

	if (mGameMode == GameMode::GAMEMODE_CHALLENGE_BUNGEE_BLITZ)
		return true;

	if (mPlayedQuickplay)
		return mQuickLevel == 45;

	return IsAdventureMode() && mPlayerInfo->mLevel == 45;
}

bool LawnApp::IsMiniBossLevel()
{
	if (mBoard == nullptr)
		return false;

	if (!IsAdventureMode())
		return false;

	if (mPlayedQuickplay)
	{
		return mQuickLevel == 10 || mQuickLevel == 20 || mQuickLevel == 30;
	}
	else
	{
		return mPlayerInfo->mLevel == 10 || mPlayerInfo->mLevel == 20 || mPlayerInfo->mLevel == 30;
	}
}

bool LawnApp::IsFinalBossLevel()
{
	if (mBoard == nullptr)
		return false;

	if (mGameMode == GameMode::GAMEMODE_CHALLENGE_FINAL_BOSS)
		return true;

	if (mPlayedQuickplay)
		return mQuickLevel == 50;

	return IsAdventureMode() && mPlayerInfo->mLevel == 50;
}

bool LawnApp::IsChallengeWithoutSeedBank()
{
	return
		mGameMode == GameMode::GAMEMODE_CHALLENGE_RAINING_SEEDS ||
		mGameMode == GameMode::GAMEMODE_UPSELL ||
		mGameMode == GameMode::GAMEMODE_INTRO ||
		IsWhackAZombieLevel() ||
		IsSquirrelLevel() ||
		IsScaryPotterLevel() ||
		mGameMode == GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN ||
		mGameMode == GameMode::GAMEMODE_TREE_OF_WISDOM;
}

bool LawnApp::CanShowSeedBankAfterSun()
{
	return IsChallengeWithoutSeedBank() && (IsScaryPotterLevel() || IsWhackAZombieLevel());
}

bool LawnApp::IsNight()
{
	if (IsIceDemo() || mPlayerInfo == nullptr)
		return false;

	if (mPlayedQuickplay)
	{
		return (mQuickLevel >= 11 && mQuickLevel <= 20) || (mQuickLevel >= 31 && mQuickLevel <= 40) || mQuickLevel == 50;
	}
	else
	{
		return (mPlayerInfo->mLevel >= 11 && mPlayerInfo->mLevel <= 20) || (mPlayerInfo->mLevel >= 31 && mPlayerInfo->mLevel <= 40) || mPlayerInfo->mLevel == 50;
	}
}

int LawnApp::GetCurrentChallengeIndex()
{
	return (int)mGameMode - (int)GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_1;
}

ChallengeDefinition& LawnApp::GetCurrentChallengeDef()
{
	return GetChallengeDefinition(GetCurrentChallengeIndex());
}

PottedPlant* LawnApp::GetPottedPlantByIndex(int thePottedPlantIndex)
{
	TOD_ASSERT(thePottedPlantIndex >= 0 && thePottedPlantIndex < mPlayerInfo->mNumPottedPlants);
	return &mPlayerInfo->mPottedPlant[thePottedPlantIndex];
}

bool LawnApp::UpdateApp()
{
	if (mCloseRequest)
	{
		Shutdown();
		return false;
	}

	//if (mLoadingThreadCompleted)
	//{
	//	LoadingThreadCompleted();
	//}

	bool updated = SexyAppBase::UpdateApp();


	//if (mLoadingThreadCompleted && !mExitToTop)
	//{
	//	CheckForUpdates();
	//}

	return updated;
}



void LawnApp::CloseRequestAsync()
{
	mDeferredMessages.clear();
	mExitToTop = true;
	mCloseRequest = true;
}

SeedType LawnApp::GetAwardSeedForLevel(int theLevel)
{
	int aArea = (theLevel - 1) / LEVELS_PER_AREA + 1;
	int aSub = (theLevel - 1) % LEVELS_PER_AREA + 1;
	int aSeedsHasGot = (aArea - 1) * 8 + aSub;  
	if (aSub >= 10)
	{
		aSeedsHasGot -= 2;  
	}
	else if (aSub >= 5)
	{
		aSeedsHasGot -= 1;  
	}
	if (aSeedsHasGot > 40)
	{
		aSeedsHasGot = 40;
	}
	
	return (SeedType)aSeedsHasGot;
}

int LawnApp::GetSeedsAvailable()
{
	int aLevel = mPlayerInfo->mLevel;
	if (HasFinishedAdventure() || aLevel > 50)
	{
		return 49;
	}

	SeedType aSeedTypeMax = GetAwardSeedForLevel(aLevel);
	return min(49, aSeedTypeMax);
}

bool LawnApp::HasSeedType(SeedType theSeedType)
{
	if (IsTrialStageLocked() && theSeedType >= SeedType::SEED_JALAPENO)
		return false;

	/*  优化
	if (theSeedType >= SeedType::SEED_TWINSUNFLOWER && theSeedType <= SeedType::SEED_IMITATER)
		return mPlayerInfo->mPurchases[theSeedType - SeedType::SEED_GATLINGPEA];
	*/

	if (theSeedType == SeedType::SEED_TWINSUNFLOWER)
	{
		return mPlayerInfo->mPurchases[(int)StoreItem::STORE_ITEM_PLANT_TWINSUNFLOWER] > 0;
	}
	if (theSeedType == SeedType::SEED_GLOOMSHROOM)
	{
		return mPlayerInfo->mPurchases[(int)StoreItem::STORE_ITEM_PLANT_GLOOMSHROOM] > 0;
	}
	if (theSeedType == SeedType::SEED_CATTAIL)
	{
		return mPlayerInfo->mPurchases[(int)StoreItem::STORE_ITEM_PLANT_CATTAIL] > 0;
	}
	if (theSeedType == SeedType::SEED_WINTERMELON)
	{
		return mPlayerInfo->mPurchases[(int)StoreItem::STORE_ITEM_PLANT_WINTERMELON] > 0;
	}
	if (theSeedType == SeedType::SEED_GOLD_MAGNET)
	{
		return mPlayerInfo->mPurchases[(int)StoreItem::STORE_ITEM_PLANT_GOLD_MAGNET] > 0;
	}
	if (theSeedType == SeedType::SEED_SPIKEROCK)
	{
		return mPlayerInfo->mPurchases[(int)StoreItem::STORE_ITEM_PLANT_SPIKEROCK] > 0;
	}
	if (theSeedType == SeedType::SEED_COBCANNON)
	{
		return mPlayerInfo->mPurchases[(int)StoreItem::STORE_ITEM_PLANT_COBCANNON] > 0;
	}
	if (theSeedType == SeedType::SEED_IMITATER)
	{
		return mPlayerInfo->mPurchases[(int)StoreItem::STORE_ITEM_PLANT_IMITATER] > 0;
	}
	if(mTodCheatKeys){
		if (theSeedType == SeedType::SEED_EXPLODE_O_NUT)
		{
			return true;
		}
		if (theSeedType == SeedType::SEED_GIANT_WALLNUT)
		{
			return true;
		}
		if (theSeedType == SeedType::SEED_SPROUT)
		{
			return true;
		}
		if (theSeedType == SeedType::SEED_LEFTPEATER)
		{
			return true;
		}
	}
	return theSeedType < GetSeedsAvailable();
}

bool LawnApp::SeedTypeAvailable(SeedType theSeedType)
{
	return (theSeedType == SeedType::SEED_GATLINGPEA && mPlayerInfo->mPurchases[StoreItem::STORE_ITEM_PLANT_GATLINGPEA]) || HasSeedType(theSeedType);
}

bool LawnApp::HasAllUpgrades()
{
	int availablePlants = 0;
	for (int seed = SEED_GATLINGPEA; seed <= SEED_IMITATER; seed++) {
		if (SeedTypeAvailable(SeedType(seed))) {
			availablePlants++;
		}
	}
	return availablePlants == 9;
}

Reanimation* LawnApp::AddReanimation(float theX, float theY, int theRenderOrder, ReanimationType theReanimationType)
{
	return mEffectSystem->mReanimationHolder->AllocReanimation(theX, theY, theRenderOrder, theReanimationType);
}

TodParticleSystem* LawnApp::AddTodParticle(float theX, float theY, int theRenderOrder, ParticleEffect theEffect)
{
	return mEffectSystem->mParticleHolder->AllocParticleSystem(theX, theY, theRenderOrder, theEffect);
}

ParticleSystemID LawnApp::ParticleGetID(TodParticleSystem* theParticle)
{
	return (ParticleSystemID)mEffectSystem->mParticleHolder->mParticleSystems.DataArrayGetID(theParticle);
}

ReanimationID LawnApp::ReanimationGetID(Reanimation* theReanimation)
{
	return (ReanimationID)mEffectSystem->mReanimationHolder->mReanimations.DataArrayGetID(theReanimation);
}

TodParticleSystem* LawnApp::ParticleGet(ParticleSystemID theParticleID)
{
	return mEffectSystem->mParticleHolder->mParticleSystems.DataArrayGet((unsigned int)theParticleID);
}

TodParticleSystem* LawnApp::ParticleTryToGet(ParticleSystemID theParticleID)
{
	return mEffectSystem->mParticleHolder->mParticleSystems.DataArrayTryToGet((unsigned int)theParticleID);
}

Reanimation* LawnApp::ReanimationGet(ReanimationID theReanimationID)
{
	return mEffectSystem->mReanimationHolder->mReanimations.DataArrayGet((unsigned int)theReanimationID);
}

Reanimation* LawnApp::ReanimationTryToGet(ReanimationID theReanimationID)
{
	return mEffectSystem->mReanimationHolder->mReanimations.DataArrayTryToGet((unsigned int)theReanimationID);
}

void LawnApp::RemoveReanimation(ReanimationID theReanimationID)
{
	Reanimation* aReanim = ReanimationTryToGet(theReanimationID);
	if (aReanim)
	{
		aReanim->ReanimationDie();
	}
}

void LawnApp::RemoveParticle(ParticleSystemID theParticleID)
{
	TodParticleSystem* aParticle = ParticleTryToGet(theParticleID);
	if (aParticle)
	{
		aParticle->ParticleSystemDie();
	}
}

bool LawnApp::AdvanceCrazyDaveText()
{
	SexyString aMessageName = StrFormat(_S("[CRAZY_DAVE_%d]"), mCrazyDaveMessageIndex + 1);
	if (!TodStringListExists(aMessageName))
	{
		return false;
	}

	CrazyDaveTalkIndex(mCrazyDaveMessageIndex + 1);
	return true;
}

SexyString LawnApp::GetCrazyDaveText(int theMessageIndex)
{
	SexyString aMessage = StrFormat(_S("[CRAZY_DAVE_%d]"), theMessageIndex);
	aMessage = TodReplaceString(aMessage, _S("{PLAYER_NAME}"), mPlayerInfo->mName);
	aMessage = TodReplaceString(aMessage, _S("{MONEY}"), GetMoneyString(mPlayerInfo->mCoins));
	int aCost = StoreScreen::GetItemCost(StoreItem::STORE_ITEM_PACKET_UPGRADE);
	aMessage = TodReplaceString(aMessage, _S("{UPGRADE_COST}"), GetMoneyString(aCost));
	return aMessage;
}

bool LawnApp::CanShowAlmanac()
{
	if (IsIceDemo())
		return false;

	if (mPlayerInfo == nullptr)
		return false;

	return HasFinishedAdventure() || mPlayerInfo->mLevel >= 15;
}

bool LawnApp::CanShowStore()
{
	if (IsIceDemo())
		return false;

	if (mPlayerInfo == nullptr)
		return false;

	return HasFinishedAdventure() || mPlayerInfo->mHasSeenUpsell || mPlayerInfo->mLevel >= 25;
}

bool LawnApp::CanShowZenGarden()
{
	if (mPlayerInfo == nullptr)
		return false;

	if (IsTrialStageLocked())
		return false;

	return HasFinishedAdventure() || mPlayerInfo->mLevel >= 45;
}

bool LawnApp::CanSpawnYetis()
{
	const ZombieDefinition& aZombieDef = GetZombieDefinition(ZombieType::ZOMBIE_YETI);
	return HasFinishedAdventure() && (mPlayerInfo->mFinishedAdventure >= 2 || mPlayerInfo->mLevel >= aZombieDef.mStartingLevel);
}

bool LawnApp::HasBeatenChallenge(GameMode theGameMode)
{
	if (mPlayerInfo == nullptr)
		return false;

	int aChallengeIndex = theGameMode - GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_1;
	TOD_ASSERT(aChallengeIndex >= 0 && aChallengeIndex < NUM_CHALLENGE_MODES);
	if (IsSurvivalNormal(theGameMode))
	{
		return mPlayerInfo->mChallengeRecords[aChallengeIndex] >= SURVIVAL_NORMAL_FLAGS;
	}
	if (IsSurvivalHard(theGameMode))
	{
		return mPlayerInfo->mChallengeRecords[aChallengeIndex] >= SURVIVAL_HARD_FLAGS;
	}
	if (IsSurvivalEndless(theGameMode) || IsEndlessScaryPotter(theGameMode) || IsEndlessIZombie(theGameMode))
	{
		return false;
	}
	return mPlayerInfo->mChallengeRecords[aChallengeIndex] > 0;
}

bool LawnApp::HasFinishedAdventure()
{
	return mPlayerInfo && mPlayerInfo->mFinishedAdventure > 0;
}

bool LawnApp::IsFirstTimeAdventureMode()
{
	return IsAdventureMode() && !HasFinishedAdventure();
}

void LawnApp::CrazyDaveEnter()
{
	TOD_ASSERT(mCrazyDaveState == CRAZY_DAVE_OFF);
	TOD_ASSERT(!ReanimationTryToGet(mCrazyDaveReanimID));

	Reanimation* aCrazyDaveReanim = AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_CRAZY_DAVE);
	aCrazyDaveReanim->mIsAttachment = true;
	aCrazyDaveReanim->SetBasePoseFromAnim("anim_idle_handing");
	mCrazyDaveReanimID = ReanimationGetID(aCrazyDaveReanim);
	aCrazyDaveReanim->PlayReanim("anim_enter", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 24.0f);

	mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_ENTERING;
	mCrazyDaveMessageIndex = -1;
	mCrazyDaveMessageText.clear();
	mCrazyDaveBlinkCounter = RandRangeInt(400, 800);

	if (mGameScene == GameScenes::SCENE_LEVEL_INTRO && IsStormyNightLevel())
	{
		aCrazyDaveReanim->mColorOverride = Color(64, 64, 64);
	}
}

void LawnApp::CrazyDaveDie()
{
	Reanimation* aCrazyDaveReanim = ReanimationTryToGet(mCrazyDaveReanimID);
	if (aCrazyDaveReanim)
	{
		aCrazyDaveReanim->ReanimationDie();

		mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_OFF;
		mCrazyDaveReanimID = ReanimationID::REANIMATIONID_NULL;
		mCrazyDaveMessageIndex = -1;
		mCrazyDaveMessageText.clear();

		CrazyDaveStopSound();
	}
}

void LawnApp::CrazyDaveLeave()
{
	Reanimation* aCrazyDaveReanim = ReanimationTryToGet(mCrazyDaveReanimID);
	if (aCrazyDaveReanim)
	{
		if (mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_HANDING_TALKING || mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_HANDING_IDLING)
		{
			CrazyDaveDoneHanding();
		}

		aCrazyDaveReanim->PlayReanim("anim_leave", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 20, 24.0f);
		aCrazyDaveReanim->SetImageOverride("Dave_mouths", nullptr);

		mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_LEAVING;
		mCrazyDaveMessageIndex = -1;
		mCrazyDaveMessageText.clear();

		CrazyDaveStopSound();
	}
}

void LawnApp::CrazyDaveTalkIndex(int theMessageIndex)
{
	mCrazyDaveMessageIndex = theMessageIndex;
	SexyString aMessageText = GetCrazyDaveText(theMessageIndex);
	CrazyDaveTalkMessage(aMessageText);
}

void LawnApp::CrazyDaveDoneHanding()
{
	Reanimation* aCrazyDaveReanim = ReanimationGet(mCrazyDaveReanimID);
	ReanimatorTrackInstance* aHandTrackInstance = aCrazyDaveReanim->GetTrackInstanceByName("Dave_handinghand");
	AttachmentDie(aHandTrackInstance->mAttachmentID);

	TodTrace("DoneHanding");
}

void LawnApp::CrazyDaveStopSound()
{
	mSoundSystem->StopFoley(FoleyType::FOLEY_CRAZY_DAVE_SHORT);
	mSoundSystem->StopFoley(FoleyType::FOLEY_CRAZY_DAVE_LONG);
	mSoundSystem->StopFoley(FoleyType::FOLEY_CRAZY_DAVE_EXTRA_LONG);
	mSoundSystem->StopFoley(FoleyType::FOLEY_CRAZY_DAVE_CRAZY);
}

void LawnApp::CrazyDaveTalkMessage(const SexyString& theMessage)
{
	Reanimation* aCrazyDaveReanim = ReanimationGet(mCrazyDaveReanimID);

	bool doHanding = false;
	if (theMessage.find(_S("{HANDING}")) != SexyString::npos)
	{
		doHanding = true;
	}
	if ((mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_HANDING_TALKING || mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_HANDING_IDLING) && !doHanding)
	{
		CrazyDaveDoneHanding();
	}

	bool doSound = true;
	if (theMessage.find(_S("{NO_SOUND}")) != SexyString::npos)
	{
		doSound = false;
	}
	else
	{
		CrazyDaveStopSound();
	}

	int aWordsCount = 0;
	bool isControlWord = false;
	for (int i = 0; i < theMessage.size(); i++)
	{
		if (theMessage[i] == _S('{'))
		{
			isControlWord = true;
		}
		else if (theMessage[i] == _S('}'))
		{
			isControlWord = false;
		}
		else if (!isControlWord)
		{
			aWordsCount++;
		}
	}

	aCrazyDaveReanim->SetImageOverride(_S("Dave_mouths"), nullptr);

	if (mCrazyDaveState != CrazyDaveState::CRAZY_DAVE_TALKING || doSound)
	{
		if (doHanding)
		{
			aCrazyDaveReanim->PlayReanim("anim_talk_handing", ReanimLoopType::REANIM_LOOP, 50, 12.0f);

			if (doSound)
			{
				if (theMessage.find(_S("{SHORT_SOUND}")) != SexyString::npos)
				{
					PlayFoley(FoleyType::FOLEY_CRAZY_DAVE_SHORT);
				}
				else if (theMessage.find(_S("{SCREAM}")) != SexyString::npos)
				{
					PlayFoley(FoleyType::FOLEY_CRAZY_DAVE_SCREAM);
				}
				else
				{
					PlayFoley(FoleyType::FOLEY_CRAZY_DAVE_LONG);
				}
			}
			
			mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_HANDING_TALKING;
		}
		else if (theMessage.find(_S("{SHAKE}")) != SexyString::npos)
		{
			aCrazyDaveReanim->PlayReanim("anim_crazy", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 50, 12.0f);

			if (doSound)
			{
				PlayFoley(FoleyType::FOLEY_CRAZY_DAVE_CRAZY);
			}

			mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_TALKING;
		}
		else if (theMessage.find(_S("{SCREAM}")) != SexyString::npos)
		{
			aCrazyDaveReanim->PlayReanim("anim_smalltalk", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 50, 12.0f);

			if (doSound)
			{
				PlayFoley(FoleyType::FOLEY_CRAZY_DAVE_SCREAM);
			}

			mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_TALKING;
		}
		else if (theMessage.find(_S("{SCREAM2}")) != SexyString::npos)
		{
			aCrazyDaveReanim->PlayReanim("anim_mediumtalk", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 50, 12.0f);

			if (doSound)
			{
				PlayFoley(FoleyType::FOLEY_CRAZY_DAVE_SCREAM_2);
			}

			mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_TALKING;
		}
		else if (theMessage.find(_S("{SHOW_WALLNUT}")) != SexyString::npos)
		{
			aCrazyDaveReanim->PlayReanim("anim_talk_handing", ReanimLoopType::REANIM_LOOP, 50, 12.0f);

			Reanimation* aWallnutReanim = AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_WALLNUT);
			aWallnutReanim->PlayReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 0, 12.0f);
			TodTrace("Handed");

			ReanimatorTrackInstance* aHandTrackInstance = aCrazyDaveReanim->GetTrackInstanceByName("Dave_handinghand");
			AttachEffect* aAttachEffect = AttachReanim(aHandTrackInstance->mAttachmentID, aWallnutReanim, 100.0f, 393.0f);
			aAttachEffect->mOffset.m00 = 1.2f;
			aAttachEffect->mOffset.m11 = 1.2f;

			aCrazyDaveReanim->Update();

			if (doSound)
			{
				PlayFoley(FoleyType::FOLEY_CRAZY_DAVE_SCREAM_2);
			}

			mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_HANDING_TALKING;
		}
		else if (theMessage.find(_S("{SHOW_HAMMER}")) != SexyString::npos)
		{
			aCrazyDaveReanim->PlayReanim("anim_talk_handing", ReanimLoopType::REANIM_LOOP, 50, 12.0f);

			Reanimation* aHammerReanim = AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_HAMMER);
			aHammerReanim->PlayReanim("anim_whack_zombie", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 24.0f);
			aHammerReanim->mAnimTime = 1.0f;

			ReanimatorTrackInstance* aHandTrackInstance = aCrazyDaveReanim->GetTrackInstanceByName("Dave_handinghand");
			AttachEffect* aAttachEffect = AttachReanim(aHandTrackInstance->mAttachmentID, aHammerReanim, 62.0f, 445.0f);
			aAttachEffect->mOffset.m00 = 1.5f;
			aAttachEffect->mOffset.m11 = 1.5f;

			aCrazyDaveReanim->Update();

			if (doSound)
			{
				PlayFoley(FoleyType::FOLEY_CRAZY_DAVE_LONG);
			}

			mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_HANDING_TALKING;
		}
		else if (theMessage.find(_S("{SHOW_FERTILIZER}")) != SexyString::npos)
		{
			aCrazyDaveReanim->PlayReanim("anim_talk_handing", ReanimLoopType::REANIM_LOOP, 50, 12.0f);

			Reanimation* aFertilizerReanim = AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_ZENGARDEN_FERTILIZER);
			aFertilizerReanim->PlayReanim("bag", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 24.0f);
			aFertilizerReanim->mAnimRate = 0.0f;

			ReanimatorTrackInstance* aHandTrackInstance = aCrazyDaveReanim->GetTrackInstanceByName("Dave_handinghand");
			AttachReanim(aHandTrackInstance->mAttachmentID, aFertilizerReanim, 102.0f, 412.0f);
			aCrazyDaveReanim->Update();

			if (doSound)
			{
				PlayFoley(FoleyType::FOLEY_CRAZY_DAVE_LONG);
			}

			mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_HANDING_TALKING;
		}
		else if (theMessage.find(_S("{SHOW_TREE_FOOD}")) != SexyString::npos)
		{
			aCrazyDaveReanim->PlayReanim("anim_talk_handing", ReanimLoopType::REANIM_LOOP, 50, 12.0f);

			Reanimation* aTreeFoodReanim = AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_TREEOFWISDOM_TREEFOOD);
			aTreeFoodReanim->PlayReanim("bag", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 24.0f);
			aTreeFoodReanim->mAnimRate = 0.0f;

			ReanimatorTrackInstance* aHandTrackInstance = aCrazyDaveReanim->GetTrackInstanceByName("Dave_handinghand");
			AttachReanim(aHandTrackInstance->mAttachmentID, aTreeFoodReanim, 102.0f, 412.0f);
			aCrazyDaveReanim->Update();

			if (doSound)
			{
				PlayFoley(FoleyType::FOLEY_CRAZY_DAVE_LONG);
			}

			mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_HANDING_TALKING;
		}
		else if (theMessage.find(_S("{SHOW_MONEYBAG}")) != SexyString::npos)
		{
			aCrazyDaveReanim->PlayReanim("anim_talk_handing", ReanimLoopType::REANIM_LOOP, 50, 12.0f);

			Reanimation* aMoneyBagReanim = AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_ZENGARDEN_FERTILIZER);
			aMoneyBagReanim->PlayReanim("bag", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 0, 24.0f);
			aMoneyBagReanim->mAnimRate = 0.0f;
			aMoneyBagReanim->SetImageOverride("bag", IMAGE_MONEYBAG);

			ReanimatorTrackInstance* aHandTrackInstance = aCrazyDaveReanim->GetTrackInstanceByName("Dave_handinghand");
			AttachReanim(aHandTrackInstance->mAttachmentID, aMoneyBagReanim, 90.0f, 405.0f);
			aCrazyDaveReanim->Update();
			/*
			v16 = Reanimation::GetTrackInstanceByName(v3, "Dave_handinghand");
			theAnimRate = 405.0;
			v17 = 90.0;
			*/
			if (doSound)
			{
				PlayFoley(FoleyType::FOLEY_CRAZY_DAVE_LONG);
			}

			mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_HANDING_TALKING;
		}
		else
		{
			if (aWordsCount < 23)
			{
				aCrazyDaveReanim->PlayReanim("anim_smalltalk", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 50, 12.0f);

				if (doSound)
				{
					PlayFoley(FoleyType::FOLEY_CRAZY_DAVE_SHORT);
				}

				mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_TALKING;
			}
			else if (aWordsCount < 52)
			{
				aCrazyDaveReanim->PlayReanim("anim_mediumtalk", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 50, 12.0f);

				if (doSound)
				{
					PlayFoley(FoleyType::FOLEY_CRAZY_DAVE_LONG);
				}

				mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_TALKING;
			}
			else
			{
				aCrazyDaveReanim->PlayReanim("anim_blahblah", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 50, 12.0f);

				if (doSound)
				{
					PlayFoley(FoleyType::FOLEY_CRAZY_DAVE_EXTRA_LONG);
				}

				mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_TALKING;
			}
		}
	}

	mCrazyDaveMessageText = theMessage;
}

void LawnApp::CrazyDaveStopTalking()
{
	bool aDoneHanding = true;
	if (mGameMode == GameMode::GAMEMODE_UPSELL)
	{
		aDoneHanding = false;
	}
	if (aDoneHanding && mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_HANDING_TALKING)
	{
		CrazyDaveDoneHanding();
	}

	Reanimation* aCrazyDaveReanim = ReanimationGet(mCrazyDaveReanimID);
	aCrazyDaveReanim->SetImageOverride("Dave_mouths", nullptr);
	if (mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_HANDING_TALKING && !aDoneHanding)
	{
		aCrazyDaveReanim->PlayReanim("anim_idle_handing", ReanimLoopType::REANIM_LOOP, 20, 12.0f);
		mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_HANDING_IDLING;
	}
	else if (mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_TALKING || mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_HANDING_TALKING)
	{
		aCrazyDaveReanim->PlayReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 20, 12.0f);
		mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_IDLING;
	}

	mCrazyDaveMessageIndex = -1;
	mCrazyDaveMessageText.clear();
	CrazyDaveStopSound();
}

void LawnApp::UpdateCrazyDave()
{
	Reanimation* aCrazyDaveReanim = ReanimationTryToGet(mCrazyDaveReanimID);
	if (aCrazyDaveReanim == nullptr)
		return;

	if (mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_ENTERING || mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_TALKING)
	{
		if (aCrazyDaveReanim->mLoopCount > 0)
		{
			aCrazyDaveReanim->PlayReanim("anim_idle", ReanimLoopType::REANIM_LOOP, 20, 12.0f);
			mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_IDLING;
		}
	}
	else if (mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_HANDING_TALKING)
	{
		if (aCrazyDaveReanim->mLoopCount > 0)
		{
			aCrazyDaveReanim->PlayReanim("anim_idle_handing", ReanimLoopType::REANIM_LOOP, 20, 12.0f);
			mCrazyDaveState = CrazyDaveState::CRAZY_DAVE_HANDING_IDLING;
		}
	}
	else if (mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_LEAVING && aCrazyDaveReanim->mLoopCount > 0)
	{
		CrazyDaveDie();
	}

	if (mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_IDLING || mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_HANDING_IDLING)
	{
		if (mCrazyDaveMessageText.find("{MOUTH_BIG_SMILE}") != std::string::npos)
		{
			aCrazyDaveReanim->SetImageOverride("Dave_mouths", IMAGE_REANIM_CRAZYDAVE_MOUTH1);
		}
		else if (mCrazyDaveMessageText.find("{MOUTH_SMALL_SMILE}") != std::string::npos)
		{
			aCrazyDaveReanim->SetImageOverride("Dave_mouths", IMAGE_REANIM_CRAZYDAVE_MOUTH5);
		}
		else if (mCrazyDaveMessageText.find("{MOUTH_BIG_OH}") != std::string::npos)
		{
			aCrazyDaveReanim->SetImageOverride("Dave_mouths", IMAGE_REANIM_CRAZYDAVE_MOUTH4);
		}
		else if (mCrazyDaveMessageText.find("{MOUTH_SMALL_OH}") != std::string::npos)
		{
			aCrazyDaveReanim->SetImageOverride("Dave_mouths", IMAGE_REANIM_CRAZYDAVE_MOUTH6);
		}
	}

	if (mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_IDLING || mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_TALKING || 
		mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_HANDING_TALKING || mCrazyDaveState == CrazyDaveState::CRAZY_DAVE_HANDING_IDLING)
	{
		mCrazyDaveBlinkCounter--;
		if (mCrazyDaveBlinkCounter <= 0)
		{
			mCrazyDaveBlinkCounter = RandRangeInt(400, 800);
			Reanimation* aBlinkReanim = AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_CRAZY_DAVE);
			aBlinkReanim->SetFramesForLayer("anim_blink");
			aBlinkReanim->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_FULL_LAST_FRAME_AND_HOLD;
			aBlinkReanim->mAnimRate = 15.0f;
			aBlinkReanim->AttachToAnotherReanimation(aCrazyDaveReanim, "Dave_head");
			aBlinkReanim->mColorOverride = aCrazyDaveReanim->mColorOverride;
			aCrazyDaveReanim->AssignRenderGroupToTrack("Dave_eye", RENDER_GROUP_HIDDEN);
			mCrazyDaveBlinkReanimID = ReanimationGetID(aBlinkReanim);
		}
	}

	Reanimation* aBlinkReanim = ReanimationTryToGet(mCrazyDaveBlinkReanimID);
	if (aBlinkReanim && aBlinkReanim->mLoopCount > 0)
	{
		aCrazyDaveReanim->AssignRenderGroupToTrack("Dave_eye", RENDER_GROUP_NORMAL);
		RemoveReanimation(mCrazyDaveBlinkReanimID);
		mCrazyDaveBlinkReanimID = ReanimationID::REANIMATIONID_NULL;
	}

	aCrazyDaveReanim->Update();
}

void LawnApp::DrawCrazyDave(Graphics* g)
{
	Reanimation* aCrazyDaveReanim = ReanimationTryToGet(mCrazyDaveReanimID);
	if (aCrazyDaveReanim == nullptr)
		return;

	if (mCrazyDaveMessageText.size())
	{
		Image* aBubbleImage = IMAGE_STORE_SPEECHBUBBLE2;
		int aPosX = 285;
		int aPosY = 20;
		if (GetDialog(Dialogs::DIALOG_STORE))
		{
			aBubbleImage = IMAGE_STORE_SPEECHBUBBLE;
			aPosX -= 180;
			aPosY -= 78;
		}
		else if (mGameMode == GameMode::GAMEMODE_UPSELL)
		{
			aPosX += 130;
			aPosY += 70;
		}
		g->DrawImage(aBubbleImage, aPosX, aPosY);

		SexyString aBubbleText = mCrazyDaveMessageText;
		Rect aRect(aPosX + 25, aPosY + 6, 233, 144);
		if (aBubbleText.find(_S("{SHAKE}")) != SexyString::npos)
		{
			aBubbleText = TodReplaceString(aBubbleText, _S("{SHAKE}"), _S(""));
			aRect.mX += rand() % 2;
			aRect.mY += rand() % 2;
		}

		bool clickToContinue = true;
		if (mGameMode == GameMode::GAMEMODE_UPSELL)
		{
			clickToContinue = false;
		}
		else if (aBubbleText.find(_S("{NO_CLICK}")) != SexyString::npos)
		{
			aBubbleText = TodReplaceString(aBubbleText, _S("{NO_CLICK}"), _S(""));
			clickToContinue = false;
		}

		TodDrawStringWrapped(g, aBubbleText, aRect, FONT_BRIANNETOD16, Color::Black, DrawStringJustification::DS_ALIGN_CENTER_VERTICAL_MIDDLE);
		if (clickToContinue)
		{
			TodDrawString(g, _S("click to continue"), aPosX + 139, aPosY + 140, FONT_PICO129, Color::Black, DrawStringJustification::DS_ALIGN_CENTER);
		}
	}
	
	if (mGameMode == GameMode::GAMEMODE_UPSELL)
	{
		Graphics aDaveGraphics(*g);
		aDaveGraphics.ClearClipRect();
		aCrazyDaveReanim->Draw(&aDaveGraphics);
	}
	else
		aCrazyDaveReanim->Draw(g);
}

int LawnApp::GetNumPreloadingTasks()
{
	int aTaskCount = 10;
	if (mPlayerInfo)
	{
		for (SeedType i = SeedType::SEED_PEASHOOTER; i < SeedType::NUM_SEED_TYPES; i = (SeedType)((int)i + 1))
		{
			if (SeedTypeAvailable(i) || HasFinishedAdventure())
			{
				aTaskCount++;
			}
		}

		for (ZombieType i = ZombieType::ZOMBIE_NORMAL; i < ZombieType::NUM_ZOMBIE_TYPES;i = (ZombieType)((int)i + 1))
		{
			if (HasFinishedAdventure() || mPlayerInfo->mLevel >= GetZombieDefinition(i).mStartingLevel)
			{
				if (i != ZombieType::ZOMBIE_BOSS &&
					i != ZombieType::ZOMBIE_CATAPULT &&
					i != ZombieType::ZOMBIE_GARGANTUAR &&
					i != ZombieType::ZOMBIE_DIGGER &&
					i != ZombieType::ZOMBIE_ZAMBONI)
				{
					aTaskCount++;
				}
			}
		}
	}
	return aTaskCount * 68;
}

void LawnApp::PreloadForUser()
{
	int aNumTasks = mNumLoadingThreadTasks + GetNumPreloadingTasks();
	if (mTitleScreen && mTitleScreen->mQuickLoadKey != KeyCode::KEYCODE_UNKNOWN)
	{
		TodTrace("preload canceled\n");
		mNumLoadingThreadTasks = aNumTasks;
		return;
	}

	ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_PUFF, true);
	ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_LAWN_MOWERED_ZOMBIE, true);
	ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_READYSETPLANT, true);
	mCompletedLoadingThreadTasks += 68;
	ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_FINAL_WAVE, true);
	ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_SUN, true);
	ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_TEXT_FADE_ON, true);
	mCompletedLoadingThreadTasks += 68;
	ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_ZOMBIE, true);
	mCompletedLoadingThreadTasks += 68;
	ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_ZOMBIE_NEWSPAPER, true);
	mCompletedLoadingThreadTasks += 68;
	ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_SELECTOR_SCREEN, true);
	mCompletedLoadingThreadTasks += 340;
	ReanimatorEnsureDefinitionLoaded(ReanimationType::REANIM_ZOMBIE_HAND, true);
	mCompletedLoadingThreadTasks += 68;

	if (mPlayerInfo)
	{
		for (SeedType i = SeedType::SEED_PEASHOOTER; i < SeedType::NUM_SEED_TYPES; i = (SeedType)((int)i + 1))
		{
			if (SeedTypeAvailable(i) || HasFinishedAdventure())
			{
				Plant::PreloadPlantResources(i);
				if (mCompletedLoadingThreadTasks < aNumTasks)
				{
					mCompletedLoadingThreadTasks += 68;
				}

				if (mTitleScreen && mTitleScreen->mQuickLoadKey != KeyCode::KEYCODE_UNKNOWN)
				{
					TodTrace("preload canceled\n");
					mNumLoadingThreadTasks = aNumTasks;
					return;
				}

				if (mShutdown || mCloseRequest)
				{
					return;
				}
			}
		}

		for (ZombieType i = ZombieType::ZOMBIE_NORMAL; i < ZombieType::NUM_ZOMBIE_TYPES;i = (ZombieType)((int)i + 1))
		{
			if (HasFinishedAdventure() || mPlayerInfo->mLevel >= GetZombieDefinition(i).mStartingLevel)
			{
				continue;
			}
			if (i == ZombieType::ZOMBIE_BOSS || i == ZombieType::ZOMBIE_CATAPULT || i == ZombieType::ZOMBIE_GARGANTUAR ||
				i == ZombieType::ZOMBIE_DIGGER || i == ZombieType::ZOMBIE_ZAMBONI)
			{
				continue;
			}

			Zombie::PreloadZombieResources(i);
			if (mCompletedLoadingThreadTasks < aNumTasks)
			{
				mCompletedLoadingThreadTasks += 68;
			}

			if (mTitleScreen && mTitleScreen->mQuickLoadKey != KeyCode::KEYCODE_UNKNOWN)
			{
				TodTrace("preload canceled\n");
				mNumLoadingThreadTasks = aNumTasks;
				return;
			}

			if (mShutdown || mCloseRequest)
			{
				return;
			}
		}
	}

	if (mCompletedLoadingThreadTasks != aNumTasks)
	{
		TodTrace("num preload tasks wasn't calculated correctly");
		mCompletedLoadingThreadTasks = aNumTasks;
	}
}

void LawnApp::EnforceCursor()
{
	if (HAS_CUSTOM_CURSOR)
	{
		::SetCursor(NULL);
		return;
	}

	if (mSEHOccured || !mMouseIn)
	{
		::SetCursor(LoadCursor(NULL, IDC_ARROW));
		return;
	}

	if (mOverrideCursor)
	{
		::SetCursor(mOverrideCursor);
		return;
	}

	switch (mCursorNum)
	{
	case CURSOR_POINTER:
		::SetCursor(LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_CURSOR1)));
		return;

	case CURSOR_HAND:
		::SetCursor(mHandCursor);
		return;

	case CURSOR_TEXT:
		::SetCursor(LoadCursor(NULL, IDC_IBEAM));
		return;

	case CURSOR_DRAGGING:
		::SetCursor(mDraggingCursor);
		return;

	case CURSOR_CIRCLE_SLASH:
		::SetCursor(LoadCursor(NULL, IDC_NO));
		return;

	case CURSOR_SIZEALL:
		::SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		return;

	case CURSOR_SIZENESW:
		::SetCursor(LoadCursor(NULL, IDC_SIZENESW));
		return;

	case CURSOR_SIZENS:
		::SetCursor(LoadCursor(NULL, IDC_SIZENS));
		return;

	case CURSOR_SIZENWSE:
		::SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
		return;

	case CURSOR_SIZEWE:
		::SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		return;

	case CURSOR_WAIT:
		::SetCursor(LoadCursor(NULL, IDC_WAIT));
		return;

	case CURSOR_CUSTOM:
		::SetCursor(NULL);
		return;

	case CURSOR_NONE:
		::SetCursor(NULL);
		return;

	default:
		::SetCursor(LoadCursor(NULL, IDC_ARROW));
		return;
	}
}

SexyString LawnApp::Pluralize(int theCount, const SexyChar* theSingular, const SexyChar* thePlural)
{
	if (theCount == 1)
	{
		return TodReplaceNumberString(theSingular, _S("{COUNT}"), theCount);
	}

	return TodReplaceNumberString(thePlural, _S("{COUNT}"), theCount);
}

int LawnApp::GetNumTrophies(ChallengePage thePage)
{
	int aNumTrophies = 0;

	for (int i = 0; i < NUM_CHALLENGE_MODES; i++)
	{
		const ChallengeDefinition& aDef = GetChallengeDefinition(i);
		if (aDef.mPage == thePage && HasBeatenChallenge(aDef.mChallengeMode))
		{
			aNumTrophies++;
		}
	}

	return aNumTrophies;
}

int LawnApp::GetTotalTrophies(ChallengePage thePage)
{
	return thePage == CHALLENGE_PAGE_SURVIVAL ? 10 : thePage == CHALLENGE_PAGE_CHALLENGE ? 20 : thePage == CHALLENGE_PAGE_PUZZLE ? 18 : thePage == CHALLENGE_PAGE_LIMBO ? 0 : 0;
}

int LawnApp::TrophiesNeedForGoldSunflower()
{
	return 48 - GetNumTrophies(CHALLENGE_PAGE_SURVIVAL) - GetNumTrophies(CHALLENGE_PAGE_CHALLENGE) - GetNumTrophies(CHALLENGE_PAGE_PUZZLE);
}

bool LawnApp::EarnedGoldTrophy()
{
	return HasFinishedAdventure() && TrophiesNeedForGoldSunflower() <= 0;
}

void LawnApp::FinishZenGardenToturial()
{
	mBoardResult = BoardResult::BOARDRESULT_WON;
	KillBoard();
	PreNewGame(GameMode::GAMEMODE_ADVENTURE, false);
}

bool LawnApp::IsTrialStageLocked()
{
	if (mDebugTrialLocked)
		return true;

	if (mDRM && mDRM->QueryData())
		return false;

	return mTrialType == TrialType::TRIALTYPE_STAGELOCKED;
}

void LawnApp::InitHook()
{
#ifdef _DEBUG
	mDRM = nullptr;
#else
	mDRM = new PopDRMComm();
	mDRM->DoIPC();
	if (sexystricmp(GetString("MarketingMode", _S("")).c_str(), _S("StageLocked")) == 0)
	{
		mTrialType = TrialType::TRIALTYPE_STAGELOCKED;
		mDRM->EnableLocking();
	}
	else
	{
		mTrialType = TrialType::TRIALTYPE_NONE;
	}
#endif
}

SexyString LawnApp::GetMoneyString(int theAmount)
{
	int aValue = theAmount * 10;
	if (aValue > 999999)
	{
		return StrFormat(_S("$%d,%03d,%03d"), aValue / 1000000, (aValue - aValue / 1000000 * 1000000) / 1000, aValue - aValue / 1000 * 1000);
	}
	else if (aValue > 999)
	{
		return StrFormat(_S("$%d,%03d"), aValue / 1000, aValue - aValue / 1000 * 1000);
	}
	else
	{
		return StrFormat(_S("$%d"), aValue);
	}
}

SexyString LawnGetCurrentLevelName()
{
	if (gLawnApp == nullptr)
	{
		return _S("Before App");
	}
	if (gLawnApp->mGameScene == GameScenes::SCENE_LOADING)
	{
		return _S("Game Loading");
	}
	if (gLawnApp->mGameScene == GameScenes::SCENE_MENU)
	{
		return _S("Game Selector");
	}
	if (gLawnApp->mGameScene == GameScenes::SCENE_AWARD)
	{
		return _S("Award Screen");
	}
	if (gLawnApp->mGameScene == GameScenes::SCENE_CHALLENGE)
	{
		return _S("Challenge Screen");
	}
	if (gLawnApp->mGameScene == GameScenes::SCENE_CREDIT)
	{
		return _S("Credits");
	}
	if (gLawnApp->mBoard == nullptr)
	{
		return _S("Not Playing");
	}

	if (gLawnApp->IsFirstTimeAdventureMode())
	{
		return gLawnApp->GetStageString(gLawnApp->mBoard->mLevel);
	}
	if (gLawnApp->IsAdventureMode())
	{
		return StrFormat(_S("F%d"), gLawnApp->GetStageString(gLawnApp->mBoard->mLevel).c_str());
	}

	return gLawnApp->GetCurrentChallengeDef().mChallengeName;
}

void LawnApp::GetAchievement(AchievementType theAchievementType)
{
	if (mAchievements == nullptr)
		return;
	mAchievements->GiveAchievement(theAchievementType);
}

void LawnApp::UpdateDiscordState(SexyString def)
{
	SexyString State;
	if (AlmanacDialog* dialog = (AlmanacDialog*)GetDialog(Dialogs::DIALOG_ALMANAC))
	{
		if (dialog->mOpenPage == AlmanacPage::ALMANAC_PAGE_INDEX)
			State = "Almanac (Index)";
		else if (dialog->mOpenPage == AlmanacPage::ALMANAC_PAGE_ZOMBIES)
			State = "Almanac (Zombies)";
		else if (dialog->mOpenPage == AlmanacPage::ALMANAC_PAGE_PLANTS)
			State = "Almanac (Plants)";
	}
	else if (GetDialog(Dialogs::DIALOG_STORE))
		State = "Store";
	else if (NewOptionsDialog* dialog = (NewOptionsDialog*)GetDialog(Dialogs::DIALOG_NEWOPTIONS))
		State = dialog->mAdvancedMode ? ("Advanced Options" + StrFormat(" (Page %d)", dialog->mAdvancedPage)) : "Options";
	else if (GetDialog(Dialogs::DIALOG_USERDIALOG))
		State = "Profiles";
	else
		State = def;
	mState = State;
}

bool LawnApp::CanDoPinataMode()
{
	if (mPlayerInfo == nullptr)
		return false;

	return mPlayerInfo->mChallengeRecords[(int)GameMode::GAMEMODE_TREE_OF_WISDOM - (int)GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_1] >= 1000;
}

bool LawnApp::CanDoDanceMode()
{
	if (mPlayerInfo == nullptr)
		return false;

	return mPlayerInfo->mChallengeRecords[(int)GameMode::GAMEMODE_TREE_OF_WISDOM - (int)GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_1] >= 500;
}

bool LawnApp::CanDoDaisyMode()
{
	if (mPlayerInfo == nullptr)
		return false;

	return mPlayerInfo->mChallengeRecords[(int)GameMode::GAMEMODE_TREE_OF_WISDOM - (int)GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_1] >= 100;
}

void LawnApp::PlaySample(int theSoundNum)
{
	if (!mMuteSoundsForCutscene)
	{
		SexyAppBase::PlaySample(theSoundNum);
	}
}

void LawnApp::SwitchScreenMode(bool wantWindowed, bool is3d, bool force)
{
	SexyAppBase::SwitchScreenMode(wantWindowed, is3d, force);

	NewOptionsDialog* aNewOptionsDialog = (NewOptionsDialog*)GetDialog(Dialogs::DIALOG_NEWOPTIONS);
	if (aNewOptionsDialog)
	{
		aNewOptionsDialog->mFullscreenCheckbox->SetChecked(!mIsWindowed);
	}
}

void LawnApp::ToggleDebugMode()
{
	NewOptionsDialog* aNewOptionsDialog = (NewOptionsDialog*)GetDialog(Dialogs::DIALOG_NEWOPTIONS);
	if (aNewOptionsDialog)
	{
		mTodCheatKeys = mDebugKeysEnabled = aNewOptionsDialog->mDebugModeBox->IsChecked();
	}
}

bool LawnApp::Is3dAccel()
{
	return mIs3dAccel;
}

void LawnApp::SetCursorMode(CursorMode theCursorMode)
{
	if (HAS_CUSTOM_CURSOR && mCursor)
	{
		mCursor->mCursorMode = theCursorMode;
	}
}

/* #################################################################################################### */

void LawnApp::BetaSubmit(bool theAskForComments)
{

}

void LawnApp::BetaRecordLevelStats()
{

}

void LawnApp::BetaAddFile(std::list<std::string>& theUploadFileList, std::string theFileName, std::string theShortName)
{

}

void LawnApp::TraceLoadGroup(const char* theGroupName, int theGroupTime, int theTotalGroupWeigth, int theTaskWeight)
{

}

/* #################################################################################################### */

void LawnApp::DoHighScoreDialog()
{

}

void LawnApp::DoRegister()
{

}

void LawnApp::DoRegisterError()
{

}

bool LawnApp::CanDoRegisterDialog()
{
	return false;
}

void LawnApp::DoNeedRegisterDialog()
{

}

void LawnApp::FinishModelessDialogs()
{

}

bool LawnApp::NeedRegister()
{
	return false;
}

void LawnApp::UpdateRegisterInfo()
{

}
