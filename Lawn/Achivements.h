#ifndef __ACHIVEMENTS_H__
#define __ACHIVEMENTS_H__

#include "../ConstEnums.h"
#include "../SexyAppFramework/Graphics.h"

using namespace Sexy;

#define NUM_ACHIVEMENTS ((int)AchivementType::TOTAL_ACHIVEMENTS)

class LawnApp;
class Achivements
{

public:
    Achivements(LawnApp* theApp);

    LawnApp*                mApp;
    void                    GiveAchievement(LawnApp* theApp, AchivementType theAchivementType, bool theForceGive);
    void                    InitAchivement();
};

class AchivementDefinition
{
public:
    AchivementType              mAchivementType;
    int                         mAchivementIconIndex;
    const SexyChar*             mAchivementName;         
};
extern AchivementDefinition gAchivementDefs[NUM_ACHIVEMENTS];
AchivementDefinition& GetAchivementDefinition(AchivementType theAchivementType);

#endif