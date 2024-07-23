#pragma once

#include <string>
#include "GameObject.h"

#define MAX_MAGNET_ITEMS 5

enum PlantSubClass
{
    SUBCLASS_NORMAL = 0,
    SUBCLASS_SHOOTER = 1
};

enum PlantWeapon
{
    WEAPON_PRIMARY,
    WEAPON_SECONDARY
};

enum PlantOnBungeeState
{
    NOT_ON_BUNGEE,
    GETTING_GRABBED_BY_BUNGEE,
    RISING_WITH_BUNGEE
};

enum PlantState
{
    STATE_NOTREADY,
    STATE_READY,
    STATE_DOINGSPECIAL,
    STATE_SQUASH_LOOK,
    STATE_SQUASH_PRE_LAUNCH,
    STATE_SQUASH_RISING,
    STATE_SQUASH_FALLING,
    STATE_SQUASH_DONE_FALLING,
    STATE_GRAVEBUSTER_LANDING,
    STATE_GRAVEBUSTER_EATING,
    STATE_CHOMPER_BITING,
    STATE_CHOMPER_BITING_GOT_ONE,
    STATE_CHOMPER_BITING_MISSED,
    STATE_CHOMPER_DIGESTING,
    STATE_CHOMPER_SWALLOWING,
    STATE_POTATO_RISING,
    STATE_POTATO_ARMED,
    STATE_POTATO_MASHED,
    STATE_SPIKEWEED_ATTACKING,
    STATE_SPIKEWEED_ATTACKING_2,
    STATE_SCAREDYSHROOM_LOWERING,
    STATE_SCAREDYSHROOM_SCARED,
    STATE_SCAREDYSHROOM_RAISING,
    STATE_SUNSHROOM_SMALL,
    STATE_SUNSHROOM_GROWING,
    STATE_SUNSHROOM_BIG,
    STATE_MAGNETSHROOM_SUCKING,
    STATE_MAGNETSHROOM_CHARGING,
    STATE_BOWLING_UP,
    STATE_BOWLING_DOWN,
    STATE_CACTUS_LOW,
    STATE_CACTUS_RISING,
    STATE_CACTUS_HIGH,
    STATE_CACTUS_LOWERING,
    STATE_TANGLEKELP_GRABBING,
    STATE_COBCANNON_ARMING,
    STATE_COBCANNON_LOADING,
    STATE_COBCANNON_READY,
    STATE_COBCANNON_FIRING,
    STATE_KERNELPULT_BUTTER,
    STATE_UMBRELLA_TRIGGERED,
    STATE_UMBRELLA_REFLECTING,
    STATE_IMITATER_MORPHING,
    STATE_ZEN_GARDEN_WATERED,
    STATE_ZEN_GARDEN_NEEDY,
    STATE_ZEN_GARDEN_HAPPY,
    STATE_MARIGOLD_ENDING,
    STATE_FLOWERPOT_INVULNERABLE,
    STATE_LILYPAD_INVULNERABLE
};

enum PLANT_LAYER
{
    PLANT_LAYER_BELOW = -1,
    PLANT_LAYER_MAIN,
    PLANT_LAYER_REANIM,
    PLANT_LAYER_REANIM_HEAD,
    PLANT_LAYER_REANIM_BLINK,
    PLANT_LAYER_ON_TOP,
    NUM_PLANT_LAYERS
};

enum PLANT_ORDER
{
    PLANT_ORDER_LILYPAD,
    PLANT_ORDER_NORMAL,
    PLANT_ORDER_PUMPKIN,
    PLANT_ORDER_FLYER,
    PLANT_ORDER_CHERRYBOMB
};

enum MagnetItemType
{
    MAGNET_ITEM_NONE,
    MAGNET_ITEM_PAIL_1,
    MAGNET_ITEM_PAIL_2,
    MAGNET_ITEM_PAIL_3,
    MAGNET_ITEM_FOOTBALL_HELMET_1,
    MAGNET_ITEM_FOOTBALL_HELMET_2,
    MAGNET_ITEM_FOOTBALL_HELMET_3,
    MAGNET_ITEM_DOOR_1,
    MAGNET_ITEM_DOOR_2,
    MAGNET_ITEM_DOOR_3,
    //MAGNET_ITEM_PROPELLER,
    MAGNET_ITEM_POGO_1,
    MAGNET_ITEM_POGO_2,
    MAGNET_ITEM_POGO_3,
    MAGNET_ITEM_JACK_IN_THE_BOX,
    MAGNET_ITEM_LADDER_1,
    MAGNET_ITEM_LADDER_2,
    MAGNET_ITEM_LADDER_3,
    MAGNET_ITEM_LADDER_PLACED,
    MAGNET_ITEM_SILVER_COIN,
    MAGNET_ITEM_GOLD_COIN,
    MAGNET_ITEM_DIAMOND,
    MAGNET_ITEM_PICK_AXE
};

class MagnetItem
{
public:
    float                   mPosX;                          
    float                   mPosY;                          
    float                   mDestOffsetX;                   
    float                   mDestOffsetY;                   
    MagnetItemType          mItemType;                      
};

class Coin;
class Zombie;
class Reanimation;
class TodParticleSystem;

class Plant : public GameObject
{
public:
    SeedType                mSeedType;                      
    int                     mPlantCol;                      
    int                     mAnimCounter;                   
    int                     mFrame;                         
    int                     mFrameLength;                   
    int                     mNumFrames;                     
    PlantState              mState;                         
    int                     mPlantHealth;                   
    int                     mPlantMaxHealth;                
    int                     mSubclass;                      
    int                     mDisappearCountdown;            
    int                     mDoSpecialCountdown;            
    int                     mStateCountdown;                
    int                     mLaunchCounter;                 
    int                     mLaunchRate;                    
    Rect                    mPlantRect;                     
    Rect                    mPlantAttackRect;               
    int                     mTargetX;                       
    int                     mTargetY;                       
    int                     mStartRow;                      
    ParticleSystemID        mParticleID;                    
    int                     mShootingCounter;               
    ReanimationID           mBodyReanimID;      // main reanimation of the plant            
    ReanimationID           mHeadReanimID;      // extra reanims for the heads of split pea and threepeater etc...
    ReanimationID           mHeadReanimID2;                 
    ReanimationID           mHeadReanimID3;                 
    ReanimationID           mBlinkReanimID;     // the blinking animation
    ReanimationID           mLightReanimID;     // reanimation of the plantern aura
    ReanimationID           mSleepingReanimID;  // the ZZZ from the sleeping plants
    int                     mBlinkCountdown;                
    int                     mRecentlyEatenCountdown;        
    int                     mEatenFlashCountdown;           
    int                     mBeghouledFlashCountdown;       
    float                   mShakeOffsetX;                  
    float                   mShakeOffsetY;                  
    MagnetItem              mMagnetItems[MAX_MAGNET_ITEMS]; 
    ZombieID                mTargetZombieID;                
    int                     mWakeUpCounter;                 
    PlantOnBungeeState      mOnBungeeState;                 
    SeedType                mImitaterType;                  
    int                     mPottedPlantIndex;              
    bool                    mAnimPing;                      
    bool                    mDead;                          
    bool                    mSquished;                      
    bool                    mIsAsleep;                      
    bool                    mIsOnBoard;                     
    bool                    mHighlighted;                   

public:
    Plant();

    void                    PlantInitialize(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType);
    void                    Update();
    void                    Animate();
    void                    Draw(Graphics* g);
    void                    MouseDown(int x, int y, int theClickCount);
    void                    DoSpecial();
    void                    Fire(Zombie* theTargetZombie, int theRow, PlantWeapon thePlantWeapon = PlantWeapon::WEAPON_PRIMARY);
    Zombie*                 FindTargetZombie(int theRow, PlantWeapon thePlantWeapon = PlantWeapon::WEAPON_PRIMARY);
    void                    Die();
    void                    UpdateProductionPlant();
    void                    UpdateShooter();
    bool                    FindTargetAndFire(int theRow, PlantWeapon thePlantWeapon = PlantWeapon::WEAPON_PRIMARY);
    void                    LaunchThreepeater();
    static Image*           GetImage(SeedType theSeedType);
    static int              GetCost(SeedType theSeedType, SeedType theImitaterType = SeedType::SEED_NONE);
    static SexyString       GetNameString(SeedType theSeedType, SeedType theImitaterType = SeedType::SEED_NONE);
    static SexyString       GetToolTip(SeedType theSeedType);
    static int              GetRefreshTime(SeedType theSeedType, SeedType theImitaterType = SeedType::SEED_NONE);
    static /*inline*/ bool  IsNocturnal(SeedType theSeedtype);
    static /*inline*/ bool  IsAquatic(SeedType theSeedType);
    static /*inline*/ bool  IsFlying(SeedType theSeedtype);
    static /*inline*/ bool  IsUpgrade(SeedType theSeedtype);
    void                    UpdateAbilities();
    void                    Squish();
    void                    DoRowAreaDamage(int theDamage, unsigned int theDamageFlags);
    int                     GetDamageRangeFlags(PlantWeapon thePlantWeapon = PlantWeapon::WEAPON_PRIMARY);
    Rect                    GetPlantRect();
    Rect                    GetPlantAttackRect(PlantWeapon thePlantWeapon = PlantWeapon::WEAPON_PRIMARY);
    Zombie*                 FindSquashTarget();
    void                    UpdateSquash();
    /*inline*/ bool         NotOnGround();
    void                    DoSquashDamage();
    void                    BurnRow(int theRow);
    void                    IceZombies();
    void                    BlowAwayFliers(int theX, int theRow);
    void                    UpdateGraveBuster();
    TodParticleSystem*      AddAttachedParticle(int thePosX, int thePosY, int theRenderPosition, ParticleEffect theEffect);
    void                    GetPeaHeadOffset(int& theOffsetX, int& theOffsetY);
    /*inline*/ bool         MakesSun();
    static void             DrawSeedType(Graphics* g, SeedType theSeedType, SeedType theImitaterType, DrawVariation theDrawVariation, float thePosX, float thePosY);
    void                    KillAllPlantsNearDoom();
    bool                    IsOnHighGround();
    void                    UpdateTorchwood();
    void                    LaunchStarFruit();
    bool                    FindStarFruitTarget();
    void                    UpdateChomper();
    void                    DoBlink();
    void                    UpdateBlink();
    void                    PlayBodyReanim(const char* theTrackName, ReanimLoopType theLoopType, int theBlendTime, float theAnimRate);
    void                    UpdateMagnetShroom();
    MagnetItem*             GetFreeMagnetItem();
    void                    DrawMagnetItems(Graphics* g);
    void                    UpdateDoomShroom();
    void                    UpdateIceShroom();
    void                    UpdatePotato();
    int                     CalcRenderOrder();
    void                    AnimateNuts();
    void                    SetSleeping(bool theIsAsleep);
    void                    UpdateShooting();
    void                    DrawShadow(Graphics* g, float theOffsetX, float theOffsetY);
    void                    UpdateScaredyShroom();
    int                     DistanceToClosestZombie();
    void                    UpdateSpikeweed();
    void                    MagnetShroomAttactItem(Zombie* theZombie);
    void                    UpdateSunShroom();
    void                    UpdateBowling();
    void                    AnimatePumpkin();
    void                    UpdateBlover();
    void                    UpdateCactus();
    void                    StarFruitFire();
    void                    UpdateTanglekelp();
    Reanimation*            AttachBlinkAnim(Reanimation* theReanimBody);
    void                    UpdateReanimColor();
    bool                    IsUpgradableTo(SeedType theUpgradedType);
    bool                    IsPartOfUpgradableTo(SeedType theUpgradedType);
    void                    UpdateCobCannon();
    void                    CobCannonFire(int theTargetX, int theTargetY);
    void                    UpdateGoldMagnetShroom();
    /*inline*/ bool         IsOnBoard();
    void                    RemoveEffects();
    void                    UpdateCoffeeBean();
    void                    UpdateUmbrella();
    void                    EndBlink();
    void                    AnimateGarlic();
    Coin*                   FindGoldMagnetTarget();
    void                    SpikeweedAttack();
    void                    ImitaterMorph();
    void                    UpdateImitater();
    void                    UpdateReanim();
    void                    SpikeRockTakeDamage();
    bool                    IsSpiky();
    static /*inline*/ void  PreloadPlantResources(SeedType theSeedType);
    /*inline*/ bool         IsInPlay();
    void                    UpdateNeedsFood() { ; }
    void                    PlayIdleAnim(float theRate);
    void                    UpdateFlowerPot();
    void                    UpdateLilypad();
    void                    GoldMagnetFindTargets();
    bool                    IsAGoldMagnetAboutToSuck();
    bool                    DrawMagnetItemsOnTop();
};

float                       PlantDrawHeightOffset(Board* theBoard, Plant* thePlant, SeedType theSeedType, int theCol, int theRow);
float                       PlantFlowerPotHeightOffset(SeedType theSeedType, float theFlowerPotScale);

class PlantDefinition
{
public:
    SeedType                mSeedType;         // identifier of the plant, ex: SEED_PEASHOOTER  
    Image**                 mPlantImage;       // leftover from beta builds, before reanims were added, for info look at beta lawn of the dead footage
    ReanimationType         mReanimationType;  // reanimation type of the plant, used in mBodyReanimID
    int                     mPacketIndex;      // unused, not much info about it, most likely used for the seed packet plant display before reanims
    int                     mSeedCost;         // the sun cost
    int                     mRefreshTime;      // time before you can plant it again !in frames!
    PlantSubClass           mSubClass;         // for Shooter plants ex: peashooter, 2 variants SUBCLASS_NORMAL and SUBCLASS_SHOOTER
    int                     mLaunchRate;       // how often the plant does its ability
    const SexyChar*         mPlantName;        // plant name
};
extern PlantDefinition gPlantDefs[SeedType::NUM_SEED_TYPES];

/*inline*/ PlantDefinition& GetPlantDefinition(SeedType theSeedType);
