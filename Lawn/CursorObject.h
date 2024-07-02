#ifndef __CURSOROBJECT_H__
#define __CURSOROBJECT_H__

#include "GameObject.h"

class CursorObject : public GameObject
{
public:
	int						mSeedBankIndex;			
	SeedType				mType;					
	SeedType				mImitaterType;			
	CursorType				mCursorType;			
	CoinID					mCoinID;				
	PlantID					mGlovePlantID;			
	PlantID					mDuplicatorPlantID;		
	PlantID					mCobCannonPlantID;		
	int						mHammerDownCounter;		
	ReanimationID			mReanimCursorID;		

public:
	CursorObject();

	void					Update();
	void					Draw(Graphics* g);
	void					Die();
};

class CursorPreview : public GameObject
{
public:
	int						mGridX;
	int						mGridY;

public:
	CursorPreview();

	void					Update();
	void					Draw(Graphics* g);
};

#endif
