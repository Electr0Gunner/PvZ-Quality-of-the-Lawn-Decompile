#include "../../LawnApp.h"
#include "Achievements.h"
#include "Board.h"
#include "System/PlayerInfo.h"
#include "../../Sexy.TodLib/TodDebug.h"
#include "../../Sexy.TodLib/TodFoley.h"
#include "../../Sexy.TodLib/TodCommon.h"
#include "../../SexyAppFramework/Debug.h"
#include "../../Sexy.TodLib/TodStringFile.h"
#include "../../GameConstants.h"

AchievementDefinition gAchievementDefs[NUM_ACHIEVEMENTS] = {
	{ AchievementType::HOME_SECURITY,			0,		_S("HOME_SECURITY"), true },
	{ AchievementType::NOBEL_PEAS_PRIZE,		1,		_S("NOBEL_PEAS_PRIZE"), true },
	{ AchievementType::BETTER_OFF_DEAD,			2,		_S("BETTER_OFF_DEAD"), false },
	{ AchievementType::CHINA_SHOP,				3,		_S("CHINA_SHOP"), false },
	{ AchievementType::SPUDOW,					4,		_S("SPUDOW"), true },
	{ AchievementType::EXPLODONATOR,			5,		_S("EXPLODONATOR"), true },
	{ AchievementType::MORTICULTURALIST,		6,		_S("MORTICULTURALIST") , false },
	{ AchievementType::DONT_PEA_IN_POOL,		7,		_S("DONT_PEA_IN_POOL"), true },
	{ AchievementType::ROLL_SOME_HEADS,			8,		_S("ROLL_SOME_HEADS"), true },
	{ AchievementType::GROUNDED,				9,		_S("GROUNDED"), true },
	{ AchievementType::ZOMBOLOGIST,				10,		_S("ZOMBOLOGIST"), true },
	{ AchievementType::PENNY_PINCHER,			11,		_S("PENNY_PINCHER"), true },
	{ AchievementType::SUNNY_DAYS,				12,		_S("SUNNY_DAYS"), true },
	{ AchievementType::POPCORN_PARTY,			13,		_S("POPCORN_PARTY"), true },
	{ AchievementType::GOOD_MORNING,			14,		_S("GOOD_MORNING"), true },
	{ AchievementType::NO_FUNGUS_AMONG_US,		15,		_S("NO_FUNGUS_AMONG_US"), true },
	{ AchievementType::BEYOND_THE_GRAVE,		16,		_S("BEYOND_THE_GRAVE"), true },
	{ AchievementType::IMMORTAL,				17,		_S("IMMORTAL"), false },
	{ AchievementType::TOWERING_WISDOM,			18,		_S("TOWERING_WISDOM"), false },
	{ AchievementType::MUSTACHE_MODE,			19,		_S("MUSTACHE_MODE"), true },
	{ AchievementType::DISCO_IS_UNDEAD,			20,		_S("DISCO_IS_UNDEAD"), true }
};

Achievements::Achievements(LawnApp* theApp)
{
	mApp = theApp;
}
void Achievements::GiveAchievement(AchievementType theAchivementType)
{
	if (!mApp || !mApp->mPlayerInfo || mApp->mPlayerInfo->mEarnedAchievements[theAchivementType])
		return;

	mApp->mPlayerInfo->mEarnedAchievements[theAchivementType] = true;

	SexyString aAchivementText = StrFormat(_S("[ACHIEVEMENT_%s_TITLE]"), ReturnAchievementName(theAchivementType).c_str());
	SexyString aMessage = TodReplaceString(_S("[ACHIEVEMENT_ACHIEVED]"), _S("{ACHIEVEMENT}"), aAchivementText);

	if(mApp->mBoard)
		mApp->mBoard->DisplayAdvice(aMessage, MESSAGE_STYLE_HINT_FAST, AdviceType::ADVICE_NONE);

	mApp->PlaySample(SOUND_ACHIEVEMENT);
}

void Achievements::InitAchievement()
{
	if (!mApp || !mApp->mPlayerInfo)
		return;

	if (mApp->HasFinishedAdventure()) {
		GiveAchievement(AchievementType::HOME_SECURITY);
	}

	if (mApp->EarnedGoldTrophy()) {
		GiveAchievement(AchievementType::NOBEL_PEAS_PRIZE);
	}

	if (mApp->CanSpawnYetis()) {
		GiveAchievement(AchievementType::ZOMBOLOGIST);
	}

	int aTreeSize = mApp->mPlayerInfo->mChallengeRecords[GAMEMODE_TREE_OF_WISDOM - 1];
	if (aTreeSize >= 100) {
		GiveAchievement(AchievementType::TOWERING_WISDOM);
	}
}

SexyString Achievements::ReturnAchievementName(int theAchivementIndex)
{
	return gAchievementDefs[theAchivementIndex].mAchievementName;
}

bool Achievements::ReturnShowInAwards(int theAchivementIndex)
{
	return gAchievementDefs[theAchivementIndex].mShowInAwards;
}
