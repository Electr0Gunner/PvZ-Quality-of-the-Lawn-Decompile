#ifndef __ALMANACDIALOG_H__
#define __ALMANACDIALOG_H__

#include "LawnDialog.h"
#include "../../ConstEnums.h"
#include "../../SexyAppFramework/SliderListener.h"
#include "../../SexyAppFramework/Slider.h"

constexpr const float			ALMANAC_PLANT_POSITION_X		= 578.0f;
constexpr const float			ALMANAC_PLANT_POSITION_Y		= 140.0f;
constexpr const float			ALMANAC_ZOMBIE_POSITION_X		= 559.0f;
constexpr const float			ALMANAC_ZOMBIE_POSITION_Y		= 175.0f;
constexpr const int				ALMANAC_INDEXPLANT_POSITION_X	= 167;
constexpr const int				ALMANAC_INDEXPLANT_POSITION_Y	= 255;
constexpr const float			ALMANAC_INDEXZOMBIE_POSITION_X	= 535.0f;
constexpr const float			ALMANAC_INDEXZOMBIE_POSITION_Y	= 215.0f;
constexpr const int				ALMANAC_DESCRIPTION_MIN_HEIGHT	= 20;
constexpr const int				WEIRD_CHARACTERS_COUNT			= 1;

class Plant;
class Zombie;
class LawnApp;
class GameButton;
class Reanimation;
class Slider;
class AlmanacDialog : public LawnDialog, public Sexy::SliderListener
{
private:
	enum
	{
		ALMANAC_BUTTON_CLOSE,
		ALMANAC_BUTTON_PLANT,
		ALMANAC_BUTTON_ZOMBIE,
		ALMANAC_BUTTON_INDEX,
		ALMANAC_BUTTON_NEXT,
		ALMANAC_BUTTON_LAST 
	};

public:
	LawnApp*					mApp;					
	GameButton*					mCloseButton;			
	GameButton*					mIndexButton;			
	GameButton*					mPlantButton;			
	GameButton*					mZombieButton;			
	Sexy::Slider*				mPlantSlider;
	Sexy::Slider*				mZombieSlider;
	AlmanacPage					mOpenPage;				
	Reanimation*				mReanim[4];				
	SeedType					mSelectedSeed;			
	ZombieType					mSelectedZombie;		
	Plant*						mPlant;					
	Zombie*						mZombie;				
	Zombie*						mZombiePerfTest[400];	
	float						mIncrement;
	float						mScrollPosition;
	float						mScrollAmount;
	const float					mBaseScrollSpeed = 1.0f;
	const float					mScrollAccel = 0.1f;
	float						mMaxScrollPosition;
	int							mLastMouseX;
	int							mLastMouseY;
	bool						mIsOverDescription;
	int							mDescriptionLineSpacing;
	float						mDescriptionScroll;
	float						mDescriptionMaxScroll;
	float						mDescriptionOffsetScroll;
	float						mDescriptionOffsetY;
	bool						mDescriptionOverfill;
	Rect						mDescriptionRect;
	Rect						mDescriptionSliderRect;
	bool						mDescriptionSliderDragging;

public:
	AlmanacDialog(LawnApp* theApp);
	virtual ~AlmanacDialog();

	void						ClearObjects();
	virtual void				RemovedFromManager(WidgetManager* theWidgetManager);
	virtual void				AddedToManager(WidgetManager* theWidgetManager);
	void                        SliderVal(int theId, double theVal);
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
	int							ZombieIsShown(ZombieType theZombieType);
	int							ZombieHasDescription(ZombieType theZombieType);
	void						GetZombiePosition(ZombieType theZombieType, int& x, int& y);
	ZombieType					ZombieHitTest(int x, int y);
	virtual void				MouseUp(int x, int y, int theClickCount);
	virtual void				MouseDown(int x, int y, int theClickCount);
	virtual void				MouseDrag(int x, int y);
	virtual void				KeyChar(char theChar) {  }

	static ZombieType			GetZombieType(int theIndex);
	/*inline*/ void				ShowPlant(SeedType theSeedType);
	/*inline*/ void				ShowZombie(ZombieType theZombieType);
	virtual void				MouseWheel(int theDelta);

	SexyString					TranslateAndSanitize(SexyString str);
};
extern int gZombieDefeated[NUM_ZOMBIE_TYPES];

/*inline*/ void					AlmanacInitForPlayer();
/*inline*/ void					AlmanacPlayerDefeatedZombie(ZombieType theZombieType);

#endif
