#include "../pchdef.h"
#include "AhBotConfig.h"
std::vector<std::string> split(const std::string &s, char delim);

using namespace std;

AhBotConfig::AhBotConfig()
{
}

template <class T>
void LoadSet(string value, T &res)
{
    vector<string> ids = split(value, ',');
    for (vector<string>::iterator i = ids.begin(); i != ids.end(); i++)
    {
        uint32 id = atoi((*i).c_str());
        if (!id)
            continue;

        res.insert(id);
    }
}

bool AhBotConfig::Initialize()
{
    string error;
    vector<string> args;
    if (!config.LoadInitial("worldserver.conf", args, error))
    {
        sLog->outMessage("ahbot", LOG_LEVEL_INFO, "AhBot is Disabled. Unable to open configuration file ahbot.conf");
        return false;
    }

    enabled = sConfigMgr->GetBoolDefault("AhBot.Enabled", true);

    if (!enabled)
        sLog->outMessage("ahbot", LOG_LEVEL_INFO, "AhBot is Disabled in ahbot.conf");

    guid = (uint64)sConfigMgr->GetIntDefault("AhBot.GUID", 0);
    updateInterval = sConfigMgr->GetIntDefault("AhBot.UpdateIntervalInSeconds", 300);
    historyDays = sConfigMgr->GetIntDefault("AhBot.History.Days", 30);
    itemBuyMinInterval = sConfigMgr->GetIntDefault("AhBot.ItemBuyMinInterval", 600);
    itemBuyMaxInterval = sConfigMgr->GetIntDefault("AhBot.ItemBuyMaxInterval", 7200);
    itemSellMinInterval = sConfigMgr->GetIntDefault("AhBot.ItemSellMinInterval", 600);
    itemSellMaxInterval = sConfigMgr->GetIntDefault("AhBot.ItemSellMaxInterval", 7200);
    maxSellInterval = sConfigMgr->GetIntDefault("AhBot.MaxSellInterval", 3600 * 8);
    alwaysAvailableMoney = sConfigMgr->GetIntDefault("AhBot.AlwaysAvailableMoney", 200000);
    priceMultiplier = sConfigMgr->GetFloatDefault("AhBot.PriceMultiplier", 1.0f);
    defaultMinPrice = sConfigMgr->GetIntDefault("AhBot.DefaultMinPrice", 20);
    maxItemLevel = sConfigMgr->GetIntDefault("AhBot.MaxItemLevel", 199);
    maxRequiredLevel = sConfigMgr->GetIntDefault("AhBot.MaxRequiredLevel", 80);
    priceQualityMultiplier = sConfigMgr->GetFloatDefault("AhBot.PriceQualityMultiplier", 1.0f);
    underPriceProbability = sConfigMgr->GetFloatDefault("AhBot.UnderPriceProbability", 0.05f);
    LoadSet<set<uint32> >(sConfigMgr->GetStringDefault("AhBot.IgnoreItemIds", "49283,52200,8494,6345,6891,2460,37164,34835"), ignoreItemIds);


    return enabled;
}
