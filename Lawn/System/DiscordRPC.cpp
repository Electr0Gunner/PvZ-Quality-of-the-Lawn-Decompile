#include "DiscordRPC.h"
#include "../System/discord_rpc.h"
#include "../System/discord_register.h"
#include <time.h>
#include "../../SexyAppFramework/Common.h"

DiscordRPC::DiscordRPC(){}

DiscordRichPresence* mDiscordPresence;

void DiscordRPC::UpdatePresence()
{
	//mDiscordPresence = new DiscordRichPresence;
	//DiscordRichPresence mDiscordPresence;
	memset(&mDiscordPresence, 0, sizeof(mDiscordPresence));
	mDiscordPresence->state = "Under our Title";
	mDiscordPresence->details = "Details Text";
	mDiscordPresence->startTimestamp = time(0); //initlialize time
	mDiscordPresence->largeImageKey = "large image"; //large image file name no extension
	mDiscordPresence->largeImageText = "Your Text";
	mDiscordPresence->smallImageKey = "small image"; //same as large
	mDiscordPresence->smallImageText = "Your Text"; //displays on hover
	Discord_UpdatePresence(mDiscordPresence); //do the do
}

void DiscordRPC::Update()
{
	DiscordRPC::Update();
	UpdatePresence();
}

void DiscordRPC::Initialize()
{
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	Discord_Initialize("1243252904878542908", &handlers, TRUE, nullptr);
}

void DiscordRPC::Shutdown()
{
	Discord_Shutdown(); //goodbye
}

void DiscordRPC::DiscordMain() //call in dllmain or hook w/e
{
	Initialize();
	UpdatePresence();
}