#ifndef __TRAIL_H__
#define __TRAIL_H__

#include "TodParticle.h"

#define MAX_TRAIL_TRIANGLES 38

enum TrailType
{
	TRAIL_NONE = -1,
	TRAIL_ICE,
	NUM_TRAILS
};

enum TrailTracks
{
	TRACK_WIDTH_OVER_LENGTH,
	TRACK_WIDTH_OVER_TIME,
	TRACK_ALPHA_OVER_LENGTH,
	TRACK_ALPHA_OVER_TIME,
	NUM_TRAIL_TRACKS
};

enum TrailFlags
{
	TRAIL_FLAG_LOOPS = 0
};

class TrailParams
{
public:
	TrailType				mTrailType;
	const char*				mTrailFileName;
};

extern int gTrailParamArraySize;  
extern TrailParams* gTrailParamArray;  

extern TrailParams gLawnTrailArray[(int)TrailType::NUM_TRAILS];  

class TrailDefinition
{
public:
	Image*					mImage;
	int						mMaxPoints;
	float					mMinPointDistance;
	int						mTrailFlags;
	FloatParameterTrack		mTrailDuration;
	FloatParameterTrack		mWidthOverLength;
	FloatParameterTrack		mWidthOverTime;
	FloatParameterTrack		mAlphaOverLength;
	FloatParameterTrack		mAlphaOverTime;

public:
	TrailDefinition();
	~TrailDefinition();
};
bool						TrailLoadADef(TrailDefinition* theTrailDef, const char* theTrailFileName);
void						TrailLoadDefinitions(TrailParams* theTrailParamArray, int theTrailParamArraySize);
void						TrailFreeDefinitions();

extern int gTrailDefCount;  
extern TrailDefinition* gTrailDefArray;  

// #################################################################################################### //

class TrailPoint
{
public:
	SexyVector2				aPos;

public:
	TrailPoint();
};

class TrailHolder;

class Trail
{
public:
	TrailPoint				mTrailPoints[20];		
	int						mNumTrailPoints;		
	bool					mDead;					
	int						mRenderOrder;			
	int						mTrailAge;				
	int						mTrailDuration;			
	TrailDefinition*		mDefinition;			
	TrailHolder*			mTrailHolder;			
	float					mTrailInterp[4];		
	SexyVector2				mTrailCenter;			
	bool					mIsAttachment;			
	Color					mColorOverride;			

public:
	Trail();

	void					Update();
	void					Draw(Graphics* g);
	void					AddPoint(float x, float y);
	bool					GetNormalAtPoint(int nIndex, SexyVector2& theNormal);
};

class TrailHolder
{
public:
	DataArray<Trail>		mTrails;

public:
	TrailHolder() { ; }
	~TrailHolder() { DisposeHolder(); }

	void					InitializeHolder();
	void					DisposeHolder();
	Trail*					AllocTrail(int theRenderOrder, TrailType theTrailType);
	Trail*					AllocTrailFromDef(int theRenderOrder, TrailDefinition* theDefinition);
};

#endif
