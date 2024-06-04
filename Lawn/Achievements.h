#ifndef __ACHIVEMENTS_H__
#define __ACHIVEMENTS_H__

#include "../ConstEnums.h"
#include "../SexyAppFramework/Graphics.h"

using namespace Sexy;

#define NUM_ACHIEVEMENTS ((int)AchievementType::TOTAL_ACHIEVEMENTS)

class LawnApp;
class Achievements
{

public:
    Achievements(LawnApp* theApp);

    LawnApp*                mApp;
    void                    GiveAchievement(LawnApp* theApp, AchievementType theAchivementType);
    void                    InitAchievement();
    SexyString              ReturnAchievementName(int theAchivementIndex);
    bool                    ReturnShowInAwards(int theAchivementIndex);
};

class AchievementDefinition
{
public:
    AchievementType             mAchievementType;
    int                         mAchievementIconIndex;
    const SexyChar*             mAchievementName;
    bool                        mShowInAwards;
};
extern AchievementDefinition gAchievementDefs[NUM_ACHIEVEMENTS];
AchievementDefinition& GetAchievementDefinition(AchievementType theAchivementType);

#endif