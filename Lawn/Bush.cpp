#include "Bush.h"
#include "Board.h"
#include "../LawnApp.h"
#include "../Resources.h"
#include "../GameConstants.h"
#include "System/PlayerInfo.h"
#include "../Sexy.TodLib/TodFoley.h"
#include "../Sexy.TodLib/TodDebug.h"
#include "../Sexy.TodLib/Reanimator.h"
#include "../Sexy.TodLib/Attachment.h"

Bush::Bush()
{
}

Bush::~Bush()
{
}

const ReanimationType BushReanims[] = { ReanimationType::REANIM_BUSH3,
                                        ReanimationType::REANIM_BUSH5,
                                        ReanimationType::REANIM_BUSH4,
                                        ReanimationType::REANIM_BUSH3_NIGHT,
                                        ReanimationType::REANIM_BUSH5_NIGHT,
                                        ReanimationType::REANIM_BUSH4_NIGHT };

//0x42FF60
void Bush::BushInitialize(int theX, int theY, int mRow, bool NightMode, int ID)
{
    int id = (ID + 3) % 3;
    if (NightMode)
        id += 3;

    mDead = false;
    mScale = 1.0f;
    
    mReanimID = REANIMATIONID_NULL;
    mRenderOrder = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_ZOMBIE, mRow + 1, 8 * abs(mRow + 1));
    Reanimation* aBodyReanim = mApp->AddReanimation(theX, theY, mRenderOrder, BushReanims[id]);
    if (ID == 4) {
        aBodyReanim->OverrideScale(1.2f, 1.3f);
    }
    mReanimID = mApp->ReanimationGetID(aBodyReanim);
    aBodyReanim->PlayReanim("base bush", REANIM_PLAY_ONCE_AND_HOLD, 1, 12.0f);
}

void Bush::AnimateBush()
{


    PlayBushReanim("anim_rustle", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 10, RandRangeFloat(9.0f, 14.0f));
}

void Bush::PlayBushReanim(const char* theTrackName, ReanimLoopType theLoopType, int theBlendTime, float theAnimRate)
{
    Reanimation* aBodyReanim = mApp->ReanimationTryToGet(mReanimID);
    if (aBodyReanim == nullptr)
        return;

    aBodyReanim->PlayReanim(theTrackName, theLoopType, theBlendTime, theAnimRate);
}

//0x432DD0
void Bush::Die()
{
    mDead = true;
    mApp->RemoveReanimation(mReanimID);
}

void Bush::Update()
{
    mApp->ReanimationGet(mReanimID)->Update();
}

void Bush::Draw(Graphics* g) {
    Graphics aBushGraphics(*g);
    mApp->ReanimationGet(mReanimID)->Draw(&aBushGraphics);
}