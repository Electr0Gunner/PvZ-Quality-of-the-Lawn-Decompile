#ifndef __SEEDPACKET_H__
#define __SEEDPACKET_H__

#include "GameObject.h"
#include "../GameConstants.h"

constexpr const int SLOT_MACHINE_TIME = 400;
constexpr const int CONVEYOR_SPEED = 4;

class HitResult;
class SeedPacket : public GameObject
{
public:
    int                 mRefreshCounter;                            
    int                 mRefreshTime;                               
    int                 mIndex;                                     
    int                 mOffsetX;                                   
    SeedType            mPacketType;                                
    SeedType            mImitaterType;                              
    int                 mSlotMachineCountDown;                      
    SeedType            mSlotMachiningNextSeed;                     
    float               mSlotMachiningPosition;                     
    bool                mActive;                                    
    bool                mRefreshing;                                
    int                 mTimesUsed;                                 

public:
    SeedPacket();

    void                Update();
    void                Draw(Graphics* g);
    void                MouseDown(int x, int y, int theClickCount);
    bool                MouseHitTest(int theX, int theY, HitResult* theHitResult);
    void                Deactivate();
    void                Activate();
    /*inline*/ void     SetActivate(bool theActivate);
    void                PickNextSlotMachineSeed();
    void                WasPlanted();
    /*inline*/ void     SlotMachineStart();
    void                FlashIfReady();
    bool                CanPickUp();
    void                SetPacketType(SeedType theSeedType, SeedType theImitaterType = SeedType::SEED_NONE);
};

class SeedBank : public GameObject
{
public:
    int				    mNumPackets;                    
    SeedPacket		    mSeedPackets[SEEDBANK_MAX];     
    int				    mCutSceneDarken;                
    int				    mConveyorBeltCounter;           

public:
    SeedBank();

    void			    Draw(Graphics* g);
    bool			    MouseHitTest(int x, int y, HitResult* theHitResult);
    inline void		    Move(int x, int y) { mX = x; mY = y; }
    bool			    ContainsPoint(int theX, int theY);
    void			    AddSeed(SeedType theSeedType, bool thePlaceOnLeft = false);
    void			    RemoveSeed(int theIndex);
    int				    GetNumSeedsOnConveyorBelt();
    /*inline*/ int		CountOfTypeOnConveyorBelt(SeedType theSeedType);
    void			    UpdateConveyorBelt();
    void			    UpdateWidth();
    void			    RefreshAllPackets();
};

void				    SeedPacketDrawSeed(Graphics* g, float x, float y, SeedType theSeedType, SeedType theImitaterType, float theOffsetX, float theOffsetY, float theScale);
void				    DrawSeedPacket(Graphics* g, float x, float y, SeedType theSeedType, SeedType theImitaterType, float thePercentDark, int theGrayness, bool theDrawCost, bool theUseCurrentCost);


#endif