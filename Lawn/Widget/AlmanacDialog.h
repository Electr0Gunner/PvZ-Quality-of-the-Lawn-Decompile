#ifndef __ALMANACDIALOG_H__
#define __ALMANACDIALOG_H__

#include "LawnDialog.h"
#include "../../ConstEnums.h"
#ifdef _DEBUG
#define NUM_ALMANAC_SEEDS NUM_SEED_TYPES
#else
#define NUM_ALMANAC_SEEDS NUM_SEED_TYPES - 4 
#endif
#define NUM_ALMANAC_ZOMBIES NUM_ZOMBIE_TYPES

constexpr const float			ALMANAC_PLANT_POSITION_X		= 874.0f;
constexpr const float			ALMANAC_PLANT_POSITION_Y		= 140.0f;
constexpr const float			ALMANAC_ZOMBIE_POSITION_X		= 920.0f;
constexpr const float			ALMANAC_ZOMBIE_POSITION_Y		= 175.0f;
constexpr const int				ALMANAC_INDEXPLANT_POSITION_X	= 157 + BOARD_OFFSET_X;
constexpr const int				ALMANAC_INDEXPLANT_POSITION_Y	= 255 + BOARD_OFFSET_Y;
constexpr const float			ALMANAC_INDEXZOMBIE_POSITION_X	= 575.0f + BOARD_OFFSET_X;
constexpr const float			ALMANAC_INDEXZOMBIE_POSITION_Y	= 225.0f + BOARD_OFFSET_Y;

class Plant;
class Zombie;
class LawnApp;
class GameButton;
class Reanimation;
class Slider;
class AlmanacDialog : public LawnDialog
{
private:
	enum
	{
		ALMANAC_BUTTON_CLOSE = 0,
		ALMANAC_BUTTON_PLANT = 1,
		ALMANAC_BUTTON_ZOMBIE = 2,
		ALMANAC_BUTTON_INDEX = 3,
		AlmanacSlider = 4, 
		ALMANAC_BUTTON_NEXT = 5,
		ALMANAC_BUTTON_LAST = 6
	};

public:
	LawnApp*					mApp;					//+0x16C
	GameButton*					mCloseButton;			//+0x170
	GameButton*					mIndexButton;			//+0x174
	GameButton*					mPlantButton;			//+0x178
	GameButton*					mZombieButton;			//+0x17C
	//Sexy::Slider* mSlider;
	AlmanacPage					mOpenPage;				//+0x180
	Reanimation*				mReanim[4];				//+0x184
	SeedType					mSelectedSeed;			//+0x194
	ZombieType					mSelectedZombie;		//+0x198
	Plant*						mPlant;					//+0x19C
	Zombie*						mZombie;				//+0x1A0
	Zombie*						mZombiePerfTest[400];	//+0x1A4
	float						mIncrement;
	float                   mScrollPosition;
	float                   mScrollAmount;

	const float             mBaseScrollSpeed = 1.0f;
	const float             mScrollAccel = 0.1f;
	
public:
	AlmanacDialog(LawnApp* theApp);
	virtual ~AlmanacDialog();

	void						ClearPlantsAndZombies();
	virtual void				RemovedFromManager(WidgetManager* theWidgetManager);
	void						SetupPlant();
	void						SetupZombie();
	void						SetPage(AlmanacPage thePage);
	virtual void				Update();
	void						DrawIndex(Graphics* g);
	void						DrawPlants(Graphics* g);
	void						DrawZombies(Graphics* g);
	virtual void				Draw(Graphics* g);
	void						GetSeedPosition(SeedType theSeedType, int& x, int& y);
	SeedType					SeedHitTest(int x, int y);
	/*inline*/ int				ZombieHasSilhouette(ZombieType theZombieType);
	int						ZombieIsShown(ZombieType theZombieType);
	int						ZombieHasDescription(ZombieType theZombieType);
	void						GetZombiePosition(ZombieType theZombieType, int& x, int& y);
	ZombieType					ZombieHitTest(int x, int y);
	virtual void				MouseUp(int x, int y, int theClickCount);
	virtual void				MouseDown(int x, int y, int theClickCount);
	virtual void				KeyChar(char theChar) {  }

	static ZombieType			GetZombieType(int theIndex);
	/*inline*/ void				ShowPlant(SeedType theSeedType);
	/*inline*/ void				ShowZombie(ZombieType theZombieType);
	virtual void				MouseWheel(int theDelta);
};
extern int gZombieDefeated[NUM_ZOMBIE_TYPES];

/*inline*/ void					AlmanacInitForPlayer();
/*inline*/ void					AlmanacPlayerDefeatedZombie(ZombieType theZombieType);

#endif
