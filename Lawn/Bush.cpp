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
    mRenderOrder = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_ZOMBIE, mRow, 9);
    for (int reanimIndex = 0; reanimIndex <= 5; reanimIndex++) {
        ReanimatorEnsureDefinitionLoaded(BushReanims[reanimIndex], true);
    }
    Reanimation* aBodyReanim = mApp->AddReanimation(theX, theY, mRenderOrder, BushReanims[id]);
    if (ID == 3) {
        aBodyReanim->OverrideScale(1.2f, 1.3f);
    }
    mReanimID = mApp->ReanimationGetID(aBodyReanim);
    aBodyReanim->PlayReanim("base bush", REANIM_PLAY_ONCE_AND_HOLD, 0, 0);
}

void Bush::AnimateBush()
{
    Reanimation* mReanim = mApp->ReanimationTryToGet(mReanimID);
    if (mReanim)
        mReanim->PlayReanim("anim_rustle", REANIM_PLAY_ONCE_AND_HOLD, 10, RandRangeFloat(8.0f, 10.0f));
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
    Reanimation* mReanim = mApp->ReanimationTryToGet(mReanimID);
    if(mReanim)
        mReanim->Draw(&aBushGraphics);
}