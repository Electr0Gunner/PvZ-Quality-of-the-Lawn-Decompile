#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "../ConstEnums.h"
#include "GameObject.h"

class Plant;
class Zombie;
namespace Sexy
{
    class Graphics;
};
using namespace Sexy;

class ProjectileDefinition
{
public:
    ProjectileType          mProjectileType; //the type of the projectile
    int                     mImageRow; // (UNUSED) image row of the projectile used in betas
    int                     mDamage; // how much damage it deals
};
extern ProjectileDefinition gProjectileDefinition[NUM_PROJECTILES];  

class Projectile : public GameObject
{
public:
    int                     mFrame;                 
    int                     mNumFrames;             
    int                     mAnimCounter;           
    float                   mPosX;                  
    float                   mPosY;                  
    float                   mPosZ;                  
    float                   mVelX;                  
    float                   mVelY;                  
    float                   mVelZ;                  
    float                   mAccZ;                  
    float                   mShadowY;               
    bool                    mDead;                  
    int                     mAnimTicksPerFrame;     
    ProjectileMotion        mMotionType;            
    ProjectileType          mProjectileType;        
    int                     mProjectileAge;         
    int                     mClickBackoffCounter;   
    float                   mRotation;              
    float                   mRotationSpeed;         
    bool                    mOnHighGround;          
    int                     mDamageRangeFlags;      
    int                     mHitTorchwoodGridX;     
    AttachmentID            mAttachmentID;          
    float                   mCobTargetX;            
    int                     mCobTargetRow;          
    ZombieID                mTargetZombieID;        
    int                     mLastPortalX;           

public:
    Projectile();
    ~Projectile();

    void                    ProjectileInitialize(int theX, int theY, int theRenderOrder, int theRow, ProjectileType theProjectileType);
    void                    Update();
    void                    Draw(Graphics* g);
    void                    DrawShadow(Graphics* g);
    void                    Die();
    void                    DoImpact(Zombie* theZombie);
    void                    UpdateMotion();
    void                    CheckForCollision();
    Zombie*                 FindCollisionTarget();
    void                    UpdateLobMotion();
    void                    CheckForHighGround();
    bool                    CantHitHighGround();
    void                    DoSplashDamage(Zombie* theZombie);
    ProjectileDefinition&   GetProjectileDef();
    unsigned int            GetDamageFlags(Zombie* theZombie/* = nullptr*/);
    Rect                    GetProjectileRect();
    void                    UpdateNormalMotion();
    Plant*                  FindCollisionTargetPlant();
    void                    ConvertToFireball(int theGridX);
    void                    ConvertToPea(int theGridX);
    bool                    IsSplashDamage(Zombie* theZombie/* = nullptr*/);
    void                    PlayImpactSound(Zombie* theZombie);
    bool                    IsZombieHitBySplash(Zombie* theZombie);
    bool                    PeaAboutToHitTorchwood();
    bool                    GetGargantuars(int theRow, int theX, int theY, int theRadius, int theRowRange);

};

#endif
