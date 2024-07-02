#ifndef __LAWNMOWER_H__
#define __LAWNMOWER_H__

#include "../ConstEnums.h"
#include "../SexyAppFramework/Rect.h"

class LawnApp;
class Board;
class Zombie;
namespace Sexy
{
    class Graphics;
};
using namespace Sexy;

class LawnMower
{
public:
    LawnApp*            mApp;                   
    Board*              mBoard;                 
    float               mPosX;                  
    float               mPosY;                  
    int                 mRenderOrder;           
    int                 mRow;                   
    int                 mAnimTicksPerFrame;     
    ReanimationID       mReanimID;              
    int                 mChompCounter;          
    int                 mRollingInCounter;      
    int                 mSquishedCounter;       
    LawnMowerState      mMowerState;            
    bool                mDead;                  
    bool                mVisible;               
    LawnMowerType       mMowerType;             
    float               mAltitude;              
    MowerHeight         mMowerHeight;           
    int                 mLastPortalX;           

public:
    void                LawnMowerInitialize(int theRow);
    void                StartMower();
    void                Update();
    void                Draw(Graphics* g);
    void                Die();
    Rect                GetLawnMowerAttackRect();
    void                UpdatePool();
    void                MowZombie(Zombie* theZombie);
    void                SquishMower();
    /*inline*/ void     EnableSuperMower(bool theEnable);
};

#endif
