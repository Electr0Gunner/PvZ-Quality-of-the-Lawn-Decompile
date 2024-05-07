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
#include "../Sexy.TodLib/EffectSystem.h"

Bush::Bush()
{
}

Bush::~Bush()
{
    AttachmentDie(mAttachmentID);
}

const ReanimationType BushReanims[] = { ReanimationType::REANIM_BUSH3,
                                        ReanimationType::REANIM_BUSH5,
                                        ReanimationType::REANIM_BUSH4,
                                        ReanimationType::REANIM_BUSH3_NIGHT,
                                        ReanimationType::REANIM_BUSH5_NIGHT,
                                        ReanimationType::REANIM_BUSH4_NIGHT };

//0x42FF60
void Bush::BushInitialize(int theX, int theY, int ID, int mRow, bool NightMode)
{
    int id = (ID + 3) % 3;
    if (NightMode)
        id += 3;

    mPosX = theX;
    mPosY = theY;
    mDead = false;
    mScale = 1.0f;
    mReanimID = REANIMATIONID_NULL;
    mAttachmentID = AttachmentID::ATTACHMENTID_NULL;
    mRenderOrder = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_ZOMBIE, mRow, 8 * abs(mRow));
    Reanimation* aBodyReanim = mApp->mEffectSystem->mReanimationHolder->AllocReanimation(theX, theY, mRenderOrder, BushReanims[id]);
    aBodyReanim->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD;
    aBodyReanim->mAnimRate = 12.0f;
    aBodyReanim->PlayReanim("anim_idle", REANIM_PLAY_ONCE_AND_HOLD, 1, 12.0f);
    mReanimID = mApp->ReanimationGetID(aBodyReanim);
    AttachReanim(mAttachmentID, aBodyReanim, 0, 0);
}

void Bush::AnimateBush()
{
    Reanimation* mReanim = mApp->ReanimationTryToGet(mReanimID);
    TOD_ASSERT(mReanim);
    if(mReanim)
        mReanim->PlayReanim("anim_rustle", ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD, 1, RandRangeFloat(9.0f, 14.0f));
}

//0x432DD0
void Bush::Die()
{
    mDead = true;
    AttachmentDie(mAttachmentID);
}

void Bush::Draw(Graphics* g) {
    if (mAttachmentID != AttachmentID::ATTACHMENTID_NULL)
    {
        Graphics theAttachmentGraphic(*g);
        MakeParentGraphicsFrame(&theAttachmentGraphic);
        AttachmentDraw(mAttachmentID, &theAttachmentGraphic, false);
    }
}