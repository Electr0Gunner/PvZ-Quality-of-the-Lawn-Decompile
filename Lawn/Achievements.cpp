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
	{ AchievementType::ACHIEVEMENT_HOME_SECURITY,			0,		_S("HOME_SECURITY"), true },
	{ AchievementType::ACHIEVEMENT_NOBEL_PEAS_PRIZE,		1,		_S("NOBEL_PEAS_PRIZE"), true },
	{ AchievementType::ACHIEVEMENT_BETTER_OFF_DEAD,			2,		_S("BETTER_OFF_DEAD"), false },
	{ AchievementType::ACHIEVEMENT_CHINA_SHOP,				3,		_S("CHINA_SHOP"), false },
	{ AchievementType::ACHIEVEMENT_SPUDOW,					4,		_S("SPUDOW"), true },
	{ AchievementType::ACHIEVEMENT_EXPLODONATOR,			5,		_S("EXPLODONATOR"), true },
	{ AchievementType::ACHIEVEMENT_MORTICULTURALIST,		6,		_S("MORTICULTURALIST") , false },
	{ AchievementType::ACHIEVEMENT_DONT_PEA_IN_POOL,		7,		_S("DONT_PEA_IN_POOL"), true },
	{ AchievementType::ACHIEVEMENT_ROLL_SOME_HEADS,			8,		_S("ROLL_SOME_HEADS"), true },
	{ AchievementType::ACHIEVEMENT_GROUNDED,				9,		_S("GROUNDED"), true },
	{ AchievementType::ACHIEVEMENT_ZOMBOLOGIST,				10,		_S("ZOMBOLOGIST"), true },
	{ AchievementType::ACHIEVEMENT_PENNY_PINCHER,			11,		_S("PENNY_PINCHER"), true },
	{ AchievementType::ACHIEVEMENT_SUNNY_DAYS,				12,		_S("SUNNY_DAYS"), true },
	{ AchievementType::ACHIEVEMENT_POPCORN_PARTY,			13,		_S("POPCORN_PARTY"), true },
	{ AchievementType::ACHIEVEMENT_GOOD_MORNING,			14,		_S("GOOD_MORNING"), true },
	{ AchievementType::ACHIEVEMENT_NO_FUNGUS_AMONG_US,		15,		_S("NO_FUNGUS_AMONG_US"), true },
	{ AchievementType::ACHIEVEMENT_BEYOND_THE_GRAVE,		16,		_S("BEYOND_THE_GRAVE"), true },
	{ AchievementType::ACHIEVEMENT_IMMORTAL,				17,		_S("IMMORTAL"), false },
	{ AchievementType::ACHIEVEMENT_TOWERING_WISDOM,			18,		_S("TOWERING_WISDOM"), false },
	{ AchievementType::ACHIEVEMENT_MUSTACHE_MODE,			19,		_S("MUSTACHE_MODE"), true },
	{ AchievementType::ACHIEVEMENT_DISCO_IS_UNDEAD,			20,		_S("DISCO_IS_UNDEAD"), true }
};

Achievements::Achievements(LawnApp* theApp)
{
	mApp = theApp;
}
void Achievements::GiveAchievement(AchievementType theAchivementType)
{
	if (!mApp || !mApp->mPlayerInfo || mApp->mPlayerInfo->mEarnedAchievements[theAchivementType] || !HAS_ACHIEVEMENTS)
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
	if (!mApp || !mApp->mPlayerInfo || !HAS_ACHIEVEMENTS)
		return;

	if (mApp->HasFinishedAdventure()) {
		GiveAchievement(AchievementType::ACHIEVEMENT_HOME_SECURITY);
	}

	if (mApp->EarnedGoldTrophy()) {
		GiveAchievement(AchievementType::ACHIEVEMENT_NOBEL_PEAS_PRIZE);
	}

	if (mApp->CanSpawnYetis()) {
		GiveAchievement(AchievementType::ACHIEVEMENT_ZOMBOLOGIST);
	}

	int aTreeSize = mApp->mPlayerInfo->mChallengeRecords[GAMEMODE_TREE_OF_WISDOM - 1];
	if (aTreeSize >= 100) {
		GiveAchievement(AchievementType::ACHIEVEMENT_TOWERING_WISDOM);
	}

	if (mApp->GetNumTrophies(ChallengePage::CHALLENGE_PAGE_CHALLENGE) >= mApp->GetTotalTrophies(ChallengePage::CHALLENGE_PAGE_CHALLENGE))
	{
		GiveAchievement(AchievementType::ACHIEVEMENT_BEYOND_THE_GRAVE);
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
