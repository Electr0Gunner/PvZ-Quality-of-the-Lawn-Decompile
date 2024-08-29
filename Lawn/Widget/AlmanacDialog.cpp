#include "../Board.h"
#include "../Plant.h"
#include "../Zombie.h"
#include "GameButton.h"
#include "../SeedPacket.h"
#include "../../LawnApp.h"
#include "AlmanacDialog.h"
#include "../../Resources.h"
#include "../System/Music.h"
#include "../../GameConstants.h"
#include "../System/PlayerInfo.h"
#include "../System/PoolEffect.h"
#include "../System/ReanimationLawn.h"
#include "../../Sexy.TodLib/TodStringFile.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "../../SexyAppFramework/Font.h"
#include "../../SexyAppFramework/Slider.h"

int gZombieDefeated[NUM_ZOMBIE_TYPES] = { false };
const Rect cSeedClipRect = Rect(0, 90, BOARD_WIDTH, 463);
const int zombieHeight = 80;
const int zombieOffsetY = 6;
const Rect cZombieClipRect = Rect(0, zombieHeight + zombieOffsetY, BOARD_WIDTH, 474);
const int seedPacketRows = 8;
const int seedPacketHeight = SEED_PACKET_HEIGHT + 8;
const int zombieRows = 5;
const char* weirdCharacters[WEIRD_CHARACTERS_COUNT] = 
{
	"®"
};

AlmanacDialog::AlmanacDialog(LawnApp* theApp) : LawnDialog(theApp, DIALOG_ALMANAC, true, _S("Almanac"), _S(""), _S(""), BUTTONS_NONE)
{
	//mIncrement = 100;
	mApp = (LawnApp*)gSexyAppBase;
	mOpenPage = ALMANAC_PAGE_INDEX;
	mSelectedSeed = SEED_PEASHOOTER;
	mSelectedZombie = ZOMBIE_NORMAL;
	mZombie = nullptr;
	mPlant = nullptr;
	mDrawStandardBack = false;
	mScrollAmount = 0;
	mScrollPosition = 0;
	mDescriptionScroll = 0;
	mDescriptionOverfill = false;
	mDescriptionSliderDragging = false;

	TodLoadResources("DelayLoad_Almanac");
	for (int i = 0; i < LENGTH(mZombiePerfTest); i++) mZombiePerfTest[i] = nullptr;
	LawnDialog::Resize(0, 0, BOARD_WIDTH, BOARD_HEIGHT);

	mCloseButton = new GameButton(AlmanacDialog::ALMANAC_BUTTON_CLOSE);
	mCloseButton->SetLabel(_S("[CLOSE_BUTTON]"));
	mCloseButton->mButtonImage = Sexy::IMAGE_ALMANAC_CLOSEBUTTON;
	mCloseButton->mOverImage = Sexy::IMAGE_ALMANAC_CLOSEBUTTONHIGHLIGHT;
	mCloseButton->mDownImage = nullptr;
	mCloseButton->SetFont(Sexy::FONT_BRIANNETOD12);
	Color aColor = Color(42, 42, 90);
	mCloseButton->mColors[ButtonWidget::COLOR_LABEL] = aColor;
	mCloseButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = aColor;
	mCloseButton->Resize(676, 567, 89, 26);
	mCloseButton->mParentWidget = this;
	mCloseButton->mTextOffsetX = -8;
	mCloseButton->mTextOffsetY = 1;

	mIndexButton = new GameButton(AlmanacDialog::ALMANAC_BUTTON_INDEX);
	mIndexButton->SetLabel(_S("[ALMANAC_INDEX]"));
	mIndexButton->mButtonImage = Sexy::IMAGE_ALMANAC_INDEXBUTTON;
	mIndexButton->mOverImage = Sexy::IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT;
	mIndexButton->mDownImage = nullptr;
	mIndexButton->SetFont(Sexy::FONT_BRIANNETOD12);
	mIndexButton->mColors[ButtonWidget::COLOR_LABEL] = aColor;
	mIndexButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = aColor;
	mIndexButton->Resize(32, 567, 164, 26);
	mIndexButton->mParentWidget = this;
	mIndexButton->mTextOffsetX = 8;
	mIndexButton->mTextOffsetY = 1;

	mPlantButton = new GameButton(AlmanacDialog::ALMANAC_BUTTON_PLANT);
	mPlantButton->SetLabel(_S("[VIEW_PLANTS]"));
	mPlantButton->mButtonImage = Sexy::IMAGE_SEEDCHOOSER_BUTTON;
	mPlantButton->mOverImage = nullptr;
	mPlantButton->mDownImage = nullptr;
	mPlantButton->mDisabledImage = Sexy::IMAGE_SEEDCHOOSER_BUTTON_DISABLED;
	mPlantButton->mOverOverlayImage = Sexy::IMAGE_SEEDCHOOSER_BUTTON_GLOW;
	mPlantButton->SetFont(Sexy::FONT_DWARVENTODCRAFT18YELLOW);
	mPlantButton->mColors[ButtonWidget::COLOR_LABEL] = Color::White;
	mPlantButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color::White;
	mPlantButton->Resize(130, 345, 156, 42);
	mPlantButton->mTextOffsetY = -1;
	mPlantButton->mParentWidget = this;

	mZombieButton = new GameButton(AlmanacDialog::ALMANAC_BUTTON_ZOMBIE);
	mZombieButton->SetLabel(_S("[VIEW_ZOMBIES]"));
	mZombieButton->Resize(487, 345, 210, 48);
	mZombieButton->mDrawStoneButton = true;
	mZombieButton->mParentWidget = this;

	mPlantSlider = new Sexy::Slider(IMAGE_OPTIONS_SLIDERSLOT_PLANT, IMAGE_OPTIONS_SLIDERKNOB_PLANT, 0, this);
	mPlantSlider->SetValue(max(0.0, min(mMaxScrollPosition, mScrollPosition)));
	mPlantSlider->mHorizontal = false;
	mPlantSlider->Resize(10, 85, 20, 470);
	mPlantSlider->mThumbOffsetX = -5;
	mPlantSlider->mVisible = false;

	mZombieSlider = new Sexy::Slider(IMAGE_CHALLENGE_SLIDERSLOT, IMAGE_OPTIONS_SLIDERKNOB2, 0, this);
	mZombieSlider->SetValue(max(0.0, min(mMaxScrollPosition, mScrollPosition)));
	mZombieSlider->mHorizontal = false;
	mZombieSlider->Resize(10, 85, 20, 470);
	mZombieSlider->mThumbOffsetX = -1;
	mZombieSlider->mVisible = false;

	SetPage(ALMANAC_PAGE_INDEX);
	if (!mApp->mBoard || !mApp->mBoard->mPaused)
		mApp->mMusic->MakeSureMusicIsPlaying(MUSIC_TUNE_CHOOSE_YOUR_SEEDS);
}

AlmanacDialog::~AlmanacDialog()
{
	if (mCloseButton)	delete mCloseButton;
	if (mIndexButton)	delete mIndexButton;
	if (mPlantButton)	delete mPlantButton;
	if (mZombieButton)	delete mZombieButton;
	delete mPlantSlider;
	delete mZombieSlider;
	ClearObjects();
}

void AlmanacDialog::ClearObjects()
{
	if (mPlant)
	{
		mPlant->Die();
		delete mPlant;
		mPlant = nullptr;
	}
	if (mZombie)
	{
		mZombie->DieNoLoot();
		delete mZombie;
		mZombie = nullptr;
	}
	for (Zombie* &aZombie : mZombiePerfTest)
	{
		if (aZombie)
		{
			aZombie->DieNoLoot();
			delete aZombie;
		}
		aZombie = nullptr;
	}
}

void AlmanacDialog::RemovedFromManager(WidgetManager* theWidgetManager)
{
	LawnDialog::RemovedFromManager(theWidgetManager);
	ClearObjects();
	RemoveWidget(mPlantSlider);
	RemoveWidget(mZombieSlider);
}

void AlmanacDialog::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
	AddWidget(mPlantSlider);
	AddWidget(mZombieSlider);
}


void AlmanacDialog::SetupPlant()
{
	ClearObjects();

	float aPosX = ALMANAC_PLANT_POSITION_X;
	float aPosY = ALMANAC_PLANT_POSITION_Y;
	if (mSelectedSeed == SEED_TALLNUT)				aPosY += 18;
	else if (mSelectedSeed == SEED_COBCANNON)		aPosX -= 40;
	else if (mSelectedSeed == SEED_FLOWERPOT)		aPosY -= 20;
	else if (mSelectedSeed == SEED_INSTANT_COFFEE)	aPosY += 20;
	else if (mSelectedSeed == SEED_GRAVEBUSTER)		aPosY += 55;

	mPlant = new Plant();
	mPlant->mBoard = nullptr;
	mPlant->mIsOnBoard = false;
	mPlant->PlantInitialize(0, 0, mSelectedSeed, SEED_NONE);
	mPlant->mX = aPosX;
	mPlant->mY = aPosY;
}

void AlmanacDialog::SetupZombie()
{
	ClearObjects();

	mZombie = new Zombie();
	mZombie->mBoard = nullptr;
	mZombie->ZombieInitialize(0, mSelectedZombie, false, nullptr, Zombie::ZOMBIE_WAVE_UI);
	mZombie->mPosX = ALMANAC_ZOMBIE_POSITION_X;
	mZombie->mPosY = ALMANAC_ZOMBIE_POSITION_Y;
}

void AlmanacDialog::SetPage(AlmanacPage thePage)
{
	mOpenPage = thePage;
	mPlantSlider->SetValue(0.1f);
	mZombieSlider->SetValue(0.1f);

	if (mOpenPage == AlmanacPage::ALMANAC_PAGE_INDEX)
	{
		ClearObjects();

		mPlant = new Plant();
		mPlant->mBoard = nullptr;
		mPlant->mIsOnBoard = false;
		mPlant->PlantInitialize(0, 0, SeedType::SEED_SUNFLOWER, SeedType::SEED_NONE);
		mPlant->mX = ALMANAC_INDEXPLANT_POSITION_X;
		mPlant->mY = ALMANAC_INDEXPLANT_POSITION_Y;

		mZombie = new Zombie();
		mZombie->mBoard = nullptr;
		mZombie->ZombieInitialize(0, ZombieType::ZOMBIE_NORMAL, false, nullptr, Zombie::ZOMBIE_WAVE_UI);
		mZombie->mPosX = ALMANAC_INDEXZOMBIE_POSITION_X;
		mZombie->mPosY = ALMANAC_INDEXZOMBIE_POSITION_Y;

		mIndexButton->mBtnNoDraw = true;
		mPlantButton->mBtnNoDraw = false;
		mZombieButton->mBtnNoDraw = false;
	}
	else
	{
		if (mOpenPage == AlmanacPage::ALMANAC_PAGE_PLANTS)
			SetupPlant();
		else if (mOpenPage == AlmanacPage::ALMANAC_PAGE_ZOMBIES)
			SetupZombie();
		else return;

		mIndexButton->mBtnNoDraw = false;
		mPlantButton->mBtnNoDraw = true;
		mZombieButton->mBtnNoDraw = true;
	}
}

void AlmanacDialog::ShowPlant(SeedType theSeedType)
{
	mSelectedSeed = theSeedType;
	SetPage(ALMANAC_PAGE_PLANTS);
}

void AlmanacDialog::ShowZombie(ZombieType theZombieType)
{
	mSelectedZombie = theZombieType;
	SetPage(ALMANAC_PAGE_ZOMBIES);
}

void AlmanacDialog::Update()
{
	mLastMouseX = mApp->mWidgetManager->mLastMouseX;
	mLastMouseY = mApp->mWidgetManager->mLastMouseY;
	mCloseButton->Update();
	mIndexButton->Update();
	mPlantButton->Update();
	mZombieButton->Update();
	if (mPlant) mPlant->Update();
	if (mZombie) mZombie->Update();

	if (mOpenPage == ALMANAC_PAGE_PLANTS)
	{
		mMaxScrollPosition = seedPacketHeight * ((cSeedClipRect.mHeight % SEED_PACKET_HEIGHT == 0 ? 1 : 0) - (cSeedClipRect.mHeight / seedPacketHeight) + ((NUM_SEEDS_IN_CHOOSER - 2) / seedPacketRows));
		float aScrollSpeed = mBaseScrollSpeed + abs(mScrollAmount) * mScrollAccel;
		mScrollPosition = ClampFloat(mScrollPosition += mScrollAmount * aScrollSpeed, 0, mMaxScrollPosition);
		mScrollAmount *= (1.0f - mScrollAccel);
		mPlantSlider->mVisible = mMaxScrollPosition != 0;
	}
	else if (mOpenPage == ALMANAC_PAGE_ZOMBIES)
	{
		mMaxScrollPosition = zombieHeight * ((cZombieClipRect.mHeight % zombieHeight == 0 ? 1 : 0) - (cZombieClipRect.mHeight / zombieHeight) + ((NUM_ZOMBIES_IN_ALMANAC - 1) / zombieRows));
		float aScrollSpeed = mBaseScrollSpeed + abs(mScrollAmount) * mScrollAccel;
		mScrollPosition += mScrollAmount * aScrollSpeed;
		mScrollPosition = ClampFloat(mScrollPosition, 0, mMaxScrollPosition);
		mScrollAmount *= (1.0f - mScrollAccel);
		mZombieSlider->mVisible = mMaxScrollPosition != 0;
	}
	else
	{
		mScrollAmount = 0;
		mScrollPosition = 0;
		mPlantSlider->mVisible = false;
		mZombieSlider->mVisible = false;
	}

	mPlantSlider->SetValue(max(0.0, min(mMaxScrollPosition, mScrollPosition)) / mMaxScrollPosition);
	mZombieSlider->SetValue(max(0.0, min(mMaxScrollPosition, mScrollPosition)) / mMaxScrollPosition);

	for (Zombie* aZombie : mZombiePerfTest)
	{
		if (aZombie)
		{
			aZombie->Update();
		}
	}

	if (!(mPlantSlider->mIsOver || mPlantSlider->mDragging) && !(mZombieSlider->mIsOver || mZombieSlider->mDragging))
	{
		ZombieType aZombieType = ZombieHitTest(mLastMouseX, mLastMouseY);
		if (SeedHitTest(mLastMouseX, mLastMouseY) != SeedType::SEED_NONE || (aZombieType != ZOMBIE_INVALID && ZombieIsShown(aZombieType)) ||
			mCloseButton->IsMouseOver() || mIndexButton->IsMouseOver() || mPlantButton->IsMouseOver() || mZombieButton->IsMouseOver())
			mApp->SetCursor(CURSOR_HAND);
		else
			mApp->SetCursor(CURSOR_POINTER);
	}

	mApp->mPoolEffect->PoolEffectUpdate();
	MarkDirty();
}

ZombieType AlmanacDialog::GetZombieType(int theIndex)
{
	return theIndex < NUM_ZOMBIE_TYPES ? (ZombieType)theIndex : ZOMBIE_INVALID;
}

void AlmanacDialog::DrawIndex(Graphics* g)
{
	g->DrawImage(Sexy::IMAGE_ALMANAC_INDEXBACK, 0, 0);
	TodDrawString(g, _S("[SUBURBAN_ALMANAC_INDEX]"), BOARD_WIDTH / 2, 60, Sexy::FONT_HOUSEOFTERROR28, Color(220, 220, 220), DrawStringJustification::DS_ALIGN_CENTER);
	
	if (mPlant)
	{
		Graphics aPlantGraphics = Graphics(*g);
		mPlant->BeginDraw(&aPlantGraphics);
		mPlant->Draw(&aPlantGraphics);
	}
	if (mZombie)
	{
		Graphics aZombieGraphics = Graphics(*g);
		mZombie->BeginDraw(&aZombieGraphics);
		mZombie->Draw(&aZombieGraphics);
	}
}

void AlmanacDialog::DrawPlants(Graphics* g)
{
	g->DrawImage(Sexy::IMAGE_ALMANAC_PLANTBACK, 0, 0);
	TodDrawString(g, _S("[SUBURBAN_ALMANAC_PLANTS]"), BOARD_WIDTH / 2, 48, Sexy::FONT_HOUSEOFTERROR20, Color(213, 159, 43), DS_ALIGN_CENTER);
	SeedType aSeedMouseOn = SeedHitTest(mLastMouseX, mLastMouseY);
	for (SeedType aSeedType = SeedType::SEED_PEASHOOTER; aSeedType < NUM_SEEDS_IN_CHOOSER; aSeedType = (SeedType)(aSeedType + 1))
	{
		int aPosX, aPosY;
		GetSeedPosition(aSeedType, aPosX, aPosY);
		PlantDefinition& aPlantDef = GetPlantDefinition(aSeedType);
		if (!mApp->SeedTypeAvailable(aSeedType))
		{
			if (aSeedType != SeedType::SEED_IMITATER){
				g->SetClipRect(cSeedClipRect);
				g->DrawImage(Sexy::IMAGE_ALMANAC_PLANTBLANK, aPosX, aPosY);
			}
			g->ClearClipRect();
		}
		else {
			if (aSeedType == SeedType::SEED_IMITATER)
			{
				g->ClearClipRect();
				if (aSeedType == aSeedMouseOn)
					g->DrawImage(Sexy::IMAGE_ALMANAC_IMITATER, aPosX, aPosY);
				g->DrawImage(Sexy::IMAGE_ALMANAC_IMITATER, aPosX, aPosY);
			}
			else
			{
				g->SetClipRect(cSeedClipRect);
				DrawSeedPacket(g, aPosX, aPosY, aSeedType, SeedType::SEED_NONE, 0, 255, true, false);
				if (aSeedType == aSeedMouseOn)
					g->DrawImage(Sexy::IMAGE_SEEDPACKETFLASH, aPosX, aPosY);
			}
		}
	}
	g->ClearClipRect();
	if (mSelectedSeed == SeedType::SEED_LILYPAD || mSelectedSeed == SeedType::SEED_TANGLEKELP || 
		mSelectedSeed == SeedType::SEED_CATTAIL || mSelectedSeed == SeedType::SEED_SEASHROOM)
	{
		bool aNight = mSelectedSeed == SeedType::SEED_SEASHROOM;
		g->DrawImage(aNight ? Sexy::IMAGE_ALMANAC_GROUNDNIGHTPOOL : Sexy::IMAGE_ALMANAC_GROUNDPOOL, 521, 107);

		if (mApp->Is3dAccel())
		{
			g->SetClipRect(475, 0, 397, 500);
			g->mTransY -= 145;
			mApp->mPoolEffect->PoolEffectDraw(g, aNight);
			g->mTransY += 145;
			g->ClearClipRect();
		}
	}
	else
	{
		g->DrawImage(
			Plant::IsNocturnal(mSelectedSeed) || mSelectedSeed == SeedType::SEED_GRAVEBUSTER || mSelectedSeed == SeedType::SEED_PLANTERN ? Sexy::IMAGE_ALMANAC_GROUNDNIGHT :
			mSelectedSeed == SeedType::SEED_FLOWERPOT ? Sexy::IMAGE_ALMANAC_GROUNDROOF : Sexy::IMAGE_ALMANAC_GROUNDDAY,
			521, 107
		);
	}
	
	if (mPlant)
	{
		Graphics aPlantGraphics = Graphics(*g);
		mPlant->BeginDraw(&aPlantGraphics);
		mPlant->Draw(&aPlantGraphics);
	}

	g->DrawImage(Sexy::IMAGE_ALMANAC_PLANTCARD, 459, 86);
	PlantDefinition& aPlantDef = GetPlantDefinition(mSelectedSeed);
	SexyString aName = Plant::GetNameString(mSelectedSeed, SEED_NONE);
	//TodDrawString(g, to_string((int)mIncrement), 32, 32, Sexy::FONT_DWARVENTODCRAFT18YELLOW, Color::White, DS_ALIGN_CENTER);
	TodDrawString(g, aName, 617, 288, Sexy::FONT_DWARVENTODCRAFT18YELLOW, Color::White, DS_ALIGN_CENTER);
	Font* descriptionFont = Sexy::FONT_BRIANNETOD12;
	Color descriptionColor = Color(40, 50, 90);
	mDescriptionRect = Rect(485, 309, 258, 210);
	DrawStringJustification descriptionJustification = DS_ALIGN_LEFT;
	SexyString descriptionHeader = TranslateAndSanitize(StrFormat(_S("[%s_DESCRIPTION_HEADER]"), aPlantDef.mPlantName));
	TodDrawStringWrapped(g, descriptionHeader, mDescriptionRect, descriptionFont, descriptionColor, descriptionJustification);
	int textSpacing = TodDrawStringWrappedHelper(g, descriptionHeader, mDescriptionRect, descriptionFont, descriptionColor, descriptionJustification, false);
	mDescriptionRect.mY += textSpacing;
	mDescriptionRect.mHeight -= textSpacing;
	SexyString description = TranslateAndSanitize(StrFormat(_S("[%s_DESCRIPTION]"), aPlantDef.mPlantName));
	textSpacing = TodDrawStringWrappedHelper(g, description, mDescriptionRect, descriptionFont, descriptionColor, descriptionJustification, false);
	int rectHeight;
	if (mDescriptionRect.mHeight < textSpacing)
	{
		mIsOverDescription = mDescriptionRect.Contains(mLastMouseX, mLastMouseY);
		mDescriptionLineSpacing = descriptionFont->GetLineSpacing();
		int barWidth = 8;
		int barX = mDescriptionRect.mX + mDescriptionRect.mWidth - (barWidth / 2);
		mDescriptionRect.mWidth -= barWidth;
		textSpacing = TodDrawStringWrappedHelper(g, description, mDescriptionRect, descriptionFont, descriptionColor, descriptionJustification, false);
		g->SetColor(Color(143, 67, 27, 75));
		g->FillRect(Rect(barX, mDescriptionRect.mY, barWidth, mDescriptionRect.mHeight));
		mDescriptionMaxScroll = textSpacing - mDescriptionRect.mHeight;
		g->SetColor(Color(143, 67, 27));
		int barHeight = mDescriptionRect.mHeight - mDescriptionMaxScroll;
		float posY = mDescriptionScroll;
		mDescriptionOverfill = barHeight < ALMANAC_DESCRIPTION_MIN_HEIGHT;
		if (mDescriptionOverfill)
		{
			barHeight = ALMANAC_DESCRIPTION_MIN_HEIGHT;
			posY = (mDescriptionScroll / mDescriptionMaxScroll) * (mDescriptionRect.mHeight - barHeight);
		}
		mDescriptionSliderRect = Rect(barX, mDescriptionRect.mY + posY, barWidth, barHeight);
		g->FillRect(mDescriptionSliderRect);
		rectHeight = textSpacing;
	}
	else
	{
		mIsOverDescription = false;
		mDescriptionLineSpacing = 0;
		mDescriptionScroll = 0;
		mDescriptionMaxScroll = 0;
		rectHeight = mDescriptionRect.mHeight;
	}
	g->SetClipRect(mDescriptionRect);
	TodDrawStringWrapped(g, description, Rect(mDescriptionRect.mX, mDescriptionRect.mY - mDescriptionScroll, mDescriptionRect.mWidth, rectHeight), descriptionFont, descriptionColor, descriptionJustification);
	g->ClearClipRect();
	if (mSelectedSeed != SeedType::SEED_IMITATER)
	{
		SexyString aCostStr = TodReplaceString(StrFormat(_S("{KEYWORD}{COST}:{STAT} %d"), aPlantDef.mSeedCost), _S("{COST}"), _S("[COST]"));
		TodDrawStringWrapped(g, aCostStr, Rect(485, 520, 134, 50), Sexy::FONT_BRIANNETOD12, Color::White, DS_ALIGN_LEFT);

		SexyString aRechargeStr = TodReplaceString(
			_S("{KEYWORD}{WAIT_TIME}:{STAT} {WAIT_TIME_LENGTH}"), 
			_S("{WAIT_TIME_LENGTH}"),
			aPlantDef.mRefreshTime == 750 ? _S("[WAIT_TIME_SHORT]") : aPlantDef.mRefreshTime == 3000 ? _S("[WAIT_TIME_LONG]") : _S("[WAIT_TIME_VERY_LONG]")
		);
		aRechargeStr = TodReplaceString(aRechargeStr, _S("{WAIT_TIME}"), _S("[WAIT_TIME]"));
		TodDrawStringWrapped(g, aRechargeStr, Rect(600, 520, 139, 50), Sexy::FONT_BRIANNETOD12, Color(40, 50, 90), DS_ALIGN_RIGHT);
	}
}

void AlmanacDialog::DrawZombies(Graphics* g)
{
	g->DrawImage(Sexy::IMAGE_ALMANAC_ZOMBIEBACK, 0, 0);
	TodDrawString(g, _S("[SUBURBAN_ALMANAC_ZOMBIES]"), BOARD_WIDTH / 2, 54, Sexy::FONT_DWARVENTODCRAFT24, Color(0, 196, 0), DS_ALIGN_CENTER);

	ZombieType aZombieMouseOn = ZombieHitTest(mLastMouseX, mLastMouseY);
	g->SetClipRect(cZombieClipRect);
	for (int i = 0; i < NUM_ZOMBIES_IN_ALMANAC; i++)
	{
		ZombieType aZombieType = GetZombieType(i);
		int aPosX, aPosY;
		GetZombiePosition(aZombieType, aPosX, aPosY);
		ZombieDefinition aZombieDefiniton = GetZombieDefinition(aZombieType);
		if (aZombieType != ZombieType::ZOMBIE_INVALID)
		{
			if (!ZombieIsShown(aZombieType))
				g->DrawImage(Sexy::IMAGE_ALMANAC_ZOMBIEBLANK, aPosX, aPosY);
			else
			{
				g->DrawImage(Sexy::IMAGE_ALMANAC_ZOMBIEWINDOW, aPosX, aPosY);
				if (aZombieType == aZombieMouseOn)
				{
					g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
					g->SetColor(Color(255, 255, 255, 48));
					g->SetColorizeImages(true);
					g->DrawImage(Sexy::IMAGE_ALMANAC_ZOMBIEWINDOW, aPosX, aPosY);
					g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
					g->SetColorizeImages(false);
				}

				ZombieType aZombieTypeToDraw = aZombieType;
				Graphics aZombieGraphics = Graphics(*g);
				aZombieGraphics.ClipRect(aPosX + 2, aPosY + 2, 72, 72);
				aZombieGraphics.Translate(aPosX + 1, aPosY - 6);
				aZombieGraphics.mScaleX = 0.5f;
				aZombieGraphics.mScaleY = 0.5f;
				switch (aZombieType)
				{
				case ZombieType::ZOMBIE_POLEVAULTER:
					aZombieGraphics.TranslateF(2, -3);
					aZombieTypeToDraw = ZombieType::ZOMBIE_CACHED_POLEVAULTER_WITH_POLE;		break;
				case ZombieType::ZOMBIE_FLAG:			aZombieGraphics.TranslateF(2, 10);		break;
				case ZombieType::ZOMBIE_TRAFFIC_CONE:
				case ZombieType::ZOMBIE_TALLNUT_HEAD:	aZombieGraphics.TranslateF(0, 12);		break;
				case ZombieType::ZOMBIE_PAIL:			aZombieGraphics.TranslateF(0, 9);		break;
				case ZombieType::ZOMBIE_FOOTBALL:		aZombieGraphics.TranslateF(-8, 5);		break;
				case ZombieType::ZOMBIE_ZAMBONI:		aZombieGraphics.TranslateF(0, 3);		break;
				case ZombieType::ZOMBIE_DOLPHIN_RIDER:	aZombieGraphics.TranslateF(-2, -10);	break;
				case ZombieType::ZOMBIE_POGO:			aZombieGraphics.TranslateF(0, -3);		break;
				case ZombieType::ZOMBIE_GARGANTUAR:
				case ZombieType::ZOMBIE_REDEYE_GARGANTUAR:		aZombieGraphics.TranslateF(15, 17);		break;
				case ZombieType::ZOMBIE_IMP:			aZombieGraphics.TranslateF(-8, -7);		break;
				case ZombieType::ZOMBIE_BUNGEE:			aZombieGraphics.TranslateF(-4, 3);		break;
				case ZombieType::ZOMBIE_BACKUP_DANCER:	aZombieGraphics.TranslateF(-8, 5);		break;
				case ZombieType::ZOMBIE_SNORKEL:		aZombieGraphics.TranslateF(-10, 0);		break;
				case ZombieType::ZOMBIE_YETI:			aZombieGraphics.TranslateF(0, 4);		break;
				case ZombieType::ZOMBIE_CATAPULT:		aZombieGraphics.TranslateF(-24, -1);	break;
				case ZombieType::ZOMBIE_BOBSLED:		aZombieGraphics.TranslateF(0, -8);		break;
				case ZombieType::ZOMBIE_LADDER:			aZombieGraphics.TranslateF(0, -3);		break;
				}
				if (ZombieHasSilhouette(aZombieType))
				{
					aZombieGraphics.SetColor(Color(0, 0, 0, 40));
					aZombieGraphics.SetColorizeImages(true);
				}
				mApp->mReanimatorCache->DrawCachedZombie(&aZombieGraphics, 0, 0, aZombieTypeToDraw);
				aZombieGraphics.SetColorizeImages(false);

				g->DrawImage(Sexy::IMAGE_ALMANAC_ZOMBIEWINDOW2, aPosX, aPosY);
				if (aZombieType == aZombieMouseOn)
				{
					g->SetDrawMode(Graphics::DRAWMODE_ADDITIVE);
					g->SetColor(Color(255, 255, 255, 48));
					g->SetColorizeImages(true);
					g->DrawImage(Sexy::IMAGE_ALMANAC_ZOMBIEWINDOW2, aPosX, aPosY);
					g->SetDrawMode(Graphics::DRAWMODE_NORMAL);
					g->SetColorizeImages(false);
				}
			}
		}
	}
	g->ClearClipRect();
	g->DrawImage(mZombie->mZombieType == ZombieType::ZOMBIE_ZAMBONI || mZombie->mZombieType == ZombieType::ZOMBIE_BOBSLED ?
		Sexy::IMAGE_ALMANAC_GROUNDICE : Sexy::IMAGE_ALMANAC_GROUNDDAY, 518, 110);
	if (mZombie && !ZombieHasSilhouette(mZombie->mZombieType))
	{
		Graphics aZombieGraphics = Graphics(*g);
		mZombie->BeginDraw(&aZombieGraphics);
		aZombieGraphics.SetClipRect(-42, -51, 197, 187);
		switch (mZombie->mZombieType)
		{
		case ZombieType::ZOMBIE_ZAMBONI:		aZombieGraphics.TranslateF(-30, 5);		break;
		case ZombieType::ZOMBIE_GARGANTUAR:
		case ZombieType::ZOMBIE_REDEYE_GARGANTUAR:	aZombieGraphics.TranslateF(0, 40);		break;
		case ZombieType::ZOMBIE_FOOTBALL:		aZombieGraphics.TranslateF(-17, 5);		break;
		case ZombieType::ZOMBIE_BALLOON:		aZombieGraphics.TranslateF(0, -20);		break;
		case ZombieType::ZOMBIE_BUNGEE:			aZombieGraphics.TranslateF(15, 0);		break;
		case ZombieType::ZOMBIE_CATAPULT:		aZombieGraphics.TranslateF(-10, 0);		break;
		case ZombieType::ZOMBIE_BOSS:			aZombieGraphics.TranslateF(-540, -175);	break;
		}
		if (mZombie->mZombieType != ZombieType::ZOMBIE_BUNGEE && mZombie->mZombieType != ZombieType::ZOMBIE_BOSS &&
			mZombie->mZombieType != ZombieType::ZOMBIE_ZAMBONI && mZombie->mZombieType != ZombieType::ZOMBIE_CATAPULT)
			mZombie->DrawShadow(&aZombieGraphics);
		mZombie->Draw(&aZombieGraphics);
	}
	g->DrawImage(Sexy::IMAGE_ALMANAC_ZOMBIECARD, 455, 78);

	ZombieDefinition& aZombieDef = GetZombieDefinition(mSelectedZombie);
	SexyString aName = ZombieHasSilhouette(mSelectedZombie) ? _S("???") : StrFormat(_S("[%s]"), aZombieDef.mZombieName);
	TodDrawString(g, aName, 613, 362, Sexy::FONT_DWARVENTODCRAFT18GREENINSET, Color(190, 255, 235, 255), DS_ALIGN_CENTER);
	Font* descriptionFont = Sexy::FONT_BRIANNETOD12;
	for (TodStringListFormat& aFormat : gLawnStringFormats)
	{
		if (TestBit(aFormat.mFormatFlags, TodStringFormatFlag::TOD_FORMAT_HIDE_UNTIL_MAGNETSHROOM))
		{
			if (mApp->HasSeedType(SeedType::SEED_MAGNETSHROOM))
			{
				aFormat.mNewColor.mAlpha = 255;
				aFormat.mLineSpacingOffset = 0;
			}
			else
			{
				aFormat.mNewColor.mAlpha = 0;
				aFormat.mLineSpacingOffset = -(descriptionFont->GetLineSpacing() / 2);
			}
		}
	}
	Color descriptionColor = Color(40, 50, 90);
	mDescriptionRect = Rect(485, 377, 257, 160);
	if (ZombieHasDescription(mSelectedZombie))
	{
		DrawStringJustification descriptionJustification = DS_ALIGN_LEFT;
		SexyString descriptionHeader = TranslateAndSanitize(StrFormat(_S("[%s_DESCRIPTION_HEADER]"), aZombieDef.mZombieName));
		TodDrawStringWrapped(g, descriptionHeader, mDescriptionRect, descriptionFont, descriptionColor, descriptionJustification);
		int textSpacing = TodDrawStringWrappedHelper(g, descriptionHeader, mDescriptionRect, descriptionFont, descriptionColor, descriptionJustification, false);
		mDescriptionRect.mY += textSpacing;
		mDescriptionRect.mHeight -= textSpacing;
		SexyString description = TranslateAndSanitize(StrFormat(_S("[%s_DESCRIPTION]"), aZombieDef.mZombieName));
		textSpacing = TodDrawStringWrappedHelper(g, description, mDescriptionRect, descriptionFont, descriptionColor, descriptionJustification, false);
		int rectHeight;
		if (mDescriptionRect.mHeight < textSpacing)
		{
			mIsOverDescription = mDescriptionRect.Contains(mLastMouseX, mLastMouseY);
			mDescriptionLineSpacing = descriptionFont->GetLineSpacing();
			int barWidth = 8;
			int barX = mDescriptionRect.mX + mDescriptionRect.mWidth - (barWidth / 2);
			mDescriptionRect.mWidth -= barWidth;
			textSpacing = TodDrawStringWrappedHelper(g, description, mDescriptionRect, descriptionFont, descriptionColor, descriptionJustification, false);
			g->SetColor(Color(95, 97, 129, 75));
			g->FillRect(Rect(barX, mDescriptionRect.mY, barWidth, mDescriptionRect.mHeight));
			mDescriptionMaxScroll = textSpacing - mDescriptionRect.mHeight;
			g->SetColor(Color(95, 97, 129));
			int barHeight = mDescriptionRect.mHeight - mDescriptionMaxScroll;
			float posY = mDescriptionScroll;
			mDescriptionOverfill = barHeight < ALMANAC_DESCRIPTION_MIN_HEIGHT;
			if (mDescriptionOverfill)
			{
				barHeight = ALMANAC_DESCRIPTION_MIN_HEIGHT;
				posY = (mDescriptionScroll / mDescriptionMaxScroll) * (mDescriptionRect.mHeight - barHeight);
			}
			mDescriptionSliderRect = Rect(barX, mDescriptionRect.mY + posY, barWidth, barHeight);
			g->FillRect(mDescriptionSliderRect);
			rectHeight = textSpacing;
		}
		else
		{
			mIsOverDescription = false;
			mDescriptionLineSpacing = 0;
			mDescriptionScroll = 0;
			mDescriptionMaxScroll = 0;
			rectHeight = mDescriptionRect.mHeight;
		}
		g->SetClipRect(mDescriptionRect);
		TodDrawStringWrapped(g, description, Rect(mDescriptionRect.mX, mDescriptionRect.mY - mDescriptionScroll, mDescriptionRect.mWidth, rectHeight), descriptionFont, descriptionColor, descriptionJustification);
		g->ClearClipRect();
	}
	else
	{
		TodDrawStringWrapped(g, _S("[NOT_ENCOUNTERED_YET]"), mDescriptionRect, descriptionFont, descriptionColor, DS_ALIGN_CENTER_VERTICAL_MIDDLE);
	}
}

void AlmanacDialog::Draw(Graphics* g)
{
	g->SetLinearBlend(true);
	if (mOpenPage == AlmanacPage::ALMANAC_PAGE_INDEX) 
		DrawIndex(g);
	else if (mOpenPage == AlmanacPage::ALMANAC_PAGE_PLANTS)
		DrawPlants(g);
	else if (mOpenPage == AlmanacPage::ALMANAC_PAGE_ZOMBIES)
		DrawZombies(g);

	for (Zombie* aZombie : mZombiePerfTest)
	{
		if (aZombie)
		{
			Graphics aTestGraphics = Graphics(*g);
			aZombie->Draw(&aTestGraphics);
		}
	}

	mCloseButton->Draw(g);
	mIndexButton->Draw(g);
	mPlantButton->Draw(g);
	mZombieButton->Draw(g);
}

void AlmanacDialog::GetSeedPosition(SeedType theSeedType, int& x, int& y)
{
	SeedType aPlantIndex = theSeedType;
	if (aPlantIndex > SeedType::SEED_IMITATER)
		aPlantIndex = (SeedType)(aPlantIndex - 1);

	if (aPlantIndex == SeedType::SEED_IMITATER)
		x = 20, y = 23;
	else
	{
		int aFinalSeedType = aPlantIndex;
		int width = SEED_PACKET_WIDTH + 2;
		int offsetY = 14;
		x = aFinalSeedType % seedPacketRows * width + (width / 2);
		y = aFinalSeedType / seedPacketRows * seedPacketHeight + (seedPacketHeight + offsetY) - mScrollPosition;
	}
}

SeedType AlmanacDialog::SeedHitTest(int x, int y)
{
	if (mMouseVisible && mOpenPage == AlmanacPage::ALMANAC_PAGE_PLANTS)
	{
		for (SeedType aSeedType = SeedType::SEED_PEASHOOTER; aSeedType < NUM_SEEDS_IN_CHOOSER; aSeedType = (SeedType)(aSeedType + 1))
		{
			PlantDefinition& aPlantDef = GetPlantDefinition(aSeedType);
			if (mApp->SeedTypeAvailable(aSeedType))
			{
				int aSeedX, aSeedY;
				GetSeedPosition(aSeedType, aSeedX, aSeedY);
				Rect aSeedRect = aSeedType != SeedType::SEED_IMITATER ? Rect(aSeedX, aSeedY, SEED_PACKET_WIDTH, SEED_PACKET_HEIGHT) : Rect(aSeedX, aSeedY, IMAGE_ALMANAC_IMITATER->mWidth, IMAGE_ALMANAC_IMITATER->mHeight);
				if ((cSeedClipRect.Contains(x, y) || aSeedType == SeedType::SEED_IMITATER) && aSeedRect.Contains(x, y))
				{
					return aSeedType;
				}
			}
		}
	}
	return SeedType::SEED_NONE;
}

int AlmanacDialog::ZombieHasSilhouette(ZombieType theZombieType)
{
	if (theZombieType != ZombieType::ZOMBIE_YETI || mApp->CanSpawnYetis())
		return false;

	return mApp->HasFinishedAdventure() || mApp->mPlayerInfo->mLevel > GetZombieDefinition(ZombieType::ZOMBIE_YETI).mStartingLevel;
}

int AlmanacDialog::ZombieIsShown(ZombieType theZombieType)
{
	if (mApp->IsTrialStageLocked() && theZombieType > ZombieType::ZOMBIE_SNORKEL)
		return false;

	if (theZombieType == ZombieType::ZOMBIE_YETI)
		return mApp->CanSpawnYetis() || ZombieHasSilhouette(ZombieType::ZOMBIE_YETI);

	if (theZombieType <= ZombieType::ZOMBIE_BOSS)
	{
		if (mApp->HasFinishedAdventure())
			return true;

		int aLevel = mApp->mPlayerInfo->mLevel;
		int aStart = GetZombieDefinition(theZombieType).mStartingLevel;
		return aStart <= aLevel && (aStart != aLevel || !Board::IsZombieTypeSpawnedOnly(theZombieType) || gZombieDefeated[theZombieType]);
	}
	else if (theZombieType > ZombieType::ZOMBIE_BOSS)
	{
		return true;
	}
	return false;
}

int AlmanacDialog::ZombieHasDescription(ZombieType theZombieType)
{
	int aLevel = mApp->mPlayerInfo->mLevel;
	int aStart = GetZombieDefinition(theZombieType).mStartingLevel;

	if (theZombieType == ZombieType::ZOMBIE_YETI)
	{
		if (!mApp->CanSpawnYetis())
			return false;
		if (mApp->mPlayerInfo->mFinishedAdventure >= 2)
			return true;
	}
	else if (mApp->HasFinishedAdventure())
		return true;

	return aStart <= aLevel && (aStart != aLevel || gZombieDefeated[theZombieType]);
}

void AlmanacDialog::GetZombiePosition(ZombieType theZombieType, int& x, int& y)
{
	int aZombieIndex = (int)theZombieType;
	if (theZombieType == ZombieType::ZOMBIE_BOSS)
		aZombieIndex += 2;

	x = aZombieIndex % zombieRows * 85 + 22;
	y = aZombieIndex / zombieRows * zombieHeight + (zombieHeight + zombieOffsetY) - mScrollPosition;
}

ZombieType AlmanacDialog::ZombieHitTest(int x, int y)
{
	if (mMouseVisible && mOpenPage == AlmanacPage::ALMANAC_PAGE_ZOMBIES)
	{
		for (int i = 0; i < NUM_ZOMBIES_IN_ALMANAC; i++)
		{
			ZombieType aZombieType = GetZombieType(i);
			ZombieDefinition aZombieDefiniton = GetZombieDefinition(aZombieType);
			if (aZombieType != ZombieType::ZOMBIE_INVALID)
			{
				int aZombieX, aZombieY;
				GetZombiePosition(aZombieType, aZombieX, aZombieY);
				Rect aZombieRect = Rect(aZombieX, aZombieY, 76 , 76);
				if (aZombieRect.Contains(x, y) && cZombieClipRect.Contains(x, y))
				{
					return aZombieType;
				}
			}
		}
	}
	return ZombieType::ZOMBIE_INVALID;
}

void AlmanacDialog::MouseUp(int x, int y, int theClickCount)
{
	if (mDescriptionSliderDragging)
	{
		mDescriptionSliderDragging = false;
		return;
	}
	if (mPlantButton->IsMouseOver())
		SetPage(ALMANAC_PAGE_PLANTS);
	else if (mZombieButton->IsMouseOver())
		SetPage(ALMANAC_PAGE_ZOMBIES);
	else if (mCloseButton->IsMouseOver())	
		mApp->KillAlmanacDialog();
	else if (mIndexButton->IsMouseOver())	
		SetPage(ALMANAC_PAGE_INDEX);
}

void AlmanacDialog::MouseDown(int x, int y, int theClickCount)
{
	if (mDescriptionSliderRect.Contains(x, y))
	{
		mDescriptionOffsetY = y - (mDescriptionOverfill ? (mDescriptionScroll / mDescriptionMaxScroll) * (mDescriptionRect.mHeight - ALMANAC_DESCRIPTION_MIN_HEIGHT) : 0);
		mDescriptionOffsetScroll = mDescriptionScroll;
		mDescriptionSliderDragging = true;
		return;
	}
	if (mPlantButton->IsMouseOver() || mCloseButton->IsMouseOver() || mIndexButton->IsMouseOver())
		mApp->PlaySample(Sexy::SOUND_TAP);
	if (mZombieButton->IsMouseOver())
		mApp->PlaySample(Sexy::SOUND_GRAVEBUTTON);

	SeedType aSeedType = SeedHitTest(x, y);
	if (aSeedType != SeedType::SEED_NONE && aSeedType != mSelectedSeed)
	{
		mSelectedSeed = aSeedType;
		SetupPlant();
		mApp->PlaySample(Sexy::SOUND_TAP);
	}
	ZombieType aZombieType = ZombieHitTest(x, y);
	if (aZombieType != ZombieType::ZOMBIE_INVALID && aZombieType != mSelectedZombie && ZombieIsShown(aZombieType))
	{
		mSelectedZombie = aZombieType;
		SetupZombie();
		mApp->PlaySample(Sexy::SOUND_TAP);
	}
}

void AlmanacDialog::MouseDrag(int x, int y)
{
	if (mDescriptionSliderDragging)
	{
		if (mDescriptionOverfill)
		{
			mDescriptionScroll = ((y - mDescriptionOffsetY) / (mDescriptionRect.mHeight - ALMANAC_DESCRIPTION_MIN_HEIGHT)) * mDescriptionMaxScroll;
		}
		else
		{
			mDescriptionScroll = y - (mDescriptionOffsetY - mDescriptionOffsetScroll);
		}
		if (mDescriptionScroll < 0)
		{
			mDescriptionScroll = 0;
		}
		else if (mDescriptionScroll > mDescriptionMaxScroll)
		{
			mDescriptionScroll = mDescriptionMaxScroll;
		}
	}
}

void AlmanacInitForPlayer()
{
	for (int i = 0; i < ZombieType::NUM_ZOMBIE_TYPES; i++)
		gZombieDefeated[i] = false;
}

void AlmanacPlayerDefeatedZombie(ZombieType theZombieType)
{
	gZombieDefeated[(int)theZombieType] = true;
}

void AlmanacDialog::MouseWheel(int theDelta)
{
	if (mIsOverDescription && !mDescriptionSliderDragging)
	{
		mDescriptionScroll -= mDescriptionLineSpacing * theDelta;
		if (mDescriptionScroll < 0)
		{
			mDescriptionScroll = 0;
		}
		else if (mDescriptionScroll > mDescriptionMaxScroll)
		{
			mDescriptionScroll = mDescriptionMaxScroll;
		}
	}
	else
	{
		mScrollAmount -= mBaseScrollSpeed * theDelta;
		mScrollAmount -= mScrollAmount * mScrollAccel;
	}
}

void AlmanacDialog::SliderVal(int theId, double theVal)
{
	switch (theId)
	{
	case 0:
		mScrollPosition = theVal * mMaxScrollPosition;
		break;
	}
}

SexyString AlmanacDialog::TranslateAndSanitize(SexyString str)
{
	SexyString ret = TodStringTranslate(str);
	for (int i = 0; i < WEIRD_CHARACTERS_COUNT; ++i) {
		char weirdChar = weirdCharacters[i][0];
		int pos = 0;
		while ((pos = ret.find(weirdChar, pos)) != SexyString::npos) {
			if (pos > 0) {
				ret.erase(pos - 1, 1);
				pos--;
			}
			pos++;
		}
	}
	return ret;
}