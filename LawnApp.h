#ifndef __LAWNAPP_H__
#define __LAWNAPP_H__

#include "ConstEnums.h"
#include "SexyAppFramework/SexyApp.h"

class Board;
class GameSelector;
class ChallengeDefinition;
class SeedChooserScreen;
class AwardScreen;
class CreditScreen;
class Achievements;
class TodFoley;
class PoolEffect;
class ZenGarden;
class PottedPlant;
class EffectSystem;
class TodParticleSystem;
class Reanimation;
class ReanimatorCache;
class ProfileMgr;
class PlayerInfo;
class Music;
class TitleScreen;
class PopDRMComm;
class ChallengeScreen;
class StoreScreen;
class AlmanacDialog;
class TypingCheck;
class MiniCreditsScreen;
class AchievementScreen;
class QuickPlayScreen;

namespace Sexy
{
	class Dialog;
	class Graphics;
	class ButtonWidget;
};

enum FoleyType;

using namespace Sexy;

typedef std::list<ButtonWidget*> ButtonList;
typedef std::list<Image*> ImageList;

class LevelStats
{
public:
	int								mUnusedLawnMowers;

public:
	LevelStats() { Reset(); }
	inline void						Reset() { mUnusedLawnMowers = 0; }
};

class LawnApp : public SexyApp
{
public:
	Board*							mBoard;											
	TitleScreen*					mTitleScreen;									
	GameSelector*					mGameSelector;									
	SeedChooserScreen*				mSeedChooserScreen;								
	AwardScreen*					mAwardScreen;									
	CreditScreen*					mCreditScreen;									
	ChallengeScreen*				mChallengeScreen;								
	MiniCreditsScreen*				mMiniCreditsScreen;	
	AchievementScreen*				mAchievementScreen;
	QuickPlayScreen*				mQuickPlayScreen;
	TodFoley*						mSoundSystem;									
	ButtonList						mControlButtonList;								
	ImageList						mCreatedImageList;								
	std::string						mReferId;										
	std::string						mRegisterLink;									
	std::string						mMod;											
	bool							mRegisterResourcesLoaded;						
	bool							mTodCheatKeys;									
	GameMode						mGameMode;										
	GameScenes						mGameScene;										
	bool							mLoadingZombiesThreadCompleted;					
	bool							mFirstTimeGameSelector;							
	int								mGamesPlayed;									
	int								mMaxExecutions;									
	int								mMaxPlays;										
	int								mMaxTime;										
	bool							mEasyPlantingCheat;								
	PoolEffect*						mPoolEffect;									
	ZenGarden*						mZenGarden;										
	EffectSystem*					mEffectSystem;									
	ReanimatorCache*				mReanimatorCache;								
	ProfileMgr*						mProfileMgr;									
	PlayerInfo*						mPlayerInfo;									
	LevelStats*						mLastLevelStats;								
	bool							mCloseRequest;									
	int								mAppCounter;									
	Music*							mMusic;											
	ReanimationID					mCrazyDaveReanimID;								
	CrazyDaveState					mCrazyDaveState;								
	int								mCrazyDaveBlinkCounter;							
	ReanimationID					mCrazyDaveBlinkReanimID;						
	int								mCrazyDaveMessageIndex;							
	SexyString						mCrazyDaveMessageText;							
	int								mAppRandSeed;									
	HICON							mBigArrowCursor;								
	PopDRMComm*						mDRM;											
	int								mSessionID;										
	int								mPlayTimeActiveSession;							
	int								mPlayTimeInactiveSession;						
	BoardResult						mBoardResult;									
	bool							mSawYeti;										
	TypingCheck*					mKonamiCheck;									
	TypingCheck*					mMustacheCheck;									
	TypingCheck*					mMoustacheCheck;								
	TypingCheck*					mSuperMowerCheck;								
	TypingCheck*					mSuperMowerCheck2;								
	TypingCheck*					mFutureCheck;									
	TypingCheck*					mPinataCheck;									
	TypingCheck*					mDanceCheck;									
	TypingCheck*					mDaisyCheck;									
	TypingCheck*					mSukhbirCheck;									
	bool							mMustacheMode;									
	bool							mSuperMowerMode;								
	bool							mFutureMode;									
	bool							mPinataMode;									
	bool							mDanceMode;										
	bool							mDaisyMode;										
	bool							mSukhbirMode;									
	TrialType						mTrialType;										
	bool							mDebugTrialLocked;								
	bool							mMuteSoundsForCutscene;							
	Achievements*					mAchievements;
	CursorWidget*					mCursor;
	bool							isFastMode;
	SexyString						mVersion;
	SexyString						mReconVersion;
	bool							mPlayedQuickplay;
	time_t							mStartTime;
	SexyString                      mDetails;
	SexyString                      mState;

public:
	LawnApp();
	virtual ~LawnApp();

	float							GetSpeedVal();
	bool							KillNewOptionsDialog();
	virtual void					GotFocus();
	virtual void					LostFocus();
	virtual void					InitHook();
	virtual void					WriteToRegistry();
	virtual void					ReadFromRegistry();
	virtual void					LoadingThreadProc();
	virtual void					LoadingCompleted();
	virtual void					LoadingThreadCompleted();
	virtual void					URLOpenFailed(const std::string& theURL);
	virtual void					URLOpenSucceeded(const std::string& theURL);
	virtual bool					OpenURL(const std::string& theURL, bool shutdownOnOpen);
	virtual bool					DebugKeyDown(int theKey);
	virtual void					HandleCmdLineParam(const std::string& theParamName, const std::string& theParamValue);
	void							ConfirmQuit();
	void							ConfirmCheckForUpdates() { ; }
	void							CheckForUpdates() { ; }
	void							DoUserDialog();
	void							FinishUserDialog(bool isYes);
	void							DoCreateUserDialog();
	void							DoCheatDialog();
	void							FinishCheatDialog(bool isYes);
	void							FinishCreateUserDialog(bool isYes);
	void							DoConfirmDeleteUserDialog(const SexyString& theName);
	void							FinishConfirmDeleteUserDialog(bool isYes);
	void							DoRenameUserDialog(const SexyString& theName);
	void							FinishRenameUserDialog(bool isYes);
	void							FinishNameError(int theId);
	void							FinishRestartConfirmDialog();
	void							DoConfirmSellDialog(const SexyString& theMessage);
	void							DoConfirmPurchaseDialog(const SexyString& theMessage);
	void							FinishTimesUpDialog();
	void							DoChallengePagesDialog();
	void							KillBoard();
	void							MakeNewBoard();
	void							StartPlaying();
	bool							TryLoadGame();
	void							NewGame();
	void							PreNewGame(GameMode theGameMode, bool theLookForSavedGame);
	void							StartQuickPlay();
	void							ShowGameSelector();
	void							KillGameSelector();
	void							ShowAwardScreen(AwardType theAwardType, bool theShowAchievements);
	void							KillAwardScreen();
	void							ShowSeedChooserScreen();
	void							KillSeedChooserScreen();
	void							DoHighScoreDialog();
	void							DoBackToMain(bool hasSound = false);
	void							DoConfirmBackToMain();
	void							DoNewOptions(bool theFromGameSelector, int x = -1, int y = -1);
	void							DoAdvancedOptions(bool theFromGameSelector, int x, int y);
	void							DoRegister();
	void							DoRegisterError();
	bool							CanDoRegisterDialog();
	/*inline*/ bool					WriteCurrentUserConfig();
	void							DoNeedRegisterDialog();
	void							DoContinueDialog();
	void							DoPauseDialog();
	void							FinishModelessDialogs();
	virtual Dialog*					DoDialog(int theDialogId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode);
	virtual Dialog*					DoDialogDelay(int theDialogId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode);
	virtual void					Shutdown();
	virtual void					Init();
	virtual void					Start();
	void							StartDiscord();
	virtual Dialog*					NewDialog(int theDialogId, bool isModal, const SexyString& theDialogHeader, const SexyString& theDialogLines, const SexyString& theDialogFooter, int theButtonMode);
	virtual bool					KillDialog(int theDialogId);
	virtual void					ModalOpen();
	virtual void					ModalClose();
	virtual void					PreDisplayHook();
	virtual bool					ChangeDirHook(const char* theIntendedPath);
	virtual bool					NeedRegister();
	virtual void					UpdateRegisterInfo();
	virtual void					ButtonPress(int theId);
	virtual void					ButtonDepress(int theId);
	virtual void					UpdateFrames();
	virtual bool					UpdateApp();
	/*inline*/ bool					IsAdventureMode();
	/*inline*/ bool					IsSurvivalMode();
	bool							IsContinuousChallenge();
	/*inline*/ bool					IsArtChallenge();
	bool							NeedPauseGame();
	virtual void					ShowResourceError(bool doExit = false);
	void							ToggleSlowMo();
	void							ToggleFastMo();
	void							PlayFoley(FoleyType theFoleyType);
	void							PlayFoleyPitch(FoleyType theFoleyType, float thePitch);
	void							PlaySample(int theSoundNum);
	void							FastLoad(GameMode theGameMode);
	static SexyString				GetStageString(int theLevel);
	/*inline*/ void					KillChallengeScreen();
	void							ShowChallengeScreen(ChallengePage thePage);
	ChallengeDefinition&			GetCurrentChallengeDef();
	void							CheckForGameEnd();
	virtual void					CloseRequestAsync();
	/*inline*/ bool					IsChallengeWithoutSeedBank();
	bool							CanShowSeedBankAfterSun();
	AlmanacDialog*					DoAlmanacDialog(SeedType theSeedType = SeedType::SEED_NONE, ZombieType theZombieType = ZombieType::ZOMBIE_INVALID);
	bool							KillAlmanacDialog();
	int								GetSeedsAvailable();
	Reanimation*					AddReanimation(float theX, float theY, int theRenderOrder, ReanimationType theReanimationType);
	TodParticleSystem*				AddTodParticle(float theX, float theY, int theRenderOrder, ParticleEffect theEffect);
	/*inline*/ ParticleSystemID		ParticleGetID(TodParticleSystem* theParticle);
	/*inline*/ TodParticleSystem*	ParticleGet(ParticleSystemID theParticleID);
	/*inline*/ TodParticleSystem*	ParticleTryToGet(ParticleSystemID theParticleID);
	/*inline*/ ReanimationID		ReanimationGetID(Reanimation* theReanimation);
	/*inline*/ Reanimation*			ReanimationGet(ReanimationID theReanimationID);
	/*inline*/ Reanimation*			ReanimationTryToGet(ReanimationID theReanimationID);
	void							RemoveReanimation(ReanimationID theReanimationID);
	void							RemoveParticle(ParticleSystemID theParticleID);
	StoreScreen*					ShowStoreScreen();
	void							KillStoreScreen();
	bool							HasSeedType(SeedType theSeedType);
	/*inline*/ bool					SeedTypeAvailable(SeedType theSeedType);
	bool							HasAllUpgrades();
	/*inline*/ void					EndLevel();
	inline bool						IsIceDemo() { return false; }
	/*inline*/ bool					IsShovelLevel();
	/*inline*/ bool					IsWallnutBowlingLevel();
	/*inline*/ bool					IsMiniBossLevel();
	/*inline*/ bool					IsSlotMachineLevel();
	/*inline*/ bool					IsLittleTroubleLevel();
	/*inline*/ bool					IsStormyNightLevel();
	/*inline*/ bool					IsFinalBossLevel();
	/*inline*/ bool					IsBungeeBlitzLevel();
	static /*inline*/ SeedType		GetAwardSeedForLevel(int theLevel);
	SexyString						GetCrazyDaveText(int theMessageIndex);
	/*inline*/ bool					CanShowAlmanac();
	/*inline*/ bool					IsNight();
	/*inline*/ bool					CanShowStore();
	/*inline*/ bool					HasBeatenChallenge(GameMode theGameMode);
	PottedPlant*					GetPottedPlantByIndex(int thePottedPlantIndex);
	static /*inline*/ bool			IsSurvivalNormal(GameMode theGameMode);
	static /*inline*/ bool			IsSurvivalHard(GameMode theGameMode);
	static /*inline*/ bool			IsSurvivalEndless(GameMode theGameMode);
	/*inline*/ bool					HasFinishedAdventure();
	/*inline*/ bool					IsFirstTimeAdventureMode();
	/*inline*/ bool					CanSpawnYetis();
	void							CrazyDaveEnter();
	void							UpdateCrazyDave();
	void							CrazyDaveTalkIndex(int theMessageIndex);
	void							CrazyDaveTalkMessage(const SexyString& theMessage);
	void							CrazyDaveLeave();
	void							DrawCrazyDave(Graphics* g);
	void							CrazyDaveDie();
	void							CrazyDaveStopTalking();
	void							PreloadForUser();
	int								GetNumPreloadingTasks();
	int								LawnMessageBox(int theDialogId, const SexyChar* theHeaderName, const SexyChar* theLinesName, const SexyChar* theButton1Name, const SexyChar* theButton2Name, int theButtonMode);
	virtual void					EnforceCursor();
	void							ShowCreditScreen();
	void							KillCreditScreen();
	void							ShowMiniCreditScreen();
	void							KillMiniCreditScreen();
	void							ShowAchievementScreen();
	void							KillAchievementScreen();
	void							ShowQuickPlayScreen();
	void							KillQuickPlayScreen();
	static SexyString				Pluralize(int theCount, const SexyChar* theSingular, const SexyChar* thePlural);
	int								GetNumTrophies(ChallengePage thePage);
	int								GetTotalTrophies(ChallengePage thePage);
	/*inline*/ bool					EarnedGoldTrophy();
	inline bool						IsRegistered() { return false; }
	inline bool						IsExpired() { return false; }
	inline bool						IsDRMConnected() { return false; }
	/*inline*/ bool					IsScaryPotterLevel();
	static /*inline*/ bool			IsEndlessScaryPotter(GameMode theGameMode);
	/*inline*/ bool					IsSquirrelLevel();
	/*inline*/ bool					IsIZombieLevel();
	/*inline*/ bool					CanShowZenGarden();
	static SexyString				GetMoneyString(int theAmount);
	bool							AdvanceCrazyDaveText();
	/*inline*/ bool					IsWhackAZombieLevel();
	void							BetaSubmit(bool theAskForComments);
	void							BetaRecordLevelStats();
	void							UpdatePlayTimeStats();
	void							BetaAddFile(std::list<std::string>& theUploadFileList, std::string theFileName, std::string theShortName);
	bool							CanPauseNow();
	/*inline*/ bool					IsPuzzleMode();
	/*inline*/ bool					IsChallengeMode();
	static /*inline*/ bool			IsEndlessIZombie(GameMode theGameMode);
	void							CrazyDaveDoneHanding();
	inline SexyString				GetCurrentLevelName() { return _S("Unknown"); }
	/*inline*/ int					TrophiesNeedForGoldSunflower();
	/*inline*/ int					GetCurrentChallengeIndex();
	void							LoadGroup(const char* theGroupName, int theGroupAveMsToLoad);
	void							TraceLoadGroup(const char* theGroupName, int theGroupTime, int theTotalGroupWeigth, int theTaskWeight);
	void							CrazyDaveStopSound();
	/*inline*/ bool					IsTrialStageLocked();
	/*inline*/ void					FinishZenGardenToturial();
	bool							UpdatePlayerProfileForFinishingLevel();
	bool							SaveFileExists();
	/*inline*/ bool					CanDoPinataMode();
	/*inline*/ bool					CanDoDanceMode();
	/*inline*/ bool					CanDoDaisyMode();
	virtual void					SwitchScreenMode(bool wantWindowed, bool is3d, bool force = false);
	virtual void					ToggleDebugMode();
	bool							Is3dAccel();
	void							SetCursorMode(CursorMode theCursorMode);
	static /*inline*/ void			CenterDialog(Dialog* theDialog, int theWidth, int theHeight);
	void							GetAchievement(AchievementType theAchievementType);
	void							UpdateDiscordState(SexyString def = "");
};

SexyString							LawnGetCurrentLevelName();
bool								LawnGetCloseRequest();
bool								LawnHasUsedCheatKeys();
void								BetaSubmitFunc();

extern bool (*gAppCloseRequest)();				
extern bool (*gAppHasUsedCheatKeys)();			
extern SexyString (*gGetCurrentLevelName)();

extern bool gIsPartnerBuild;
extern bool gFastMo;  
extern bool gSlowMo;  
extern LawnApp* gLawnApp;  
extern int gSlowMoCounter;  


#endif	// __LAWNAPP_H__