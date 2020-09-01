#include "profilechanger.h"

#include "../settings.h"
#include "../interfaces.h"

int Settings::ProfileChanger::coinID = 890;
int Settings::ProfileChanger::musicID = 10;
int Settings::ProfileChanger::compRank = 18;
int Settings::ProfileChanger::weaponStatus = 0;
int Settings::ProfileChanger::weaponRarity = 0;

void ProfileChanger::UpdateProfile()
{
	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	const auto local_index = localplayer->GetIndex();

	if (auto player_resource = *csPlayerResource){
		player_resource->SetActiveCoinRank()[local_index] = Settings::ProfileChanger::coinID;
		player_resource->SetMusicID()[local_index] = Settings::ProfileChanger::musicID;
		player_resource->SetCompetitiveRanking()[local_index] = Settings::ProfileChanger::compRank;
	}
}
