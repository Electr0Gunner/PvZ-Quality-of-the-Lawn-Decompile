#include "Resources.h"
#include "SexyAppFramework/ResourceManager.h"

using namespace Sexy;

#pragma warning(disable:4311 4312)

static bool gNeedRecalcVariableToIdMap = false;

bool Sexy::ExtractResourcesByName(ResourceManager *theManager, const char *theName)
{
	if (strcmp(theName,"DelayLoad_Achievements")==0) return ExtractDelayLoad_AchievementsResources(theManager);
	if (strcmp(theName,"DelayLoad_Almanac")==0) return ExtractDelayLoad_AlmanacResources(theManager);
	if (strcmp(theName,"DelayLoad_AwardScreen")==0) return ExtractDelayLoad_AwardScreenResources(theManager);
	if (strcmp(theName,"DelayLoad_Background1")==0) return ExtractDelayLoad_Background1Resources(theManager);
	if (strcmp(theName,"DelayLoad_Background2")==0) return ExtractDelayLoad_Background2Resources(theManager);
	if (strcmp(theName,"DelayLoad_Background3")==0) return ExtractDelayLoad_Background3Resources(theManager);
	if (strcmp(theName,"DelayLoad_Background4")==0) return ExtractDelayLoad_Background4Resources(theManager);
	if (strcmp(theName,"DelayLoad_Background5")==0) return ExtractDelayLoad_Background5Resources(theManager);
	if (strcmp(theName,"DelayLoad_Background6")==0) return ExtractDelayLoad_Background6Resources(theManager);
	if (strcmp(theName,"DelayLoad_BackgroundUnsodded")==0) return ExtractDelayLoad_BackgroundUnsoddedResources(theManager);
	if (strcmp(theName,"DelayLoad_ChallengeScreen")==0) return ExtractDelayLoad_ChallengeScreenResources(theManager);
	if (strcmp(theName,"DelayLoad_Credits")==0) return ExtractDelayLoad_CreditsResources(theManager);
	if (strcmp(theName,"DelayLoad_GreenHouseGarden")==0) return ExtractDelayLoad_GreenHouseGardenResources(theManager);
	if (strcmp(theName,"DelayLoad_GreenHouseOverlay")==0) return ExtractDelayLoad_GreenHouseOverlayResources(theManager);
	if (strcmp(theName,"DelayLoad_MushroomGarden")==0) return ExtractDelayLoad_MushroomGardenResources(theManager);
	if (strcmp(theName,"DelayLoad_QuickPlay")==0) return ExtractDelayLoad_QuickPlayResources(theManager);
	if (strcmp(theName,"DelayLoad_Store")==0) return ExtractDelayLoad_StoreResources(theManager);
	if (strcmp(theName,"DelayLoad_TreeOfWisdom")==0) return ExtractDelayLoad_TreeOfWisdomResources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieFinalNote")==0) return ExtractDelayLoad_ZombieFinalNoteResources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieNote")==0) return ExtractDelayLoad_ZombieNoteResources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieNote1")==0) return ExtractDelayLoad_ZombieNote1Resources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieNote2")==0) return ExtractDelayLoad_ZombieNote2Resources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieNote3")==0) return ExtractDelayLoad_ZombieNote3Resources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieNote4")==0) return ExtractDelayLoad_ZombieNote4Resources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieNoteHelp")==0) return ExtractDelayLoad_ZombieNoteHelpResources(theManager);
	if (strcmp(theName,"DelayLoad_Zombiquarium")==0) return ExtractDelayLoad_ZombiquariumResources(theManager);
	if (strcmp(theName,"Init")==0) return ExtractInitResources(theManager);
	if (strcmp(theName,"LoaderBar")==0) return ExtractLoaderBarResources(theManager);
	if (strcmp(theName,"LoadingFonts")==0) return ExtractLoadingFontsResources(theManager);
	if (strcmp(theName,"LoadingImages")==0) return ExtractLoadingImagesResources(theManager);
	if (strcmp(theName,"LoadingSounds")==0) return ExtractLoadingSoundsResources(theManager);
	return false;
}

Sexy::ResourceId Sexy::GetIdByStringId(const char *theStringId)
{
	typedef std::map<std::string,int> MyMap;
	static MyMap aMap;
	if(aMap.empty())
	{
		for(int i=0; i<RESOURCE_ID_MAX; i++)
			aMap[GetStringIdById(i)] = i;
	}

	MyMap::iterator anItr = aMap.find(theStringId);
	if (anItr == aMap.end())
		return RESOURCE_ID_MAX;
	else
		return (ResourceId) anItr->second;
}

// DelayLoad_Achievements Resources
Image* Sexy::IMAGE_ACHIEVEMENT_BACK_GLOW;
Image* Sexy::IMAGE_ACHIEVEMENT_BEJEWELED;
Image* Sexy::IMAGE_ACHIEVEMENT_BOOKWORM;
Image* Sexy::IMAGE_ACHIEVEMENT_CHUZZLE;
Image* Sexy::IMAGE_ACHIEVEMENT_MORE;
Image* Sexy::IMAGE_ACHIEVEMENT_MORE_HIGHLIGHT;
Image* Sexy::IMAGE_ACHIEVEMENT_PEGGLE;
Image* Sexy::IMAGE_ACHIEVEMENT_PIPE;
Image* Sexy::IMAGE_ACHIEVEMENT_ROCK;
Image* Sexy::IMAGE_ACHIEVEMENT_SELECTOR_TILE;
Image* Sexy::IMAGE_ACHIEVEMENT_TILE;
Image* Sexy::IMAGE_ACHIEVEMENT_TILE_CHINA;
Image* Sexy::IMAGE_ACHIEVEMENT_TOP;
Image* Sexy::IMAGE_ACHIEVEMENT_TOP_HIGHLIGHT;
Image* Sexy::IMAGE_ACHIEVEMENT_ZUMA;

bool Sexy::ExtractDelayLoad_AchievementsResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ACHIEVEMENT_BACK_GLOW = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_BACK_GLOW");
		IMAGE_ACHIEVEMENT_BEJEWELED = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_BEJEWELED");
		IMAGE_ACHIEVEMENT_BOOKWORM = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_BOOKWORM");
		IMAGE_ACHIEVEMENT_CHUZZLE = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_CHUZZLE");
		IMAGE_ACHIEVEMENT_MORE = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_MORE");
		IMAGE_ACHIEVEMENT_MORE_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_MORE_HIGHLIGHT");
		IMAGE_ACHIEVEMENT_PEGGLE = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_PEGGLE");
		IMAGE_ACHIEVEMENT_PIPE = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_PIPE");
		IMAGE_ACHIEVEMENT_ROCK = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_ROCK");
		IMAGE_ACHIEVEMENT_SELECTOR_TILE = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_SELECTOR_TILE");
		IMAGE_ACHIEVEMENT_TILE = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_TILE");
		IMAGE_ACHIEVEMENT_TILE_CHINA = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_TILE_CHINA");
		IMAGE_ACHIEVEMENT_TOP = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_TOP");
		IMAGE_ACHIEVEMENT_TOP_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_TOP_HIGHLIGHT");
		IMAGE_ACHIEVEMENT_ZUMA = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_ZUMA");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Almanac Resources
Image* Sexy::IMAGE_ALMANAC_CLOSEBUTTON;
Image* Sexy::IMAGE_ALMANAC_CLOSEBUTTONHIGHLIGHT;
Image* Sexy::IMAGE_ALMANAC_GROUNDDAY;
Image* Sexy::IMAGE_ALMANAC_GROUNDICE;
Image* Sexy::IMAGE_ALMANAC_GROUNDNIGHT;
Image* Sexy::IMAGE_ALMANAC_GROUNDNIGHTPOOL;
Image* Sexy::IMAGE_ALMANAC_GROUNDPOOL;
Image* Sexy::IMAGE_ALMANAC_GROUNDROOF;
Image* Sexy::IMAGE_ALMANAC_INDEXBACK;
Image* Sexy::IMAGE_ALMANAC_INDEXBUTTON;
Image* Sexy::IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT;
Image* Sexy::IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT_DISABLE;
Image* Sexy::IMAGE_ALMANAC_INDEXBUTTON_DISABLE;
Image* Sexy::IMAGE_ALMANAC_PLANTBACK;
Image* Sexy::IMAGE_ALMANAC_PLANTBLANK;
Image* Sexy::IMAGE_ALMANAC_PLANTCARD;
Image* Sexy::IMAGE_ALMANAC_ZOMBIEBACK;
Image* Sexy::IMAGE_ALMANAC_ZOMBIEBLANK;
Image* Sexy::IMAGE_ALMANAC_ZOMBIECARD;
Image* Sexy::IMAGE_ALMANAC_ZOMBIEWINDOW;
Image* Sexy::IMAGE_ALMANAC_ZOMBIEWINDOW2;

bool Sexy::ExtractDelayLoad_AlmanacResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ALMANAC_CLOSEBUTTON = aMgr.GetImageThrow("IMAGE_ALMANAC_CLOSEBUTTON");
		IMAGE_ALMANAC_CLOSEBUTTONHIGHLIGHT = aMgr.GetImageThrow("IMAGE_ALMANAC_CLOSEBUTTONHIGHLIGHT");
		IMAGE_ALMANAC_GROUNDDAY = aMgr.GetImageThrow("IMAGE_ALMANAC_GROUNDDAY");
		IMAGE_ALMANAC_GROUNDICE = aMgr.GetImageThrow("IMAGE_ALMANAC_GROUNDICE");
		IMAGE_ALMANAC_GROUNDNIGHT = aMgr.GetImageThrow("IMAGE_ALMANAC_GROUNDNIGHT");
		IMAGE_ALMANAC_GROUNDNIGHTPOOL = aMgr.GetImageThrow("IMAGE_ALMANAC_GROUNDNIGHTPOOL");
		IMAGE_ALMANAC_GROUNDPOOL = aMgr.GetImageThrow("IMAGE_ALMANAC_GROUNDPOOL");
		IMAGE_ALMANAC_GROUNDROOF = aMgr.GetImageThrow("IMAGE_ALMANAC_GROUNDROOF");
		IMAGE_ALMANAC_INDEXBACK = aMgr.GetImageThrow("IMAGE_ALMANAC_INDEXBACK");
		IMAGE_ALMANAC_INDEXBUTTON = aMgr.GetImageThrow("IMAGE_ALMANAC_INDEXBUTTON");
		IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT = aMgr.GetImageThrow("IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT");
		IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT_DISABLE = aMgr.GetImageThrow("IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT_DISABLE");
		IMAGE_ALMANAC_INDEXBUTTON_DISABLE = aMgr.GetImageThrow("IMAGE_ALMANAC_INDEXBUTTON_DISABLE");
		IMAGE_ALMANAC_PLANTBACK = aMgr.GetImageThrow("IMAGE_ALMANAC_PLANTBACK");
		IMAGE_ALMANAC_PLANTBLANK = aMgr.GetImageThrow("IMAGE_ALMANAC_PLANTBLANK");
		IMAGE_ALMANAC_PLANTCARD = aMgr.GetImageThrow("IMAGE_ALMANAC_PLANTCARD");
		IMAGE_ALMANAC_ZOMBIEBACK = aMgr.GetImageThrow("IMAGE_ALMANAC_ZOMBIEBACK");
		IMAGE_ALMANAC_ZOMBIEBLANK = aMgr.GetImageThrow("IMAGE_ALMANAC_ZOMBIEBLANK");
		IMAGE_ALMANAC_ZOMBIECARD = aMgr.GetImageThrow("IMAGE_ALMANAC_ZOMBIECARD");
		IMAGE_ALMANAC_ZOMBIEWINDOW = aMgr.GetImageThrow("IMAGE_ALMANAC_ZOMBIEWINDOW");
		IMAGE_ALMANAC_ZOMBIEWINDOW2 = aMgr.GetImageThrow("IMAGE_ALMANAC_ZOMBIEWINDOW2");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_AwardScreen Resources
Image* Sexy::IMAGE_ACHIEVEMENTS_PORTRAITS;
Image* Sexy::IMAGE_AWARDSCREEN_BACK;

bool Sexy::ExtractDelayLoad_AwardScreenResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ACHIEVEMENTS_PORTRAITS = aMgr.GetImageThrow("IMAGE_ACHIEVEMENTS_PORTRAITS");
		IMAGE_AWARDSCREEN_BACK = aMgr.GetImageThrow("IMAGE_AWARDSCREEN_BACK");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Background1 Resources
Image* Sexy::IMAGE_BACKGROUND1;
Image* Sexy::IMAGE_BACKGROUND1_GAMEOVER_INTERIOR_OVERLAY;
Image* Sexy::IMAGE_BACKGROUND1_GAMEOVER_MASK;

bool Sexy::ExtractDelayLoad_Background1Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND1 = aMgr.GetImageThrow("IMAGE_BACKGROUND1");
		IMAGE_BACKGROUND1_GAMEOVER_INTERIOR_OVERLAY = aMgr.GetImageThrow("IMAGE_BACKGROUND1_GAMEOVER_INTERIOR_OVERLAY");
		IMAGE_BACKGROUND1_GAMEOVER_MASK = aMgr.GetImageThrow("IMAGE_BACKGROUND1_GAMEOVER_MASK");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Background2 Resources
Image* Sexy::IMAGE_BACKGROUND2;
Image* Sexy::IMAGE_BACKGROUND2_GAMEOVER_INTERIOR_OVERLAY;
Image* Sexy::IMAGE_BACKGROUND2_GAMEOVER_MASK;

bool Sexy::ExtractDelayLoad_Background2Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND2 = aMgr.GetImageThrow("IMAGE_BACKGROUND2");
		IMAGE_BACKGROUND2_GAMEOVER_INTERIOR_OVERLAY = aMgr.GetImageThrow("IMAGE_BACKGROUND2_GAMEOVER_INTERIOR_OVERLAY");
		IMAGE_BACKGROUND2_GAMEOVER_MASK = aMgr.GetImageThrow("IMAGE_BACKGROUND2_GAMEOVER_MASK");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Background3 Resources
Image* Sexy::IMAGE_BACKGROUND3;
Image* Sexy::IMAGE_BACKGROUND3_GAMEOVER_INTERIOR_OVERLAY;
Image* Sexy::IMAGE_BACKGROUND3_GAMEOVER_MASK;

bool Sexy::ExtractDelayLoad_Background3Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND3 = aMgr.GetImageThrow("IMAGE_BACKGROUND3");
		IMAGE_BACKGROUND3_GAMEOVER_INTERIOR_OVERLAY = aMgr.GetImageThrow("IMAGE_BACKGROUND3_GAMEOVER_INTERIOR_OVERLAY");
		IMAGE_BACKGROUND3_GAMEOVER_MASK = aMgr.GetImageThrow("IMAGE_BACKGROUND3_GAMEOVER_MASK");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Background4 Resources
Image* Sexy::IMAGE_BACKGROUND4;
Image* Sexy::IMAGE_BACKGROUND4_GAMEOVER_INTERIOR_OVERLAY;
Image* Sexy::IMAGE_BACKGROUND4_GAMEOVER_MASK;
Image* Sexy::IMAGE_FOG;
Image* Sexy::IMAGE_FOG_SOFTWARE;

bool Sexy::ExtractDelayLoad_Background4Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND4 = aMgr.GetImageThrow("IMAGE_BACKGROUND4");
		IMAGE_BACKGROUND4_GAMEOVER_INTERIOR_OVERLAY = aMgr.GetImageThrow("IMAGE_BACKGROUND4_GAMEOVER_INTERIOR_OVERLAY");
		IMAGE_BACKGROUND4_GAMEOVER_MASK = aMgr.GetImageThrow("IMAGE_BACKGROUND4_GAMEOVER_MASK");
		IMAGE_FOG = aMgr.GetImageThrow("IMAGE_FOG");
		IMAGE_FOG_SOFTWARE = aMgr.GetImageThrow("IMAGE_FOG_SOFTWARE");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Background5 Resources
Image* Sexy::IMAGE_BACKGROUND5;
Image* Sexy::IMAGE_BACKGROUND5_GAMEOVER_MASK;

bool Sexy::ExtractDelayLoad_Background5Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND5 = aMgr.GetImageThrow("IMAGE_BACKGROUND5");
		IMAGE_BACKGROUND5_GAMEOVER_MASK = aMgr.GetImageThrow("IMAGE_BACKGROUND5_GAMEOVER_MASK");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Background6 Resources
Image* Sexy::IMAGE_BACKGROUND6BOSS;
Image* Sexy::IMAGE_BACKGROUND6_GAMEOVER_MASK;

bool Sexy::ExtractDelayLoad_Background6Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND6BOSS = aMgr.GetImageThrow("IMAGE_BACKGROUND6BOSS");
		IMAGE_BACKGROUND6_GAMEOVER_MASK = aMgr.GetImageThrow("IMAGE_BACKGROUND6_GAMEOVER_MASK");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_BackgroundUnsodded Resources
Image* Sexy::IMAGE_BACKGROUND1UNSODDED;
Image* Sexy::IMAGE_SOD1ROW;
Image* Sexy::IMAGE_SOD3ROW;

bool Sexy::ExtractDelayLoad_BackgroundUnsoddedResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND1UNSODDED = aMgr.GetImageThrow("IMAGE_BACKGROUND1UNSODDED");
		IMAGE_SOD1ROW = aMgr.GetImageThrow("IMAGE_SOD1ROW");
		IMAGE_SOD3ROW = aMgr.GetImageThrow("IMAGE_SOD3ROW");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ChallengeScreen Resources
Image* Sexy::IMAGE_CHALLENGE_BACKGROUND;
Image* Sexy::IMAGE_CHALLENGE_BLANK;
Image* Sexy::IMAGE_CHALLENGE_THUMBNAILS;
Image* Sexy::IMAGE_CHALLENGE_WINDOW;
Image* Sexy::IMAGE_CHALLENGE_WINDOW_HIGHLIGHT;
Image* Sexy::IMAGE_LOCK;
Image* Sexy::IMAGE_LOCK_OPEN;
Image* Sexy::IMAGE_SURVIVAL_THUMBNAILS;

bool Sexy::ExtractDelayLoad_ChallengeScreenResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_CHALLENGE_BACKGROUND = aMgr.GetImageThrow("IMAGE_CHALLENGE_BACKGROUND");
		IMAGE_CHALLENGE_BLANK = aMgr.GetImageThrow("IMAGE_CHALLENGE_BLANK");
		IMAGE_CHALLENGE_THUMBNAILS = aMgr.GetImageThrow("IMAGE_CHALLENGE_THUMBNAILS");
		IMAGE_CHALLENGE_WINDOW = aMgr.GetImageThrow("IMAGE_CHALLENGE_WINDOW");
		IMAGE_CHALLENGE_WINDOW_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_CHALLENGE_WINDOW_HIGHLIGHT");
		IMAGE_LOCK = aMgr.GetImageThrow("IMAGE_LOCK");
		IMAGE_LOCK_OPEN = aMgr.GetImageThrow("IMAGE_LOCK_OPEN");
		IMAGE_SURVIVAL_THUMBNAILS = aMgr.GetImageThrow("IMAGE_SURVIVAL_THUMBNAILS");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Credits Resources
Font* Sexy::FONT_BRIANNETOD32;
Font* Sexy::FONT_BRIANNETOD32BLACK;
Image* Sexy::IMAGE_CREDITS_BG;
Image* Sexy::IMAGE_CREDITS_PLAYBUTTON;
Image* Sexy::IMAGE_CREDITS_ZOMBIENOTE;
Image* Sexy::IMAGE_REANIM_CREDITS_DISCOLIGHTS;
Image* Sexy::IMAGE_REANIM_CREDITS_FOGMACHINE;
Image* Sexy::IMAGE_REANIM_SUNFLOWER_HEAD_SING1;
Image* Sexy::IMAGE_REANIM_SUNFLOWER_HEAD_SING2;
Image* Sexy::IMAGE_REANIM_SUNFLOWER_HEAD_SING3;
Image* Sexy::IMAGE_REANIM_SUNFLOWER_HEAD_SING4;
Image* Sexy::IMAGE_REANIM_SUNFLOWER_HEAD_SING5;
Image* Sexy::IMAGE_REANIM_SUNFLOWER_HEAD_WINK;

bool Sexy::ExtractDelayLoad_CreditsResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		FONT_BRIANNETOD32 = aMgr.GetFontThrow("FONT_BRIANNETOD32");
		FONT_BRIANNETOD32BLACK = aMgr.GetFontThrow("FONT_BRIANNETOD32BLACK");
		IMAGE_CREDITS_BG = aMgr.GetImageThrow("IMAGE_CREDITS_BG");
		IMAGE_CREDITS_PLAYBUTTON = aMgr.GetImageThrow("IMAGE_CREDITS_PLAYBUTTON");
		IMAGE_CREDITS_ZOMBIENOTE = aMgr.GetImageThrow("IMAGE_CREDITS_ZOMBIENOTE");
		IMAGE_REANIM_CREDITS_DISCOLIGHTS = aMgr.GetImageThrow("IMAGE_REANIM_CREDITS_DISCOLIGHTS");
		IMAGE_REANIM_CREDITS_FOGMACHINE = aMgr.GetImageThrow("IMAGE_REANIM_CREDITS_FOGMACHINE");
		IMAGE_REANIM_SUNFLOWER_HEAD_SING1 = aMgr.GetImageThrow("IMAGE_REANIM_SUNFLOWER_HEAD_SING1");
		IMAGE_REANIM_SUNFLOWER_HEAD_SING2 = aMgr.GetImageThrow("IMAGE_REANIM_SUNFLOWER_HEAD_SING2");
		IMAGE_REANIM_SUNFLOWER_HEAD_SING3 = aMgr.GetImageThrow("IMAGE_REANIM_SUNFLOWER_HEAD_SING3");
		IMAGE_REANIM_SUNFLOWER_HEAD_SING4 = aMgr.GetImageThrow("IMAGE_REANIM_SUNFLOWER_HEAD_SING4");
		IMAGE_REANIM_SUNFLOWER_HEAD_SING5 = aMgr.GetImageThrow("IMAGE_REANIM_SUNFLOWER_HEAD_SING5");
		IMAGE_REANIM_SUNFLOWER_HEAD_WINK = aMgr.GetImageThrow("IMAGE_REANIM_SUNFLOWER_HEAD_WINK");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_GreenHouseGarden Resources
Image* Sexy::IMAGE_BACKGROUND_GREENHOUSE;

bool Sexy::ExtractDelayLoad_GreenHouseGardenResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND_GREENHOUSE = aMgr.GetImageThrow("IMAGE_BACKGROUND_GREENHOUSE");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_GreenHouseOverlay Resources
Image* Sexy::IMAGE_BACKGROUND_GREENHOUSE_OVERLAY;

bool Sexy::ExtractDelayLoad_GreenHouseOverlayResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND_GREENHOUSE_OVERLAY = aMgr.GetImageThrow("IMAGE_BACKGROUND_GREENHOUSE_OVERLAY");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_MushroomGarden Resources
Image* Sexy::IMAGE_BACKGROUND_MUSHROOMGARDEN;

bool Sexy::ExtractDelayLoad_MushroomGardenResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND_MUSHROOMGARDEN = aMgr.GetImageThrow("IMAGE_BACKGROUND_MUSHROOMGARDEN");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_QuickPlay Resources
Image* Sexy::IMAGE_QUICKPLAY_BACKGROUND;
Image* Sexy::IMAGE_QUICKPLAY_BACK_HIGHLIGHT;
Image* Sexy::IMAGE_QUICKPLAY_LEFT_BUTTON;
Image* Sexy::IMAGE_QUICKPLAY_LEFT_BUTTON_HIGHLIGHT;
Image* Sexy::IMAGE_QUICKPLAY_RIGHT_BUTTON;
Image* Sexy::IMAGE_QUICKPLAY_RIGHT_BUTTON_HIGHLIGHT;
Image* Sexy::IMAGE_QUICKPLAY_WIDGET;

bool Sexy::ExtractDelayLoad_QuickPlayResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_QUICKPLAY_BACKGROUND = aMgr.GetImageThrow("IMAGE_QUICKPLAY_BACKGROUND");
		IMAGE_QUICKPLAY_BACK_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_QUICKPLAY_BACK_HIGHLIGHT");
		IMAGE_QUICKPLAY_LEFT_BUTTON = aMgr.GetImageThrow("IMAGE_QUICKPLAY_LEFT_BUTTON");
		IMAGE_QUICKPLAY_LEFT_BUTTON_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_QUICKPLAY_LEFT_BUTTON_HIGHLIGHT");
		IMAGE_QUICKPLAY_RIGHT_BUTTON = aMgr.GetImageThrow("IMAGE_QUICKPLAY_RIGHT_BUTTON");
		IMAGE_QUICKPLAY_RIGHT_BUTTON_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_QUICKPLAY_RIGHT_BUTTON_HIGHLIGHT");
		IMAGE_QUICKPLAY_WIDGET = aMgr.GetImageThrow("IMAGE_QUICKPLAY_WIDGET");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Store Resources
Image* Sexy::IMAGE_STORE_AQUARIUMGARDENICON;
Image* Sexy::IMAGE_STORE_BACKGROUND;
Image* Sexy::IMAGE_STORE_BACKGROUNDNIGHT;
Image* Sexy::IMAGE_STORE_CAR;
Image* Sexy::IMAGE_STORE_CARCLOSED;
Image* Sexy::IMAGE_STORE_CARCLOSED_NIGHT;
Image* Sexy::IMAGE_STORE_CAR_NIGHT;
Image* Sexy::IMAGE_STORE_FIRSTAIDWALLNUTICON;
Image* Sexy::IMAGE_STORE_HATCHBACKOPEN;
Image* Sexy::IMAGE_STORE_MAINMENUBUTTON;
Image* Sexy::IMAGE_STORE_MAINMENUBUTTONDOWN;
Image* Sexy::IMAGE_STORE_MAINMENUBUTTONHIGHLIGHT;
Image* Sexy::IMAGE_STORE_MUSHROOMGARDENICON;
Image* Sexy::IMAGE_STORE_NEXTBUTTON;
Image* Sexy::IMAGE_STORE_NEXTBUTTONDISABLED;
Image* Sexy::IMAGE_STORE_NEXTBUTTONHIGHLIGHT;
Image* Sexy::IMAGE_STORE_PACKETUPGRADE;
Image* Sexy::IMAGE_STORE_PREVBUTTON;
Image* Sexy::IMAGE_STORE_PREVBUTTONDISABLED;
Image* Sexy::IMAGE_STORE_PREVBUTTONHIGHLIGHT;
Image* Sexy::IMAGE_STORE_PRICETAG;
Image* Sexy::IMAGE_STORE_PVZICON;
Image* Sexy::IMAGE_STORE_SIGN;
Image* Sexy::IMAGE_STORE_TREEOFWISDOMICON;

bool Sexy::ExtractDelayLoad_StoreResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_STORE_AQUARIUMGARDENICON = aMgr.GetImageThrow("IMAGE_STORE_AQUARIUMGARDENICON");
		IMAGE_STORE_BACKGROUND = aMgr.GetImageThrow("IMAGE_STORE_BACKGROUND");
		IMAGE_STORE_BACKGROUNDNIGHT = aMgr.GetImageThrow("IMAGE_STORE_BACKGROUNDNIGHT");
		IMAGE_STORE_CAR = aMgr.GetImageThrow("IMAGE_STORE_CAR");
		IMAGE_STORE_CARCLOSED = aMgr.GetImageThrow("IMAGE_STORE_CARCLOSED");
		IMAGE_STORE_CARCLOSED_NIGHT = aMgr.GetImageThrow("IMAGE_STORE_CARCLOSED_NIGHT");
		IMAGE_STORE_CAR_NIGHT = aMgr.GetImageThrow("IMAGE_STORE_CAR_NIGHT");
		IMAGE_STORE_FIRSTAIDWALLNUTICON = aMgr.GetImageThrow("IMAGE_STORE_FIRSTAIDWALLNUTICON");
		IMAGE_STORE_HATCHBACKOPEN = aMgr.GetImageThrow("IMAGE_STORE_HATCHBACKOPEN");
		IMAGE_STORE_MAINMENUBUTTON = aMgr.GetImageThrow("IMAGE_STORE_MAINMENUBUTTON");
		IMAGE_STORE_MAINMENUBUTTONDOWN = aMgr.GetImageThrow("IMAGE_STORE_MAINMENUBUTTONDOWN");
		IMAGE_STORE_MAINMENUBUTTONHIGHLIGHT = aMgr.GetImageThrow("IMAGE_STORE_MAINMENUBUTTONHIGHLIGHT");
		IMAGE_STORE_MUSHROOMGARDENICON = aMgr.GetImageThrow("IMAGE_STORE_MUSHROOMGARDENICON");
		IMAGE_STORE_NEXTBUTTON = aMgr.GetImageThrow("IMAGE_STORE_NEXTBUTTON");
		IMAGE_STORE_NEXTBUTTONDISABLED = aMgr.GetImageThrow("IMAGE_STORE_NEXTBUTTONDISABLED");
		IMAGE_STORE_NEXTBUTTONHIGHLIGHT = aMgr.GetImageThrow("IMAGE_STORE_NEXTBUTTONHIGHLIGHT");
		IMAGE_STORE_PACKETUPGRADE = aMgr.GetImageThrow("IMAGE_STORE_PACKETUPGRADE");
		IMAGE_STORE_PREVBUTTON = aMgr.GetImageThrow("IMAGE_STORE_PREVBUTTON");
		IMAGE_STORE_PREVBUTTONDISABLED = aMgr.GetImageThrow("IMAGE_STORE_PREVBUTTONDISABLED");
		IMAGE_STORE_PREVBUTTONHIGHLIGHT = aMgr.GetImageThrow("IMAGE_STORE_PREVBUTTONHIGHLIGHT");
		IMAGE_STORE_PRICETAG = aMgr.GetImageThrow("IMAGE_STORE_PRICETAG");
		IMAGE_STORE_PVZICON = aMgr.GetImageThrow("IMAGE_STORE_PVZICON");
		IMAGE_STORE_SIGN = aMgr.GetImageThrow("IMAGE_STORE_SIGN");
		IMAGE_STORE_TREEOFWISDOMICON = aMgr.GetImageThrow("IMAGE_STORE_TREEOFWISDOMICON");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_TreeOfWisdom Resources

bool Sexy::ExtractDelayLoad_TreeOfWisdomResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieFinalNote Resources
Image* Sexy::IMAGE_ZOMBIE_FINAL_NOTE;

bool Sexy::ExtractDelayLoad_ZombieFinalNoteResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_FINAL_NOTE = aMgr.GetImageThrow("IMAGE_ZOMBIE_FINAL_NOTE");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieNote Resources
Image* Sexy::IMAGE_ZOMBIE_NOTE;

bool Sexy::ExtractDelayLoad_ZombieNoteResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_NOTE = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieNote1 Resources
Image* Sexy::IMAGE_ZOMBIE_NOTE1;

bool Sexy::ExtractDelayLoad_ZombieNote1Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_NOTE1 = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE1");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieNote2 Resources
Image* Sexy::IMAGE_ZOMBIE_NOTE2;

bool Sexy::ExtractDelayLoad_ZombieNote2Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_NOTE2 = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE2");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieNote3 Resources
Image* Sexy::IMAGE_ZOMBIE_NOTE3;

bool Sexy::ExtractDelayLoad_ZombieNote3Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_NOTE3 = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE3");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieNote4 Resources
Image* Sexy::IMAGE_ZOMBIE_NOTE4;

bool Sexy::ExtractDelayLoad_ZombieNote4Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_NOTE4 = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE4");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieNoteHelp Resources
Image* Sexy::IMAGE_ZOMBIE_NOTE_HELP;

bool Sexy::ExtractDelayLoad_ZombieNoteHelpResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_NOTE_HELP = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE_HELP");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Zombiquarium Resources
Image* Sexy::IMAGE_AQUARIUM1;
Image* Sexy::IMAGE_WAVECENTER;
Image* Sexy::IMAGE_WAVESIDE;

bool Sexy::ExtractDelayLoad_ZombiquariumResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_AQUARIUM1 = aMgr.GetImageThrow("IMAGE_AQUARIUM1");
		IMAGE_WAVECENTER = aMgr.GetImageThrow("IMAGE_WAVECENTER");
		IMAGE_WAVESIDE = aMgr.GetImageThrow("IMAGE_WAVESIDE");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// Init Resources
Image* Sexy::IMAGE_BLANK;
Image* Sexy::IMAGE_PARTNER_LOGO;
Image* Sexy::IMAGE_POPCAP_LOGO;

bool Sexy::ExtractInitResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BLANK = aMgr.GetImageThrow("IMAGE_BLANK");
		IMAGE_PARTNER_LOGO = aMgr.GetImageThrow("IMAGE_PARTNER_LOGO");
		IMAGE_POPCAP_LOGO = aMgr.GetImageThrow("IMAGE_POPCAP_LOGO");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// LoaderBar Resources
Font* Sexy::FONT_BRIANNETOD16;
Image* Sexy::IMAGE_LOADBAR_DIRT;
Image* Sexy::IMAGE_LOADBAR_GRASS;
Image* Sexy::IMAGE_PVZ_LOGO;
Image* Sexy::IMAGE_REANIM_SODROLLCAP;
Image* Sexy::IMAGE_TITLESCREEN;
int Sexy::SOUND_BUTTONCLICK;
int Sexy::SOUND_LOADINGBAR_FLOWER;
int Sexy::SOUND_LOADINGBAR_ZOMBIE;

bool Sexy::ExtractLoaderBarResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		FONT_BRIANNETOD16 = aMgr.GetFontThrow("FONT_BRIANNETOD16");
		IMAGE_LOADBAR_DIRT = aMgr.GetImageThrow("IMAGE_LOADBAR_DIRT");
		IMAGE_LOADBAR_GRASS = aMgr.GetImageThrow("IMAGE_LOADBAR_GRASS");
		IMAGE_PVZ_LOGO = aMgr.GetImageThrow("IMAGE_PVZ_LOGO");
		IMAGE_REANIM_SODROLLCAP = aMgr.GetImageThrow("IMAGE_REANIM_SODROLLCAP");
		IMAGE_TITLESCREEN = aMgr.GetImageThrow("IMAGE_TITLESCREEN");
		SOUND_BUTTONCLICK = aMgr.GetSoundThrow("SOUND_BUTTONCLICK");
		SOUND_LOADINGBAR_FLOWER = aMgr.GetSoundThrow("SOUND_LOADINGBAR_FLOWER");
		SOUND_LOADINGBAR_ZOMBIE = aMgr.GetSoundThrow("SOUND_LOADINGBAR_ZOMBIE");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// LoadingFonts Resources
Font* Sexy::FONT_BRIANNETOD12;
Font* Sexy::FONT_CONTINUUMBOLD14;
Font* Sexy::FONT_CONTINUUMBOLD14OUTLINE;
Font* Sexy::FONT_DWARVENTODCRAFT12;
Font* Sexy::FONT_DWARVENTODCRAFT15;
Font* Sexy::FONT_DWARVENTODCRAFT18;
Font* Sexy::FONT_DWARVENTODCRAFT18BRIGHTGREENINSET;
Font* Sexy::FONT_DWARVENTODCRAFT18GREENINSET;
Font* Sexy::FONT_DWARVENTODCRAFT18YELLOW;
Font* Sexy::FONT_DWARVENTODCRAFT24;
Font* Sexy::FONT_DWARVENTODCRAFT36BRIGHTGREENINSET;
Font* Sexy::FONT_DWARVENTODCRAFT36GREENINSET;
Font* Sexy::FONT_HOUSEOFTERROR16;
Font* Sexy::FONT_HOUSEOFTERROR20;
Font* Sexy::FONT_HOUSEOFTERROR28;
Image* Sexy::FONT_IMAGE_HOUSEOFTERROR28;
Font* Sexy::FONT_PICO129;
Font* Sexy::FONT_TINYBOLD;

bool Sexy::ExtractLoadingFontsResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		FONT_BRIANNETOD12 = aMgr.GetFontThrow("FONT_BRIANNETOD12");
		FONT_CONTINUUMBOLD14 = aMgr.GetFontThrow("FONT_CONTINUUMBOLD14");
		FONT_CONTINUUMBOLD14OUTLINE = aMgr.GetFontThrow("FONT_CONTINUUMBOLD14OUTLINE");
		FONT_DWARVENTODCRAFT12 = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT12");
		FONT_DWARVENTODCRAFT15 = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT15");
		FONT_DWARVENTODCRAFT18 = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT18");
		FONT_DWARVENTODCRAFT18BRIGHTGREENINSET = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT18BRIGHTGREENINSET");
		FONT_DWARVENTODCRAFT18GREENINSET = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT18GREENINSET");
		FONT_DWARVENTODCRAFT18YELLOW = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT18YELLOW");
		FONT_DWARVENTODCRAFT24 = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT24");
		FONT_DWARVENTODCRAFT36BRIGHTGREENINSET = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT36BRIGHTGREENINSET");
		FONT_DWARVENTODCRAFT36GREENINSET = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT36GREENINSET");
		FONT_HOUSEOFTERROR16 = aMgr.GetFontThrow("FONT_HOUSEOFTERROR16");
		FONT_HOUSEOFTERROR20 = aMgr.GetFontThrow("FONT_HOUSEOFTERROR20");
		FONT_HOUSEOFTERROR28 = aMgr.GetFontThrow("FONT_HOUSEOFTERROR28");
		FONT_IMAGE_HOUSEOFTERROR28 = aMgr.GetImageThrow("FONT_IMAGE_HOUSEOFTERROR28");
		FONT_PICO129 = aMgr.GetFontThrow("FONT_PICO129");
		FONT_TINYBOLD = aMgr.GetFontThrow("FONT_TINYBOLD");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// LoadingImages Resources
Image* Sexy::IMAGE_ACHIEVEMENT_BUTTON;
Image* Sexy::IMAGE_ACHIEVEMENT_HIGHLIGHT;
Image* Sexy::IMAGE_ALMANAC;
Image* Sexy::IMAGE_ALMANAC_IMITATER;
Image* Sexy::IMAGE_AWARDPICKUPGLOW;
Image* Sexy::IMAGE_BEGHOULED_TWIST_OVERLAY;
Image* Sexy::IMAGE_BRAIN;
Image* Sexy::IMAGE_BUG_SPRAY;
Image* Sexy::IMAGE_BUNGEECORD;
Image* Sexy::IMAGE_BUNGEETARGET;
Image* Sexy::IMAGE_BUTTON_DOWN_LEFT;
Image* Sexy::IMAGE_BUTTON_DOWN_MIDDLE;
Image* Sexy::IMAGE_BUTTON_DOWN_RIGHT;
Image* Sexy::IMAGE_BUTTON_DOWN_SMALL;
Image* Sexy::IMAGE_BUTTON_LEFT;
Image* Sexy::IMAGE_BUTTON_MIDDLE;
Image* Sexy::IMAGE_BUTTON_RIGHT;
Image* Sexy::IMAGE_BUTTON_SMALL;
Image* Sexy::IMAGE_CARKEYS;
Image* Sexy::IMAGE_CHALLENGE_SLIDERSLOT;
Image* Sexy::IMAGE_CHOCOLATE;
Image* Sexy::IMAGE_COBCANNON_POPCORN;
Image* Sexy::IMAGE_COBCANNON_TARGET;
Image* Sexy::IMAGE_COINBANK;
Image* Sexy::IMAGE_CONVEYORBELT;
Image* Sexy::IMAGE_CONVEYORBELT_BACKDROP;
Image* Sexy::IMAGE_CRATER;
Image* Sexy::IMAGE_CRATER_FADING;
Image* Sexy::IMAGE_CRATER_ROOF_CENTER;
Image* Sexy::IMAGE_CRATER_ROOF_LEFT;
Image* Sexy::IMAGE_CRATER_WATER_DAY;
Image* Sexy::IMAGE_CRATER_WATER_NIGHT;
Image* Sexy::IMAGE_DIALOG_BIGBOTTOMLEFT;
Image* Sexy::IMAGE_DIALOG_BIGBOTTOMMIDDLE;
Image* Sexy::IMAGE_DIALOG_BIGBOTTOMRIGHT;
Image* Sexy::IMAGE_DIALOG_BOTTOMLEFT;
Image* Sexy::IMAGE_DIALOG_BOTTOMMIDDLE;
Image* Sexy::IMAGE_DIALOG_BOTTOMRIGHT;
Image* Sexy::IMAGE_DIALOG_CENTERLEFT;
Image* Sexy::IMAGE_DIALOG_CENTERMIDDLE;
Image* Sexy::IMAGE_DIALOG_CENTERRIGHT;
Image* Sexy::IMAGE_DIALOG_HEADER;
Image* Sexy::IMAGE_DIALOG_TOPLEFT;
Image* Sexy::IMAGE_DIALOG_TOPMIDDLE;
Image* Sexy::IMAGE_DIALOG_TOPRIGHT;
Image* Sexy::IMAGE_DIRTBIG;
Image* Sexy::IMAGE_DIRTSMALL;
Image* Sexy::IMAGE_DOOMSHROOM_EXPLOSION_BASE;
Image* Sexy::IMAGE_DUST_PUFFS;
Image* Sexy::IMAGE_EDITBOX;
Image* Sexy::IMAGE_FASTBUTTON;
Image* Sexy::IMAGE_FASTBUTTON_HIGHLIGHT;
Image* Sexy::IMAGE_FERTILIZER;
Image* Sexy::IMAGE_FLAGMETER;
Image* Sexy::IMAGE_FLAGMETERLEVELPROGRESS;
Image* Sexy::IMAGE_FLAGMETERPARTS;
Image* Sexy::IMAGE_ICE;
Image* Sexy::IMAGE_ICETRAP;
Image* Sexy::IMAGE_ICETRAP2;
Image* Sexy::IMAGE_ICETRAP_PARTICLES;
Image* Sexy::IMAGE_ICE_CAP;
Image* Sexy::IMAGE_ICE_SPARKLES;
Image* Sexy::IMAGE_ICON_POOLCLEANER;
Image* Sexy::IMAGE_ICON_RAKE;
Image* Sexy::IMAGE_ICON_ROOFCLEANER;
Image* Sexy::IMAGE_IMITATERCLOUDS;
Image* Sexy::IMAGE_IMITATERPUFFS;
Image* Sexy::IMAGE_IMITATERSEED;
Image* Sexy::IMAGE_IMITATERSEEDDISABLED;
Image* Sexy::IMAGE_MELONPULT_PARTICLES;
Image* Sexy::IMAGE_MINIGAME_TROPHY;
Image* Sexy::IMAGE_MONEYBAG;
Image* Sexy::IMAGE_MONEYBAG_HI_RES;
Image* Sexy::IMAGE_MOUSE_CURSOR;
Image* Sexy::IMAGE_NIGHT_GRAVE_GRAPHIC;
Image* Sexy::IMAGE_OPTIONS_BACKTOGAMEBUTTON0;
Image* Sexy::IMAGE_OPTIONS_BACKTOGAMEBUTTON2;
Image* Sexy::IMAGE_OPTIONS_CHECKBOX0;
Image* Sexy::IMAGE_OPTIONS_CHECKBOX1;
Image* Sexy::IMAGE_OPTIONS_MENUBACK;
Image* Sexy::IMAGE_OPTIONS_SLIDERKNOB2;
Image* Sexy::IMAGE_OPTIONS_SLIDERKNOB_PLANT;
Image* Sexy::IMAGE_OPTIONS_SLIDERSLOT;
Image* Sexy::IMAGE_OPTIONS_SLIDERSLOT_PLANT;
Image* Sexy::IMAGE_PACKET_PLANTS;
Image* Sexy::IMAGE_PEA_PARTICLES;
Image* Sexy::IMAGE_PEA_SHADOWS;
Image* Sexy::IMAGE_PEA_SPLATS;
Image* Sexy::IMAGE_PHONOGRAPH;
Image* Sexy::IMAGE_PINATA;
Image* Sexy::IMAGE_PLANTSHADOW;
Image* Sexy::IMAGE_PLANTSHADOW2;
Image* Sexy::IMAGE_PLANTSPEECHBUBBLE;
Image* Sexy::IMAGE_POOL;
Image* Sexy::IMAGE_POOLSPARKLY;
Image* Sexy::IMAGE_POOL_BASE;
Image* Sexy::IMAGE_POOL_BASE_NIGHT;
Image* Sexy::IMAGE_POOL_CAUSTIC_EFFECT;
Image* Sexy::IMAGE_POOL_NIGHT;
Image* Sexy::IMAGE_POOL_SHADING;
Image* Sexy::IMAGE_POOL_SHADING_NIGHT;
Image* Sexy::IMAGE_POTATOMINE_PARTICLES;
Image* Sexy::IMAGE_PRESENT;
Image* Sexy::IMAGE_PRESENTOPEN;
Image* Sexy::IMAGE_PROJECTILECACTUS;
Image* Sexy::IMAGE_PROJECTILEPEA;
Image* Sexy::IMAGE_PROJECTILESNOWPEA;
Image* Sexy::IMAGE_PROJECTILE_STAR;
Image* Sexy::IMAGE_PUFFSHROOM_PUFF1;
Image* Sexy::IMAGE_QUICKPLAY_BUTTON;
Image* Sexy::IMAGE_QUICKPLAY_BUTTON_HIGHLIGHT;
Image* Sexy::IMAGE_RAIN;
Image* Sexy::IMAGE_REANIM_CABBAGEPULT_CABBAGE;
Image* Sexy::IMAGE_REANIM_COBCANNON_COB;
Image* Sexy::IMAGE_REANIM_COINGLOW;
Image* Sexy::IMAGE_REANIM_COIN_GOLD_DOLLAR;
Image* Sexy::IMAGE_REANIM_COIN_SILVER_DOLLAR;
Image* Sexy::IMAGE_REANIM_CORNPULT_BUTTER;
Image* Sexy::IMAGE_REANIM_CORNPULT_BUTTER_SPLAT;
Image* Sexy::IMAGE_REANIM_CORNPULT_KERNAL;
Image* Sexy::IMAGE_REANIM_CRAZYDAVE_MOUTH1;
Image* Sexy::IMAGE_REANIM_CRAZYDAVE_MOUTH4;
Image* Sexy::IMAGE_REANIM_CRAZYDAVE_MOUTH5;
Image* Sexy::IMAGE_REANIM_CRAZYDAVE_MOUTH6;
Image* Sexy::IMAGE_REANIM_DIAMOND;
Image* Sexy::IMAGE_REANIM_GARLIC_BODY2;
Image* Sexy::IMAGE_REANIM_GARLIC_BODY3;
Image* Sexy::IMAGE_REANIM_MELONPULT_MELON;
Image* Sexy::IMAGE_REANIM_POT_TOP_DARK;
Image* Sexy::IMAGE_REANIM_PUMPKIN_DAMAGE1;
Image* Sexy::IMAGE_REANIM_PUMPKIN_DAMAGE3;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_BUTTON;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_HIGHLIGHT;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_ALMANAC_SHADOW;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_BG;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_BUTTON;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_HIGHLIGHT;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_KEY_SHADOW;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_BUTTON;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_HIGHLIGHT;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_BUTTON;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_HIGHLIGHT;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_BUTTON;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_HIGHLIGHT;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_WOODSIGN2_PRESS;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3_PRESS;
Image* Sexy::IMAGE_REANIM_STINKY_TURN3;
Image* Sexy::IMAGE_REANIM_TALLNUT_CRACKED1;
Image* Sexy::IMAGE_REANIM_TALLNUT_CRACKED2;
Image* Sexy::IMAGE_REANIM_TREE_BG;
Image* Sexy::IMAGE_REANIM_WALLNUT_BODY;
Image* Sexy::IMAGE_REANIM_WALLNUT_CRACKED1;
Image* Sexy::IMAGE_REANIM_WALLNUT_CRACKED2;
Image* Sexy::IMAGE_REANIM_WINTERMELON_PROJECTILE;
Image* Sexy::IMAGE_REANIM_ZENGARDEN_BUGSPRAY_BOTTLE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BACKUP_INNERARM_HAND;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BACKUP_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BALLOON_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_HAND;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_EYEGLOW_BLUE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_ICEBALL;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_MOUTHGLOW_BLUE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BUCKET1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BUCKET2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BUCKET3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BUNGI_HEAD_SCARED;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CATAPULT_BASKETBALL;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CATAPULT_POLE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE_WITHBALL;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_WITHBALL;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CATAPULT_SIDING_DAMAGE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CONE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CONE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CONE3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT;
Image* Sexy::IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_DIGGER_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_DIGGER_PICKAXE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_DISCO_OUTERARM_HAND;
Image* Sexy::IMAGE_REANIM_ZOMBIE_DISCO_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_DOLPHINRIDER_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FLAG1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FLAG3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_HAND;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_DUCKXING;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_FOOT2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_REDEYE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_ZOMBIE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_HEAD_GROSSOUT;
Image* Sexy::IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES4;
Image* Sexy::IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_IMP_ARM2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_JACKBOX_BOX;
Image* Sexy::IMAGE_REANIM_ZOMBIE_JACKBOX_OUTERARM_LOWER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_LADDER_1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_LADDER_5;
Image* Sexy::IMAGE_REANIM_ZOMBIE_LADDER_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_MUSTACHE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_MUSTACHE3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_OUTERARM_HAND;
Image* Sexy::IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_LOWER;
Image* Sexy::IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_PAPER_MADHEAD;
Image* Sexy::IMAGE_REANIM_ZOMBIE_PAPER_PAPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_PAPER_PAPER3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POGO_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POGO_STICKHANDS2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POLEVAULTER_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_SCREENDOOR1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_SCREENDOOR2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_SCREENDOOR3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_SNORKLE_HEAD;
Image* Sexy::IMAGE_REANIM_ZOMBIE_SNORKLE_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_HAND;
Image* Sexy::IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_ZAMBONI_WHEEL_FLAT;
Image* Sexy::IMAGE_ROCKSMALL;
Image* Sexy::IMAGE_SCARY_POT;
Image* Sexy::IMAGE_SEEDBANK;
Image* Sexy::IMAGE_SEEDCHOOSER_BACKGROUND;
Image* Sexy::IMAGE_SEEDCHOOSER_BUTTON;
Image* Sexy::IMAGE_SEEDCHOOSER_BUTTON2;
Image* Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW;
Image* Sexy::IMAGE_SEEDCHOOSER_BUTTON_DISABLED;
Image* Sexy::IMAGE_SEEDCHOOSER_BUTTON_GLOW;
Image* Sexy::IMAGE_SEEDCHOOSER_IMITATERADDON;
Image* Sexy::IMAGE_SEEDPACKETFLASH;
Image* Sexy::IMAGE_SEEDPACKETSILHOUETTE;
Image* Sexy::IMAGE_SEEDPACKET_LARGER;
Image* Sexy::IMAGE_SEEDS;
Image* Sexy::IMAGE_SELECTORSCREEN_ALMANAC;
Image* Sexy::IMAGE_SELECTORSCREEN_ALMANACHIGHLIGHT;
Image* Sexy::IMAGE_SELECTORSCREEN_HELP1;
Image* Sexy::IMAGE_SELECTORSCREEN_HELP2;
Image* Sexy::IMAGE_SELECTORSCREEN_LEVELNUMBERS;
Image* Sexy::IMAGE_SELECTORSCREEN_OPTIONS1;
Image* Sexy::IMAGE_SELECTORSCREEN_OPTIONS2;
Image* Sexy::IMAGE_SELECTORSCREEN_QUIT1;
Image* Sexy::IMAGE_SELECTORSCREEN_QUIT2;
Image* Sexy::IMAGE_SELECTORSCREEN_STORE;
Image* Sexy::IMAGE_SELECTORSCREEN_STOREHIGHLIGHT;
Image* Sexy::IMAGE_SELECTORSCREEN_ZENGARDEN;
Image* Sexy::IMAGE_SELECTORSCREEN_ZENGARDENHIGHLIGHT;
Image* Sexy::IMAGE_SHOVEL;
Image* Sexy::IMAGE_SHOVELBANK;
Image* Sexy::IMAGE_SHOVEL_HI_RES;
Image* Sexy::IMAGE_SLOTMACHINE_OVERLAY;
Image* Sexy::IMAGE_SNOWFLAKES;
Image* Sexy::IMAGE_SNOWPEA_PARTICLES;
Image* Sexy::IMAGE_SNOWPEA_PUFF;
Image* Sexy::IMAGE_SNOWPEA_SPLATS;
Image* Sexy::IMAGE_SPOTLIGHT;
Image* Sexy::IMAGE_SPOTLIGHT2;
Image* Sexy::IMAGE_SQUIRREL;
Image* Sexy::IMAGE_STAR_PARTICLES;
Image* Sexy::IMAGE_STAR_SPLATS;
Image* Sexy::IMAGE_STORE_SPEECHBUBBLE;
Image* Sexy::IMAGE_STORE_SPEECHBUBBLE2;
Image* Sexy::IMAGE_SUNBANK;
Image* Sexy::IMAGE_SUNFLOWER_TROPHY;
Image* Sexy::IMAGE_TACO;
Image* Sexy::IMAGE_TOMBSTONES;
Image* Sexy::IMAGE_TOMBSTONE_MOUNDS;
Image* Sexy::IMAGE_TREEFOOD;
Image* Sexy::IMAGE_TROPHY;
Image* Sexy::IMAGE_TROPHY_HI_RES;
Image* Sexy::IMAGE_VASE_CHUNKS;
Image* Sexy::IMAGE_WALLNUTPARTICLESLARGE;
Image* Sexy::IMAGE_WALLNUTPARTICLESSMALL;
Image* Sexy::IMAGE_WALLNUT_BOWLINGSTRIPE;
Image* Sexy::IMAGE_WATERDROP;
Image* Sexy::IMAGE_WATERINGCAN;
Image* Sexy::IMAGE_WATERINGCANGOLD;
Image* Sexy::IMAGE_WATERPARTICLE;
Image* Sexy::IMAGE_WHITEPIXEL;
Image* Sexy::IMAGE_WHITEWATER;
Image* Sexy::IMAGE_WHITEWATER_SHADOW;
Image* Sexy::IMAGE_WINTERMELON_PARTICLES;
Image* Sexy::IMAGE_ZAMBONISMOKE;
Image* Sexy::IMAGE_ZENSHOPBUTTON;
Image* Sexy::IMAGE_ZENSHOPBUTTON_HIGHLIGHT;
Image* Sexy::IMAGE_ZEN_GARDENGLOVE;
Image* Sexy::IMAGE_ZEN_GOLDTOOLRETICLE;
Image* Sexy::IMAGE_ZEN_MONEYSIGN;
Image* Sexy::IMAGE_ZEN_NEED_ICONS;
Image* Sexy::IMAGE_ZEN_NEXTGARDEN;
Image* Sexy::IMAGE_ZEN_WHEELBARROW;
Image* Sexy::IMAGE_ZOMBIEBACKUPDANCERHEAD;
Image* Sexy::IMAGE_ZOMBIEBALLOONHEAD;
Image* Sexy::IMAGE_ZOMBIEBOBSLEDHEAD;
Image* Sexy::IMAGE_ZOMBIEDANCERHEAD;
Image* Sexy::IMAGE_ZOMBIEDIGGERARM;
Image* Sexy::IMAGE_ZOMBIEDIGGERHEAD;
Image* Sexy::IMAGE_ZOMBIEDOLPHINRIDERHEAD;
Image* Sexy::IMAGE_ZOMBIEFOOTBALLHEAD;
Image* Sexy::IMAGE_ZOMBIEFUTUREGLASSES;
Image* Sexy::IMAGE_ZOMBIEIMPHEAD;
Image* Sexy::IMAGE_ZOMBIEJACKBOXARM;
Image* Sexy::IMAGE_ZOMBIELADDERHEAD;
Image* Sexy::IMAGE_ZOMBIEPOGO;
Image* Sexy::IMAGE_ZOMBIEPOLEVAULTERHEAD;
Image* Sexy::IMAGE_ZOMBIEYETIHEAD;
Image* Sexy::IMAGE_ZOMBIE_BOBSLED1;
Image* Sexy::IMAGE_ZOMBIE_BOBSLED2;
Image* Sexy::IMAGE_ZOMBIE_BOBSLED3;
Image* Sexy::IMAGE_ZOMBIE_BOBSLED4;
Image* Sexy::IMAGE_ZOMBIE_BOBSLED_INSIDE;
Image* Sexy::IMAGE_ZOMBIE_BOSS_FIREBALL_GROUNDPARTICLES;
Image* Sexy::IMAGE_ZOMBIE_BOSS_FIREBALL_PARTICLES;
Image* Sexy::IMAGE_ZOMBIE_BOSS_ICEBALL_GROUNDPARTICLES;
Image* Sexy::IMAGE_ZOMBIE_BOSS_ICEBALL_PARTICLES;
Image* Sexy::IMAGE_ZOMBIE_NOTE_SMALL;
Image* Sexy::IMAGE_ZOMBIE_SEAWEED;
Image* Sexy::IMAGE_ZOMBOSS_PARTICLES;

bool Sexy::ExtractLoadingImagesResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ACHIEVEMENT_BUTTON = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_BUTTON");
		IMAGE_ACHIEVEMENT_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_ACHIEVEMENT_HIGHLIGHT");
		IMAGE_ALMANAC = aMgr.GetImageThrow("IMAGE_ALMANAC");
		IMAGE_ALMANAC_IMITATER = aMgr.GetImageThrow("IMAGE_ALMANAC_IMITATER");
		IMAGE_AWARDPICKUPGLOW = aMgr.GetImageThrow("IMAGE_AWARDPICKUPGLOW");
		IMAGE_BEGHOULED_TWIST_OVERLAY = aMgr.GetImageThrow("IMAGE_BEGHOULED_TWIST_OVERLAY");
		IMAGE_BRAIN = aMgr.GetImageThrow("IMAGE_BRAIN");
		IMAGE_BUG_SPRAY = aMgr.GetImageThrow("IMAGE_BUG_SPRAY");
		IMAGE_BUNGEECORD = aMgr.GetImageThrow("IMAGE_BUNGEECORD");
		IMAGE_BUNGEETARGET = aMgr.GetImageThrow("IMAGE_BUNGEETARGET");
		IMAGE_BUTTON_DOWN_LEFT = aMgr.GetImageThrow("IMAGE_BUTTON_DOWN_LEFT");
		IMAGE_BUTTON_DOWN_MIDDLE = aMgr.GetImageThrow("IMAGE_BUTTON_DOWN_MIDDLE");
		IMAGE_BUTTON_DOWN_RIGHT = aMgr.GetImageThrow("IMAGE_BUTTON_DOWN_RIGHT");
		IMAGE_BUTTON_DOWN_SMALL = aMgr.GetImageThrow("IMAGE_BUTTON_DOWN_SMALL");
		IMAGE_BUTTON_LEFT = aMgr.GetImageThrow("IMAGE_BUTTON_LEFT");
		IMAGE_BUTTON_MIDDLE = aMgr.GetImageThrow("IMAGE_BUTTON_MIDDLE");
		IMAGE_BUTTON_RIGHT = aMgr.GetImageThrow("IMAGE_BUTTON_RIGHT");
		IMAGE_BUTTON_SMALL = aMgr.GetImageThrow("IMAGE_BUTTON_SMALL");
		IMAGE_CARKEYS = aMgr.GetImageThrow("IMAGE_CARKEYS");
		IMAGE_CHALLENGE_SLIDERSLOT = aMgr.GetImageThrow("IMAGE_CHALLENGE_SLIDERSLOT");
		IMAGE_CHOCOLATE = aMgr.GetImageThrow("IMAGE_CHOCOLATE");
		IMAGE_COBCANNON_POPCORN = aMgr.GetImageThrow("IMAGE_COBCANNON_POPCORN");
		IMAGE_COBCANNON_TARGET = aMgr.GetImageThrow("IMAGE_COBCANNON_TARGET");
		IMAGE_COINBANK = aMgr.GetImageThrow("IMAGE_COINBANK");
		IMAGE_CONVEYORBELT = aMgr.GetImageThrow("IMAGE_CONVEYORBELT");
		IMAGE_CONVEYORBELT_BACKDROP = aMgr.GetImageThrow("IMAGE_CONVEYORBELT_BACKDROP");
		IMAGE_CRATER = aMgr.GetImageThrow("IMAGE_CRATER");
		IMAGE_CRATER_FADING = aMgr.GetImageThrow("IMAGE_CRATER_FADING");
		IMAGE_CRATER_ROOF_CENTER = aMgr.GetImageThrow("IMAGE_CRATER_ROOF_CENTER");
		IMAGE_CRATER_ROOF_LEFT = aMgr.GetImageThrow("IMAGE_CRATER_ROOF_LEFT");
		IMAGE_CRATER_WATER_DAY = aMgr.GetImageThrow("IMAGE_CRATER_WATER_DAY");
		IMAGE_CRATER_WATER_NIGHT = aMgr.GetImageThrow("IMAGE_CRATER_WATER_NIGHT");
		IMAGE_DIALOG_BIGBOTTOMLEFT = aMgr.GetImageThrow("IMAGE_DIALOG_BIGBOTTOMLEFT");
		IMAGE_DIALOG_BIGBOTTOMMIDDLE = aMgr.GetImageThrow("IMAGE_DIALOG_BIGBOTTOMMIDDLE");
		IMAGE_DIALOG_BIGBOTTOMRIGHT = aMgr.GetImageThrow("IMAGE_DIALOG_BIGBOTTOMRIGHT");
		IMAGE_DIALOG_BOTTOMLEFT = aMgr.GetImageThrow("IMAGE_DIALOG_BOTTOMLEFT");
		IMAGE_DIALOG_BOTTOMMIDDLE = aMgr.GetImageThrow("IMAGE_DIALOG_BOTTOMMIDDLE");
		IMAGE_DIALOG_BOTTOMRIGHT = aMgr.GetImageThrow("IMAGE_DIALOG_BOTTOMRIGHT");
		IMAGE_DIALOG_CENTERLEFT = aMgr.GetImageThrow("IMAGE_DIALOG_CENTERLEFT");
		IMAGE_DIALOG_CENTERMIDDLE = aMgr.GetImageThrow("IMAGE_DIALOG_CENTERMIDDLE");
		IMAGE_DIALOG_CENTERRIGHT = aMgr.GetImageThrow("IMAGE_DIALOG_CENTERRIGHT");
		IMAGE_DIALOG_HEADER = aMgr.GetImageThrow("IMAGE_DIALOG_HEADER");
		IMAGE_DIALOG_TOPLEFT = aMgr.GetImageThrow("IMAGE_DIALOG_TOPLEFT");
		IMAGE_DIALOG_TOPMIDDLE = aMgr.GetImageThrow("IMAGE_DIALOG_TOPMIDDLE");
		IMAGE_DIALOG_TOPRIGHT = aMgr.GetImageThrow("IMAGE_DIALOG_TOPRIGHT");
		IMAGE_DIRTBIG = aMgr.GetImageThrow("IMAGE_DIRTBIG");
		IMAGE_DIRTSMALL = aMgr.GetImageThrow("IMAGE_DIRTSMALL");
		IMAGE_DOOMSHROOM_EXPLOSION_BASE = aMgr.GetImageThrow("IMAGE_DOOMSHROOM_EXPLOSION_BASE");
		IMAGE_DUST_PUFFS = aMgr.GetImageThrow("IMAGE_DUST_PUFFS");
		IMAGE_EDITBOX = aMgr.GetImageThrow("IMAGE_EDITBOX");
		IMAGE_FASTBUTTON = aMgr.GetImageThrow("IMAGE_FASTBUTTON");
		IMAGE_FASTBUTTON_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_FASTBUTTON_HIGHLIGHT");
		IMAGE_FERTILIZER = aMgr.GetImageThrow("IMAGE_FERTILIZER");
		IMAGE_FLAGMETER = aMgr.GetImageThrow("IMAGE_FLAGMETER");
		IMAGE_FLAGMETERLEVELPROGRESS = aMgr.GetImageThrow("IMAGE_FLAGMETERLEVELPROGRESS");
		IMAGE_FLAGMETERPARTS = aMgr.GetImageThrow("IMAGE_FLAGMETERPARTS");
		IMAGE_ICE = aMgr.GetImageThrow("IMAGE_ICE");
		IMAGE_ICETRAP = aMgr.GetImageThrow("IMAGE_ICETRAP");
		IMAGE_ICETRAP2 = aMgr.GetImageThrow("IMAGE_ICETRAP2");
		IMAGE_ICETRAP_PARTICLES = aMgr.GetImageThrow("IMAGE_ICETRAP_PARTICLES");
		IMAGE_ICE_CAP = aMgr.GetImageThrow("IMAGE_ICE_CAP");
		IMAGE_ICE_SPARKLES = aMgr.GetImageThrow("IMAGE_ICE_SPARKLES");
		IMAGE_ICON_POOLCLEANER = aMgr.GetImageThrow("IMAGE_ICON_POOLCLEANER");
		IMAGE_ICON_RAKE = aMgr.GetImageThrow("IMAGE_ICON_RAKE");
		IMAGE_ICON_ROOFCLEANER = aMgr.GetImageThrow("IMAGE_ICON_ROOFCLEANER");
		IMAGE_IMITATERCLOUDS = aMgr.GetImageThrow("IMAGE_IMITATERCLOUDS");
		IMAGE_IMITATERPUFFS = aMgr.GetImageThrow("IMAGE_IMITATERPUFFS");
		IMAGE_IMITATERSEED = aMgr.GetImageThrow("IMAGE_IMITATERSEED");
		IMAGE_IMITATERSEEDDISABLED = aMgr.GetImageThrow("IMAGE_IMITATERSEEDDISABLED");
		IMAGE_MELONPULT_PARTICLES = aMgr.GetImageThrow("IMAGE_MELONPULT_PARTICLES");
		IMAGE_MINIGAME_TROPHY = aMgr.GetImageThrow("IMAGE_MINIGAME_TROPHY");
		IMAGE_MONEYBAG = aMgr.GetImageThrow("IMAGE_MONEYBAG");
		IMAGE_MONEYBAG_HI_RES = aMgr.GetImageThrow("IMAGE_MONEYBAG_HI_RES");
		IMAGE_MOUSE_CURSOR = aMgr.GetImageThrow("IMAGE_MOUSE_CURSOR");
		IMAGE_NIGHT_GRAVE_GRAPHIC = aMgr.GetImageThrow("IMAGE_NIGHT_GRAVE_GRAPHIC");
		IMAGE_OPTIONS_BACKTOGAMEBUTTON0 = aMgr.GetImageThrow("IMAGE_OPTIONS_BACKTOGAMEBUTTON0");
		IMAGE_OPTIONS_BACKTOGAMEBUTTON2 = aMgr.GetImageThrow("IMAGE_OPTIONS_BACKTOGAMEBUTTON2");
		IMAGE_OPTIONS_CHECKBOX0 = aMgr.GetImageThrow("IMAGE_OPTIONS_CHECKBOX0");
		IMAGE_OPTIONS_CHECKBOX1 = aMgr.GetImageThrow("IMAGE_OPTIONS_CHECKBOX1");
		IMAGE_OPTIONS_MENUBACK = aMgr.GetImageThrow("IMAGE_OPTIONS_MENUBACK");
		IMAGE_OPTIONS_SLIDERKNOB2 = aMgr.GetImageThrow("IMAGE_OPTIONS_SLIDERKNOB2");
		IMAGE_OPTIONS_SLIDERKNOB_PLANT = aMgr.GetImageThrow("IMAGE_OPTIONS_SLIDERKNOB_PLANT");
		IMAGE_OPTIONS_SLIDERSLOT = aMgr.GetImageThrow("IMAGE_OPTIONS_SLIDERSLOT");
		IMAGE_OPTIONS_SLIDERSLOT_PLANT = aMgr.GetImageThrow("IMAGE_OPTIONS_SLIDERSLOT_PLANT");
		IMAGE_PACKET_PLANTS = aMgr.GetImageThrow("IMAGE_PACKET_PLANTS");
		IMAGE_PEA_PARTICLES = aMgr.GetImageThrow("IMAGE_PEA_PARTICLES");
		IMAGE_PEA_SHADOWS = aMgr.GetImageThrow("IMAGE_PEA_SHADOWS");
		IMAGE_PEA_SPLATS = aMgr.GetImageThrow("IMAGE_PEA_SPLATS");
		IMAGE_PHONOGRAPH = aMgr.GetImageThrow("IMAGE_PHONOGRAPH");
		IMAGE_PINATA = aMgr.GetImageThrow("IMAGE_PINATA");
		IMAGE_PLANTSHADOW = aMgr.GetImageThrow("IMAGE_PLANTSHADOW");
		IMAGE_PLANTSHADOW2 = aMgr.GetImageThrow("IMAGE_PLANTSHADOW2");
		IMAGE_PLANTSPEECHBUBBLE = aMgr.GetImageThrow("IMAGE_PLANTSPEECHBUBBLE");
		IMAGE_POOL = aMgr.GetImageThrow("IMAGE_POOL");
		IMAGE_POOLSPARKLY = aMgr.GetImageThrow("IMAGE_POOLSPARKLY");
		IMAGE_POOL_BASE = aMgr.GetImageThrow("IMAGE_POOL_BASE");
		IMAGE_POOL_BASE_NIGHT = aMgr.GetImageThrow("IMAGE_POOL_BASE_NIGHT");
		IMAGE_POOL_CAUSTIC_EFFECT = aMgr.GetImageThrow("IMAGE_POOL_CAUSTIC_EFFECT");
		IMAGE_POOL_NIGHT = aMgr.GetImageThrow("IMAGE_POOL_NIGHT");
		IMAGE_POOL_SHADING = aMgr.GetImageThrow("IMAGE_POOL_SHADING");
		IMAGE_POOL_SHADING_NIGHT = aMgr.GetImageThrow("IMAGE_POOL_SHADING_NIGHT");
		IMAGE_POTATOMINE_PARTICLES = aMgr.GetImageThrow("IMAGE_POTATOMINE_PARTICLES");
		IMAGE_PRESENT = aMgr.GetImageThrow("IMAGE_PRESENT");
		IMAGE_PRESENTOPEN = aMgr.GetImageThrow("IMAGE_PRESENTOPEN");
		IMAGE_PROJECTILECACTUS = aMgr.GetImageThrow("IMAGE_PROJECTILECACTUS");
		IMAGE_PROJECTILEPEA = aMgr.GetImageThrow("IMAGE_PROJECTILEPEA");
		IMAGE_PROJECTILESNOWPEA = aMgr.GetImageThrow("IMAGE_PROJECTILESNOWPEA");
		IMAGE_PROJECTILE_STAR = aMgr.GetImageThrow("IMAGE_PROJECTILE_STAR");
		IMAGE_PUFFSHROOM_PUFF1 = aMgr.GetImageThrow("IMAGE_PUFFSHROOM_PUFF1");
		IMAGE_QUICKPLAY_BUTTON = aMgr.GetImageThrow("IMAGE_QUICKPLAY_BUTTON");
		IMAGE_QUICKPLAY_BUTTON_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_QUICKPLAY_BUTTON_HIGHLIGHT");
		IMAGE_RAIN = aMgr.GetImageThrow("IMAGE_RAIN");
		IMAGE_REANIM_CABBAGEPULT_CABBAGE = aMgr.GetImageThrow("IMAGE_REANIM_CABBAGEPULT_CABBAGE");
		IMAGE_REANIM_COBCANNON_COB = aMgr.GetImageThrow("IMAGE_REANIM_COBCANNON_COB");
		IMAGE_REANIM_COINGLOW = aMgr.GetImageThrow("IMAGE_REANIM_COINGLOW");
		IMAGE_REANIM_COIN_GOLD_DOLLAR = aMgr.GetImageThrow("IMAGE_REANIM_COIN_GOLD_DOLLAR");
		IMAGE_REANIM_COIN_SILVER_DOLLAR = aMgr.GetImageThrow("IMAGE_REANIM_COIN_SILVER_DOLLAR");
		IMAGE_REANIM_CORNPULT_BUTTER = aMgr.GetImageThrow("IMAGE_REANIM_CORNPULT_BUTTER");
		IMAGE_REANIM_CORNPULT_BUTTER_SPLAT = aMgr.GetImageThrow("IMAGE_REANIM_CORNPULT_BUTTER_SPLAT");
		IMAGE_REANIM_CORNPULT_KERNAL = aMgr.GetImageThrow("IMAGE_REANIM_CORNPULT_KERNAL");
		IMAGE_REANIM_CRAZYDAVE_MOUTH1 = aMgr.GetImageThrow("IMAGE_REANIM_CRAZYDAVE_MOUTH1");
		IMAGE_REANIM_CRAZYDAVE_MOUTH4 = aMgr.GetImageThrow("IMAGE_REANIM_CRAZYDAVE_MOUTH4");
		IMAGE_REANIM_CRAZYDAVE_MOUTH5 = aMgr.GetImageThrow("IMAGE_REANIM_CRAZYDAVE_MOUTH5");
		IMAGE_REANIM_CRAZYDAVE_MOUTH6 = aMgr.GetImageThrow("IMAGE_REANIM_CRAZYDAVE_MOUTH6");
		IMAGE_REANIM_DIAMOND = aMgr.GetImageThrow("IMAGE_REANIM_DIAMOND");
		IMAGE_REANIM_GARLIC_BODY2 = aMgr.GetImageThrow("IMAGE_REANIM_GARLIC_BODY2");
		IMAGE_REANIM_GARLIC_BODY3 = aMgr.GetImageThrow("IMAGE_REANIM_GARLIC_BODY3");
		IMAGE_REANIM_MELONPULT_MELON = aMgr.GetImageThrow("IMAGE_REANIM_MELONPULT_MELON");
		IMAGE_REANIM_POT_TOP_DARK = aMgr.GetImageThrow("IMAGE_REANIM_POT_TOP_DARK");
		IMAGE_REANIM_PUMPKIN_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_PUMPKIN_DAMAGE1");
		IMAGE_REANIM_PUMPKIN_DAMAGE3 = aMgr.GetImageThrow("IMAGE_REANIM_PUMPKIN_DAMAGE3");
		IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_BUTTON = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_BUTTON");
		IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_HIGHLIGHT");
		IMAGE_REANIM_SELECTORSCREEN_ALMANAC_SHADOW = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_ALMANAC_SHADOW");
		IMAGE_REANIM_SELECTORSCREEN_BG = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_BG");
		IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_BUTTON = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_BUTTON");
		IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_HIGHLIGHT");
		IMAGE_REANIM_SELECTORSCREEN_KEY_SHADOW = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_KEY_SHADOW");
		IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_BUTTON = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_BUTTON");
		IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_HIGHLIGHT");
		IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_BUTTON = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_BUTTON");
		IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_HIGHLIGHT");
		IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_BUTTON = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_BUTTON");
		IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_HIGHLIGHT");
		IMAGE_REANIM_SELECTORSCREEN_WOODSIGN2_PRESS = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_WOODSIGN2_PRESS");
		IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3_PRESS = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3_PRESS");
		IMAGE_REANIM_STINKY_TURN3 = aMgr.GetImageThrow("IMAGE_REANIM_STINKY_TURN3");
		IMAGE_REANIM_TALLNUT_CRACKED1 = aMgr.GetImageThrow("IMAGE_REANIM_TALLNUT_CRACKED1");
		IMAGE_REANIM_TALLNUT_CRACKED2 = aMgr.GetImageThrow("IMAGE_REANIM_TALLNUT_CRACKED2");
		IMAGE_REANIM_TREE_BG = aMgr.GetImageThrow("IMAGE_REANIM_TREE_BG");
		IMAGE_REANIM_WALLNUT_BODY = aMgr.GetImageThrow("IMAGE_REANIM_WALLNUT_BODY");
		IMAGE_REANIM_WALLNUT_CRACKED1 = aMgr.GetImageThrow("IMAGE_REANIM_WALLNUT_CRACKED1");
		IMAGE_REANIM_WALLNUT_CRACKED2 = aMgr.GetImageThrow("IMAGE_REANIM_WALLNUT_CRACKED2");
		IMAGE_REANIM_WINTERMELON_PROJECTILE = aMgr.GetImageThrow("IMAGE_REANIM_WINTERMELON_PROJECTILE");
		IMAGE_REANIM_ZENGARDEN_BUGSPRAY_BOTTLE = aMgr.GetImageThrow("IMAGE_REANIM_ZENGARDEN_BUGSPRAY_BOTTLE");
		IMAGE_REANIM_ZOMBIE_BACKUP_INNERARM_HAND = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BACKUP_INNERARM_HAND");
		IMAGE_REANIM_ZOMBIE_BACKUP_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BACKUP_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_BALLOON_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BALLOON_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_HAND = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_HAND");
		IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_BOSS_EYEGLOW_BLUE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_EYEGLOW_BLUE");
		IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_BOSS_ICEBALL = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_ICEBALL");
		IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_BOSS_MOUTHGLOW_BLUE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_MOUTHGLOW_BLUE");
		IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_BUCKET1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BUCKET1");
		IMAGE_REANIM_ZOMBIE_BUCKET2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BUCKET2");
		IMAGE_REANIM_ZOMBIE_BUCKET3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BUCKET3");
		IMAGE_REANIM_ZOMBIE_BUNGI_HEAD_SCARED = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BUNGI_HEAD_SCARED");
		IMAGE_REANIM_ZOMBIE_CATAPULT_BASKETBALL = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CATAPULT_BASKETBALL");
		IMAGE_REANIM_ZOMBIE_CATAPULT_POLE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CATAPULT_POLE");
		IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE");
		IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE_WITHBALL = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE_WITHBALL");
		IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_WITHBALL = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_WITHBALL");
		IMAGE_REANIM_ZOMBIE_CATAPULT_SIDING_DAMAGE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CATAPULT_SIDING_DAMAGE");
		IMAGE_REANIM_ZOMBIE_CONE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CONE1");
		IMAGE_REANIM_ZOMBIE_CONE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CONE2");
		IMAGE_REANIM_ZOMBIE_CONE3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CONE3");
		IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT");
		IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT2");
		IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT3");
		IMAGE_REANIM_ZOMBIE_DIGGER_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_DIGGER_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_DIGGER_PICKAXE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_DIGGER_PICKAXE");
		IMAGE_REANIM_ZOMBIE_DISCO_OUTERARM_HAND = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_DISCO_OUTERARM_HAND");
		IMAGE_REANIM_ZOMBIE_DISCO_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_DISCO_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_DOLPHINRIDER_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_DOLPHINRIDER_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_FLAG1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FLAG1");
		IMAGE_REANIM_ZOMBIE_FLAG3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FLAG3");
		IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET");
		IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET2");
		IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET3");
		IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_HAND = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_HAND");
		IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_2");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_3");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_DUCKXING = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_DUCKXING");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_FOOT2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_FOOT2");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_REDEYE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_REDEYE");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_ZOMBIE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_ZOMBIE");
		IMAGE_REANIM_ZOMBIE_HEAD_GROSSOUT = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_HEAD_GROSSOUT");
		IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES1");
		IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES2");
		IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES3");
		IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES4 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES4");
		IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE");
		IMAGE_REANIM_ZOMBIE_IMP_ARM2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_IMP_ARM2");
		IMAGE_REANIM_ZOMBIE_JACKBOX_BOX = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_JACKBOX_BOX");
		IMAGE_REANIM_ZOMBIE_JACKBOX_OUTERARM_LOWER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_JACKBOX_OUTERARM_LOWER2");
		IMAGE_REANIM_ZOMBIE_LADDER_1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_LADDER_1");
		IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_LADDER_5 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_LADDER_5");
		IMAGE_REANIM_ZOMBIE_LADDER_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_LADDER_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_MUSTACHE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_MUSTACHE2");
		IMAGE_REANIM_ZOMBIE_MUSTACHE3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_MUSTACHE3");
		IMAGE_REANIM_ZOMBIE_OUTERARM_HAND = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_OUTERARM_HAND");
		IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_LOWER = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_LOWER");
		IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_PAPER_MADHEAD = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_PAPER_MADHEAD");
		IMAGE_REANIM_ZOMBIE_PAPER_PAPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_PAPER_PAPER2");
		IMAGE_REANIM_ZOMBIE_PAPER_PAPER3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_PAPER_PAPER3");
		IMAGE_REANIM_ZOMBIE_POGO_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POGO_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE1");
		IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE2");
		IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE1");
		IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE2");
		IMAGE_REANIM_ZOMBIE_POGO_STICKHANDS2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POGO_STICKHANDS2");
		IMAGE_REANIM_ZOMBIE_POLEVAULTER_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POLEVAULTER_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_SCREENDOOR1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_SCREENDOOR1");
		IMAGE_REANIM_ZOMBIE_SCREENDOOR2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_SCREENDOOR2");
		IMAGE_REANIM_ZOMBIE_SCREENDOOR3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_SCREENDOOR3");
		IMAGE_REANIM_ZOMBIE_SNORKLE_HEAD = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_SNORKLE_HEAD");
		IMAGE_REANIM_ZOMBIE_SNORKLE_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_SNORKLE_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_HAND = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_HAND");
		IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_ZAMBONI_WHEEL_FLAT = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_ZAMBONI_WHEEL_FLAT");
		IMAGE_ROCKSMALL = aMgr.GetImageThrow("IMAGE_ROCKSMALL");
		IMAGE_SCARY_POT = aMgr.GetImageThrow("IMAGE_SCARY_POT");
		IMAGE_SEEDBANK = aMgr.GetImageThrow("IMAGE_SEEDBANK");
		IMAGE_SEEDCHOOSER_BACKGROUND = aMgr.GetImageThrow("IMAGE_SEEDCHOOSER_BACKGROUND");
		IMAGE_SEEDCHOOSER_BUTTON = aMgr.GetImageThrow("IMAGE_SEEDCHOOSER_BUTTON");
		IMAGE_SEEDCHOOSER_BUTTON2 = aMgr.GetImageThrow("IMAGE_SEEDCHOOSER_BUTTON2");
		IMAGE_SEEDCHOOSER_BUTTON2_GLOW = aMgr.GetImageThrow("IMAGE_SEEDCHOOSER_BUTTON2_GLOW");
		IMAGE_SEEDCHOOSER_BUTTON_DISABLED = aMgr.GetImageThrow("IMAGE_SEEDCHOOSER_BUTTON_DISABLED");
		IMAGE_SEEDCHOOSER_BUTTON_GLOW = aMgr.GetImageThrow("IMAGE_SEEDCHOOSER_BUTTON_GLOW");
		IMAGE_SEEDCHOOSER_IMITATERADDON = aMgr.GetImageThrow("IMAGE_SEEDCHOOSER_IMITATERADDON");
		IMAGE_SEEDPACKETFLASH = aMgr.GetImageThrow("IMAGE_SEEDPACKETFLASH");
		IMAGE_SEEDPACKETSILHOUETTE = aMgr.GetImageThrow("IMAGE_SEEDPACKETSILHOUETTE");
		IMAGE_SEEDPACKET_LARGER = aMgr.GetImageThrow("IMAGE_SEEDPACKET_LARGER");
		IMAGE_SEEDS = aMgr.GetImageThrow("IMAGE_SEEDS");
		IMAGE_SELECTORSCREEN_ALMANAC = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_ALMANAC");
		IMAGE_SELECTORSCREEN_ALMANACHIGHLIGHT = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_ALMANACHIGHLIGHT");
		IMAGE_SELECTORSCREEN_HELP1 = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_HELP1");
		IMAGE_SELECTORSCREEN_HELP2 = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_HELP2");
		IMAGE_SELECTORSCREEN_LEVELNUMBERS = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_LEVELNUMBERS");
		IMAGE_SELECTORSCREEN_OPTIONS1 = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_OPTIONS1");
		IMAGE_SELECTORSCREEN_OPTIONS2 = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_OPTIONS2");
		IMAGE_SELECTORSCREEN_QUIT1 = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_QUIT1");
		IMAGE_SELECTORSCREEN_QUIT2 = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_QUIT2");
		IMAGE_SELECTORSCREEN_STORE = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_STORE");
		IMAGE_SELECTORSCREEN_STOREHIGHLIGHT = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_STOREHIGHLIGHT");
		IMAGE_SELECTORSCREEN_ZENGARDEN = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_ZENGARDEN");
		IMAGE_SELECTORSCREEN_ZENGARDENHIGHLIGHT = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_ZENGARDENHIGHLIGHT");
		IMAGE_SHOVEL = aMgr.GetImageThrow("IMAGE_SHOVEL");
		IMAGE_SHOVELBANK = aMgr.GetImageThrow("IMAGE_SHOVELBANK");
		IMAGE_SHOVEL_HI_RES = aMgr.GetImageThrow("IMAGE_SHOVEL_HI_RES");
		IMAGE_SLOTMACHINE_OVERLAY = aMgr.GetImageThrow("IMAGE_SLOTMACHINE_OVERLAY");
		IMAGE_SNOWFLAKES = aMgr.GetImageThrow("IMAGE_SNOWFLAKES");
		IMAGE_SNOWPEA_PARTICLES = aMgr.GetImageThrow("IMAGE_SNOWPEA_PARTICLES");
		IMAGE_SNOWPEA_PUFF = aMgr.GetImageThrow("IMAGE_SNOWPEA_PUFF");
		IMAGE_SNOWPEA_SPLATS = aMgr.GetImageThrow("IMAGE_SNOWPEA_SPLATS");
		IMAGE_SPOTLIGHT = aMgr.GetImageThrow("IMAGE_SPOTLIGHT");
		IMAGE_SPOTLIGHT2 = aMgr.GetImageThrow("IMAGE_SPOTLIGHT2");
		IMAGE_SQUIRREL = aMgr.GetImageThrow("IMAGE_SQUIRREL");
		IMAGE_STAR_PARTICLES = aMgr.GetImageThrow("IMAGE_STAR_PARTICLES");
		IMAGE_STAR_SPLATS = aMgr.GetImageThrow("IMAGE_STAR_SPLATS");
		IMAGE_STORE_SPEECHBUBBLE = aMgr.GetImageThrow("IMAGE_STORE_SPEECHBUBBLE");
		IMAGE_STORE_SPEECHBUBBLE2 = aMgr.GetImageThrow("IMAGE_STORE_SPEECHBUBBLE2");
		IMAGE_SUNBANK = aMgr.GetImageThrow("IMAGE_SUNBANK");
		IMAGE_SUNFLOWER_TROPHY = aMgr.GetImageThrow("IMAGE_SUNFLOWER_TROPHY");
		IMAGE_TACO = aMgr.GetImageThrow("IMAGE_TACO");
		IMAGE_TOMBSTONES = aMgr.GetImageThrow("IMAGE_TOMBSTONES");
		IMAGE_TOMBSTONE_MOUNDS = aMgr.GetImageThrow("IMAGE_TOMBSTONE_MOUNDS");
		IMAGE_TREEFOOD = aMgr.GetImageThrow("IMAGE_TREEFOOD");
		IMAGE_TROPHY = aMgr.GetImageThrow("IMAGE_TROPHY");
		IMAGE_TROPHY_HI_RES = aMgr.GetImageThrow("IMAGE_TROPHY_HI_RES");
		IMAGE_VASE_CHUNKS = aMgr.GetImageThrow("IMAGE_VASE_CHUNKS");
		IMAGE_WALLNUTPARTICLESLARGE = aMgr.GetImageThrow("IMAGE_WALLNUTPARTICLESLARGE");
		IMAGE_WALLNUTPARTICLESSMALL = aMgr.GetImageThrow("IMAGE_WALLNUTPARTICLESSMALL");
		IMAGE_WALLNUT_BOWLINGSTRIPE = aMgr.GetImageThrow("IMAGE_WALLNUT_BOWLINGSTRIPE");
		IMAGE_WATERDROP = aMgr.GetImageThrow("IMAGE_WATERDROP");
		IMAGE_WATERINGCAN = aMgr.GetImageThrow("IMAGE_WATERINGCAN");
		IMAGE_WATERINGCANGOLD = aMgr.GetImageThrow("IMAGE_WATERINGCANGOLD");
		IMAGE_WATERPARTICLE = aMgr.GetImageThrow("IMAGE_WATERPARTICLE");
		IMAGE_WHITEPIXEL = aMgr.GetImageThrow("IMAGE_WHITEPIXEL");
		IMAGE_WHITEWATER = aMgr.GetImageThrow("IMAGE_WHITEWATER");
		IMAGE_WHITEWATER_SHADOW = aMgr.GetImageThrow("IMAGE_WHITEWATER_SHADOW");
		IMAGE_WINTERMELON_PARTICLES = aMgr.GetImageThrow("IMAGE_WINTERMELON_PARTICLES");
		IMAGE_ZAMBONISMOKE = aMgr.GetImageThrow("IMAGE_ZAMBONISMOKE");
		IMAGE_ZENSHOPBUTTON = aMgr.GetImageThrow("IMAGE_ZENSHOPBUTTON");
		IMAGE_ZENSHOPBUTTON_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_ZENSHOPBUTTON_HIGHLIGHT");
		IMAGE_ZEN_GARDENGLOVE = aMgr.GetImageThrow("IMAGE_ZEN_GARDENGLOVE");
		IMAGE_ZEN_GOLDTOOLRETICLE = aMgr.GetImageThrow("IMAGE_ZEN_GOLDTOOLRETICLE");
		IMAGE_ZEN_MONEYSIGN = aMgr.GetImageThrow("IMAGE_ZEN_MONEYSIGN");
		IMAGE_ZEN_NEED_ICONS = aMgr.GetImageThrow("IMAGE_ZEN_NEED_ICONS");
		IMAGE_ZEN_NEXTGARDEN = aMgr.GetImageThrow("IMAGE_ZEN_NEXTGARDEN");
		IMAGE_ZEN_WHEELBARROW = aMgr.GetImageThrow("IMAGE_ZEN_WHEELBARROW");
		IMAGE_ZOMBIEBACKUPDANCERHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEBACKUPDANCERHEAD");
		IMAGE_ZOMBIEBALLOONHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEBALLOONHEAD");
		IMAGE_ZOMBIEBOBSLEDHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEBOBSLEDHEAD");
		IMAGE_ZOMBIEDANCERHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEDANCERHEAD");
		IMAGE_ZOMBIEDIGGERARM = aMgr.GetImageThrow("IMAGE_ZOMBIEDIGGERARM");
		IMAGE_ZOMBIEDIGGERHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEDIGGERHEAD");
		IMAGE_ZOMBIEDOLPHINRIDERHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEDOLPHINRIDERHEAD");
		IMAGE_ZOMBIEFOOTBALLHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEFOOTBALLHEAD");
		IMAGE_ZOMBIEFUTUREGLASSES = aMgr.GetImageThrow("IMAGE_ZOMBIEFUTUREGLASSES");
		IMAGE_ZOMBIEIMPHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEIMPHEAD");
		IMAGE_ZOMBIEJACKBOXARM = aMgr.GetImageThrow("IMAGE_ZOMBIEJACKBOXARM");
		IMAGE_ZOMBIELADDERHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIELADDERHEAD");
		IMAGE_ZOMBIEPOGO = aMgr.GetImageThrow("IMAGE_ZOMBIEPOGO");
		IMAGE_ZOMBIEPOLEVAULTERHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEPOLEVAULTERHEAD");
		IMAGE_ZOMBIEYETIHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEYETIHEAD");
		IMAGE_ZOMBIE_BOBSLED1 = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOBSLED1");
		IMAGE_ZOMBIE_BOBSLED2 = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOBSLED2");
		IMAGE_ZOMBIE_BOBSLED3 = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOBSLED3");
		IMAGE_ZOMBIE_BOBSLED4 = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOBSLED4");
		IMAGE_ZOMBIE_BOBSLED_INSIDE = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOBSLED_INSIDE");
		IMAGE_ZOMBIE_BOSS_FIREBALL_GROUNDPARTICLES = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOSS_FIREBALL_GROUNDPARTICLES");
		IMAGE_ZOMBIE_BOSS_FIREBALL_PARTICLES = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOSS_FIREBALL_PARTICLES");
		IMAGE_ZOMBIE_BOSS_ICEBALL_GROUNDPARTICLES = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOSS_ICEBALL_GROUNDPARTICLES");
		IMAGE_ZOMBIE_BOSS_ICEBALL_PARTICLES = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOSS_ICEBALL_PARTICLES");
		IMAGE_ZOMBIE_NOTE_SMALL = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE_SMALL");
		IMAGE_ZOMBIE_SEAWEED = aMgr.GetImageThrow("IMAGE_ZOMBIE_SEAWEED");
		IMAGE_ZOMBOSS_PARTICLES = aMgr.GetImageThrow("IMAGE_ZOMBOSS_PARTICLES");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// LoadingSounds Resources
int Sexy::SOUND_ACHIEVEMENT;
int Sexy::SOUND_AWOOGA;
int Sexy::SOUND_BALLOONINFLATE;
int Sexy::SOUND_BALLOON_POP;
int Sexy::SOUND_BASKETBALL;
int Sexy::SOUND_BIGCHOMP;
int Sexy::SOUND_BLEEP;
int Sexy::SOUND_BLOVER;
int Sexy::SOUND_BOING;
int Sexy::SOUND_BONK;
int Sexy::SOUND_BOSSBOULDERATTACK;
int Sexy::SOUND_BOSSEXPLOSION;
int Sexy::SOUND_BOWLING;
int Sexy::SOUND_BOWLINGIMPACT;
int Sexy::SOUND_BOWLINGIMPACT2;
int Sexy::SOUND_BUGSPRAY;
int Sexy::SOUND_BUNGEE_SCREAM;
int Sexy::SOUND_BUNGEE_SCREAM2;
int Sexy::SOUND_BUNGEE_SCREAM3;
int Sexy::SOUND_BUTTER;
int Sexy::SOUND_BUZZER;
int Sexy::SOUND_CERAMIC;
int Sexy::SOUND_CHERRYBOMB;
int Sexy::SOUND_CHIME;
int Sexy::SOUND_CHOMP;
int Sexy::SOUND_CHOMP2;
int Sexy::SOUND_CHOMPSOFT;
int Sexy::SOUND_COBLAUNCH;
int Sexy::SOUND_COFFEE;
int Sexy::SOUND_COIN;
int Sexy::SOUND_CRAZYDAVECRAZY;
int Sexy::SOUND_CRAZYDAVEEXTRALONG1;
int Sexy::SOUND_CRAZYDAVEEXTRALONG2;
int Sexy::SOUND_CRAZYDAVEEXTRALONG3;
int Sexy::SOUND_CRAZYDAVELONG1;
int Sexy::SOUND_CRAZYDAVELONG2;
int Sexy::SOUND_CRAZYDAVELONG3;
int Sexy::SOUND_CRAZYDAVESCREAM;
int Sexy::SOUND_CRAZYDAVESCREAM2;
int Sexy::SOUND_CRAZYDAVESHORT1;
int Sexy::SOUND_CRAZYDAVESHORT2;
int Sexy::SOUND_CRAZYDAVESHORT3;
int Sexy::SOUND_DANCER;
int Sexy::SOUND_DIAMOND;
int Sexy::SOUND_DIGGER_ZOMBIE;
int Sexy::SOUND_DIRT_RISE;
int Sexy::SOUND_DOLPHIN_APPEARS;
int Sexy::SOUND_DOLPHIN_BEFORE_JUMPING;
int Sexy::SOUND_DOOMSHROOM;
int Sexy::SOUND_EVILLAUGH;
int Sexy::SOUND_EXPLOSION;
int Sexy::SOUND_FERTILIZER;
int Sexy::SOUND_FINALFANFARE;
int Sexy::SOUND_FINALWAVE;
int Sexy::SOUND_FIREPEA;
int Sexy::SOUND_FLOOP;
int Sexy::SOUND_FROZEN;
int Sexy::SOUND_FUME;
int Sexy::SOUND_GARGANTUAR_THUMP;
int Sexy::SOUND_GARGANTUDEATH;
int Sexy::SOUND_GRASSSTEP;
int Sexy::SOUND_GRAVEBUSTERCHOMP;
int Sexy::SOUND_GRAVEBUTTON;
int Sexy::SOUND_GRAVESTONE_RUMBLE;
int Sexy::SOUND_GROAN;
int Sexy::SOUND_GROAN2;
int Sexy::SOUND_GROAN3;
int Sexy::SOUND_GROAN4;
int Sexy::SOUND_GROAN5;
int Sexy::SOUND_GROAN6;
int Sexy::SOUND_GULP;
int Sexy::SOUND_HATCHBACK_CLOSE;
int Sexy::SOUND_HATCHBACK_OPEN;
int Sexy::SOUND_HUGE_WAVE;
int Sexy::SOUND_HYDRAULIC;
int Sexy::SOUND_HYDRAULIC_SHORT;
int Sexy::SOUND_IGNITE;
int Sexy::SOUND_IGNITE2;
int Sexy::SOUND_IMP;
int Sexy::SOUND_IMP2;
int Sexy::SOUND_JACKINTHEBOX;
int Sexy::SOUND_JACK_SURPRISE;
int Sexy::SOUND_JACK_SURPRISE2;
int Sexy::SOUND_JALAPENO;
int Sexy::SOUND_JUICY;
int Sexy::SOUND_KERNELPULT;
int Sexy::SOUND_KERNELPULT2;
int Sexy::SOUND_LADDER_ZOMBIE;
int Sexy::SOUND_LAWNMOWER;
int Sexy::SOUND_LIGHTFILL;
int Sexy::SOUND_LIMBS_POP;
int Sexy::SOUND_LOSEMUSIC;
int Sexy::SOUND_LOWGROAN;
int Sexy::SOUND_LOWGROAN2;
int Sexy::SOUND_MAGNETSHROOM;
int Sexy::SOUND_MELONIMPACT;
int Sexy::SOUND_MELONIMPACT2;
int Sexy::SOUND_MINDCONTROLLED;
int Sexy::SOUND_MONEYFALLS;
int Sexy::SOUND_NEWSPAPER_RARRGH;
int Sexy::SOUND_NEWSPAPER_RARRGH2;
int Sexy::SOUND_NEWSPAPER_RIP;
int Sexy::SOUND_PAPER;
int Sexy::SOUND_PAUSE;
int Sexy::SOUND_PHONOGRAPH;
int Sexy::SOUND_PLANT;
int Sexy::SOUND_PLANT2;
int Sexy::SOUND_PLANTERN;
int Sexy::SOUND_PLANTGROW;
int Sexy::SOUND_PLANT_WATER;
int Sexy::SOUND_PLASTICHIT;
int Sexy::SOUND_PLASTICHIT2;
int Sexy::SOUND_POGO_ZOMBIE;
int Sexy::SOUND_POINTS;
int Sexy::SOUND_POLEVAULT;
int Sexy::SOUND_POOL_CLEANER;
int Sexy::SOUND_PORTAL;
int Sexy::SOUND_POTATO_MINE;
int Sexy::SOUND_PRIZE;
int Sexy::SOUND_PUFF;
int Sexy::SOUND_RAIN;
int Sexy::SOUND_READYSETPLANT;
int Sexy::SOUND_REVERSE_EXPLOSION;
int Sexy::SOUND_ROLL_IN;
int Sexy::SOUND_RVTHROW;
int Sexy::SOUND_SCREAM;
int Sexy::SOUND_SEEDLIFT;
int Sexy::SOUND_SHIELDHIT;
int Sexy::SOUND_SHIELDHIT2;
int Sexy::SOUND_SHOOP;
int Sexy::SOUND_SHOVEL;
int Sexy::SOUND_SIREN;
int Sexy::SOUND_SLOT_MACHINE;
int Sexy::SOUND_SLURP;
int Sexy::SOUND_SNOW_PEA_SPARKLES;
int Sexy::SOUND_SPLAT;
int Sexy::SOUND_SPLAT2;
int Sexy::SOUND_SPLAT3;
int Sexy::SOUND_SQUASH_HMM;
int Sexy::SOUND_SQUASH_HMM2;
int Sexy::SOUND_SUKHBIR;
int Sexy::SOUND_SUKHBIR2;
int Sexy::SOUND_SUKHBIR3;
int Sexy::SOUND_SUKHBIR4;
int Sexy::SOUND_SUKHBIR5;
int Sexy::SOUND_SUKHBIR6;
int Sexy::SOUND_SWING;
int Sexy::SOUND_TAP;
int Sexy::SOUND_TAP2;
int Sexy::SOUND_TAPGLASS;
int Sexy::SOUND_THROW;
int Sexy::SOUND_THROW2;
int Sexy::SOUND_THUNDER;
int Sexy::SOUND_VASE_BREAKING;
int Sexy::SOUND_WAKEUP;
int Sexy::SOUND_WATERING;
int Sexy::SOUND_WINMUSIC;
int Sexy::SOUND_YUCK;
int Sexy::SOUND_YUCK2;
int Sexy::SOUND_ZAMBONI;
int Sexy::SOUND_ZOMBAQUARIUM_DIE;
int Sexy::SOUND_ZOMBIESPLASH;
int Sexy::SOUND_ZOMBIE_ENTERING_WATER;
int Sexy::SOUND_ZOMBIE_FALLING_1;
int Sexy::SOUND_ZOMBIE_FALLING_2;

bool Sexy::ExtractLoadingSoundsResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		SOUND_ACHIEVEMENT = aMgr.GetSoundThrow("SOUND_ACHIEVEMENT");
		SOUND_AWOOGA = aMgr.GetSoundThrow("SOUND_AWOOGA");
		SOUND_BALLOONINFLATE = aMgr.GetSoundThrow("SOUND_BALLOONINFLATE");
		SOUND_BALLOON_POP = aMgr.GetSoundThrow("SOUND_BALLOON_POP");
		SOUND_BASKETBALL = aMgr.GetSoundThrow("SOUND_BASKETBALL");
		SOUND_BIGCHOMP = aMgr.GetSoundThrow("SOUND_BIGCHOMP");
		SOUND_BLEEP = aMgr.GetSoundThrow("SOUND_BLEEP");
		SOUND_BLOVER = aMgr.GetSoundThrow("SOUND_BLOVER");
		SOUND_BOING = aMgr.GetSoundThrow("SOUND_BOING");
		SOUND_BONK = aMgr.GetSoundThrow("SOUND_BONK");
		SOUND_BOSSBOULDERATTACK = aMgr.GetSoundThrow("SOUND_BOSSBOULDERATTACK");
		SOUND_BOSSEXPLOSION = aMgr.GetSoundThrow("SOUND_BOSSEXPLOSION");
		SOUND_BOWLING = aMgr.GetSoundThrow("SOUND_BOWLING");
		SOUND_BOWLINGIMPACT = aMgr.GetSoundThrow("SOUND_BOWLINGIMPACT");
		SOUND_BOWLINGIMPACT2 = aMgr.GetSoundThrow("SOUND_BOWLINGIMPACT2");
		SOUND_BUGSPRAY = aMgr.GetSoundThrow("SOUND_BUGSPRAY");
		SOUND_BUNGEE_SCREAM = aMgr.GetSoundThrow("SOUND_BUNGEE_SCREAM");
		SOUND_BUNGEE_SCREAM2 = aMgr.GetSoundThrow("SOUND_BUNGEE_SCREAM2");
		SOUND_BUNGEE_SCREAM3 = aMgr.GetSoundThrow("SOUND_BUNGEE_SCREAM3");
		SOUND_BUTTER = aMgr.GetSoundThrow("SOUND_BUTTER");
		SOUND_BUZZER = aMgr.GetSoundThrow("SOUND_BUZZER");
		SOUND_CERAMIC = aMgr.GetSoundThrow("SOUND_CERAMIC");
		SOUND_CHERRYBOMB = aMgr.GetSoundThrow("SOUND_CHERRYBOMB");
		SOUND_CHIME = aMgr.GetSoundThrow("SOUND_CHIME");
		SOUND_CHOMP = aMgr.GetSoundThrow("SOUND_CHOMP");
		SOUND_CHOMP2 = aMgr.GetSoundThrow("SOUND_CHOMP2");
		SOUND_CHOMPSOFT = aMgr.GetSoundThrow("SOUND_CHOMPSOFT");
		SOUND_COBLAUNCH = aMgr.GetSoundThrow("SOUND_COBLAUNCH");
		SOUND_COFFEE = aMgr.GetSoundThrow("SOUND_COFFEE");
		SOUND_COIN = aMgr.GetSoundThrow("SOUND_COIN");
		SOUND_CRAZYDAVECRAZY = aMgr.GetSoundThrow("SOUND_CRAZYDAVECRAZY");
		SOUND_CRAZYDAVEEXTRALONG1 = aMgr.GetSoundThrow("SOUND_CRAZYDAVEEXTRALONG1");
		SOUND_CRAZYDAVEEXTRALONG2 = aMgr.GetSoundThrow("SOUND_CRAZYDAVEEXTRALONG2");
		SOUND_CRAZYDAVEEXTRALONG3 = aMgr.GetSoundThrow("SOUND_CRAZYDAVEEXTRALONG3");
		SOUND_CRAZYDAVELONG1 = aMgr.GetSoundThrow("SOUND_CRAZYDAVELONG1");
		SOUND_CRAZYDAVELONG2 = aMgr.GetSoundThrow("SOUND_CRAZYDAVELONG2");
		SOUND_CRAZYDAVELONG3 = aMgr.GetSoundThrow("SOUND_CRAZYDAVELONG3");
		SOUND_CRAZYDAVESCREAM = aMgr.GetSoundThrow("SOUND_CRAZYDAVESCREAM");
		SOUND_CRAZYDAVESCREAM2 = aMgr.GetSoundThrow("SOUND_CRAZYDAVESCREAM2");
		SOUND_CRAZYDAVESHORT1 = aMgr.GetSoundThrow("SOUND_CRAZYDAVESHORT1");
		SOUND_CRAZYDAVESHORT2 = aMgr.GetSoundThrow("SOUND_CRAZYDAVESHORT2");
		SOUND_CRAZYDAVESHORT3 = aMgr.GetSoundThrow("SOUND_CRAZYDAVESHORT3");
		SOUND_DANCER = aMgr.GetSoundThrow("SOUND_DANCER");
		SOUND_DIAMOND = aMgr.GetSoundThrow("SOUND_DIAMOND");
		SOUND_DIGGER_ZOMBIE = aMgr.GetSoundThrow("SOUND_DIGGER_ZOMBIE");
		SOUND_DIRT_RISE = aMgr.GetSoundThrow("SOUND_DIRT_RISE");
		SOUND_DOLPHIN_APPEARS = aMgr.GetSoundThrow("SOUND_DOLPHIN_APPEARS");
		SOUND_DOLPHIN_BEFORE_JUMPING = aMgr.GetSoundThrow("SOUND_DOLPHIN_BEFORE_JUMPING");
		SOUND_DOOMSHROOM = aMgr.GetSoundThrow("SOUND_DOOMSHROOM");
		SOUND_EVILLAUGH = aMgr.GetSoundThrow("SOUND_EVILLAUGH");
		SOUND_EXPLOSION = aMgr.GetSoundThrow("SOUND_EXPLOSION");
		SOUND_FERTILIZER = aMgr.GetSoundThrow("SOUND_FERTILIZER");
		SOUND_FINALFANFARE = aMgr.GetSoundThrow("SOUND_FINALFANFARE");
		SOUND_FINALWAVE = aMgr.GetSoundThrow("SOUND_FINALWAVE");
		SOUND_FIREPEA = aMgr.GetSoundThrow("SOUND_FIREPEA");
		SOUND_FLOOP = aMgr.GetSoundThrow("SOUND_FLOOP");
		SOUND_FROZEN = aMgr.GetSoundThrow("SOUND_FROZEN");
		SOUND_FUME = aMgr.GetSoundThrow("SOUND_FUME");
		SOUND_GARGANTUAR_THUMP = aMgr.GetSoundThrow("SOUND_GARGANTUAR_THUMP");
		SOUND_GARGANTUDEATH = aMgr.GetSoundThrow("SOUND_GARGANTUDEATH");
		SOUND_GRASSSTEP = aMgr.GetSoundThrow("SOUND_GRASSSTEP");
		SOUND_GRAVEBUSTERCHOMP = aMgr.GetSoundThrow("SOUND_GRAVEBUSTERCHOMP");
		SOUND_GRAVEBUTTON = aMgr.GetSoundThrow("SOUND_GRAVEBUTTON");
		SOUND_GRAVESTONE_RUMBLE = aMgr.GetSoundThrow("SOUND_GRAVESTONE_RUMBLE");
		SOUND_GROAN = aMgr.GetSoundThrow("SOUND_GROAN");
		SOUND_GROAN2 = aMgr.GetSoundThrow("SOUND_GROAN2");
		SOUND_GROAN3 = aMgr.GetSoundThrow("SOUND_GROAN3");
		SOUND_GROAN4 = aMgr.GetSoundThrow("SOUND_GROAN4");
		SOUND_GROAN5 = aMgr.GetSoundThrow("SOUND_GROAN5");
		SOUND_GROAN6 = aMgr.GetSoundThrow("SOUND_GROAN6");
		SOUND_GULP = aMgr.GetSoundThrow("SOUND_GULP");
		SOUND_HATCHBACK_CLOSE = aMgr.GetSoundThrow("SOUND_HATCHBACK_CLOSE");
		SOUND_HATCHBACK_OPEN = aMgr.GetSoundThrow("SOUND_HATCHBACK_OPEN");
		SOUND_HUGE_WAVE = aMgr.GetSoundThrow("SOUND_HUGE_WAVE");
		SOUND_HYDRAULIC = aMgr.GetSoundThrow("SOUND_HYDRAULIC");
		SOUND_HYDRAULIC_SHORT = aMgr.GetSoundThrow("SOUND_HYDRAULIC_SHORT");
		SOUND_IGNITE = aMgr.GetSoundThrow("SOUND_IGNITE");
		SOUND_IGNITE2 = aMgr.GetSoundThrow("SOUND_IGNITE2");
		SOUND_IMP = aMgr.GetSoundThrow("SOUND_IMP");
		SOUND_IMP2 = aMgr.GetSoundThrow("SOUND_IMP2");
		SOUND_JACKINTHEBOX = aMgr.GetSoundThrow("SOUND_JACKINTHEBOX");
		SOUND_JACK_SURPRISE = aMgr.GetSoundThrow("SOUND_JACK_SURPRISE");
		SOUND_JACK_SURPRISE2 = aMgr.GetSoundThrow("SOUND_JACK_SURPRISE2");
		SOUND_JALAPENO = aMgr.GetSoundThrow("SOUND_JALAPENO");
		SOUND_JUICY = aMgr.GetSoundThrow("SOUND_JUICY");
		SOUND_KERNELPULT = aMgr.GetSoundThrow("SOUND_KERNELPULT");
		SOUND_KERNELPULT2 = aMgr.GetSoundThrow("SOUND_KERNELPULT2");
		SOUND_LADDER_ZOMBIE = aMgr.GetSoundThrow("SOUND_LADDER_ZOMBIE");
		SOUND_LAWNMOWER = aMgr.GetSoundThrow("SOUND_LAWNMOWER");
		SOUND_LIGHTFILL = aMgr.GetSoundThrow("SOUND_LIGHTFILL");
		SOUND_LIMBS_POP = aMgr.GetSoundThrow("SOUND_LIMBS_POP");
		SOUND_LOSEMUSIC = aMgr.GetSoundThrow("SOUND_LOSEMUSIC");
		SOUND_LOWGROAN = aMgr.GetSoundThrow("SOUND_LOWGROAN");
		SOUND_LOWGROAN2 = aMgr.GetSoundThrow("SOUND_LOWGROAN2");
		SOUND_MAGNETSHROOM = aMgr.GetSoundThrow("SOUND_MAGNETSHROOM");
		SOUND_MELONIMPACT = aMgr.GetSoundThrow("SOUND_MELONIMPACT");
		SOUND_MELONIMPACT2 = aMgr.GetSoundThrow("SOUND_MELONIMPACT2");
		SOUND_MINDCONTROLLED = aMgr.GetSoundThrow("SOUND_MINDCONTROLLED");
		SOUND_MONEYFALLS = aMgr.GetSoundThrow("SOUND_MONEYFALLS");
		SOUND_NEWSPAPER_RARRGH = aMgr.GetSoundThrow("SOUND_NEWSPAPER_RARRGH");
		SOUND_NEWSPAPER_RARRGH2 = aMgr.GetSoundThrow("SOUND_NEWSPAPER_RARRGH2");
		SOUND_NEWSPAPER_RIP = aMgr.GetSoundThrow("SOUND_NEWSPAPER_RIP");
		SOUND_PAPER = aMgr.GetSoundThrow("SOUND_PAPER");
		SOUND_PAUSE = aMgr.GetSoundThrow("SOUND_PAUSE");
		SOUND_PHONOGRAPH = aMgr.GetSoundThrow("SOUND_PHONOGRAPH");
		SOUND_PLANT = aMgr.GetSoundThrow("SOUND_PLANT");
		SOUND_PLANT2 = aMgr.GetSoundThrow("SOUND_PLANT2");
		SOUND_PLANTERN = aMgr.GetSoundThrow("SOUND_PLANTERN");
		SOUND_PLANTGROW = aMgr.GetSoundThrow("SOUND_PLANTGROW");
		SOUND_PLANT_WATER = aMgr.GetSoundThrow("SOUND_PLANT_WATER");
		SOUND_PLASTICHIT = aMgr.GetSoundThrow("SOUND_PLASTICHIT");
		SOUND_PLASTICHIT2 = aMgr.GetSoundThrow("SOUND_PLASTICHIT2");
		SOUND_POGO_ZOMBIE = aMgr.GetSoundThrow("SOUND_POGO_ZOMBIE");
		SOUND_POINTS = aMgr.GetSoundThrow("SOUND_POINTS");
		SOUND_POLEVAULT = aMgr.GetSoundThrow("SOUND_POLEVAULT");
		SOUND_POOL_CLEANER = aMgr.GetSoundThrow("SOUND_POOL_CLEANER");
		SOUND_PORTAL = aMgr.GetSoundThrow("SOUND_PORTAL");
		SOUND_POTATO_MINE = aMgr.GetSoundThrow("SOUND_POTATO_MINE");
		SOUND_PRIZE = aMgr.GetSoundThrow("SOUND_PRIZE");
		SOUND_PUFF = aMgr.GetSoundThrow("SOUND_PUFF");
		SOUND_RAIN = aMgr.GetSoundThrow("SOUND_RAIN");
		SOUND_READYSETPLANT = aMgr.GetSoundThrow("SOUND_READYSETPLANT");
		SOUND_REVERSE_EXPLOSION = aMgr.GetSoundThrow("SOUND_REVERSE_EXPLOSION");
		SOUND_ROLL_IN = aMgr.GetSoundThrow("SOUND_ROLL_IN");
		SOUND_RVTHROW = aMgr.GetSoundThrow("SOUND_RVTHROW");
		SOUND_SCREAM = aMgr.GetSoundThrow("SOUND_SCREAM");
		SOUND_SEEDLIFT = aMgr.GetSoundThrow("SOUND_SEEDLIFT");
		SOUND_SHIELDHIT = aMgr.GetSoundThrow("SOUND_SHIELDHIT");
		SOUND_SHIELDHIT2 = aMgr.GetSoundThrow("SOUND_SHIELDHIT2");
		SOUND_SHOOP = aMgr.GetSoundThrow("SOUND_SHOOP");
		SOUND_SHOVEL = aMgr.GetSoundThrow("SOUND_SHOVEL");
		SOUND_SIREN = aMgr.GetSoundThrow("SOUND_SIREN");
		SOUND_SLOT_MACHINE = aMgr.GetSoundThrow("SOUND_SLOT_MACHINE");
		SOUND_SLURP = aMgr.GetSoundThrow("SOUND_SLURP");
		SOUND_SNOW_PEA_SPARKLES = aMgr.GetSoundThrow("SOUND_SNOW_PEA_SPARKLES");
		SOUND_SPLAT = aMgr.GetSoundThrow("SOUND_SPLAT");
		SOUND_SPLAT2 = aMgr.GetSoundThrow("SOUND_SPLAT2");
		SOUND_SPLAT3 = aMgr.GetSoundThrow("SOUND_SPLAT3");
		SOUND_SQUASH_HMM = aMgr.GetSoundThrow("SOUND_SQUASH_HMM");
		SOUND_SQUASH_HMM2 = aMgr.GetSoundThrow("SOUND_SQUASH_HMM2");
		SOUND_SUKHBIR = aMgr.GetSoundThrow("SOUND_SUKHBIR");
		SOUND_SUKHBIR2 = aMgr.GetSoundThrow("SOUND_SUKHBIR2");
		SOUND_SUKHBIR3 = aMgr.GetSoundThrow("SOUND_SUKHBIR3");
		SOUND_SUKHBIR4 = aMgr.GetSoundThrow("SOUND_SUKHBIR4");
		SOUND_SUKHBIR5 = aMgr.GetSoundThrow("SOUND_SUKHBIR5");
		SOUND_SUKHBIR6 = aMgr.GetSoundThrow("SOUND_SUKHBIR6");
		SOUND_SWING = aMgr.GetSoundThrow("SOUND_SWING");
		SOUND_TAP = aMgr.GetSoundThrow("SOUND_TAP");
		SOUND_TAP2 = aMgr.GetSoundThrow("SOUND_TAP2");
		SOUND_TAPGLASS = aMgr.GetSoundThrow("SOUND_TAPGLASS");
		SOUND_THROW = aMgr.GetSoundThrow("SOUND_THROW");
		SOUND_THROW2 = aMgr.GetSoundThrow("SOUND_THROW2");
		SOUND_THUNDER = aMgr.GetSoundThrow("SOUND_THUNDER");
		SOUND_VASE_BREAKING = aMgr.GetSoundThrow("SOUND_VASE_BREAKING");
		SOUND_WAKEUP = aMgr.GetSoundThrow("SOUND_WAKEUP");
		SOUND_WATERING = aMgr.GetSoundThrow("SOUND_WATERING");
		SOUND_WINMUSIC = aMgr.GetSoundThrow("SOUND_WINMUSIC");
		SOUND_YUCK = aMgr.GetSoundThrow("SOUND_YUCK");
		SOUND_YUCK2 = aMgr.GetSoundThrow("SOUND_YUCK2");
		SOUND_ZAMBONI = aMgr.GetSoundThrow("SOUND_ZAMBONI");
		SOUND_ZOMBAQUARIUM_DIE = aMgr.GetSoundThrow("SOUND_ZOMBAQUARIUM_DIE");
		SOUND_ZOMBIESPLASH = aMgr.GetSoundThrow("SOUND_ZOMBIESPLASH");
		SOUND_ZOMBIE_ENTERING_WATER = aMgr.GetSoundThrow("SOUND_ZOMBIE_ENTERING_WATER");
		SOUND_ZOMBIE_FALLING_1 = aMgr.GetSoundThrow("SOUND_ZOMBIE_FALLING_1");
		SOUND_ZOMBIE_FALLING_2 = aMgr.GetSoundThrow("SOUND_ZOMBIE_FALLING_2");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

static void* gResources[] =
{
	&IMAGE_BLANK,
	&IMAGE_POPCAP_LOGO,
	&IMAGE_PARTNER_LOGO,
	&IMAGE_TITLESCREEN,
	&IMAGE_LOADBAR_DIRT,
	&IMAGE_LOADBAR_GRASS,
	&IMAGE_PVZ_LOGO,
	&IMAGE_REANIM_SODROLLCAP,
	&FONT_BRIANNETOD16,
	&SOUND_BUTTONCLICK,
	&SOUND_LOADINGBAR_FLOWER,
	&SOUND_LOADINGBAR_ZOMBIE,
	&FONT_IMAGE_HOUSEOFTERROR28,
	&FONT_HOUSEOFTERROR28,
	&FONT_HOUSEOFTERROR20,
	&FONT_HOUSEOFTERROR16,
	&FONT_TINYBOLD,
	&FONT_CONTINUUMBOLD14,
	&FONT_CONTINUUMBOLD14OUTLINE,
	&FONT_DWARVENTODCRAFT12,
	&FONT_DWARVENTODCRAFT15,
	&FONT_DWARVENTODCRAFT18,
	&FONT_DWARVENTODCRAFT18BRIGHTGREENINSET,
	&FONT_DWARVENTODCRAFT18GREENINSET,
	&FONT_DWARVENTODCRAFT18YELLOW,
	&FONT_DWARVENTODCRAFT24,
	&FONT_DWARVENTODCRAFT36BRIGHTGREENINSET,
	&FONT_DWARVENTODCRAFT36GREENINSET,
	&FONT_PICO129,
	&FONT_BRIANNETOD12,
	&IMAGE_MOUSE_CURSOR,
	&IMAGE_EDITBOX,
	&IMAGE_DIALOG_TOPLEFT,
	&IMAGE_DIALOG_TOPMIDDLE,
	&IMAGE_DIALOG_TOPRIGHT,
	&IMAGE_DIALOG_CENTERLEFT,
	&IMAGE_DIALOG_CENTERMIDDLE,
	&IMAGE_DIALOG_CENTERRIGHT,
	&IMAGE_DIALOG_BOTTOMLEFT,
	&IMAGE_DIALOG_BOTTOMMIDDLE,
	&IMAGE_DIALOG_BOTTOMRIGHT,
	&IMAGE_DIALOG_BIGBOTTOMLEFT,
	&IMAGE_DIALOG_BIGBOTTOMMIDDLE,
	&IMAGE_DIALOG_BIGBOTTOMRIGHT,
	&IMAGE_DIALOG_HEADER,
	&IMAGE_BUTTON_LEFT,
	&IMAGE_BUTTON_MIDDLE,
	&IMAGE_BUTTON_RIGHT,
	&IMAGE_BUTTON_SMALL,
	&IMAGE_BUTTON_DOWN_LEFT,
	&IMAGE_BUTTON_DOWN_MIDDLE,
	&IMAGE_BUTTON_DOWN_RIGHT,
	&IMAGE_BUTTON_DOWN_SMALL,
	&IMAGE_SEEDCHOOSER_BACKGROUND,
	&IMAGE_SEEDCHOOSER_BUTTON,
	&IMAGE_SEEDCHOOSER_BUTTON_DISABLED,
	&IMAGE_SEEDCHOOSER_BUTTON_GLOW,
	&IMAGE_SEEDCHOOSER_BUTTON2,
	&IMAGE_SEEDCHOOSER_BUTTON2_GLOW,
	&IMAGE_SEEDCHOOSER_IMITATERADDON,
	&IMAGE_SEEDS,
	&IMAGE_SEEDPACKET_LARGER,
	&IMAGE_SEEDPACKETSILHOUETTE,
	&IMAGE_FLAGMETER,
	&IMAGE_FLAGMETERLEVELPROGRESS,
	&IMAGE_FLAGMETERPARTS,
	&IMAGE_TROPHY,
	&IMAGE_TROPHY_HI_RES,
	&IMAGE_MINIGAME_TROPHY,
	&IMAGE_ZOMBIE_NOTE_SMALL,
	&IMAGE_TACO,
	&IMAGE_CARKEYS,
	&IMAGE_ALMANAC,
	&IMAGE_ICON_POOLCLEANER,
	&IMAGE_ICON_ROOFCLEANER,
	&IMAGE_ICON_RAKE,
	&IMAGE_BRAIN,
	&IMAGE_MONEYBAG,
	&IMAGE_MONEYBAG_HI_RES,
	&IMAGE_CHOCOLATE,
	&IMAGE_OPTIONS_BACKTOGAMEBUTTON0,
	&IMAGE_OPTIONS_BACKTOGAMEBUTTON2,
	&IMAGE_OPTIONS_CHECKBOX0,
	&IMAGE_OPTIONS_CHECKBOX1,
	&IMAGE_OPTIONS_MENUBACK,
	&IMAGE_OPTIONS_SLIDERKNOB2,
	&IMAGE_OPTIONS_SLIDERSLOT,
	&IMAGE_OPTIONS_SLIDERKNOB_PLANT,
	&IMAGE_OPTIONS_SLIDERSLOT_PLANT,
	&IMAGE_CHALLENGE_SLIDERSLOT,
	&IMAGE_SELECTORSCREEN_HELP1,
	&IMAGE_SELECTORSCREEN_HELP2,
	&IMAGE_SELECTORSCREEN_OPTIONS1,
	&IMAGE_SELECTORSCREEN_OPTIONS2,
	&IMAGE_SELECTORSCREEN_QUIT1,
	&IMAGE_SELECTORSCREEN_QUIT2,
	&IMAGE_SELECTORSCREEN_ALMANAC,
	&IMAGE_SELECTORSCREEN_ALMANACHIGHLIGHT,
	&IMAGE_SELECTORSCREEN_STORE,
	&IMAGE_SELECTORSCREEN_STOREHIGHLIGHT,
	&IMAGE_SELECTORSCREEN_LEVELNUMBERS,
	&IMAGE_SELECTORSCREEN_ZENGARDEN,
	&IMAGE_ACHIEVEMENT_BUTTON,
	&IMAGE_ACHIEVEMENT_HIGHLIGHT,
	&IMAGE_QUICKPLAY_BUTTON,
	&IMAGE_QUICKPLAY_BUTTON_HIGHLIGHT,
	&IMAGE_SELECTORSCREEN_ZENGARDENHIGHLIGHT,
	&IMAGE_STORE_SPEECHBUBBLE,
	&IMAGE_STORE_SPEECHBUBBLE2,
	&IMAGE_SHOVEL,
	&IMAGE_SHOVEL_HI_RES,
	&IMAGE_TOMBSTONES,
	&IMAGE_TOMBSTONE_MOUNDS,
	&IMAGE_NIGHT_GRAVE_GRAPHIC,
	&IMAGE_CRATER,
	&IMAGE_CRATER_FADING,
	&IMAGE_CRATER_ROOF_CENTER,
	&IMAGE_CRATER_ROOF_LEFT,
	&IMAGE_CRATER_WATER_DAY,
	&IMAGE_CRATER_WATER_NIGHT,
	&IMAGE_COBCANNON_TARGET,
	&IMAGE_COBCANNON_POPCORN,
	&IMAGE_FERTILIZER,
	&IMAGE_WATERINGCAN,
	&IMAGE_WATERINGCANGOLD,
	&IMAGE_PHONOGRAPH,
	&IMAGE_BEGHOULED_TWIST_OVERLAY,
	&IMAGE_ZEN_GOLDTOOLRETICLE,
	&IMAGE_ZEN_GARDENGLOVE,
	&IMAGE_ZEN_MONEYSIGN,
	&IMAGE_ZEN_NEXTGARDEN,
	&IMAGE_ZEN_WHEELBARROW,
	&IMAGE_ZENSHOPBUTTON,
	&IMAGE_ZENSHOPBUTTON_HIGHLIGHT,
	&IMAGE_FASTBUTTON,
	&IMAGE_FASTBUTTON_HIGHLIGHT,
	&IMAGE_PRESENT,
	&IMAGE_PRESENTOPEN,
	&IMAGE_SUNFLOWER_TROPHY,
	&IMAGE_SLOTMACHINE_OVERLAY,
	&IMAGE_SCARY_POT,
	&IMAGE_BUG_SPRAY,
	&IMAGE_PLANTSPEECHBUBBLE,
	&IMAGE_WATERDROP,
	&IMAGE_TREEFOOD,
	&IMAGE_PACKET_PLANTS,
	&IMAGE_ZEN_NEED_ICONS,
	&IMAGE_SQUIRREL,
	&IMAGE_PROJECTILEPEA,
	&IMAGE_PROJECTILESNOWPEA,
	&IMAGE_PROJECTILECACTUS,
	&IMAGE_DIRTSMALL,
	&IMAGE_DIRTBIG,
	&IMAGE_ROCKSMALL,
	&IMAGE_WATERPARTICLE,
	&IMAGE_WHITEWATER,
	&IMAGE_WHITEWATER_SHADOW,
	&IMAGE_MELONPULT_PARTICLES,
	&IMAGE_WINTERMELON_PARTICLES,
	&IMAGE_PROJECTILE_STAR,
	&IMAGE_SEEDBANK,
	&IMAGE_CONVEYORBELT_BACKDROP,
	&IMAGE_CONVEYORBELT,
	&IMAGE_SHOVELBANK,
	&IMAGE_SUNBANK,
	&IMAGE_COINBANK,
	&IMAGE_POOL,
	&IMAGE_POOL_NIGHT,
	&IMAGE_POOL_BASE,
	&IMAGE_POOL_BASE_NIGHT,
	&IMAGE_POOL_SHADING,
	&IMAGE_POOL_SHADING_NIGHT,
	&IMAGE_POOL_CAUSTIC_EFFECT,
	&IMAGE_PLANTSHADOW,
	&IMAGE_PLANTSHADOW2,
	&IMAGE_PEA_SHADOWS,
	&IMAGE_WALLNUT_BOWLINGSTRIPE,
	&IMAGE_ICE,
	&IMAGE_ICE_CAP,
	&IMAGE_ICE_SPARKLES,
	&IMAGE_IMITATERSEED,
	&IMAGE_ALMANAC_IMITATER,
	&IMAGE_IMITATERSEEDDISABLED,
	&IMAGE_ICETRAP,
	&IMAGE_ICETRAP2,
	&IMAGE_ICETRAP_PARTICLES,
	&IMAGE_ZOMBIE_BOBSLED1,
	&IMAGE_ZOMBIE_BOBSLED2,
	&IMAGE_ZOMBIE_BOBSLED3,
	&IMAGE_ZOMBIE_BOBSLED4,
	&IMAGE_ZOMBIE_BOBSLED_INSIDE,
	&IMAGE_BUNGEECORD,
	&IMAGE_BUNGEETARGET,
	&IMAGE_SPOTLIGHT,
	&IMAGE_SPOTLIGHT2,
	&IMAGE_WHITEPIXEL,
	&IMAGE_ZOMBIEPOLEVAULTERHEAD,
	&IMAGE_ZOMBIEFOOTBALLHEAD,
	&IMAGE_POOLSPARKLY,
	&IMAGE_WALLNUTPARTICLESSMALL,
	&IMAGE_WALLNUTPARTICLESLARGE,
	&IMAGE_PEA_SPLATS,
	&IMAGE_STAR_PARTICLES,
	&IMAGE_STAR_SPLATS,
	&IMAGE_PEA_PARTICLES,
	&IMAGE_SNOWPEA_SPLATS,
	&IMAGE_SNOWPEA_PARTICLES,
	&IMAGE_SNOWPEA_PUFF,
	&IMAGE_SNOWFLAKES,
	&IMAGE_POTATOMINE_PARTICLES,
	&IMAGE_PUFFSHROOM_PUFF1,
	&IMAGE_ZAMBONISMOKE,
	&IMAGE_ZOMBIEDANCERHEAD,
	&IMAGE_ZOMBIEBALLOONHEAD,
	&IMAGE_ZOMBIEIMPHEAD,
	&IMAGE_ZOMBIEDIGGERHEAD,
	&IMAGE_ZOMBIEDIGGERARM,
	&IMAGE_ZOMBIEDOLPHINRIDERHEAD,
	&IMAGE_ZOMBIEPOGO,
	&IMAGE_ZOMBIEBACKUPDANCERHEAD,
	&IMAGE_ZOMBIEBOBSLEDHEAD,
	&IMAGE_ZOMBIELADDERHEAD,
	&IMAGE_ZOMBIEYETIHEAD,
	&IMAGE_SEEDPACKETFLASH,
	&IMAGE_ZOMBIEJACKBOXARM,
	&IMAGE_IMITATERCLOUDS,
	&IMAGE_IMITATERPUFFS,
	&IMAGE_ZOMBIE_BOSS_FIREBALL_PARTICLES,
	&IMAGE_ZOMBIE_BOSS_ICEBALL_PARTICLES,
	&IMAGE_ZOMBIE_BOSS_FIREBALL_GROUNDPARTICLES,
	&IMAGE_ZOMBIE_BOSS_ICEBALL_GROUNDPARTICLES,
	&IMAGE_DOOMSHROOM_EXPLOSION_BASE,
	&IMAGE_RAIN,
	&IMAGE_VASE_CHUNKS,
	&IMAGE_ZOMBOSS_PARTICLES,
	&IMAGE_AWARDPICKUPGLOW,
	&IMAGE_ZOMBIE_SEAWEED,
	&IMAGE_PINATA,
	&IMAGE_ZOMBIEFUTUREGLASSES,
	&IMAGE_DUST_PUFFS,
	&IMAGE_REANIM_WALLNUT_BODY,
	&IMAGE_REANIM_WALLNUT_CRACKED1,
	&IMAGE_REANIM_WALLNUT_CRACKED2,
	&IMAGE_REANIM_TALLNUT_CRACKED1,
	&IMAGE_REANIM_TALLNUT_CRACKED2,
	&IMAGE_REANIM_PUMPKIN_DAMAGE1,
	&IMAGE_REANIM_PUMPKIN_DAMAGE3,
	&IMAGE_REANIM_ZOMBIE_CONE1,
	&IMAGE_REANIM_ZOMBIE_CONE2,
	&IMAGE_REANIM_ZOMBIE_CONE3,
	&IMAGE_REANIM_ZOMBIE_BUCKET1,
	&IMAGE_REANIM_ZOMBIE_BUCKET2,
	&IMAGE_REANIM_ZOMBIE_BUCKET3,
	&IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT,
	&IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT2,
	&IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT3,
	&IMAGE_REANIM_ZOMBIE_SCREENDOOR1,
	&IMAGE_REANIM_ZOMBIE_SCREENDOOR2,
	&IMAGE_REANIM_ZOMBIE_SCREENDOOR3,
	&IMAGE_REANIM_ZOMBIE_FLAG1,
	&IMAGE_REANIM_ZOMBIE_FLAG3,
	&IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET,
	&IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET2,
	&IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET3,
	&IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_HAND,
	&IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_LOWER,
	&IMAGE_REANIM_ZOMBIE_PAPER_PAPER2,
	&IMAGE_REANIM_ZOMBIE_PAPER_PAPER3,
	&IMAGE_REANIM_ZOMBIE_PAPER_MADHEAD,
	&IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_ZAMBONI_WHEEL_FLAT,
	&IMAGE_REANIM_COIN_SILVER_DOLLAR,
	&IMAGE_REANIM_COIN_GOLD_DOLLAR,
	&IMAGE_REANIM_DIAMOND,
	&IMAGE_REANIM_COINGLOW,
	&IMAGE_REANIM_ZOMBIE_DISCO_OUTERARM_HAND,
	&IMAGE_REANIM_ZOMBIE_DISCO_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_BACKUP_INNERARM_HAND,
	&IMAGE_REANIM_ZOMBIE_BACKUP_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_POLEVAULTER_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_OUTERARM_HAND,
	&IMAGE_REANIM_ZOMBIE_BALLOON_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE,
	&IMAGE_REANIM_ZOMBIE_IMP_ARM2,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_2,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_3,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_DUCKXING,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_ZOMBIE,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_FOOT2,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_REDEYE,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE,
	&IMAGE_REANIM_ZOMBIE_DIGGER_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_DOLPHINRIDER_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_POGO_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE1,
	&IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE2,
	&IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_POGO_STICKHANDS2,
	&IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_HAND,
	&IMAGE_REANIM_ZOMBIE_JACKBOX_BOX,
	&IMAGE_REANIM_ZOMBIE_JACKBOX_OUTERARM_LOWER2,
	&IMAGE_REANIM_ZOMBIE_SNORKLE_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_BUNGI_HEAD_SCARED,
	&IMAGE_REANIM_ZOMBIE_CATAPULT_BASKETBALL,
	&IMAGE_REANIM_ZOMBIE_CATAPULT_POLE,
	&IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE,
	&IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_WITHBALL,
	&IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE_WITHBALL,
	&IMAGE_REANIM_ZOMBIE_CATAPULT_SIDING_DAMAGE,
	&IMAGE_REANIM_ZOMBIE_LADDER_1,
	&IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_LADDER_5,
	&IMAGE_REANIM_ZOMBIE_LADDER_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_BOSS_ICEBALL,
	&IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_BOSS_EYEGLOW_BLUE,
	&IMAGE_REANIM_ZOMBIE_BOSS_MOUTHGLOW_BLUE,
	&IMAGE_REANIM_CABBAGEPULT_CABBAGE,
	&IMAGE_REANIM_CORNPULT_KERNAL,
	&IMAGE_REANIM_CORNPULT_BUTTER,
	&IMAGE_REANIM_CORNPULT_BUTTER_SPLAT,
	&IMAGE_REANIM_MELONPULT_MELON,
	&IMAGE_REANIM_WINTERMELON_PROJECTILE,
	&IMAGE_REANIM_ZOMBIE_DIGGER_PICKAXE,
	&IMAGE_REANIM_ZOMBIE_HEAD_GROSSOUT,
	&IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES1,
	&IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES2,
	&IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES3,
	&IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES4,
	&IMAGE_REANIM_GARLIC_BODY2,
	&IMAGE_REANIM_GARLIC_BODY3,
	&IMAGE_REANIM_COBCANNON_COB,
	&IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_HAND,
	&IMAGE_REANIM_ZOMBIE_SNORKLE_HEAD,
	&IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_BUTTON,
	&IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_HIGHLIGHT,
	&IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_BUTTON,
	&IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_HIGHLIGHT,
	&IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_BUTTON,
	&IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_HIGHLIGHT,
	&IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_BUTTON,
	&IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_HIGHLIGHT,
	&IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_BUTTON,
	&IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_HIGHLIGHT,
	&IMAGE_REANIM_SELECTORSCREEN_WOODSIGN2_PRESS,
	&IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3_PRESS,
	&IMAGE_REANIM_SELECTORSCREEN_BG,
	&IMAGE_REANIM_SELECTORSCREEN_ALMANAC_SHADOW,
	&IMAGE_REANIM_SELECTORSCREEN_KEY_SHADOW,
	&IMAGE_REANIM_TREE_BG,
	&IMAGE_REANIM_POT_TOP_DARK,
	&IMAGE_REANIM_ZENGARDEN_BUGSPRAY_BOTTLE,
	&IMAGE_REANIM_STINKY_TURN3,
	&IMAGE_REANIM_CRAZYDAVE_MOUTH1,
	&IMAGE_REANIM_CRAZYDAVE_MOUTH4,
	&IMAGE_REANIM_CRAZYDAVE_MOUTH5,
	&IMAGE_REANIM_CRAZYDAVE_MOUTH6,
	&IMAGE_REANIM_ZOMBIE_MUSTACHE2,
	&IMAGE_REANIM_ZOMBIE_MUSTACHE3,
	&SOUND_ACHIEVEMENT,
	&SOUND_AWOOGA,
	&SOUND_BLEEP,
	&SOUND_BUZZER,
	&SOUND_CHOMP,
	&SOUND_CHOMP2,
	&SOUND_CHOMPSOFT,
	&SOUND_EVILLAUGH,
	&SOUND_FLOOP,
	&SOUND_FROZEN,
	&SOUND_GULP,
	&SOUND_GROAN,
	&SOUND_GROAN2,
	&SOUND_GROAN3,
	&SOUND_GROAN4,
	&SOUND_GROAN5,
	&SOUND_GROAN6,
	&SOUND_LOSEMUSIC,
	&SOUND_MINDCONTROLLED,
	&SOUND_PAUSE,
	&SOUND_PLANT,
	&SOUND_PLANT2,
	&SOUND_POINTS,
	&SOUND_SEEDLIFT,
	&SOUND_SIREN,
	&SOUND_SLURP,
	&SOUND_SPLAT,
	&SOUND_SPLAT2,
	&SOUND_SPLAT3,
	&SOUND_SUKHBIR,
	&SOUND_SUKHBIR2,
	&SOUND_SUKHBIR3,
	&SOUND_SUKHBIR4,
	&SOUND_SUKHBIR5,
	&SOUND_SUKHBIR6,
	&SOUND_TAP,
	&SOUND_TAP2,
	&SOUND_THROW,
	&SOUND_THROW2,
	&SOUND_BLOVER,
	&SOUND_WINMUSIC,
	&SOUND_LAWNMOWER,
	&SOUND_BOING,
	&SOUND_JACKINTHEBOX,
	&SOUND_DIAMOND,
	&SOUND_DOLPHIN_APPEARS,
	&SOUND_DOLPHIN_BEFORE_JUMPING,
	&SOUND_POTATO_MINE,
	&SOUND_ZAMBONI,
	&SOUND_BALLOON_POP,
	&SOUND_THUNDER,
	&SOUND_ZOMBIESPLASH,
	&SOUND_BOWLING,
	&SOUND_BOWLINGIMPACT,
	&SOUND_BOWLINGIMPACT2,
	&SOUND_GRAVEBUSTERCHOMP,
	&SOUND_GRAVEBUTTON,
	&SOUND_LIMBS_POP,
	&SOUND_PLANTERN,
	&SOUND_POGO_ZOMBIE,
	&SOUND_SNOW_PEA_SPARKLES,
	&SOUND_PLANT_WATER,
	&SOUND_ZOMBIE_ENTERING_WATER,
	&SOUND_ZOMBIE_FALLING_1,
	&SOUND_ZOMBIE_FALLING_2,
	&SOUND_PUFF,
	&SOUND_FUME,
	&SOUND_HUGE_WAVE,
	&SOUND_SLOT_MACHINE,
	&SOUND_COIN,
	&SOUND_ROLL_IN,
	&SOUND_DIGGER_ZOMBIE,
	&SOUND_HATCHBACK_CLOSE,
	&SOUND_HATCHBACK_OPEN,
	&SOUND_KERNELPULT,
	&SOUND_KERNELPULT2,
	&SOUND_ZOMBAQUARIUM_DIE,
	&SOUND_BUNGEE_SCREAM,
	&SOUND_BUNGEE_SCREAM2,
	&SOUND_BUNGEE_SCREAM3,
	&SOUND_BUTTER,
	&SOUND_JACK_SURPRISE,
	&SOUND_JACK_SURPRISE2,
	&SOUND_NEWSPAPER_RARRGH,
	&SOUND_NEWSPAPER_RARRGH2,
	&SOUND_NEWSPAPER_RIP,
	&SOUND_SQUASH_HMM,
	&SOUND_SQUASH_HMM2,
	&SOUND_VASE_BREAKING,
	&SOUND_POOL_CLEANER,
	&SOUND_MAGNETSHROOM,
	&SOUND_LADDER_ZOMBIE,
	&SOUND_GARGANTUAR_THUMP,
	&SOUND_BASKETBALL,
	&SOUND_FIREPEA,
	&SOUND_IGNITE,
	&SOUND_IGNITE2,
	&SOUND_READYSETPLANT,
	&SOUND_DOOMSHROOM,
	&SOUND_EXPLOSION,
	&SOUND_FINALWAVE,
	&SOUND_REVERSE_EXPLOSION,
	&SOUND_RVTHROW,
	&SOUND_SHIELDHIT,
	&SOUND_SHIELDHIT2,
	&SOUND_BOSSEXPLOSION,
	&SOUND_CHERRYBOMB,
	&SOUND_BONK,
	&SOUND_SWING,
	&SOUND_RAIN,
	&SOUND_LIGHTFILL,
	&SOUND_PLASTICHIT,
	&SOUND_PLASTICHIT2,
	&SOUND_JALAPENO,
	&SOUND_BALLOONINFLATE,
	&SOUND_BIGCHOMP,
	&SOUND_MELONIMPACT,
	&SOUND_MELONIMPACT2,
	&SOUND_PLANTGROW,
	&SOUND_SHOOP,
	&SOUND_TAPGLASS,
	&SOUND_JUICY,
	&SOUND_COFFEE,
	&SOUND_WAKEUP,
	&SOUND_LOWGROAN,
	&SOUND_LOWGROAN2,
	&SOUND_PRIZE,
	&SOUND_YUCK,
	&SOUND_YUCK2,
	&SOUND_GRASSSTEP,
	&SOUND_SHOVEL,
	&SOUND_COBLAUNCH,
	&SOUND_WATERING,
	&SOUND_POLEVAULT,
	&SOUND_GRAVESTONE_RUMBLE,
	&SOUND_DIRT_RISE,
	&SOUND_FERTILIZER,
	&SOUND_PORTAL,
	&SOUND_BUGSPRAY,
	&SOUND_SCREAM,
	&SOUND_PAPER,
	&SOUND_MONEYFALLS,
	&SOUND_IMP,
	&SOUND_IMP2,
	&SOUND_HYDRAULIC_SHORT,
	&SOUND_HYDRAULIC,
	&SOUND_GARGANTUDEATH,
	&SOUND_CERAMIC,
	&SOUND_BOSSBOULDERATTACK,
	&SOUND_CHIME,
	&SOUND_CRAZYDAVESHORT1,
	&SOUND_CRAZYDAVESHORT2,
	&SOUND_CRAZYDAVESHORT3,
	&SOUND_CRAZYDAVELONG1,
	&SOUND_CRAZYDAVELONG2,
	&SOUND_CRAZYDAVELONG3,
	&SOUND_CRAZYDAVEEXTRALONG1,
	&SOUND_CRAZYDAVEEXTRALONG2,
	&SOUND_CRAZYDAVEEXTRALONG3,
	&SOUND_CRAZYDAVECRAZY,
	&SOUND_PHONOGRAPH,
	&SOUND_DANCER,
	&SOUND_FINALFANFARE,
	&SOUND_CRAZYDAVESCREAM,
	&SOUND_CRAZYDAVESCREAM2,
	&IMAGE_BACKGROUND1,
	&IMAGE_BACKGROUND1_GAMEOVER_INTERIOR_OVERLAY,
	&IMAGE_BACKGROUND1_GAMEOVER_MASK,
	&IMAGE_BACKGROUND1UNSODDED,
	&IMAGE_SOD1ROW,
	&IMAGE_SOD3ROW,
	&IMAGE_BACKGROUND2,
	&IMAGE_BACKGROUND2_GAMEOVER_INTERIOR_OVERLAY,
	&IMAGE_BACKGROUND2_GAMEOVER_MASK,
	&IMAGE_BACKGROUND3,
	&IMAGE_BACKGROUND3_GAMEOVER_INTERIOR_OVERLAY,
	&IMAGE_BACKGROUND3_GAMEOVER_MASK,
	&IMAGE_BACKGROUND4,
	&IMAGE_BACKGROUND4_GAMEOVER_INTERIOR_OVERLAY,
	&IMAGE_BACKGROUND4_GAMEOVER_MASK,
	&IMAGE_FOG,
	&IMAGE_FOG_SOFTWARE,
	&IMAGE_BACKGROUND5,
	&IMAGE_BACKGROUND5_GAMEOVER_MASK,
	&IMAGE_BACKGROUND6BOSS,
	&IMAGE_BACKGROUND6_GAMEOVER_MASK,
	&IMAGE_BACKGROUND_MUSHROOMGARDEN,
	&IMAGE_BACKGROUND_GREENHOUSE,
	&IMAGE_BACKGROUND_GREENHOUSE_OVERLAY,
	&IMAGE_AQUARIUM1,
	&IMAGE_WAVECENTER,
	&IMAGE_WAVESIDE,
	&IMAGE_AWARDSCREEN_BACK,
	&IMAGE_ACHIEVEMENTS_PORTRAITS,
	&IMAGE_CHALLENGE_BACKGROUND,
	&IMAGE_CHALLENGE_WINDOW,
	&IMAGE_CHALLENGE_WINDOW_HIGHLIGHT,
	&IMAGE_CHALLENGE_BLANK,
	&IMAGE_CHALLENGE_THUMBNAILS,
	&IMAGE_SURVIVAL_THUMBNAILS,
	&IMAGE_LOCK,
	&IMAGE_LOCK_OPEN,
	&IMAGE_ACHIEVEMENT_TILE,
	&IMAGE_ACHIEVEMENT_BACK_GLOW,
	&IMAGE_ACHIEVEMENT_SELECTOR_TILE,
	&IMAGE_ACHIEVEMENT_TILE_CHINA,
	&IMAGE_ACHIEVEMENT_MORE,
	&IMAGE_ACHIEVEMENT_MORE_HIGHLIGHT,
	&IMAGE_ACHIEVEMENT_TOP,
	&IMAGE_ACHIEVEMENT_TOP_HIGHLIGHT,
	&IMAGE_ACHIEVEMENT_ROCK,
	&IMAGE_ACHIEVEMENT_BOOKWORM,
	&IMAGE_ACHIEVEMENT_BEJEWELED,
	&IMAGE_ACHIEVEMENT_CHUZZLE,
	&IMAGE_ACHIEVEMENT_PEGGLE,
	&IMAGE_ACHIEVEMENT_PIPE,
	&IMAGE_ACHIEVEMENT_ZUMA,
	&IMAGE_QUICKPLAY_BACKGROUND,
	&IMAGE_QUICKPLAY_LEFT_BUTTON,
	&IMAGE_QUICKPLAY_LEFT_BUTTON_HIGHLIGHT,
	&IMAGE_QUICKPLAY_RIGHT_BUTTON,
	&IMAGE_QUICKPLAY_RIGHT_BUTTON_HIGHLIGHT,
	&IMAGE_QUICKPLAY_BACK_HIGHLIGHT,
	&IMAGE_QUICKPLAY_WIDGET,
	&IMAGE_ALMANAC_INDEXBACK,
	&IMAGE_ALMANAC_PLANTBACK,
	&IMAGE_ALMANAC_ZOMBIEBACK,
	&IMAGE_ALMANAC_PLANTCARD,
	&IMAGE_ALMANAC_ZOMBIECARD,
	&IMAGE_ALMANAC_ZOMBIEWINDOW,
	&IMAGE_ALMANAC_ZOMBIEWINDOW2,
	&IMAGE_ALMANAC_ZOMBIEBLANK,
	&IMAGE_ALMANAC_PLANTBLANK,
	&IMAGE_ALMANAC_GROUNDDAY,
	&IMAGE_ALMANAC_GROUNDNIGHT,
	&IMAGE_ALMANAC_GROUNDPOOL,
	&IMAGE_ALMANAC_GROUNDNIGHTPOOL,
	&IMAGE_ALMANAC_GROUNDROOF,
	&IMAGE_ALMANAC_GROUNDICE,
	&IMAGE_ALMANAC_CLOSEBUTTON,
	&IMAGE_ALMANAC_CLOSEBUTTONHIGHLIGHT,
	&IMAGE_ALMANAC_INDEXBUTTON,
	&IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT,
	&IMAGE_ALMANAC_INDEXBUTTON_DISABLE,
	&IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT_DISABLE,
	&IMAGE_STORE_BACKGROUND,
	&IMAGE_STORE_BACKGROUNDNIGHT,
	&IMAGE_STORE_CAR,
	&IMAGE_STORE_CAR_NIGHT,
	&IMAGE_STORE_CARCLOSED,
	&IMAGE_STORE_CARCLOSED_NIGHT,
	&IMAGE_STORE_HATCHBACKOPEN,
	&IMAGE_STORE_SIGN,
	&IMAGE_STORE_MAINMENUBUTTON,
	&IMAGE_STORE_MAINMENUBUTTONDOWN,
	&IMAGE_STORE_MAINMENUBUTTONHIGHLIGHT,
	&IMAGE_STORE_NEXTBUTTON,
	&IMAGE_STORE_NEXTBUTTONHIGHLIGHT,
	&IMAGE_STORE_NEXTBUTTONDISABLED,
	&IMAGE_STORE_PREVBUTTON,
	&IMAGE_STORE_PREVBUTTONHIGHLIGHT,
	&IMAGE_STORE_PREVBUTTONDISABLED,
	&IMAGE_STORE_PRICETAG,
	&IMAGE_STORE_PACKETUPGRADE,
	&IMAGE_STORE_MUSHROOMGARDENICON,
	&IMAGE_STORE_AQUARIUMGARDENICON,
	&IMAGE_STORE_TREEOFWISDOMICON,
	&IMAGE_STORE_FIRSTAIDWALLNUTICON,
	&IMAGE_STORE_PVZICON,
	&IMAGE_ZOMBIE_NOTE,
	&IMAGE_ZOMBIE_NOTE1,
	&IMAGE_ZOMBIE_NOTE2,
	&IMAGE_ZOMBIE_NOTE3,
	&IMAGE_ZOMBIE_NOTE4,
	&IMAGE_ZOMBIE_FINAL_NOTE,
	&IMAGE_ZOMBIE_NOTE_HELP,
	&FONT_BRIANNETOD32,
	&FONT_BRIANNETOD32BLACK,
	&IMAGE_REANIM_SUNFLOWER_HEAD_SING1,
	&IMAGE_REANIM_SUNFLOWER_HEAD_SING2,
	&IMAGE_REANIM_SUNFLOWER_HEAD_SING3,
	&IMAGE_REANIM_SUNFLOWER_HEAD_SING4,
	&IMAGE_REANIM_SUNFLOWER_HEAD_SING5,
	&IMAGE_REANIM_SUNFLOWER_HEAD_WINK,
	&IMAGE_REANIM_CREDITS_DISCOLIGHTS,
	&IMAGE_REANIM_CREDITS_FOGMACHINE,
	&IMAGE_CREDITS_ZOMBIENOTE,
	&IMAGE_CREDITS_PLAYBUTTON,
	&IMAGE_CREDITS_BG,
	NULL
};

Image* Sexy::LoadImageById(ResourceManager *theManager, int theId)
{
	return (*((Image**)gResources[theId]) = theManager->LoadImage(GetStringIdById(theId)));
}

void Sexy::ReplaceImageById(ResourceManager *theManager, int theId, Image *theImage)
{
	theManager->ReplaceImage(GetStringIdById(theId),theImage);
	*(Image**)gResources[theId] = theImage;
}

Image* Sexy::GetImageById(int theId)
{
	return *(Image**)gResources[theId];
}

Font* Sexy::GetFontById(int theId)
{
	return *(Font**)gResources[theId];
}

int Sexy::GetSoundById(int theId)
{
	return *(int*)gResources[theId];
}

Image*& Sexy::GetImageRefById(int theId)
{
	return *(Image**)gResources[theId];
}

Font*& Sexy::GetFontRefById(int theId)
{
	return *(Font**)gResources[theId];
}

int& Sexy::GetSoundRefById(int theId)
{
	return *(int*)gResources[theId];
}

static Sexy::ResourceId GetIdByVariable(const void *theVariable)
{
	typedef std::map<int,int> MyMap;
	static MyMap aMap;
	if(gNeedRecalcVariableToIdMap)
	{
		gNeedRecalcVariableToIdMap = false;
		aMap.clear();
		for(int i=0; i<RESOURCE_ID_MAX; i++)
			aMap[*(int*)gResources[i]] = i;
	}

	MyMap::iterator anItr = aMap.find((int)theVariable);
	if (anItr == aMap.end())
		return RESOURCE_ID_MAX;
	else
		return (ResourceId) anItr->second;
}

Sexy::ResourceId Sexy::GetIdByImage(Image *theImage)
{
	return GetIdByVariable(theImage);
}

Sexy::ResourceId Sexy::GetIdByFont(Font *theFont)
{
	return GetIdByVariable(theFont);
}

Sexy::ResourceId Sexy::GetIdBySound(int theSound)
{
	return GetIdByVariable((void*)theSound);
}

const char* Sexy::GetStringIdById(int theId)
{
	switch(theId)
	{
		case IMAGE_BLANK_ID: return "IMAGE_BLANK";
		case IMAGE_POPCAP_LOGO_ID: return "IMAGE_POPCAP_LOGO";
		case IMAGE_PARTNER_LOGO_ID: return "IMAGE_PARTNER_LOGO";
		case IMAGE_TITLESCREEN_ID: return "IMAGE_TITLESCREEN";
		case IMAGE_LOADBAR_DIRT_ID: return "IMAGE_LOADBAR_DIRT";
		case IMAGE_LOADBAR_GRASS_ID: return "IMAGE_LOADBAR_GRASS";
		case IMAGE_PVZ_LOGO_ID: return "IMAGE_PVZ_LOGO";
		case IMAGE_REANIM_SODROLLCAP_ID: return "IMAGE_REANIM_SODROLLCAP";
		case FONT_BRIANNETOD16_ID: return "FONT_BRIANNETOD16";
		case SOUND_BUTTONCLICK_ID: return "SOUND_BUTTONCLICK";
		case SOUND_LOADINGBAR_FLOWER_ID: return "SOUND_LOADINGBAR_FLOWER";
		case SOUND_LOADINGBAR_ZOMBIE_ID: return "SOUND_LOADINGBAR_ZOMBIE";
		case FONT_IMAGE_HOUSEOFTERROR28_ID: return "FONT_IMAGE_HOUSEOFTERROR28";
		case FONT_HOUSEOFTERROR28_ID: return "FONT_HOUSEOFTERROR28";
		case FONT_HOUSEOFTERROR20_ID: return "FONT_HOUSEOFTERROR20";
		case FONT_HOUSEOFTERROR16_ID: return "FONT_HOUSEOFTERROR16";
		case FONT_TINYBOLD_ID: return "FONT_TINYBOLD";
		case FONT_CONTINUUMBOLD14_ID: return "FONT_CONTINUUMBOLD14";
		case FONT_CONTINUUMBOLD14OUTLINE_ID: return "FONT_CONTINUUMBOLD14OUTLINE";
		case FONT_DWARVENTODCRAFT12_ID: return "FONT_DWARVENTODCRAFT12";
		case FONT_DWARVENTODCRAFT15_ID: return "FONT_DWARVENTODCRAFT15";
		case FONT_DWARVENTODCRAFT18_ID: return "FONT_DWARVENTODCRAFT18";
		case FONT_DWARVENTODCRAFT18BRIGHTGREENINSET_ID: return "FONT_DWARVENTODCRAFT18BRIGHTGREENINSET";
		case FONT_DWARVENTODCRAFT18GREENINSET_ID: return "FONT_DWARVENTODCRAFT18GREENINSET";
		case FONT_DWARVENTODCRAFT18YELLOW_ID: return "FONT_DWARVENTODCRAFT18YELLOW";
		case FONT_DWARVENTODCRAFT24_ID: return "FONT_DWARVENTODCRAFT24";
		case FONT_DWARVENTODCRAFT36BRIGHTGREENINSET_ID: return "FONT_DWARVENTODCRAFT36BRIGHTGREENINSET";
		case FONT_DWARVENTODCRAFT36GREENINSET_ID: return "FONT_DWARVENTODCRAFT36GREENINSET";
		case FONT_PICO129_ID: return "FONT_PICO129";
		case FONT_BRIANNETOD12_ID: return "FONT_BRIANNETOD12";
		case IMAGE_MOUSE_CURSOR_ID: return "IMAGE_MOUSE_CURSOR";
		case IMAGE_EDITBOX_ID: return "IMAGE_EDITBOX";
		case IMAGE_DIALOG_TOPLEFT_ID: return "IMAGE_DIALOG_TOPLEFT";
		case IMAGE_DIALOG_TOPMIDDLE_ID: return "IMAGE_DIALOG_TOPMIDDLE";
		case IMAGE_DIALOG_TOPRIGHT_ID: return "IMAGE_DIALOG_TOPRIGHT";
		case IMAGE_DIALOG_CENTERLEFT_ID: return "IMAGE_DIALOG_CENTERLEFT";
		case IMAGE_DIALOG_CENTERMIDDLE_ID: return "IMAGE_DIALOG_CENTERMIDDLE";
		case IMAGE_DIALOG_CENTERRIGHT_ID: return "IMAGE_DIALOG_CENTERRIGHT";
		case IMAGE_DIALOG_BOTTOMLEFT_ID: return "IMAGE_DIALOG_BOTTOMLEFT";
		case IMAGE_DIALOG_BOTTOMMIDDLE_ID: return "IMAGE_DIALOG_BOTTOMMIDDLE";
		case IMAGE_DIALOG_BOTTOMRIGHT_ID: return "IMAGE_DIALOG_BOTTOMRIGHT";
		case IMAGE_DIALOG_BIGBOTTOMLEFT_ID: return "IMAGE_DIALOG_BIGBOTTOMLEFT";
		case IMAGE_DIALOG_BIGBOTTOMMIDDLE_ID: return "IMAGE_DIALOG_BIGBOTTOMMIDDLE";
		case IMAGE_DIALOG_BIGBOTTOMRIGHT_ID: return "IMAGE_DIALOG_BIGBOTTOMRIGHT";
		case IMAGE_DIALOG_HEADER_ID: return "IMAGE_DIALOG_HEADER";
		case IMAGE_BUTTON_LEFT_ID: return "IMAGE_BUTTON_LEFT";
		case IMAGE_BUTTON_MIDDLE_ID: return "IMAGE_BUTTON_MIDDLE";
		case IMAGE_BUTTON_RIGHT_ID: return "IMAGE_BUTTON_RIGHT";
		case IMAGE_BUTTON_SMALL_ID: return "IMAGE_BUTTON_SMALL";
		case IMAGE_BUTTON_DOWN_LEFT_ID: return "IMAGE_BUTTON_DOWN_LEFT";
		case IMAGE_BUTTON_DOWN_MIDDLE_ID: return "IMAGE_BUTTON_DOWN_MIDDLE";
		case IMAGE_BUTTON_DOWN_RIGHT_ID: return "IMAGE_BUTTON_DOWN_RIGHT";
		case IMAGE_BUTTON_DOWN_SMALL_ID: return "IMAGE_BUTTON_DOWN_SMALL";
		case IMAGE_SEEDCHOOSER_BACKGROUND_ID: return "IMAGE_SEEDCHOOSER_BACKGROUND";
		case IMAGE_SEEDCHOOSER_BUTTON_ID: return "IMAGE_SEEDCHOOSER_BUTTON";
		case IMAGE_SEEDCHOOSER_BUTTON_DISABLED_ID: return "IMAGE_SEEDCHOOSER_BUTTON_DISABLED";
		case IMAGE_SEEDCHOOSER_BUTTON_GLOW_ID: return "IMAGE_SEEDCHOOSER_BUTTON_GLOW";
		case IMAGE_SEEDCHOOSER_BUTTON2_ID: return "IMAGE_SEEDCHOOSER_BUTTON2";
		case IMAGE_SEEDCHOOSER_BUTTON2_GLOW_ID: return "IMAGE_SEEDCHOOSER_BUTTON2_GLOW";
		case IMAGE_SEEDCHOOSER_IMITATERADDON_ID: return "IMAGE_SEEDCHOOSER_IMITATERADDON";
		case IMAGE_SEEDS_ID: return "IMAGE_SEEDS";
		case IMAGE_SEEDPACKET_LARGER_ID: return "IMAGE_SEEDPACKET_LARGER";
		case IMAGE_SEEDPACKETSILHOUETTE_ID: return "IMAGE_SEEDPACKETSILHOUETTE";
		case IMAGE_FLAGMETER_ID: return "IMAGE_FLAGMETER";
		case IMAGE_FLAGMETERLEVELPROGRESS_ID: return "IMAGE_FLAGMETERLEVELPROGRESS";
		case IMAGE_FLAGMETERPARTS_ID: return "IMAGE_FLAGMETERPARTS";
		case IMAGE_TROPHY_ID: return "IMAGE_TROPHY";
		case IMAGE_TROPHY_HI_RES_ID: return "IMAGE_TROPHY_HI_RES";
		case IMAGE_MINIGAME_TROPHY_ID: return "IMAGE_MINIGAME_TROPHY";
		case IMAGE_ZOMBIE_NOTE_SMALL_ID: return "IMAGE_ZOMBIE_NOTE_SMALL";
		case IMAGE_TACO_ID: return "IMAGE_TACO";
		case IMAGE_CARKEYS_ID: return "IMAGE_CARKEYS";
		case IMAGE_ALMANAC_ID: return "IMAGE_ALMANAC";
		case IMAGE_ICON_POOLCLEANER_ID: return "IMAGE_ICON_POOLCLEANER";
		case IMAGE_ICON_ROOFCLEANER_ID: return "IMAGE_ICON_ROOFCLEANER";
		case IMAGE_ICON_RAKE_ID: return "IMAGE_ICON_RAKE";
		case IMAGE_BRAIN_ID: return "IMAGE_BRAIN";
		case IMAGE_MONEYBAG_ID: return "IMAGE_MONEYBAG";
		case IMAGE_MONEYBAG_HI_RES_ID: return "IMAGE_MONEYBAG_HI_RES";
		case IMAGE_CHOCOLATE_ID: return "IMAGE_CHOCOLATE";
		case IMAGE_OPTIONS_BACKTOGAMEBUTTON0_ID: return "IMAGE_OPTIONS_BACKTOGAMEBUTTON0";
		case IMAGE_OPTIONS_BACKTOGAMEBUTTON2_ID: return "IMAGE_OPTIONS_BACKTOGAMEBUTTON2";
		case IMAGE_OPTIONS_CHECKBOX0_ID: return "IMAGE_OPTIONS_CHECKBOX0";
		case IMAGE_OPTIONS_CHECKBOX1_ID: return "IMAGE_OPTIONS_CHECKBOX1";
		case IMAGE_OPTIONS_MENUBACK_ID: return "IMAGE_OPTIONS_MENUBACK";
		case IMAGE_OPTIONS_SLIDERKNOB2_ID: return "IMAGE_OPTIONS_SLIDERKNOB2";
		case IMAGE_OPTIONS_SLIDERSLOT_ID: return "IMAGE_OPTIONS_SLIDERSLOT";
		case IMAGE_OPTIONS_SLIDERKNOB_PLANT_ID: return "IMAGE_OPTIONS_SLIDERKNOB_PLANT";
		case IMAGE_OPTIONS_SLIDERSLOT_PLANT_ID: return "IMAGE_OPTIONS_SLIDERSLOT_PLANT";
		case IMAGE_CHALLENGE_SLIDERSLOT_ID: return "IMAGE_CHALLENGE_SLIDERSLOT";
		case IMAGE_SELECTORSCREEN_HELP1_ID: return "IMAGE_SELECTORSCREEN_HELP1";
		case IMAGE_SELECTORSCREEN_HELP2_ID: return "IMAGE_SELECTORSCREEN_HELP2";
		case IMAGE_SELECTORSCREEN_OPTIONS1_ID: return "IMAGE_SELECTORSCREEN_OPTIONS1";
		case IMAGE_SELECTORSCREEN_OPTIONS2_ID: return "IMAGE_SELECTORSCREEN_OPTIONS2";
		case IMAGE_SELECTORSCREEN_QUIT1_ID: return "IMAGE_SELECTORSCREEN_QUIT1";
		case IMAGE_SELECTORSCREEN_QUIT2_ID: return "IMAGE_SELECTORSCREEN_QUIT2";
		case IMAGE_SELECTORSCREEN_ALMANAC_ID: return "IMAGE_SELECTORSCREEN_ALMANAC";
		case IMAGE_SELECTORSCREEN_ALMANACHIGHLIGHT_ID: return "IMAGE_SELECTORSCREEN_ALMANACHIGHLIGHT";
		case IMAGE_SELECTORSCREEN_STORE_ID: return "IMAGE_SELECTORSCREEN_STORE";
		case IMAGE_SELECTORSCREEN_STOREHIGHLIGHT_ID: return "IMAGE_SELECTORSCREEN_STOREHIGHLIGHT";
		case IMAGE_SELECTORSCREEN_LEVELNUMBERS_ID: return "IMAGE_SELECTORSCREEN_LEVELNUMBERS";
		case IMAGE_SELECTORSCREEN_ZENGARDEN_ID: return "IMAGE_SELECTORSCREEN_ZENGARDEN";
		case IMAGE_ACHIEVEMENT_BUTTON_ID: return "IMAGE_ACHIEVEMENT_BUTTON";
		case IMAGE_ACHIEVEMENT_HIGHLIGHT_ID: return "IMAGE_ACHIEVEMENT_HIGHLIGHT";
		case IMAGE_QUICKPLAY_BUTTON_ID: return "IMAGE_QUICKPLAY_BUTTON";
		case IMAGE_QUICKPLAY_BUTTON_HIGHLIGHT_ID: return "IMAGE_QUICKPLAY_BUTTON_HIGHLIGHT";
		case IMAGE_SELECTORSCREEN_ZENGARDENHIGHLIGHT_ID: return "IMAGE_SELECTORSCREEN_ZENGARDENHIGHLIGHT";
		case IMAGE_STORE_SPEECHBUBBLE_ID: return "IMAGE_STORE_SPEECHBUBBLE";
		case IMAGE_STORE_SPEECHBUBBLE2_ID: return "IMAGE_STORE_SPEECHBUBBLE2";
		case IMAGE_SHOVEL_ID: return "IMAGE_SHOVEL";
		case IMAGE_SHOVEL_HI_RES_ID: return "IMAGE_SHOVEL_HI_RES";
		case IMAGE_TOMBSTONES_ID: return "IMAGE_TOMBSTONES";
		case IMAGE_TOMBSTONE_MOUNDS_ID: return "IMAGE_TOMBSTONE_MOUNDS";
		case IMAGE_NIGHT_GRAVE_GRAPHIC_ID: return "IMAGE_NIGHT_GRAVE_GRAPHIC";
		case IMAGE_CRATER_ID: return "IMAGE_CRATER";
		case IMAGE_CRATER_FADING_ID: return "IMAGE_CRATER_FADING";
		case IMAGE_CRATER_ROOF_CENTER_ID: return "IMAGE_CRATER_ROOF_CENTER";
		case IMAGE_CRATER_ROOF_LEFT_ID: return "IMAGE_CRATER_ROOF_LEFT";
		case IMAGE_CRATER_WATER_DAY_ID: return "IMAGE_CRATER_WATER_DAY";
		case IMAGE_CRATER_WATER_NIGHT_ID: return "IMAGE_CRATER_WATER_NIGHT";
		case IMAGE_COBCANNON_TARGET_ID: return "IMAGE_COBCANNON_TARGET";
		case IMAGE_COBCANNON_POPCORN_ID: return "IMAGE_COBCANNON_POPCORN";
		case IMAGE_FERTILIZER_ID: return "IMAGE_FERTILIZER";
		case IMAGE_WATERINGCAN_ID: return "IMAGE_WATERINGCAN";
		case IMAGE_WATERINGCANGOLD_ID: return "IMAGE_WATERINGCANGOLD";
		case IMAGE_PHONOGRAPH_ID: return "IMAGE_PHONOGRAPH";
		case IMAGE_BEGHOULED_TWIST_OVERLAY_ID: return "IMAGE_BEGHOULED_TWIST_OVERLAY";
		case IMAGE_ZEN_GOLDTOOLRETICLE_ID: return "IMAGE_ZEN_GOLDTOOLRETICLE";
		case IMAGE_ZEN_GARDENGLOVE_ID: return "IMAGE_ZEN_GARDENGLOVE";
		case IMAGE_ZEN_MONEYSIGN_ID: return "IMAGE_ZEN_MONEYSIGN";
		case IMAGE_ZEN_NEXTGARDEN_ID: return "IMAGE_ZEN_NEXTGARDEN";
		case IMAGE_ZEN_WHEELBARROW_ID: return "IMAGE_ZEN_WHEELBARROW";
		case IMAGE_ZENSHOPBUTTON_ID: return "IMAGE_ZENSHOPBUTTON";
		case IMAGE_ZENSHOPBUTTON_HIGHLIGHT_ID: return "IMAGE_ZENSHOPBUTTON_HIGHLIGHT";
		case IMAGE_FASTBUTTON_ID: return "IMAGE_FASTBUTTON";
		case IMAGE_FASTBUTTON_HIGHLIGHT_ID: return "IMAGE_FASTBUTTON_HIGHLIGHT";
		case IMAGE_PRESENT_ID: return "IMAGE_PRESENT";
		case IMAGE_PRESENTOPEN_ID: return "IMAGE_PRESENTOPEN";
		case IMAGE_SUNFLOWER_TROPHY_ID: return "IMAGE_SUNFLOWER_TROPHY";
		case IMAGE_SLOTMACHINE_OVERLAY_ID: return "IMAGE_SLOTMACHINE_OVERLAY";
		case IMAGE_SCARY_POT_ID: return "IMAGE_SCARY_POT";
		case IMAGE_BUG_SPRAY_ID: return "IMAGE_BUG_SPRAY";
		case IMAGE_PLANTSPEECHBUBBLE_ID: return "IMAGE_PLANTSPEECHBUBBLE";
		case IMAGE_WATERDROP_ID: return "IMAGE_WATERDROP";
		case IMAGE_TREEFOOD_ID: return "IMAGE_TREEFOOD";
		case IMAGE_PACKET_PLANTS_ID: return "IMAGE_PACKET_PLANTS";
		case IMAGE_ZEN_NEED_ICONS_ID: return "IMAGE_ZEN_NEED_ICONS";
		case IMAGE_SQUIRREL_ID: return "IMAGE_SQUIRREL";
		case IMAGE_PROJECTILEPEA_ID: return "IMAGE_PROJECTILEPEA";
		case IMAGE_PROJECTILESNOWPEA_ID: return "IMAGE_PROJECTILESNOWPEA";
		case IMAGE_PROJECTILECACTUS_ID: return "IMAGE_PROJECTILECACTUS";
		case IMAGE_DIRTSMALL_ID: return "IMAGE_DIRTSMALL";
		case IMAGE_DIRTBIG_ID: return "IMAGE_DIRTBIG";
		case IMAGE_ROCKSMALL_ID: return "IMAGE_ROCKSMALL";
		case IMAGE_WATERPARTICLE_ID: return "IMAGE_WATERPARTICLE";
		case IMAGE_WHITEWATER_ID: return "IMAGE_WHITEWATER";
		case IMAGE_WHITEWATER_SHADOW_ID: return "IMAGE_WHITEWATER_SHADOW";
		case IMAGE_MELONPULT_PARTICLES_ID: return "IMAGE_MELONPULT_PARTICLES";
		case IMAGE_WINTERMELON_PARTICLES_ID: return "IMAGE_WINTERMELON_PARTICLES";
		case IMAGE_PROJECTILE_STAR_ID: return "IMAGE_PROJECTILE_STAR";
		case IMAGE_SEEDBANK_ID: return "IMAGE_SEEDBANK";
		case IMAGE_CONVEYORBELT_BACKDROP_ID: return "IMAGE_CONVEYORBELT_BACKDROP";
		case IMAGE_CONVEYORBELT_ID: return "IMAGE_CONVEYORBELT";
		case IMAGE_SHOVELBANK_ID: return "IMAGE_SHOVELBANK";
		case IMAGE_SUNBANK_ID: return "IMAGE_SUNBANK";
		case IMAGE_COINBANK_ID: return "IMAGE_COINBANK";
		case IMAGE_POOL_ID: return "IMAGE_POOL";
		case IMAGE_POOL_NIGHT_ID: return "IMAGE_POOL_NIGHT";
		case IMAGE_POOL_BASE_ID: return "IMAGE_POOL_BASE";
		case IMAGE_POOL_BASE_NIGHT_ID: return "IMAGE_POOL_BASE_NIGHT";
		case IMAGE_POOL_SHADING_ID: return "IMAGE_POOL_SHADING";
		case IMAGE_POOL_SHADING_NIGHT_ID: return "IMAGE_POOL_SHADING_NIGHT";
		case IMAGE_POOL_CAUSTIC_EFFECT_ID: return "IMAGE_POOL_CAUSTIC_EFFECT";
		case IMAGE_PLANTSHADOW_ID: return "IMAGE_PLANTSHADOW";
		case IMAGE_PLANTSHADOW2_ID: return "IMAGE_PLANTSHADOW2";
		case IMAGE_PEA_SHADOWS_ID: return "IMAGE_PEA_SHADOWS";
		case IMAGE_WALLNUT_BOWLINGSTRIPE_ID: return "IMAGE_WALLNUT_BOWLINGSTRIPE";
		case IMAGE_ICE_ID: return "IMAGE_ICE";
		case IMAGE_ICE_CAP_ID: return "IMAGE_ICE_CAP";
		case IMAGE_ICE_SPARKLES_ID: return "IMAGE_ICE_SPARKLES";
		case IMAGE_IMITATERSEED_ID: return "IMAGE_IMITATERSEED";
		case IMAGE_ALMANAC_IMITATER_ID: return "IMAGE_ALMANAC_IMITATER";
		case IMAGE_IMITATERSEEDDISABLED_ID: return "IMAGE_IMITATERSEEDDISABLED";
		case IMAGE_ICETRAP_ID: return "IMAGE_ICETRAP";
		case IMAGE_ICETRAP2_ID: return "IMAGE_ICETRAP2";
		case IMAGE_ICETRAP_PARTICLES_ID: return "IMAGE_ICETRAP_PARTICLES";
		case IMAGE_ZOMBIE_BOBSLED1_ID: return "IMAGE_ZOMBIE_BOBSLED1";
		case IMAGE_ZOMBIE_BOBSLED2_ID: return "IMAGE_ZOMBIE_BOBSLED2";
		case IMAGE_ZOMBIE_BOBSLED3_ID: return "IMAGE_ZOMBIE_BOBSLED3";
		case IMAGE_ZOMBIE_BOBSLED4_ID: return "IMAGE_ZOMBIE_BOBSLED4";
		case IMAGE_ZOMBIE_BOBSLED_INSIDE_ID: return "IMAGE_ZOMBIE_BOBSLED_INSIDE";
		case IMAGE_BUNGEECORD_ID: return "IMAGE_BUNGEECORD";
		case IMAGE_BUNGEETARGET_ID: return "IMAGE_BUNGEETARGET";
		case IMAGE_SPOTLIGHT_ID: return "IMAGE_SPOTLIGHT";
		case IMAGE_SPOTLIGHT2_ID: return "IMAGE_SPOTLIGHT2";
		case IMAGE_WHITEPIXEL_ID: return "IMAGE_WHITEPIXEL";
		case IMAGE_ZOMBIEPOLEVAULTERHEAD_ID: return "IMAGE_ZOMBIEPOLEVAULTERHEAD";
		case IMAGE_ZOMBIEFOOTBALLHEAD_ID: return "IMAGE_ZOMBIEFOOTBALLHEAD";
		case IMAGE_POOLSPARKLY_ID: return "IMAGE_POOLSPARKLY";
		case IMAGE_WALLNUTPARTICLESSMALL_ID: return "IMAGE_WALLNUTPARTICLESSMALL";
		case IMAGE_WALLNUTPARTICLESLARGE_ID: return "IMAGE_WALLNUTPARTICLESLARGE";
		case IMAGE_PEA_SPLATS_ID: return "IMAGE_PEA_SPLATS";
		case IMAGE_STAR_PARTICLES_ID: return "IMAGE_STAR_PARTICLES";
		case IMAGE_STAR_SPLATS_ID: return "IMAGE_STAR_SPLATS";
		case IMAGE_PEA_PARTICLES_ID: return "IMAGE_PEA_PARTICLES";
		case IMAGE_SNOWPEA_SPLATS_ID: return "IMAGE_SNOWPEA_SPLATS";
		case IMAGE_SNOWPEA_PARTICLES_ID: return "IMAGE_SNOWPEA_PARTICLES";
		case IMAGE_SNOWPEA_PUFF_ID: return "IMAGE_SNOWPEA_PUFF";
		case IMAGE_SNOWFLAKES_ID: return "IMAGE_SNOWFLAKES";
		case IMAGE_POTATOMINE_PARTICLES_ID: return "IMAGE_POTATOMINE_PARTICLES";
		case IMAGE_PUFFSHROOM_PUFF1_ID: return "IMAGE_PUFFSHROOM_PUFF1";
		case IMAGE_ZAMBONISMOKE_ID: return "IMAGE_ZAMBONISMOKE";
		case IMAGE_ZOMBIEDANCERHEAD_ID: return "IMAGE_ZOMBIEDANCERHEAD";
		case IMAGE_ZOMBIEBALLOONHEAD_ID: return "IMAGE_ZOMBIEBALLOONHEAD";
		case IMAGE_ZOMBIEIMPHEAD_ID: return "IMAGE_ZOMBIEIMPHEAD";
		case IMAGE_ZOMBIEDIGGERHEAD_ID: return "IMAGE_ZOMBIEDIGGERHEAD";
		case IMAGE_ZOMBIEDIGGERARM_ID: return "IMAGE_ZOMBIEDIGGERARM";
		case IMAGE_ZOMBIEDOLPHINRIDERHEAD_ID: return "IMAGE_ZOMBIEDOLPHINRIDERHEAD";
		case IMAGE_ZOMBIEPOGO_ID: return "IMAGE_ZOMBIEPOGO";
		case IMAGE_ZOMBIEBACKUPDANCERHEAD_ID: return "IMAGE_ZOMBIEBACKUPDANCERHEAD";
		case IMAGE_ZOMBIEBOBSLEDHEAD_ID: return "IMAGE_ZOMBIEBOBSLEDHEAD";
		case IMAGE_ZOMBIELADDERHEAD_ID: return "IMAGE_ZOMBIELADDERHEAD";
		case IMAGE_ZOMBIEYETIHEAD_ID: return "IMAGE_ZOMBIEYETIHEAD";
		case IMAGE_SEEDPACKETFLASH_ID: return "IMAGE_SEEDPACKETFLASH";
		case IMAGE_ZOMBIEJACKBOXARM_ID: return "IMAGE_ZOMBIEJACKBOXARM";
		case IMAGE_IMITATERCLOUDS_ID: return "IMAGE_IMITATERCLOUDS";
		case IMAGE_IMITATERPUFFS_ID: return "IMAGE_IMITATERPUFFS";
		case IMAGE_ZOMBIE_BOSS_FIREBALL_PARTICLES_ID: return "IMAGE_ZOMBIE_BOSS_FIREBALL_PARTICLES";
		case IMAGE_ZOMBIE_BOSS_ICEBALL_PARTICLES_ID: return "IMAGE_ZOMBIE_BOSS_ICEBALL_PARTICLES";
		case IMAGE_ZOMBIE_BOSS_FIREBALL_GROUNDPARTICLES_ID: return "IMAGE_ZOMBIE_BOSS_FIREBALL_GROUNDPARTICLES";
		case IMAGE_ZOMBIE_BOSS_ICEBALL_GROUNDPARTICLES_ID: return "IMAGE_ZOMBIE_BOSS_ICEBALL_GROUNDPARTICLES";
		case IMAGE_DOOMSHROOM_EXPLOSION_BASE_ID: return "IMAGE_DOOMSHROOM_EXPLOSION_BASE";
		case IMAGE_RAIN_ID: return "IMAGE_RAIN";
		case IMAGE_VASE_CHUNKS_ID: return "IMAGE_VASE_CHUNKS";
		case IMAGE_ZOMBOSS_PARTICLES_ID: return "IMAGE_ZOMBOSS_PARTICLES";
		case IMAGE_AWARDPICKUPGLOW_ID: return "IMAGE_AWARDPICKUPGLOW";
		case IMAGE_ZOMBIE_SEAWEED_ID: return "IMAGE_ZOMBIE_SEAWEED";
		case IMAGE_PINATA_ID: return "IMAGE_PINATA";
		case IMAGE_ZOMBIEFUTUREGLASSES_ID: return "IMAGE_ZOMBIEFUTUREGLASSES";
		case IMAGE_DUST_PUFFS_ID: return "IMAGE_DUST_PUFFS";
		case IMAGE_REANIM_WALLNUT_BODY_ID: return "IMAGE_REANIM_WALLNUT_BODY";
		case IMAGE_REANIM_WALLNUT_CRACKED1_ID: return "IMAGE_REANIM_WALLNUT_CRACKED1";
		case IMAGE_REANIM_WALLNUT_CRACKED2_ID: return "IMAGE_REANIM_WALLNUT_CRACKED2";
		case IMAGE_REANIM_TALLNUT_CRACKED1_ID: return "IMAGE_REANIM_TALLNUT_CRACKED1";
		case IMAGE_REANIM_TALLNUT_CRACKED2_ID: return "IMAGE_REANIM_TALLNUT_CRACKED2";
		case IMAGE_REANIM_PUMPKIN_DAMAGE1_ID: return "IMAGE_REANIM_PUMPKIN_DAMAGE1";
		case IMAGE_REANIM_PUMPKIN_DAMAGE3_ID: return "IMAGE_REANIM_PUMPKIN_DAMAGE3";
		case IMAGE_REANIM_ZOMBIE_CONE1_ID: return "IMAGE_REANIM_ZOMBIE_CONE1";
		case IMAGE_REANIM_ZOMBIE_CONE2_ID: return "IMAGE_REANIM_ZOMBIE_CONE2";
		case IMAGE_REANIM_ZOMBIE_CONE3_ID: return "IMAGE_REANIM_ZOMBIE_CONE3";
		case IMAGE_REANIM_ZOMBIE_BUCKET1_ID: return "IMAGE_REANIM_ZOMBIE_BUCKET1";
		case IMAGE_REANIM_ZOMBIE_BUCKET2_ID: return "IMAGE_REANIM_ZOMBIE_BUCKET2";
		case IMAGE_REANIM_ZOMBIE_BUCKET3_ID: return "IMAGE_REANIM_ZOMBIE_BUCKET3";
		case IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT_ID: return "IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT";
		case IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT2_ID: return "IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT2";
		case IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT3_ID: return "IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT3";
		case IMAGE_REANIM_ZOMBIE_SCREENDOOR1_ID: return "IMAGE_REANIM_ZOMBIE_SCREENDOOR1";
		case IMAGE_REANIM_ZOMBIE_SCREENDOOR2_ID: return "IMAGE_REANIM_ZOMBIE_SCREENDOOR2";
		case IMAGE_REANIM_ZOMBIE_SCREENDOOR3_ID: return "IMAGE_REANIM_ZOMBIE_SCREENDOOR3";
		case IMAGE_REANIM_ZOMBIE_FLAG1_ID: return "IMAGE_REANIM_ZOMBIE_FLAG1";
		case IMAGE_REANIM_ZOMBIE_FLAG3_ID: return "IMAGE_REANIM_ZOMBIE_FLAG3";
		case IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET_ID: return "IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET";
		case IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET2_ID: return "IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET2";
		case IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET3_ID: return "IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET3";
		case IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_HAND_ID: return "IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_HAND";
		case IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_LOWER_ID: return "IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_LOWER";
		case IMAGE_REANIM_ZOMBIE_PAPER_PAPER2_ID: return "IMAGE_REANIM_ZOMBIE_PAPER_PAPER2";
		case IMAGE_REANIM_ZOMBIE_PAPER_PAPER3_ID: return "IMAGE_REANIM_ZOMBIE_PAPER_PAPER3";
		case IMAGE_REANIM_ZOMBIE_PAPER_MADHEAD_ID: return "IMAGE_REANIM_ZOMBIE_PAPER_MADHEAD";
		case IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_ZAMBONI_WHEEL_FLAT_ID: return "IMAGE_REANIM_ZOMBIE_ZAMBONI_WHEEL_FLAT";
		case IMAGE_REANIM_COIN_SILVER_DOLLAR_ID: return "IMAGE_REANIM_COIN_SILVER_DOLLAR";
		case IMAGE_REANIM_COIN_GOLD_DOLLAR_ID: return "IMAGE_REANIM_COIN_GOLD_DOLLAR";
		case IMAGE_REANIM_DIAMOND_ID: return "IMAGE_REANIM_DIAMOND";
		case IMAGE_REANIM_COINGLOW_ID: return "IMAGE_REANIM_COINGLOW";
		case IMAGE_REANIM_ZOMBIE_DISCO_OUTERARM_HAND_ID: return "IMAGE_REANIM_ZOMBIE_DISCO_OUTERARM_HAND";
		case IMAGE_REANIM_ZOMBIE_DISCO_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_DISCO_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_BACKUP_INNERARM_HAND_ID: return "IMAGE_REANIM_ZOMBIE_BACKUP_INNERARM_HAND";
		case IMAGE_REANIM_ZOMBIE_BACKUP_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_BACKUP_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_POLEVAULTER_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_POLEVAULTER_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_OUTERARM_HAND_ID: return "IMAGE_REANIM_ZOMBIE_OUTERARM_HAND";
		case IMAGE_REANIM_ZOMBIE_BALLOON_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_BALLOON_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE_ID: return "IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE";
		case IMAGE_REANIM_ZOMBIE_IMP_ARM2_ID: return "IMAGE_REANIM_ZOMBIE_IMP_ARM2";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_2_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_2";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_3_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_3";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_DUCKXING_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_DUCKXING";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_ZOMBIE_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_ZOMBIE";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_FOOT2_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_FOOT2";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_REDEYE_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_REDEYE";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE";
		case IMAGE_REANIM_ZOMBIE_DIGGER_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_DIGGER_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_DOLPHINRIDER_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_DOLPHINRIDER_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_POGO_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_POGO_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE1";
		case IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE2";
		case IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_POGO_STICKHANDS2_ID: return "IMAGE_REANIM_ZOMBIE_POGO_STICKHANDS2";
		case IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_HAND_ID: return "IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_HAND";
		case IMAGE_REANIM_ZOMBIE_JACKBOX_BOX_ID: return "IMAGE_REANIM_ZOMBIE_JACKBOX_BOX";
		case IMAGE_REANIM_ZOMBIE_JACKBOX_OUTERARM_LOWER2_ID: return "IMAGE_REANIM_ZOMBIE_JACKBOX_OUTERARM_LOWER2";
		case IMAGE_REANIM_ZOMBIE_SNORKLE_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_SNORKLE_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_BUNGI_HEAD_SCARED_ID: return "IMAGE_REANIM_ZOMBIE_BUNGI_HEAD_SCARED";
		case IMAGE_REANIM_ZOMBIE_CATAPULT_BASKETBALL_ID: return "IMAGE_REANIM_ZOMBIE_CATAPULT_BASKETBALL";
		case IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_ID: return "IMAGE_REANIM_ZOMBIE_CATAPULT_POLE";
		case IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE_ID: return "IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE";
		case IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_WITHBALL_ID: return "IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_WITHBALL";
		case IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE_WITHBALL_ID: return "IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE_WITHBALL";
		case IMAGE_REANIM_ZOMBIE_CATAPULT_SIDING_DAMAGE_ID: return "IMAGE_REANIM_ZOMBIE_CATAPULT_SIDING_DAMAGE";
		case IMAGE_REANIM_ZOMBIE_LADDER_1_ID: return "IMAGE_REANIM_ZOMBIE_LADDER_1";
		case IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_LADDER_5_ID: return "IMAGE_REANIM_ZOMBIE_LADDER_5";
		case IMAGE_REANIM_ZOMBIE_LADDER_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_LADDER_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_BOSS_ICEBALL_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_ICEBALL";
		case IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_BOSS_EYEGLOW_BLUE_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_EYEGLOW_BLUE";
		case IMAGE_REANIM_ZOMBIE_BOSS_MOUTHGLOW_BLUE_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_MOUTHGLOW_BLUE";
		case IMAGE_REANIM_CABBAGEPULT_CABBAGE_ID: return "IMAGE_REANIM_CABBAGEPULT_CABBAGE";
		case IMAGE_REANIM_CORNPULT_KERNAL_ID: return "IMAGE_REANIM_CORNPULT_KERNAL";
		case IMAGE_REANIM_CORNPULT_BUTTER_ID: return "IMAGE_REANIM_CORNPULT_BUTTER";
		case IMAGE_REANIM_CORNPULT_BUTTER_SPLAT_ID: return "IMAGE_REANIM_CORNPULT_BUTTER_SPLAT";
		case IMAGE_REANIM_MELONPULT_MELON_ID: return "IMAGE_REANIM_MELONPULT_MELON";
		case IMAGE_REANIM_WINTERMELON_PROJECTILE_ID: return "IMAGE_REANIM_WINTERMELON_PROJECTILE";
		case IMAGE_REANIM_ZOMBIE_DIGGER_PICKAXE_ID: return "IMAGE_REANIM_ZOMBIE_DIGGER_PICKAXE";
		case IMAGE_REANIM_ZOMBIE_HEAD_GROSSOUT_ID: return "IMAGE_REANIM_ZOMBIE_HEAD_GROSSOUT";
		case IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES1_ID: return "IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES1";
		case IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES2_ID: return "IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES2";
		case IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES3_ID: return "IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES3";
		case IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES4_ID: return "IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES4";
		case IMAGE_REANIM_GARLIC_BODY2_ID: return "IMAGE_REANIM_GARLIC_BODY2";
		case IMAGE_REANIM_GARLIC_BODY3_ID: return "IMAGE_REANIM_GARLIC_BODY3";
		case IMAGE_REANIM_COBCANNON_COB_ID: return "IMAGE_REANIM_COBCANNON_COB";
		case IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_HAND_ID: return "IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_HAND";
		case IMAGE_REANIM_ZOMBIE_SNORKLE_HEAD_ID: return "IMAGE_REANIM_ZOMBIE_SNORKLE_HEAD";
		case IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_BUTTON_ID: return "IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_BUTTON";
		case IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_HIGHLIGHT_ID: return "IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_HIGHLIGHT";
		case IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_BUTTON_ID: return "IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_BUTTON";
		case IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_HIGHLIGHT_ID: return "IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_HIGHLIGHT";
		case IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_BUTTON_ID: return "IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_BUTTON";
		case IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_HIGHLIGHT_ID: return "IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_HIGHLIGHT";
		case IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_BUTTON_ID: return "IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_BUTTON";
		case IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_HIGHLIGHT_ID: return "IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_HIGHLIGHT";
		case IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_BUTTON_ID: return "IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_BUTTON";
		case IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_HIGHLIGHT_ID: return "IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_HIGHLIGHT";
		case IMAGE_REANIM_SELECTORSCREEN_WOODSIGN2_PRESS_ID: return "IMAGE_REANIM_SELECTORSCREEN_WOODSIGN2_PRESS";
		case IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3_PRESS_ID: return "IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3_PRESS";
		case IMAGE_REANIM_SELECTORSCREEN_BG_ID: return "IMAGE_REANIM_SELECTORSCREEN_BG";
		case IMAGE_REANIM_SELECTORSCREEN_ALMANAC_SHADOW_ID: return "IMAGE_REANIM_SELECTORSCREEN_ALMANAC_SHADOW";
		case IMAGE_REANIM_SELECTORSCREEN_KEY_SHADOW_ID: return "IMAGE_REANIM_SELECTORSCREEN_KEY_SHADOW";
		case IMAGE_REANIM_TREE_BG_ID: return "IMAGE_REANIM_TREE_BG";
		case IMAGE_REANIM_POT_TOP_DARK_ID: return "IMAGE_REANIM_POT_TOP_DARK";
		case IMAGE_REANIM_ZENGARDEN_BUGSPRAY_BOTTLE_ID: return "IMAGE_REANIM_ZENGARDEN_BUGSPRAY_BOTTLE";
		case IMAGE_REANIM_STINKY_TURN3_ID: return "IMAGE_REANIM_STINKY_TURN3";
		case IMAGE_REANIM_CRAZYDAVE_MOUTH1_ID: return "IMAGE_REANIM_CRAZYDAVE_MOUTH1";
		case IMAGE_REANIM_CRAZYDAVE_MOUTH4_ID: return "IMAGE_REANIM_CRAZYDAVE_MOUTH4";
		case IMAGE_REANIM_CRAZYDAVE_MOUTH5_ID: return "IMAGE_REANIM_CRAZYDAVE_MOUTH5";
		case IMAGE_REANIM_CRAZYDAVE_MOUTH6_ID: return "IMAGE_REANIM_CRAZYDAVE_MOUTH6";
		case IMAGE_REANIM_ZOMBIE_MUSTACHE2_ID: return "IMAGE_REANIM_ZOMBIE_MUSTACHE2";
		case IMAGE_REANIM_ZOMBIE_MUSTACHE3_ID: return "IMAGE_REANIM_ZOMBIE_MUSTACHE3";
		case SOUND_ACHIEVEMENT_ID: return "SOUND_ACHIEVEMENT";
		case SOUND_AWOOGA_ID: return "SOUND_AWOOGA";
		case SOUND_BLEEP_ID: return "SOUND_BLEEP";
		case SOUND_BUZZER_ID: return "SOUND_BUZZER";
		case SOUND_CHOMP_ID: return "SOUND_CHOMP";
		case SOUND_CHOMP2_ID: return "SOUND_CHOMP2";
		case SOUND_CHOMPSOFT_ID: return "SOUND_CHOMPSOFT";
		case SOUND_EVILLAUGH_ID: return "SOUND_EVILLAUGH";
		case SOUND_FLOOP_ID: return "SOUND_FLOOP";
		case SOUND_FROZEN_ID: return "SOUND_FROZEN";
		case SOUND_GULP_ID: return "SOUND_GULP";
		case SOUND_GROAN_ID: return "SOUND_GROAN";
		case SOUND_GROAN2_ID: return "SOUND_GROAN2";
		case SOUND_GROAN3_ID: return "SOUND_GROAN3";
		case SOUND_GROAN4_ID: return "SOUND_GROAN4";
		case SOUND_GROAN5_ID: return "SOUND_GROAN5";
		case SOUND_GROAN6_ID: return "SOUND_GROAN6";
		case SOUND_LOSEMUSIC_ID: return "SOUND_LOSEMUSIC";
		case SOUND_MINDCONTROLLED_ID: return "SOUND_MINDCONTROLLED";
		case SOUND_PAUSE_ID: return "SOUND_PAUSE";
		case SOUND_PLANT_ID: return "SOUND_PLANT";
		case SOUND_PLANT2_ID: return "SOUND_PLANT2";
		case SOUND_POINTS_ID: return "SOUND_POINTS";
		case SOUND_SEEDLIFT_ID: return "SOUND_SEEDLIFT";
		case SOUND_SIREN_ID: return "SOUND_SIREN";
		case SOUND_SLURP_ID: return "SOUND_SLURP";
		case SOUND_SPLAT_ID: return "SOUND_SPLAT";
		case SOUND_SPLAT2_ID: return "SOUND_SPLAT2";
		case SOUND_SPLAT3_ID: return "SOUND_SPLAT3";
		case SOUND_SUKHBIR_ID: return "SOUND_SUKHBIR";
		case SOUND_SUKHBIR2_ID: return "SOUND_SUKHBIR2";
		case SOUND_SUKHBIR3_ID: return "SOUND_SUKHBIR3";
		case SOUND_SUKHBIR4_ID: return "SOUND_SUKHBIR4";
		case SOUND_SUKHBIR5_ID: return "SOUND_SUKHBIR5";
		case SOUND_SUKHBIR6_ID: return "SOUND_SUKHBIR6";
		case SOUND_TAP_ID: return "SOUND_TAP";
		case SOUND_TAP2_ID: return "SOUND_TAP2";
		case SOUND_THROW_ID: return "SOUND_THROW";
		case SOUND_THROW2_ID: return "SOUND_THROW2";
		case SOUND_BLOVER_ID: return "SOUND_BLOVER";
		case SOUND_WINMUSIC_ID: return "SOUND_WINMUSIC";
		case SOUND_LAWNMOWER_ID: return "SOUND_LAWNMOWER";
		case SOUND_BOING_ID: return "SOUND_BOING";
		case SOUND_JACKINTHEBOX_ID: return "SOUND_JACKINTHEBOX";
		case SOUND_DIAMOND_ID: return "SOUND_DIAMOND";
		case SOUND_DOLPHIN_APPEARS_ID: return "SOUND_DOLPHIN_APPEARS";
		case SOUND_DOLPHIN_BEFORE_JUMPING_ID: return "SOUND_DOLPHIN_BEFORE_JUMPING";
		case SOUND_POTATO_MINE_ID: return "SOUND_POTATO_MINE";
		case SOUND_ZAMBONI_ID: return "SOUND_ZAMBONI";
		case SOUND_BALLOON_POP_ID: return "SOUND_BALLOON_POP";
		case SOUND_THUNDER_ID: return "SOUND_THUNDER";
		case SOUND_ZOMBIESPLASH_ID: return "SOUND_ZOMBIESPLASH";
		case SOUND_BOWLING_ID: return "SOUND_BOWLING";
		case SOUND_BOWLINGIMPACT_ID: return "SOUND_BOWLINGIMPACT";
		case SOUND_BOWLINGIMPACT2_ID: return "SOUND_BOWLINGIMPACT2";
		case SOUND_GRAVEBUSTERCHOMP_ID: return "SOUND_GRAVEBUSTERCHOMP";
		case SOUND_GRAVEBUTTON_ID: return "SOUND_GRAVEBUTTON";
		case SOUND_LIMBS_POP_ID: return "SOUND_LIMBS_POP";
		case SOUND_PLANTERN_ID: return "SOUND_PLANTERN";
		case SOUND_POGO_ZOMBIE_ID: return "SOUND_POGO_ZOMBIE";
		case SOUND_SNOW_PEA_SPARKLES_ID: return "SOUND_SNOW_PEA_SPARKLES";
		case SOUND_PLANT_WATER_ID: return "SOUND_PLANT_WATER";
		case SOUND_ZOMBIE_ENTERING_WATER_ID: return "SOUND_ZOMBIE_ENTERING_WATER";
		case SOUND_ZOMBIE_FALLING_1_ID: return "SOUND_ZOMBIE_FALLING_1";
		case SOUND_ZOMBIE_FALLING_2_ID: return "SOUND_ZOMBIE_FALLING_2";
		case SOUND_PUFF_ID: return "SOUND_PUFF";
		case SOUND_FUME_ID: return "SOUND_FUME";
		case SOUND_HUGE_WAVE_ID: return "SOUND_HUGE_WAVE";
		case SOUND_SLOT_MACHINE_ID: return "SOUND_SLOT_MACHINE";
		case SOUND_COIN_ID: return "SOUND_COIN";
		case SOUND_ROLL_IN_ID: return "SOUND_ROLL_IN";
		case SOUND_DIGGER_ZOMBIE_ID: return "SOUND_DIGGER_ZOMBIE";
		case SOUND_HATCHBACK_CLOSE_ID: return "SOUND_HATCHBACK_CLOSE";
		case SOUND_HATCHBACK_OPEN_ID: return "SOUND_HATCHBACK_OPEN";
		case SOUND_KERNELPULT_ID: return "SOUND_KERNELPULT";
		case SOUND_KERNELPULT2_ID: return "SOUND_KERNELPULT2";
		case SOUND_ZOMBAQUARIUM_DIE_ID: return "SOUND_ZOMBAQUARIUM_DIE";
		case SOUND_BUNGEE_SCREAM_ID: return "SOUND_BUNGEE_SCREAM";
		case SOUND_BUNGEE_SCREAM2_ID: return "SOUND_BUNGEE_SCREAM2";
		case SOUND_BUNGEE_SCREAM3_ID: return "SOUND_BUNGEE_SCREAM3";
		case SOUND_BUTTER_ID: return "SOUND_BUTTER";
		case SOUND_JACK_SURPRISE_ID: return "SOUND_JACK_SURPRISE";
		case SOUND_JACK_SURPRISE2_ID: return "SOUND_JACK_SURPRISE2";
		case SOUND_NEWSPAPER_RARRGH_ID: return "SOUND_NEWSPAPER_RARRGH";
		case SOUND_NEWSPAPER_RARRGH2_ID: return "SOUND_NEWSPAPER_RARRGH2";
		case SOUND_NEWSPAPER_RIP_ID: return "SOUND_NEWSPAPER_RIP";
		case SOUND_SQUASH_HMM_ID: return "SOUND_SQUASH_HMM";
		case SOUND_SQUASH_HMM2_ID: return "SOUND_SQUASH_HMM2";
		case SOUND_VASE_BREAKING_ID: return "SOUND_VASE_BREAKING";
		case SOUND_POOL_CLEANER_ID: return "SOUND_POOL_CLEANER";
		case SOUND_MAGNETSHROOM_ID: return "SOUND_MAGNETSHROOM";
		case SOUND_LADDER_ZOMBIE_ID: return "SOUND_LADDER_ZOMBIE";
		case SOUND_GARGANTUAR_THUMP_ID: return "SOUND_GARGANTUAR_THUMP";
		case SOUND_BASKETBALL_ID: return "SOUND_BASKETBALL";
		case SOUND_FIREPEA_ID: return "SOUND_FIREPEA";
		case SOUND_IGNITE_ID: return "SOUND_IGNITE";
		case SOUND_IGNITE2_ID: return "SOUND_IGNITE2";
		case SOUND_READYSETPLANT_ID: return "SOUND_READYSETPLANT";
		case SOUND_DOOMSHROOM_ID: return "SOUND_DOOMSHROOM";
		case SOUND_EXPLOSION_ID: return "SOUND_EXPLOSION";
		case SOUND_FINALWAVE_ID: return "SOUND_FINALWAVE";
		case SOUND_REVERSE_EXPLOSION_ID: return "SOUND_REVERSE_EXPLOSION";
		case SOUND_RVTHROW_ID: return "SOUND_RVTHROW";
		case SOUND_SHIELDHIT_ID: return "SOUND_SHIELDHIT";
		case SOUND_SHIELDHIT2_ID: return "SOUND_SHIELDHIT2";
		case SOUND_BOSSEXPLOSION_ID: return "SOUND_BOSSEXPLOSION";
		case SOUND_CHERRYBOMB_ID: return "SOUND_CHERRYBOMB";
		case SOUND_BONK_ID: return "SOUND_BONK";
		case SOUND_SWING_ID: return "SOUND_SWING";
		case SOUND_RAIN_ID: return "SOUND_RAIN";
		case SOUND_LIGHTFILL_ID: return "SOUND_LIGHTFILL";
		case SOUND_PLASTICHIT_ID: return "SOUND_PLASTICHIT";
		case SOUND_PLASTICHIT2_ID: return "SOUND_PLASTICHIT2";
		case SOUND_JALAPENO_ID: return "SOUND_JALAPENO";
		case SOUND_BALLOONINFLATE_ID: return "SOUND_BALLOONINFLATE";
		case SOUND_BIGCHOMP_ID: return "SOUND_BIGCHOMP";
		case SOUND_MELONIMPACT_ID: return "SOUND_MELONIMPACT";
		case SOUND_MELONIMPACT2_ID: return "SOUND_MELONIMPACT2";
		case SOUND_PLANTGROW_ID: return "SOUND_PLANTGROW";
		case SOUND_SHOOP_ID: return "SOUND_SHOOP";
		case SOUND_TAPGLASS_ID: return "SOUND_TAPGLASS";
		case SOUND_JUICY_ID: return "SOUND_JUICY";
		case SOUND_COFFEE_ID: return "SOUND_COFFEE";
		case SOUND_WAKEUP_ID: return "SOUND_WAKEUP";
		case SOUND_LOWGROAN_ID: return "SOUND_LOWGROAN";
		case SOUND_LOWGROAN2_ID: return "SOUND_LOWGROAN2";
		case SOUND_PRIZE_ID: return "SOUND_PRIZE";
		case SOUND_YUCK_ID: return "SOUND_YUCK";
		case SOUND_YUCK2_ID: return "SOUND_YUCK2";
		case SOUND_GRASSSTEP_ID: return "SOUND_GRASSSTEP";
		case SOUND_SHOVEL_ID: return "SOUND_SHOVEL";
		case SOUND_COBLAUNCH_ID: return "SOUND_COBLAUNCH";
		case SOUND_WATERING_ID: return "SOUND_WATERING";
		case SOUND_POLEVAULT_ID: return "SOUND_POLEVAULT";
		case SOUND_GRAVESTONE_RUMBLE_ID: return "SOUND_GRAVESTONE_RUMBLE";
		case SOUND_DIRT_RISE_ID: return "SOUND_DIRT_RISE";
		case SOUND_FERTILIZER_ID: return "SOUND_FERTILIZER";
		case SOUND_PORTAL_ID: return "SOUND_PORTAL";
		case SOUND_BUGSPRAY_ID: return "SOUND_BUGSPRAY";
		case SOUND_SCREAM_ID: return "SOUND_SCREAM";
		case SOUND_PAPER_ID: return "SOUND_PAPER";
		case SOUND_MONEYFALLS_ID: return "SOUND_MONEYFALLS";
		case SOUND_IMP_ID: return "SOUND_IMP";
		case SOUND_IMP2_ID: return "SOUND_IMP2";
		case SOUND_HYDRAULIC_SHORT_ID: return "SOUND_HYDRAULIC_SHORT";
		case SOUND_HYDRAULIC_ID: return "SOUND_HYDRAULIC";
		case SOUND_GARGANTUDEATH_ID: return "SOUND_GARGANTUDEATH";
		case SOUND_CERAMIC_ID: return "SOUND_CERAMIC";
		case SOUND_BOSSBOULDERATTACK_ID: return "SOUND_BOSSBOULDERATTACK";
		case SOUND_CHIME_ID: return "SOUND_CHIME";
		case SOUND_CRAZYDAVESHORT1_ID: return "SOUND_CRAZYDAVESHORT1";
		case SOUND_CRAZYDAVESHORT2_ID: return "SOUND_CRAZYDAVESHORT2";
		case SOUND_CRAZYDAVESHORT3_ID: return "SOUND_CRAZYDAVESHORT3";
		case SOUND_CRAZYDAVELONG1_ID: return "SOUND_CRAZYDAVELONG1";
		case SOUND_CRAZYDAVELONG2_ID: return "SOUND_CRAZYDAVELONG2";
		case SOUND_CRAZYDAVELONG3_ID: return "SOUND_CRAZYDAVELONG3";
		case SOUND_CRAZYDAVEEXTRALONG1_ID: return "SOUND_CRAZYDAVEEXTRALONG1";
		case SOUND_CRAZYDAVEEXTRALONG2_ID: return "SOUND_CRAZYDAVEEXTRALONG2";
		case SOUND_CRAZYDAVEEXTRALONG3_ID: return "SOUND_CRAZYDAVEEXTRALONG3";
		case SOUND_CRAZYDAVECRAZY_ID: return "SOUND_CRAZYDAVECRAZY";
		case SOUND_PHONOGRAPH_ID: return "SOUND_PHONOGRAPH";
		case SOUND_DANCER_ID: return "SOUND_DANCER";
		case SOUND_FINALFANFARE_ID: return "SOUND_FINALFANFARE";
		case SOUND_CRAZYDAVESCREAM_ID: return "SOUND_CRAZYDAVESCREAM";
		case SOUND_CRAZYDAVESCREAM2_ID: return "SOUND_CRAZYDAVESCREAM2";
		case IMAGE_BACKGROUND1_ID: return "IMAGE_BACKGROUND1";
		case IMAGE_BACKGROUND1_GAMEOVER_INTERIOR_OVERLAY_ID: return "IMAGE_BACKGROUND1_GAMEOVER_INTERIOR_OVERLAY";
		case IMAGE_BACKGROUND1_GAMEOVER_MASK_ID: return "IMAGE_BACKGROUND1_GAMEOVER_MASK";
		case IMAGE_BACKGROUND1UNSODDED_ID: return "IMAGE_BACKGROUND1UNSODDED";
		case IMAGE_SOD1ROW_ID: return "IMAGE_SOD1ROW";
		case IMAGE_SOD3ROW_ID: return "IMAGE_SOD3ROW";
		case IMAGE_BACKGROUND2_ID: return "IMAGE_BACKGROUND2";
		case IMAGE_BACKGROUND2_GAMEOVER_INTERIOR_OVERLAY_ID: return "IMAGE_BACKGROUND2_GAMEOVER_INTERIOR_OVERLAY";
		case IMAGE_BACKGROUND2_GAMEOVER_MASK_ID: return "IMAGE_BACKGROUND2_GAMEOVER_MASK";
		case IMAGE_BACKGROUND3_ID: return "IMAGE_BACKGROUND3";
		case IMAGE_BACKGROUND3_GAMEOVER_INTERIOR_OVERLAY_ID: return "IMAGE_BACKGROUND3_GAMEOVER_INTERIOR_OVERLAY";
		case IMAGE_BACKGROUND3_GAMEOVER_MASK_ID: return "IMAGE_BACKGROUND3_GAMEOVER_MASK";
		case IMAGE_BACKGROUND4_ID: return "IMAGE_BACKGROUND4";
		case IMAGE_BACKGROUND4_GAMEOVER_INTERIOR_OVERLAY_ID: return "IMAGE_BACKGROUND4_GAMEOVER_INTERIOR_OVERLAY";
		case IMAGE_BACKGROUND4_GAMEOVER_MASK_ID: return "IMAGE_BACKGROUND4_GAMEOVER_MASK";
		case IMAGE_FOG_ID: return "IMAGE_FOG";
		case IMAGE_FOG_SOFTWARE_ID: return "IMAGE_FOG_SOFTWARE";
		case IMAGE_BACKGROUND5_ID: return "IMAGE_BACKGROUND5";
		case IMAGE_BACKGROUND5_GAMEOVER_MASK_ID: return "IMAGE_BACKGROUND5_GAMEOVER_MASK";
		case IMAGE_BACKGROUND6BOSS_ID: return "IMAGE_BACKGROUND6BOSS";
		case IMAGE_BACKGROUND6_GAMEOVER_MASK_ID: return "IMAGE_BACKGROUND6_GAMEOVER_MASK";
		case IMAGE_BACKGROUND_MUSHROOMGARDEN_ID: return "IMAGE_BACKGROUND_MUSHROOMGARDEN";
		case IMAGE_BACKGROUND_GREENHOUSE_ID: return "IMAGE_BACKGROUND_GREENHOUSE";
		case IMAGE_BACKGROUND_GREENHOUSE_OVERLAY_ID: return "IMAGE_BACKGROUND_GREENHOUSE_OVERLAY";
		case IMAGE_AQUARIUM1_ID: return "IMAGE_AQUARIUM1";
		case IMAGE_WAVECENTER_ID: return "IMAGE_WAVECENTER";
		case IMAGE_WAVESIDE_ID: return "IMAGE_WAVESIDE";
		case IMAGE_AWARDSCREEN_BACK_ID: return "IMAGE_AWARDSCREEN_BACK";
		case IMAGE_ACHIEVEMENTS_PORTRAITS_ID: return "IMAGE_ACHIEVEMENTS_PORTRAITS";
		case IMAGE_CHALLENGE_BACKGROUND_ID: return "IMAGE_CHALLENGE_BACKGROUND";
		case IMAGE_CHALLENGE_WINDOW_ID: return "IMAGE_CHALLENGE_WINDOW";
		case IMAGE_CHALLENGE_WINDOW_HIGHLIGHT_ID: return "IMAGE_CHALLENGE_WINDOW_HIGHLIGHT";
		case IMAGE_CHALLENGE_BLANK_ID: return "IMAGE_CHALLENGE_BLANK";
		case IMAGE_CHALLENGE_THUMBNAILS_ID: return "IMAGE_CHALLENGE_THUMBNAILS";
		case IMAGE_SURVIVAL_THUMBNAILS_ID: return "IMAGE_SURVIVAL_THUMBNAILS";
		case IMAGE_LOCK_ID: return "IMAGE_LOCK";
		case IMAGE_LOCK_OPEN_ID: return "IMAGE_LOCK_OPEN";
		case IMAGE_ACHIEVEMENT_TILE_ID: return "IMAGE_ACHIEVEMENT_TILE";
		case IMAGE_ACHIEVEMENT_BACK_GLOW_ID: return "IMAGE_ACHIEVEMENT_BACK_GLOW";
		case IMAGE_ACHIEVEMENT_SELECTOR_TILE_ID: return "IMAGE_ACHIEVEMENT_SELECTOR_TILE";
		case IMAGE_ACHIEVEMENT_TILE_CHINA_ID: return "IMAGE_ACHIEVEMENT_TILE_CHINA";
		case IMAGE_ACHIEVEMENT_MORE_ID: return "IMAGE_ACHIEVEMENT_MORE";
		case IMAGE_ACHIEVEMENT_MORE_HIGHLIGHT_ID: return "IMAGE_ACHIEVEMENT_MORE_HIGHLIGHT";
		case IMAGE_ACHIEVEMENT_TOP_ID: return "IMAGE_ACHIEVEMENT_TOP";
		case IMAGE_ACHIEVEMENT_TOP_HIGHLIGHT_ID: return "IMAGE_ACHIEVEMENT_TOP_HIGHLIGHT";
		case IMAGE_ACHIEVEMENT_ROCK_ID: return "IMAGE_ACHIEVEMENT_ROCK";
		case IMAGE_ACHIEVEMENT_BOOKWORM_ID: return "IMAGE_ACHIEVEMENT_BOOKWORM";
		case IMAGE_ACHIEVEMENT_BEJEWELED_ID: return "IMAGE_ACHIEVEMENT_BEJEWELED";
		case IMAGE_ACHIEVEMENT_CHUZZLE_ID: return "IMAGE_ACHIEVEMENT_CHUZZLE";
		case IMAGE_ACHIEVEMENT_PEGGLE_ID: return "IMAGE_ACHIEVEMENT_PEGGLE";
		case IMAGE_ACHIEVEMENT_PIPE_ID: return "IMAGE_ACHIEVEMENT_PIPE";
		case IMAGE_ACHIEVEMENT_ZUMA_ID: return "IMAGE_ACHIEVEMENT_ZUMA";
		case IMAGE_QUICKPLAY_BACKGROUND_ID: return "IMAGE_QUICKPLAY_BACKGROUND";
		case IMAGE_QUICKPLAY_LEFT_BUTTON_ID: return "IMAGE_QUICKPLAY_LEFT_BUTTON";
		case IMAGE_QUICKPLAY_LEFT_BUTTON_HIGHLIGHT_ID: return "IMAGE_QUICKPLAY_LEFT_BUTTON_HIGHLIGHT";
		case IMAGE_QUICKPLAY_RIGHT_BUTTON_ID: return "IMAGE_QUICKPLAY_RIGHT_BUTTON";
		case IMAGE_QUICKPLAY_RIGHT_BUTTON_HIGHLIGHT_ID: return "IMAGE_QUICKPLAY_RIGHT_BUTTON_HIGHLIGHT";
		case IMAGE_QUICKPLAY_BACK_HIGHLIGHT_ID: return "IMAGE_QUICKPLAY_BACK_HIGHLIGHT";
		case IMAGE_QUICKPLAY_WIDGET_ID: return "IMAGE_QUICKPLAY_WIDGET";
		case IMAGE_ALMANAC_INDEXBACK_ID: return "IMAGE_ALMANAC_INDEXBACK";
		case IMAGE_ALMANAC_PLANTBACK_ID: return "IMAGE_ALMANAC_PLANTBACK";
		case IMAGE_ALMANAC_ZOMBIEBACK_ID: return "IMAGE_ALMANAC_ZOMBIEBACK";
		case IMAGE_ALMANAC_PLANTCARD_ID: return "IMAGE_ALMANAC_PLANTCARD";
		case IMAGE_ALMANAC_ZOMBIECARD_ID: return "IMAGE_ALMANAC_ZOMBIECARD";
		case IMAGE_ALMANAC_ZOMBIEWINDOW_ID: return "IMAGE_ALMANAC_ZOMBIEWINDOW";
		case IMAGE_ALMANAC_ZOMBIEWINDOW2_ID: return "IMAGE_ALMANAC_ZOMBIEWINDOW2";
		case IMAGE_ALMANAC_ZOMBIEBLANK_ID: return "IMAGE_ALMANAC_ZOMBIEBLANK";
		case IMAGE_ALMANAC_PLANTBLANK_ID: return "IMAGE_ALMANAC_PLANTBLANK";
		case IMAGE_ALMANAC_GROUNDDAY_ID: return "IMAGE_ALMANAC_GROUNDDAY";
		case IMAGE_ALMANAC_GROUNDNIGHT_ID: return "IMAGE_ALMANAC_GROUNDNIGHT";
		case IMAGE_ALMANAC_GROUNDPOOL_ID: return "IMAGE_ALMANAC_GROUNDPOOL";
		case IMAGE_ALMANAC_GROUNDNIGHTPOOL_ID: return "IMAGE_ALMANAC_GROUNDNIGHTPOOL";
		case IMAGE_ALMANAC_GROUNDROOF_ID: return "IMAGE_ALMANAC_GROUNDROOF";
		case IMAGE_ALMANAC_GROUNDICE_ID: return "IMAGE_ALMANAC_GROUNDICE";
		case IMAGE_ALMANAC_CLOSEBUTTON_ID: return "IMAGE_ALMANAC_CLOSEBUTTON";
		case IMAGE_ALMANAC_CLOSEBUTTONHIGHLIGHT_ID: return "IMAGE_ALMANAC_CLOSEBUTTONHIGHLIGHT";
		case IMAGE_ALMANAC_INDEXBUTTON_ID: return "IMAGE_ALMANAC_INDEXBUTTON";
		case IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT_ID: return "IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT";
		case IMAGE_ALMANAC_INDEXBUTTON_DISABLE_ID: return "IMAGE_ALMANAC_INDEXBUTTON_DISABLE";
		case IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT_DISABLE_ID: return "IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT_DISABLE";
		case IMAGE_STORE_BACKGROUND_ID: return "IMAGE_STORE_BACKGROUND";
		case IMAGE_STORE_BACKGROUNDNIGHT_ID: return "IMAGE_STORE_BACKGROUNDNIGHT";
		case IMAGE_STORE_CAR_ID: return "IMAGE_STORE_CAR";
		case IMAGE_STORE_CAR_NIGHT_ID: return "IMAGE_STORE_CAR_NIGHT";
		case IMAGE_STORE_CARCLOSED_ID: return "IMAGE_STORE_CARCLOSED";
		case IMAGE_STORE_CARCLOSED_NIGHT_ID: return "IMAGE_STORE_CARCLOSED_NIGHT";
		case IMAGE_STORE_HATCHBACKOPEN_ID: return "IMAGE_STORE_HATCHBACKOPEN";
		case IMAGE_STORE_SIGN_ID: return "IMAGE_STORE_SIGN";
		case IMAGE_STORE_MAINMENUBUTTON_ID: return "IMAGE_STORE_MAINMENUBUTTON";
		case IMAGE_STORE_MAINMENUBUTTONDOWN_ID: return "IMAGE_STORE_MAINMENUBUTTONDOWN";
		case IMAGE_STORE_MAINMENUBUTTONHIGHLIGHT_ID: return "IMAGE_STORE_MAINMENUBUTTONHIGHLIGHT";
		case IMAGE_STORE_NEXTBUTTON_ID: return "IMAGE_STORE_NEXTBUTTON";
		case IMAGE_STORE_NEXTBUTTONHIGHLIGHT_ID: return "IMAGE_STORE_NEXTBUTTONHIGHLIGHT";
		case IMAGE_STORE_NEXTBUTTONDISABLED_ID: return "IMAGE_STORE_NEXTBUTTONDISABLED";
		case IMAGE_STORE_PREVBUTTON_ID: return "IMAGE_STORE_PREVBUTTON";
		case IMAGE_STORE_PREVBUTTONHIGHLIGHT_ID: return "IMAGE_STORE_PREVBUTTONHIGHLIGHT";
		case IMAGE_STORE_PREVBUTTONDISABLED_ID: return "IMAGE_STORE_PREVBUTTONDISABLED";
		case IMAGE_STORE_PRICETAG_ID: return "IMAGE_STORE_PRICETAG";
		case IMAGE_STORE_PACKETUPGRADE_ID: return "IMAGE_STORE_PACKETUPGRADE";
		case IMAGE_STORE_MUSHROOMGARDENICON_ID: return "IMAGE_STORE_MUSHROOMGARDENICON";
		case IMAGE_STORE_AQUARIUMGARDENICON_ID: return "IMAGE_STORE_AQUARIUMGARDENICON";
		case IMAGE_STORE_TREEOFWISDOMICON_ID: return "IMAGE_STORE_TREEOFWISDOMICON";
		case IMAGE_STORE_FIRSTAIDWALLNUTICON_ID: return "IMAGE_STORE_FIRSTAIDWALLNUTICON";
		case IMAGE_STORE_PVZICON_ID: return "IMAGE_STORE_PVZICON";
		case IMAGE_ZOMBIE_NOTE_ID: return "IMAGE_ZOMBIE_NOTE";
		case IMAGE_ZOMBIE_NOTE1_ID: return "IMAGE_ZOMBIE_NOTE1";
		case IMAGE_ZOMBIE_NOTE2_ID: return "IMAGE_ZOMBIE_NOTE2";
		case IMAGE_ZOMBIE_NOTE3_ID: return "IMAGE_ZOMBIE_NOTE3";
		case IMAGE_ZOMBIE_NOTE4_ID: return "IMAGE_ZOMBIE_NOTE4";
		case IMAGE_ZOMBIE_FINAL_NOTE_ID: return "IMAGE_ZOMBIE_FINAL_NOTE";
		case IMAGE_ZOMBIE_NOTE_HELP_ID: return "IMAGE_ZOMBIE_NOTE_HELP";
		case FONT_BRIANNETOD32_ID: return "FONT_BRIANNETOD32";
		case FONT_BRIANNETOD32BLACK_ID: return "FONT_BRIANNETOD32BLACK";
		case IMAGE_REANIM_SUNFLOWER_HEAD_SING1_ID: return "IMAGE_REANIM_SUNFLOWER_HEAD_SING1";
		case IMAGE_REANIM_SUNFLOWER_HEAD_SING2_ID: return "IMAGE_REANIM_SUNFLOWER_HEAD_SING2";
		case IMAGE_REANIM_SUNFLOWER_HEAD_SING3_ID: return "IMAGE_REANIM_SUNFLOWER_HEAD_SING3";
		case IMAGE_REANIM_SUNFLOWER_HEAD_SING4_ID: return "IMAGE_REANIM_SUNFLOWER_HEAD_SING4";
		case IMAGE_REANIM_SUNFLOWER_HEAD_SING5_ID: return "IMAGE_REANIM_SUNFLOWER_HEAD_SING5";
		case IMAGE_REANIM_SUNFLOWER_HEAD_WINK_ID: return "IMAGE_REANIM_SUNFLOWER_HEAD_WINK";
		case IMAGE_REANIM_CREDITS_DISCOLIGHTS_ID: return "IMAGE_REANIM_CREDITS_DISCOLIGHTS";
		case IMAGE_REANIM_CREDITS_FOGMACHINE_ID: return "IMAGE_REANIM_CREDITS_FOGMACHINE";
		case IMAGE_CREDITS_ZOMBIENOTE_ID: return "IMAGE_CREDITS_ZOMBIENOTE";
		case IMAGE_CREDITS_PLAYBUTTON_ID: return "IMAGE_CREDITS_PLAYBUTTON";
		case IMAGE_CREDITS_BG_ID: return "IMAGE_CREDITS_BG";
		default: return "";
	}
}

