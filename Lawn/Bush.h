#ifndef __BUSH_H__
#define __BUSH_H__

#include "GameObject.h"

namespace Sexy
{
    class Graphics;
}
using namespace Sexy;

class Bush : public GameObject
{
public:
    float                   mPosX;
    float                   mPosY;
    float                   mVelX;
    float                   mVelY;
    float                   mScale;
    bool                    mDead;
    bool                    mNight;
    ReanimationID           mReanimID;

public:
    Bush();
    ~Bush();

    void                    BushInitialize(int theX, int theY, int mRow, bool NightMode, int ID);
    void                    Die();
    void                    Update();
    void                    Draw(Graphics* g);
    void                    AnimateBush();
    void                    PlayBushReanim(const char* theTrackName, ReanimLoopType theLoopType, int theBlendTime, float theAnimRate);

};

#endif
