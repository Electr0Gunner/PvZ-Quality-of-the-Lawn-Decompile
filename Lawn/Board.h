#ifndef __BOARD_H__
#define __BOARD_H__

#include "../ConstEnums.h"
#include "../Sexy.TodLib/DataArray.h"
#include "../SexyAppFramework/Widget.h"
#include "../SexyAppFramework/ButtonListener.h"

#include "Plant.h"
#include "Zombie.h"
#include "Projectile.h"
#include "Coin.h"
#include "LawnMower.h"
#include "GridItem.h"

using namespace Sexy;

#define MAX_GRID_SIZE_X 9
#define MAX_GRID_SIZE_Y 6
#define MAX_ZOMBIES_IN_WAVE 50
#define MAX_ZOMBIE_WAVES 100
#define MAX_GRAVE_STONES MAX_GRID_SIZE_X * MAX_GRID_SIZE_Y
#define MAX_POOL_GRID_SIZE 10
#define MAX_RENDER_ITEMS 2048
#define PROGRESS_METER_COUNTER 150

class LawnApp;
class CursorObject;
class CursorPreview;
class GameButton;
class MessageWidget;
class SeedBank;
class ToolTipWidget;
class CutScene;
class Challenge;
class Reanimation;
class DataSync;
class TodParticleSystem;
namespace Sexy
{
	class Graphics;
	class ButtonWidget;
	class WidgetManager;
	class Image;
	class MTRand;
}

class HitResult
{
public:
	void*							mObject;
	GameObjectType					mObjectType;
};

class RenderItem
{
public:
	RenderObjectType				mRenderObjectType;
	int								mZPos;
	union
	{
		GameObject*					mGameObject;
		Plant*						mPlant;
		Zombie*						mZombie;
		Coin*						mCoin;
		Projectile*					mProjectile;
		CursorPreview*				mCursorPreview;
		TodParticleSystem*			mParticleSytem;
		Reanimation*				mReanimation;
		GridItem*					mGridItem;
		LawnMower*					mMower;
		BossPart					mBossPart;
		int							mBoardGridY;
	};
};
bool RenderItemSortFunc(const RenderItem& theItem1, const RenderItem& theItem2);

struct ZombiePicker
{
	int								mZombieCount;
	int								mZombiePoints;
	int								mZombieTypeCount[NUM_ZOMBIE_TYPES];
	int								mAllWavesZombieTypeCount[NUM_ZOMBIE_TYPES];
};

/*inline*/ void						ZombiePickerInitForWave(ZombiePicker* theZombiePicker);
/*inline*/ void						ZombiePickerInit(ZombiePicker* theZombiePicker);

struct PlantsOnLawn
{
	Plant*							mUnderPlant;
	Plant*							mPumpkinPlant;
	Plant*							mFlyingPlant;
	Plant*							mNormalPlant;
};

struct BungeeDropGrid
{
	TodWeightedGridArray			mGridArray[MAX_GRID_SIZE_X * MAX_GRID_SIZE_Y];
	int								mGridArrayCount;
};

class Board : public Widget, public ButtonListener
{
public:
	LawnApp*						mApp;													
	DataArray<Zombie>				mZombies;												
	DataArray<Plant>				mPlants;												
	DataArray<Projectile>			mProjectiles;											
	DataArray<Coin>					mCoins;													
	DataArray<LawnMower>			mLawnMowers;											
	DataArray<GridItem>				mGridItems;												
	CursorObject*					mCursorObject;											
	CursorPreview*					mCursorPreview;											
	MessageWidget*					mAdvice;												
	SeedBank*						mSeedBank;												
	GameButton*						mMenuButton;											
	GameButton*						mStoreButton;											
	GameButton*						mFastButton;											
	bool							mIgnoreMouseUp;											
	ToolTipWidget*					mToolTip;												
	Font*							mDebugFont;												
	CutScene*						mCutScene;												
	Challenge*						mChallenge;												
	bool							mPaused;												
	GridSquareType					mGridSquareType[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y];		
	int								mGridCelLook[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y];			
	int								mGridCelOffset[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y][2];	
	int								mGridCelFog[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y + 1];		
	bool							mEnableGraveStones;										
	int								mSpecialGraveStoneX;									
	int								mSpecialGraveStoneY;									
	float							mFogOffset;												
	int								mFogBlownCountDown;										
	PlantRowType					mPlantRow[MAX_GRID_SIZE_Y];								
	int								mWaveRowGotLawnMowered[MAX_GRID_SIZE_Y];				
	int								mBonusLawnMowersRemaining;								
	int								mIceMinX[MAX_GRID_SIZE_Y];								
	int								mIceTimer[MAX_GRID_SIZE_Y];								
	ParticleSystemID				mIceParticleID[MAX_GRID_SIZE_Y];						
	TodSmoothArray					mRowPickingArray[MAX_GRID_SIZE_Y];						
	ZombieType						mZombiesInWave[MAX_ZOMBIE_WAVES][MAX_ZOMBIES_IN_WAVE];	
	bool							mZombieAllowed[100];									
	int								mSunCountDown;											
	int								mNumSunsFallen;											
	int								mShakeCounter;											
	int								mShakeAmountX;											
	int								mShakeAmountY;											
	BackgroundType					mBackground;											
	int								mLevel;													
	int								mSodPosition;											
	int								mPrevMouseX;											
	int								mPrevMouseY;											
	int								mSunMoney;												
	int								mNumWaves;												
	int								mMainCounter;											
	int								mEffectCounter;											
	int								mDrawCount;												
	int								mRiseFromGraveCounter;									
	int								mOutOfMoneyCounter;										
	int								mCurrentWave;											
	int								mTotalSpawnedWaves;										
	TutorialState					mTutorialState;											
	ParticleSystemID				mTutorialParticleID;									
	int								mTutorialTimer;											
	int								mLastBungeeWave;										
	int								mZombieHealthToNextWave;								
	int								mZombieHealthWaveStart;									
	int								mZombieCountDown;										
	int								mZombieCountDownStart;									
	int								mHugeWaveCountDown;										
	bool							mHelpDisplayed[NUM_ADVICE_TYPES];						
	AdviceType						mHelpIndex;												
	bool							mFinalBossKilled;										
	bool							mShowShovel;											
	int								mCoinBankFadeCount;										
	DebugTextMode					mDebugTextMode;											
	bool							mLevelComplete;											
	int								mBoardFadeOutCounter;									
	int								mNextSurvivalStageCounter;								
	int								mScoreNextMowerCounter;									
	bool							mLevelAwardSpawned;										
	int								mProgressMeterWidth;									
	int								mFlagRaiseCounter;										
	int								mIceTrapCounter;										
	int								mBoardRandSeed;											
	ParticleSystemID				mPoolSparklyParticleID;									
	ReanimationID					mFwooshID[MAX_GRID_SIZE_Y][12];							
	int								mFwooshCountDown;										
	int								mTimeStopCounter;										
	bool							mDroppedFirstCoin;										
	int								mFinalWaveSoundCounter;									
	int								mCobCannonCursorDelayCounter;							
	int								mCobCannonMouseX;										
	int								mCobCannonMouseY;										
	bool							mKilledYeti;											
	bool							mMustacheMode;											
	bool							mSuperMowerMode;										
	bool							mFutureMode;											
	bool							mPinataMode;											
	bool							mDanceMode;												
	bool							mDaisyMode;												
	bool							mSukhbirMode;											
	BoardResult						mPrevBoardResult;										
	int								mTriggeredLawnMowers;									
	int								mPlayTimeActiveLevel;									
	int								mPlayTimeInactiveLevel;									
	int								mMaxSunPlants;											
	DWORD							mStartDrawTime;											
	DWORD							mIntervalDrawTime;										
	int								mIntervalDrawCountStart;								
	float							mMinFPS;												
	int								mPreloadTime;											
	int								mGameID;												
	int								mGravesCleared;											
	int								mPlantsEaten;											
	int								mPlantsShoveled;										
	int								mCoinsCollected;										
	int								mDiamondsCollected;										
	int								mPottedPlantsCollected;									
	int								mChocolateCollected;									
	bool							mPeashootersUsed;
	bool							mCatapultsUsed;
	bool							mMushroomsUsed;
	bool							mMushroomsNCoffeeUsed;
	bool							mUsedNonMushrooms;
	bool							mCoinFaded;
	int								mAchievementCoinCount;
	int								mGargantuarsKilled;

public:
	Board(LawnApp* theApp);
	virtual ~Board();

	void							DisposeBoard();
	int								CountSunBeingCollected();
	void							DrawGameObjects(Graphics* g);
	void							ClearCursor();
	/*inline*/ bool					AreEnemyZombiesOnScreen();
	LawnMower*						FindLawnMowerInRow(int theRow);
	inline bool						SyncState(DataSync& theDataSync) { return true; }
	/*inline*/ void					SaveGame(const std::string& theFileName);
	bool							LoadGame(const std::string& theFileName);
	void							InitLevel();
	void							DisplayAdvice(const SexyString& theAdvice, MessageStyle theMessageStyle, AdviceType theHelpIndex);
	void							StartLevel();
	Plant*							AddPlant(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType = SeedType::SEED_NONE);
	Projectile*						AddProjectile(int theX, int theY, int theRenderOrder, int theRow, ProjectileType theProjectileType);
	Coin*							AddCoin(int theX, int theY, CoinType theCoinType, CoinMotion theCoinMotion);
	void							RefreshSeedPacketFromCursor();
	ZombieType						PickGraveRisingZombieType(int theZombiePoints);
	ZombieType						PickZombieType(int theZombiePoints, int theWaveIndex, ZombiePicker* theZombiePicker);
	int								PickRowForNewZombie(ZombieType theZombieType);
	/*inline*/ Zombie*				AddZombie(ZombieType theZombieType, int theFromWave);
	void							SpawnZombieWave();
	void							RemoveAllZombies();
	void							RemoveCutsceneZombies();
	void							SpawnZombiesFromGraves();
	PlantingReason					CanPlantAt(int theGridX, int theGridY, SeedType theSeedType);
	virtual void					MouseMove(int x, int y);
	virtual void					MouseDrag(int x, int y);
	virtual void					MouseDown(int x, int y, int theClickCount);
	virtual void					MouseUp(int x, int y, int theClickCount);
	virtual void					KeyChar(SexyChar theChar);
	virtual void					KeyUp(KeyCode theKey) { ; }
	virtual void					KeyDown(KeyCode theKey);
	virtual void					Update();
	void							UpdateLayers();
	virtual void					Draw(Graphics* g);
	void							DrawBackdrop(Graphics* g);
	virtual void					ButtonMouseEnter(int theId) { ; }
	virtual void					ButtonMouseLeave(int theId) { ; }
	virtual void					ButtonPress(int theId) { ; }
	/*inline*/ void					AddSunMoney(int theAmount);
	bool							TakeSunMoney(int theAmount);
	/*inline*/ bool					CanTakeSunMoney(int theAmount);
	/*inline*/ void					Pause(bool thePause);
	inline bool						MakeEasyZombieType() { return false; }
	void							TryToSaveGame();
	/*inline*/ bool					NeedSaveGame();
	/*inline*/ bool					RowCanHaveZombies(int theRow);
	void							ProcessDeleteQueue();
	bool							ChooseSeedsOnCurrentLevel();
	int								GetNumSeedsInBank();
	/*inline*/ bool					StageIsNight();
	/*inline*/ bool					StageHasPool();
	/*inline*/ bool					StageHas6Rows();
	/*inline*/ bool					StageHasFog();
	bool							StageHasGraveStones();
	int								PixelToGridX(int theX, int theY);
	int								PixelToGridY(int theX, int theY);
	/*inline*/ int					GridToPixelX(int theGridX, int theGridY);
	int								GridToPixelY(int theGridX, int theGridY);
	/*inline*/ int					PixelToGridXKeepOnBoard(int theX, int theY);
	/*inline*/ int					PixelToGridYKeepOnBoard(int theX, int theY);
	void							UpdateGameObjects();
	bool							MouseHitTest(int x, int y, HitResult* theHitResult);
	void							MouseDownWithPlant(int x, int y, int theClickCount);
	void							MouseDownWithTool(int x, int y, int theClickCount, CursorType theCursorType);
	inline void						MouseDownNormal(int x, int y, int theClickCount) { ; }
	bool							CanInteractWithBoardButtons();
	void							DrawProgressMeter(Graphics* g);
	void							UpdateToolTip();
	Plant*							GetTopPlantAt(int theGridX, int theGridY, PlantPriority thePriority);
	void							GetPlantsOnLawn(int theGridX, int theGridY, PlantsOnLawn* thePlantOnLawn);
	/*inline*/ int					CountSunFlowers();
	int								GetSeedPacketPositionX(int theIndex);
	void							AddGraveStones(int theGridX, int theCount, MTRand& theLevelRNG);
	int								GetGraveStoneCount();
	void							ZombiesWon(Zombie* theZombie = nullptr);
	void							DrawLevel(Graphics* g);
	void							DrawShovel(Graphics* g);
	void							UpdateZombieSpawning();
	void							UpdateSunSpawning();
	/*inline*/ void					ClearAdvice(AdviceType theHelpIndex);
	bool							RowCanHaveZombieType(int theRow, ZombieType theZombieType);
	/*inline*/ int					NumberZombiesInWave(int theWaveIndex);
	int								TotalZombiesHealthInWave(int theWaveIndex);
	void							DrawDebugText(Graphics* g);
	void							DrawUICoinBank(Graphics* g);
	/*inline*/ void					ShowCoinBank(int theDuration = 1000);
	void							FadeOutLevel();
	void							DrawFadeOut(Graphics* g);
	void							DrawIce(Graphics* g, int theGridY);
	bool							IsIceAt(int theGridX, int theGridY);
	/*inline*/ ZombieID				ZombieGetID(Zombie* theZombie);
	/*inline*/ Zombie*				ZombieGet(ZombieID theZombieID);
	/*inline*/ Zombie*				ZombieTryToGet(ZombieID theZombieID);
	void							DrawDebugObjectRects(Graphics* g);
	void							UpdateIce();
	/*inline*/ int					GetIceZPos(int theRow);
	/*inline*/ bool					CanAddBobSled();
	/*inline*/ void					ShakeBoard(int theShakeAmountX, int theShakeAmountY);
	int								CountUntriggerLawnMowers();
	bool							IterateZombies(Zombie*& theZombie);
	bool							IteratePlants(Plant*& thePlant);
	bool							IterateProjectiles(Projectile*& theProjectile);
	bool							IterateCoins(Coin*& theCoin);
	bool							IterateLawnMowers(LawnMower*& theLawnMower);
	bool							IterateParticles(TodParticleSystem*& theParticle);
	bool							IterateReanimations(Reanimation*& theReanimation);
	bool							IterateGridItems(GridItem*& theGridItem);
	/*inline*/ Zombie*				AddZombieInRow(ZombieType theZombieType, int theRow, int theFromWave);
	/*inline*/ bool					IsPoolSquare(int theGridX, int theGridY);
	void							PickZombieWaves();
	void							StopAllZombieSounds();
	/*inline*/ bool					HasLevelAwardDropped();
	void							UpdateProgressMeter();
	void							DrawUIBottom(Graphics* g);
	void							DrawUITop(Graphics* g);
	void							KillAllPlantsInRadius(int theX, int theY, int theRadius);
	Plant*							GetPumpkinAt(int theGridX, int theGridY);
	Plant*							GetFlowerPotAt(int theGridX, int theGridY);
	bool							LawnHasNocturnal();
	static bool						CanZombieSpawnOnLevel(ZombieType theZombieType, int theLevel);
	bool							IsZombieWaveDistributionOk();
	void							PickBackground();
	void							InitZombieWaves();
	void							InitSurvivalStage();
	static /*inline*/ int			MakeRenderOrder(RenderLayer theRenderLayer, int theRow, int theLayerOffset);
	void							UpdateGame();
	void							InitZombieWavesForLevel(int theForLevel);
	unsigned int					SeedNotRecommendedForLevel(SeedType theSeedType);
	void							DrawTopRightUI(Graphics* g);
	void							DrawFog(Graphics* g);
	void							UpdateFog();
	/*inline*/ int					LeftFogColumn();
	static /*inline*/ bool			IsZombieTypePoolOnly(ZombieType theZombieType);
	void							DropLootPiece(int thePosX, int thePosY, int theDropFactor);
	void							UpdateLevelEndSequence();
	LawnMower*						GetBottomLawnMower();
	bool							CanDropLoot();
	ZombieType						GetIntroducedZombieType();
	void							PickSpecialGraveStone();
	float							GetPosYBasedOnRow(float thePosX, int theRow);
	void							NextWaveComing();
	bool							BungeeIsTargetingCell(int theGridX, int theGridY);
	/*inline*/ int					PlantingPixelToGridX(int theX, int theY, SeedType theSeedType);
	/*inline*/ int					PlantingPixelToGridY(int theX, int theY, SeedType theSeedType);
	Plant*							FindUmbrellaPlant(int theGridX, int theGridY);
	void							SetTutorialState(TutorialState theTutorialState);
	void							DoFwoosh(int theRow);
	void							UpdateFwoosh();
	Plant*							SpecialPlantHitTest(int x, int y);
	void							UpdateMousePosition();
	/*inline*/ Plant*				ToolHitTestHelper(HitResult* theHitResult);
	/*inline*/ Plant*				ToolHitTest(int theX, int theY);
	bool							CanAddGraveStoneAt(int theGridX, int theGridY);
	void							UpdateGridItems();
	/*inline*/ GridItem*			AddAGraveStone(int theGridX, int theGridY);
	int								GetSurvivalFlagsCompleted();
	bool							HasProgressMeter();
	void							UpdateCursor();
	void							UpdateTutorial();
	SeedType						GetSeedTypeInCursor();
	/*inline*/ int					CountPlantByType(SeedType theSeedType);
	bool							PlantingRequirementsMet(SeedType theSeedType);
	bool							HasValidCobCannonSpot();
	bool							IsValidCobCannonSpot(int theGridX, int theGridY);
	bool							IsValidCobCannonSpotHelper(int theGridX, int theGridY);
	void							MouseDownCobcannonFire(int x, int y, int theClickCount);
	void							KillAllZombiesInRadius(int theRow, int theX, int theY, int theRadius, int theRowRange, bool theBurn, int theDamageRangeFlags);
	int								GetAllZombiesInRadius(int theRow, int theX, int theY, int theRadius, int theRowRange, int theDamageRangeFlags);
	/*inline*/ int					GetSeedBankExtraWidth();
	bool							IsFlagWave(int theWaveNumber);
	void							DrawHouseDoorTop(Graphics* g);
	void							DrawHouseDoorBottom(Graphics* g);
	Zombie*							GetBossZombie();
	bool							HasConveyorBeltSeedBank();
	/*inline*/ bool					StageHasRoof();
	void							SpawnZombiesFromPool();
	void							SpawnZombiesFromSky();
	void							PickUpTool(GameObjectType theObjectType);
	void							TutorialArrowShow(int theX, int theY);
	void							TutorialArrowRemove();
	int								CountCoinsBeingCollected();
	void							BungeeDropZombie(BungeeDropGrid* theBungeeDropGrid, ZombieType theZombieType);
	void							SetupBungeeDrop(BungeeDropGrid* theBungeeDropGrid);
	/*inline*/ void					PutZombieInWave(ZombieType theZombieType, int theWaveNumber, ZombiePicker* theZombiePicker);
	/*inline*/ void					PutInMissingZombies(int theWaveNumber, ZombiePicker* theZombiePicker);
	Rect							GetShovelButtonRect();
	void							GetZenButtonRect(GameObjectType theObjectType, Rect& theRect);
	Plant*							NewPlant(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType = SeedType::SEED_NONE);
	void							DoPlantingEffects(int theGridX, int theGridY, Plant* thePlant);
	bool							IsFinalSurvivalStage();
	void							SurvivalSaveScore();
	int								CountZombiesOnScreen();
	/*inline*/ int					GetNumWavesPerSurvivalStage();
	int								GetLevelRandSeed();
	void							AddBossRenderItem(RenderItem* theRenderList, int& theCurRenderItem, Zombie* theBossZombie);
	/*inline*/ GridItem*			GetCraterAt(int theGridX, int theGridY);
	/*inline*/ GridItem*			GetGraveStoneAt(int theGridX, int theGridY);
	/*inline*/ GridItem*			GetLadderAt(int theGridX, int theGridY);
	/*inline*/ GridItem*			AddALadder(int theGridX, int theGridY);
	/*inline*/ GridItem*			AddACrater(int theGridX, int theGridY);
	void							InitLawnMowers();
	/*inline*/ bool					IsPlantInCursor();
	void							HighlightPlantsForMouse(int theMouseX, int theMouseY);
	void							ClearFogAroundPlant(Plant* thePlant, int theSize);
	/*inline*/ void					RemoveParticleByType(ParticleEffect theEffectType);
	/*inline*/ GridItem*			GetScaryPotAt(int theGridX, int theGridY);
	void							PuzzleSaveStreak();
	/*inline*/ void					ClearAdviceImmediately();
	/*inline*/ bool					IsFinalScaryPotterStage();
	/*inline*/ void					DisplayAdviceAgain(const SexyString& theAdvice, MessageStyle theMessageStyle, AdviceType theHelpIndex);
	GridItem*						GetSquirrelAt(int theGridX, int theGridY);
	GridItem*						GetZenToolAt(int theGridX, int theGridY);
	bool							IsPlantInGoldWateringCanRange(int theMouseX, int theMouseY, Plant* thePlant);
	bool							StageHasZombieWalkInFromRight();
	void							PlaceRake();
	GridItem*						GetRake();
	/*inline*/ bool					IsScaryPotterDaveTalking();
	/*inline*/ Zombie*				GetWinningZombie();
	/*inline*/ void					ResetFPSStats();
	int								CountEmptyPotsOrLilies(SeedType theSeedType);
	GridItem*						GetGridItemAt(GridItemType theGridItemType, int theGridX, int theGridY);
	bool							ProgressMeterHasFlags();
	/*inline*/ bool					IsLastStandFinalStage();
	/*inline*/ int					GetNumWavesPerFlag();
	int								GetCurrentPlantCost(SeedType theSeedType, SeedType theImitaterType);
	/*inline*/ bool					PlantUsesAcceleratedPricing(SeedType theSeedType);
	void							FreezeEffectsForCutscene(bool theFreeze);
	void							LoadBackgroundImages();
	bool							CanUseGameObject(GameObjectType theGameObject);
	void							SetMustacheMode(bool theEnableMustache);
	int								CountCoinByType(CoinType theCoinType);
	void							SetSuperMowerMode(bool theEnableSuperMower);
	void							DrawZenWheelBarrowButton(Graphics* g, int theOffsetY);
	void							DrawZenButtons(Graphics* g);
	/*inline*/ void					OffsetYForPlanting(int& theY, SeedType theSeedType);
	void							SetDanceMode(bool theEnableDance);
	void							SetFutureMode(bool theEnableFuture);
	void							SetPinataMode(bool theEnablePinata);
	void							SetDaisyMode(bool theEnableDaisy);
	void							SetSukhbirMode(bool theEnableSukhbir);
	bool							MouseHitTestPlant(int x, int y, HitResult* theHitResult);
	
	/*inline*/ Reanimation*			CreateRakeReanim(float theRakeX, float theRakeY, int theRenderOrder);
	void							CompleteEndLevelSequenceForSaving();
	void							RemoveZombiesForRepick();
	int								GetGraveStonesCount();
	/*inline*/ bool					IsSurvivalStageWithRepick();
	/*inline*/ bool					IsLastStandStageWithRepick();
	void							DoTypingCheck(KeyCode theKey);
	int								CountZombieByType(ZombieType theZombieType);
	static /*inline*/ bool			IsZombieTypeSpawnedOnly(ZombieType theZombieType);
	void							DrawHealthbar(Graphics* g, Rect rect, Color maxColor, int maxNumber, Color baseColor, int baseNumber, int barWidth, int barHeight, int barOffsetX, int barOffsetY, Color textColor, Font* textFont, int textOffsetY, Color textOutlineColor, int textOutlineOffset, bool drawBarOutline);
};
extern bool gShownMoreSunTutorial;

int									GetRectOverlap(const Rect& rect1, const Rect& rect2);
bool								GetCircleRectOverlap(int theCircleX, int theCircleY, int theRadius, const Rect& theRect);
/*inline*/ void						BoardInitForPlayer();

#endif // __BOARD_H__