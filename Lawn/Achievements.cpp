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
	{ AchievementType::HOME_LAWN_SECURITY,				0,   _S("[HOME_LAWN_SECURITY]") },
	{ AchievementType::NOBEL_PEAS_PRIZE,					1,   _S("[NOBEL_PEAS_PRIZE]") },
	{ AchievementType::BETTER_OFF_DEAD,					2,   _S("[BETTER_OFF_DEAD]") },
	{ AchievementType::CHINA_SHOP,						3,   _S("[CHINA_SHOP]") },
	{ AchievementType::SPUDOW,							4,   _S("[SPUDOW]") },
	{ AchievementType::EXPLODONATOR,						5,   _S("[EXPLODONATOR]") },
	{ AchievementType::MORTICULTURALIST,					6,   _S("[MORTICULTURALIST]") },
	{ AchievementType::DONT_PEA_IN_THE_POOL,				7,   _S("[DONT_PEA_IN_THE_POOL]") },
	{ AchievementType::ROLL_SOME_HEADS,					8,   _S("[ROLL_SOME_HEADS]") },
	{ AchievementType::GROUNDED,							9,   _S("[GROUNDED]") },
	{ AchievementType::ZOMBOLOGIST,						10,   _S("[ZOMBOLOGIST]") },
	{ AchievementType::PENNY_PINCHER,					11,   _S("[PENNY_PINCHER]") },
	{ AchievementType::SUNNY_DAYS,						12,   _S("[SUNNY_DAYS]") },
	{ AchievementType::POPCORN_PARTY,					13,   _S("[POPCORN_PARTY]") },
	{ AchievementType::GOOD_MORNING,						14,   _S("[GOOD_MORNING]") },
	{ AchievementType::NO_FUNGUS_AMONG_US,				15,   _S("[NO_FUNGUS_AMONG_US]") },
	{ AchievementType::BEYOND_THE_GRAVE,					16,   _S("[BEYOND_THE_GRAVE]") },
	{ AchievementType::IMMORTAL,							17,   _S("[IMMORTAL]") },
	{ AchievementType::TOWERING_WISDOM,					18,   _S("[TOWERING_WISDOM]") },
	{ AchievementType::MUSTACHE_MODE,					19,   _S("[MUSTACHE_MODE]") }
};

Achievements::Achievements(LawnApp* theApp)
{
	mApp = theApp;
}
void Achievements::GiveAchievement(LawnApp* theApp, AchievementType theAchivementType)
{
	if (!theApp->mPlayerInfo)
		return;

	if (theApp->mPlayerInfo->mEarnedAchievements[theAchivementType])
		return;

	theApp->mPlayerInfo->mEarnedAchievements[theAchivementType] = true;

	std::string aAchievementName = gAchievementDefs[theAchivementType].mAchievementName;
	aAchievementName.append(" Achievement!");

	if(theApp->mBoard)
		theApp->mBoard->DisplayAdvice(aAchievementName, MESSAGE_STYLE_HINT_FAST, AdviceType::ADVICE_NONE);
	theApp->PlaySample(SOUND_BOSSEXPLOSION);
}

void Achievements::InitAchievement()
{
	if (!mApp || !mApp->mPlayerInfo)
		return;

	if (mApp->HasFinishedAdventure()) {
		GiveAchievement(mApp, AchievementType::HOME_LAWN_SECURITY);
	}

	if (mApp->EarnedGoldTrophy()) {
		GiveAchievement(mApp, AchievementType::NOBEL_PEAS_PRIZE);
	}

	if (mApp->CanSpawnYetis()) {
		GiveAchievement(mApp, AchievementType::ZOMBOLOGIST);
	}

	int aTreeSize = mApp->mPlayerInfo->mChallengeRecords[GAMEMODE_TREE_OF_WISDOM - GAMEMODE_SURVIVAL_NORMAL_STAGE_1];
	if (aTreeSize >= 100) {
		GiveAchievement(mApp, AchievementType::TOWERING_WISDOM);
	}
	for (int i = SEED_PEASHOOTER; i <= SEED_IMITATER; i++) {
		if (mApp->SeedTypeAvailable(SeedType(i)))
			GiveAchievement(mApp, AchievementType::MORTICULTURALIST);
	}
}

AchievementDefinition& GetAchievementDefinition(int theAchivementID)
{
	TOD_ASSERT(theAchivementID >= 0 && theAchivementID < NUM_ACHIEVEMENTS);

	AchievementDefinition& aDef = gAchievementDefs[theAchivementID];
	TOD_ASSERT(aDef.mAchievementType == theAchivementID + HOME_LAWN_SECURITY + 1);

	return gAchievementDefs[theAchivementID];
}
