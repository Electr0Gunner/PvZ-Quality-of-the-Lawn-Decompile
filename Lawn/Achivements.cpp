#include "../../LawnApp.h"
#include "Achivements.h"
#include "System/PlayerInfo.h"
#include "../../Sexy.TodLib/TodDebug.h"
#include "../../Sexy.TodLib/TodFoley.h"
#include "../../Sexy.TodLib/TodCommon.h"
#include "../../SexyAppFramework/Debug.h"
#include "../../Sexy.TodLib/TodStringFile.h"
#include "../../GameConstants.h"

AchivementDefinition gAchivementDefs[NUM_ACHIVEMENTS] = {
	{ AchivementType::HOME_LAWN_SECURITY,				0,   _S("[HOME_LAWN_SECURITY]") },
	{ AchivementType::NOBEL_PEAS_PRIZE,					1,   _S("[NOBEL_PEAS_PRIZE]") },
	{ AchivementType::BETTER_OFF_DEAD,					2,   _S("[BETTER_OFF_DEAD]") },
	{ AchivementType::CHINA_SHOP,						3,   _S("[CHINA_SHOP]") },
	{ AchivementType::SPUDOW,							4,   _S("[SPUDOW]") },
	{ AchivementType::EXPLODONATOR,						5,   _S("[EXPLODONATOR]") },
	{ AchivementType::MORTICULTURALIST,					6,   _S("[MORTICULTURALIST]") },
	{ AchivementType::DONT_PEA_IN_THE_POOL,				7,   _S("[DONT_PEA_IN_THE_POOL]") },
	{ AchivementType::ROLL_SOME_HEADS,					8,   _S("[ROLL_SOME_HEADS]") },
	{ AchivementType::GROUNDED,							9,   _S("[GROUNDED]") },
	{ AchivementType::ZOMBOLOGIST,						10,   _S("[ZOMBOLOGIST]") },
	{ AchivementType::PENNY_PINCHER,					11,   _S("[PENNY_PINCHER]") },
	{ AchivementType::SUNNY_DAYS,						12,   _S("[SUNNY_DAYS]") },
	{ AchivementType::POPCORN_PARTY,					13,   _S("[POPCORN_PARTY]") },
	{ AchivementType::GOOD_MORNING,						14,   _S("[GOOD_MORNING]") },
	{ AchivementType::NO_FUNGUS_AMONG_US,				15,   _S("[NO_FUNGUS_AMONG_US]") },
	{ AchivementType::BEYOND_THE_GRAVE,					16,   _S("[BEYOND_THE_GRAVE]") },
	{ AchivementType::IMMORTAL,							17,   _S("[IMMORTAL]") },
	{ AchivementType::TOWERING_WISDOM,					18,   _S("[TOWERING_WISDOM]") },
	{ AchivementType::MUSTACHE_MODE,					19,   _S("[MUSTACHE_MODE]") }
};

Achivements::Achivements(LawnApp* theApp)
{
	mApp = theApp;
}
void Achivements::GiveAchievement(LawnApp* theApp, AchivementType theAchivementType, bool theForceGive)
{
	if (!theApp->mPlayerInfo)
		return;

	if (theApp->mPlayerInfo->mEarnedAchievements[theAchivementType])
		return;

	theApp->mPlayerInfo->mEarnedAchievements[theAchivementType] = true;

	if (!theForceGive)
		return;

	//std::string aAchievementName = gAchievementList[theAchivementType].name;
	//aAchievementName.append(" Achievement!");

	//theApp->mBoard->DisplayAdvice(aAchievementName, MESSAGE_STYLE_ACHIEVEMENT, AdviceType::ADVICE_NONE);
	theApp->PlaySample(SOUND_BOSSEXPLOSION);
}

void Achivements::InitAchivement()
{
	if (!mApp || !mApp->mPlayerInfo)
		return;

	if (mApp->HasFinishedAdventure()) {
		GiveAchievement(mApp, AchivementType::HOME_LAWN_SECURITY, true);
	}

	if (mApp->EarnedGoldTrophy()) {
		GiveAchievement(mApp, AchivementType::NOBEL_PEAS_PRIZE, true);
	}

	if (mApp->CanSpawnYetis()) {
		GiveAchievement(mApp, AchivementType::ZOMBOLOGIST, true);
	}

	int aTreeSize = mApp->mPlayerInfo->mChallengeRecords[GAMEMODE_TREE_OF_WISDOM - GAMEMODE_SURVIVAL_NORMAL_STAGE_1];
	if (aTreeSize >= 100) {
		GiveAchievement(mApp, AchivementType::TOWERING_WISDOM, true);
	}
	for (int i = SEED_PEASHOOTER; i <= SEED_IMITATER; i++) {
		if (mApp->SeedTypeAvailable(SeedType(i)))
			GiveAchievement(mApp, AchivementType::MORTICULTURALIST, true);
	}
}

AchivementDefinition& GetAchivementDefinition(int theAchivementID)
{
	TOD_ASSERT(theAchivementID >= 0 && theAchivementID < NUM_ACHIVEMENTS);

	AchivementDefinition& aDef = gAchivementDefs[theAchivementID];
	TOD_ASSERT(aDef.mAchivementType == theAchivementID + HOME_LAWN_SECURITY + 1);

	return gAchivementDefs[theAchivementID];
}
