#ifndef __DISCORDRPC_H__ 
#define __DISCORDRPC_H__

#include "../../SexyAppFramework/Common.h"

class DiscordRichPresence;
class DiscordRPC
{
public:
    DiscordRichPresence* mDiscordPresence;

public:
    DiscordRPC();

    void                Initialize();
    void                Shutdown();
    void                UpdatePresence();
    void                DiscordMain();
    void                Update();
};

#endif