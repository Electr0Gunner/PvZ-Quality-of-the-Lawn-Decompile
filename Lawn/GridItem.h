#ifndef __GRIDITEM_H__
#define __GRIDITEM_H__

#include "../ConstEnums.h"

#define NUM_MOTION_TRAIL_FRAMES 12

class LawnApp;
class Board;
class Zombie;
namespace Sexy
{
	class Graphics;
};

class MotionTrailFrame
{
public:
	float					mPosX;
	float					mPosY;
	float					mAnimTime;
};

class GridItem
{
public:
	LawnApp*				mApp;											
	Board*					mBoard;											
	GridItemType			mGridItemType;									
	GridItemState			mGridItemState;									
	int						mGridX;											
	int						mGridY;											
	int						mGridItemCounter;								
	int						mRenderOrder;									
	bool					mDead;											
	float					mPosX;											
	float					mPosY;											
	float					mGoalX;											
	float					mGoalY;											
	ReanimationID			mGridItemReanimID;								
	ParticleSystemID		mGridItemParticleID;							
	ZombieType				mZombieType;									
	SeedType				mSeedType;										
	ScaryPotType			mScaryPotType;									
	bool					mHighlighted;									
	int						mTransparentCounter;							
	int						mSunCount;										
	MotionTrailFrame		mMotionTrailFrames[NUM_MOTION_TRAIL_FRAMES];	
	int						mMotionTrailCount;								

public:
	GridItem();

	void					DrawLadder(Sexy::Graphics* g);
	void					DrawCrater(Sexy::Graphics* g);
	void					DrawGraveStone(Sexy::Graphics* g);
	void					GridItemDie();
	void					AddGraveStoneParticles();
	void					DrawGridItem(Sexy::Graphics* g);
	void					DrawGridItemOverlay(Sexy::Graphics* g);
	void					OpenPortal();
	void					Update();
	void					ClosePortal();
	void					DrawScaryPot(Sexy::Graphics* g);
	void					UpdateScaryPot();
	void					UpdatePortal();
	void					DrawSquirrel(Sexy::Graphics* g);
	void					UpdateRake();
	Zombie*					RakeFindZombie();
	void					DrawIZombieBrain(Sexy::Graphics* g);
	void					UpdateBrain();
	void					DrawStinky(Sexy::Graphics* g);
	/*inline*/ bool			IsOpenPortal();
};

#endif
