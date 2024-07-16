#include "ChallengePagesDialog.h"
#include "../../LawnApp.h"
#include "ChallengeScreen.h"
#include "../../Resources.h"
#include "../../GameConstants.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "../System/PlayerInfo.h"
#include "GameButton.h"

ChallengePagesDialog::ChallengePagesDialog(LawnApp* theApp) : LawnDialog(theApp, Dialogs::DIALOG_CHALLENGE_PAGES, true, _S("Page Selection"), _S(""), _S("Close Page Selection"), Dialog::BUTTONS_FOOTER)
{
	mApp = theApp;

	CalcSize(150, 350);
	mClipRect = Rect(45, 120, mWidth - 100, mHeight - 230);

	mScrollAmount = 0;
	mScrollPosition = 0;

	mSlider = new Slider(IMAGE_CHALLENGE_SLIDERSLOT, IMAGE_OPTIONS_SLIDERKNOB2, -1, this);
	mSlider->SetValue(max(0.0, min(mMaxScrollPosition, mScrollPosition)));
	mSlider->mHorizontal = false;
	mSlider->Resize(mWidth - 70, mClipRect.mY, 20, mClipRect.mHeight);
	mSlider->mThumbOffsetX = -1;
	mSlider->mNoDraw = true;

	for (int aPage = 0; aPage < MAX_CHALLENGE_PAGES; aPage++)
	{
		LawnStoneButton* aPageButton = MakeButton(aPage, this, mApp->mChallengeScreen->GetPageTitle((ChallengePage)aPage));
		mPageButtons[aPage] = aPageButton;
		aPageButton->mBtnNoDraw = true;
	}
}

ChallengePagesDialog::~ChallengePagesDialog()
{
	delete mSlider;
	for (LawnStoneButton* aPageButton : mPageButtons) delete aPageButton;
}

void ChallengePagesDialog::AddedToManager(WidgetManager* theWidgetManager)
{
	LawnDialog::AddedToManager(theWidgetManager);
	AddWidget(mSlider);
	for (LawnStoneButton* aPageButton : mPageButtons) AddWidget(aPageButton);
}

void ChallengePagesDialog::RemovedFromManager(WidgetManager* theWidgetManager)
{
	LawnDialog::RemovedFromManager(theWidgetManager);
	RemoveWidget(mSlider);
	for (LawnStoneButton* aPageButton : mPageButtons) RemoveWidget(aPageButton);
}

void ChallengePagesDialog::Draw(Graphics* g)
{
	LawnDialog::Draw(g);
	g->SetClipRect(mClipRect);
	int totalHidden = 0;
	int maxScroll = 0;
	for (int aPage = 0; aPage < MAX_CHALLENGE_PAGES; aPage++)
	{
		bool isSelected = aPage == mApp->mChallengeScreen->mPageIndex;
		LawnStoneButton* aPageButton = mPageButtons[aPage];
		aPageButton->mDisabled = isSelected || !mClipRect.Contains(mWidgetManager->mLastMouseX - mX, mWidgetManager->mLastMouseY - mY);
		aPageButton->mVisible = mApp->mChallengeScreen->IsPageUnlocked((ChallengePage)aPage);
		int aHeight = 46;
		int aOffset = 3;
		mPageButtonRects[aPage] = Rect(mClipRect.mX, mClipRect.mY + ((aPage - totalHidden) * (aHeight + aOffset)) - mScrollPosition, mClipRect.mWidth - (mSlider->mVisible ? mSlider->mWidth : 0), aHeight);
		Rect aPageButtonRect = mPageButtonRects[aPage];
		aPageButton->Resize(aPageButtonRect);
		if (aPageButton->mVisible)
		{
			DrawStoneButton(g, aPageButtonRect.mX, aPageButtonRect.mY, aPageButtonRect.mWidth, aPageButtonRect.mHeight,
				(aPageButton->mIsDown && aPageButton->mIsOver && !aPageButton->mDisabled) ^ aPageButton->mInverted, aPageButton->mIsOver, aPageButton->mLabel, isSelected ? 175 : 255);
			maxScroll += aHeight + aOffset;
		}
		else
		{
			totalHidden++;
		}
	}
	mMaxScrollPosition = max(0, maxScroll - mClipRect.mHeight);
	g->ClearClipRect();
	mSlider->SliderDraw(g);
}

void ChallengePagesDialog::Update()
{
	mScrollPosition = ClampFloat(mScrollPosition += mScrollAmount * (mBaseScrollSpeed + abs(mScrollAmount) * mScrollAccel), 0, mMaxScrollPosition);
	mScrollAmount *= (1.0f - mScrollAccel);
	mSlider->SetValue(max(0.0, min(mMaxScrollPosition, mScrollPosition)) / mMaxScrollPosition);
	mSlider->mVisible = mMaxScrollPosition != 0;
}

void ChallengePagesDialog::ButtonDepress(int theId)
{
	if (theId == Dialog::ID_OK)
	{
		mApp->KillDialog(Dialogs::DIALOG_CHALLENGE_PAGES);
		mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
	}
	else
	{
		mApp->mChallengeScreen->mPageIndex = (ChallengePage)theId;
		mApp->mChallengeScreen->mSlider->SetValue(0);
		mApp->mChallengeScreen->mScrollPosition = 0;
		mApp->mChallengeScreen->UpdateButtons();
		for (int aPage = 0; aPage < MAX_CHALLENGE_PAGES; aPage++)
			mPageButtons[aPage]->mIsOver = false;
		mApp->SetCursor(CURSOR_POINTER);
	}
}

void ChallengePagesDialog::SliderVal(int theId, double theVal)
{
	switch (theId)
	{
	case -1:
		mScrollPosition = theVal * mMaxScrollPosition;
		break;
	}
}

void ChallengePagesDialog::MouseWheel(int theDelta)
{
	mScrollAmount -= mBaseScrollSpeed * theDelta;
	mScrollAmount -= mScrollAmount * mScrollAccel;
}

void ChallengePagesDialog::KeyDown(KeyCode theKey)
{
	if (theKey == KeyCode::KEYCODE_ESCAPE)
	{
		mApp->KillDialog(Dialogs::DIALOG_CHALLENGE_PAGES);
		mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
	}
}