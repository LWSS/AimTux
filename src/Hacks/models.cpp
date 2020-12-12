#include "models.h"
#include "../Utils/xorstring.h"
#include "../interfaces.h"
#include "../settings.h"

static int IndexList[] = { -1, -1, -1, -1 };

bool Models::PrecacheModel(const char* model)
{
	INetworkStringTable* modelPrecacheTable = networkString->FindTable(XORSTR("modelprecache"));
	if (!modelPrecacheTable)
		return false;

	modelInfo->FindOrLoadModel(model);
	if (modelPrecacheTable->AddString(false, model) == INVALID_STRING_TABLE)
		return false;

	return true;
}

void Models::LevelInitPostEntity()
{
	UpdateModels();
}

// TODO: Sometime need to Update twite to make it work
void Models::UpdateModels()
{
	int i = 0;
#define MODEL(__name)                                                                                      \
	if (Settings::Models::__name[0])                                                                       \
	{                                                                                                      \
		PrecacheModel(Settings::Models::__name);                                                           \
		IndexList[i] = modelInfo->GetModelIndex(Settings::Models::__name);                                 \
		cvar->ConsoleDPrintf("UpdateModels() : [%d::%d] %s\n", i, IndexList[i], Settings::Models::__name); \
	}                                                                                                      \
	else                                                                                                   \
		IndexList[i] = -1;                                                                                 \
	++i; //p100 codenz

	MODEL(playerT)
	MODEL(knifeT)
	MODEL(playerCT)
	MODEL(knifeCT)

#undef MODEL
}

void Models::FrameStageNotify(ClientFrameStage_t stage)
{
	if (!Settings::ESP::enabled || !Settings::Models::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		return;

	C_BasePlayer* localplayer =
		(C_BasePlayer*)entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	// Player models
	for (int i = 1; i < entityList->GetHighestEntityIndex(); i++)
	{
		C_BaseEntity* entity = entityList->GetClientEntity(i);
		if (!entity)
			continue;

		ClientClass* client = entity->GetClientClass();
		if (client->m_ClassID == EClassIds::CCSPlayer || client->m_ClassID == EClassIds::CCSRagdoll)
		{
			if (entity->GetTeam() == TeamID::TEAM_TERRORIST && IndexList[0] != INVALID_STRING_TABLE && *entity->GetModelIndex() != IndexList[0])
				entity->SetModelIndex(IndexList[0]);
			else if (entity->GetTeam() == TeamID::TEAM_COUNTER_TERRORIST && IndexList[2] != INVALID_STRING_TABLE && *entity->GetModelIndex() != IndexList[2])
				entity->SetModelIndex(IndexList[2]);
		}
	}

	/* TODO: Find the entity for arms
	 * Haven't been able to find it yet, could use the hooked FindMDL but it is a
	 * pain to work with because you have to restart the game to see the changes. */

	C_BaseViewModel* viewmodel = (C_BaseViewModel*)entityList->GetClientEntityFromHandle(localplayer->GetViewModel());
	if (!viewmodel)
		return;

	IEngineClient::player_info_t localplayer_info;
	if (!engine->GetPlayerInfo(engine->GetLocalPlayer(), &localplayer_info))
		return;

	// Player weapons (no thirdperson atm)
	C_BaseAttributableItem* weapon = (C_BaseAttributableItem* ) entityList->GetClientEntity(viewmodel->GetWeapon() & 0xFFF);
	
	if (!weapon)
		return;
	
	if (*weapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_KNIFE_T && IndexList[1] != INVALID_STRING_TABLE && *viewmodel->GetModelIndex() != IndexList[1])
		viewmodel->SetModelIndex(IndexList[1]);
	else if (*weapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_KNIFE && IndexList[3] != INVALID_STRING_TABLE && *viewmodel->GetModelIndex() != IndexList[3])
		viewmodel->SetModelIndex(IndexList[3]);
}

void Models::MDLCache(char* FilePath)
{
	/* It's a Surprise Tool That MAY Help Us Later */
}
