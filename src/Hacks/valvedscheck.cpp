#include "valvedscheck.h"

bool ValveDSCheck::forceUT = false;

void ValveDSCheck::FireGameEvent(IGameEvent* event)
{
	if (!event)
		return;

	const char *eventName = event->GetName();
	if (strcmp(eventName, XORSTR("player_connect_full")) != 0
		&& strcmp(eventName, XORSTR("cs_game_disconnected")) != 0)
		return;

	const int userid = event->GetInt(XORSTR("userid"));
	if (userid
		&& engine->GetPlayerForUserID(userid) != engine->GetLocalPlayer())
		return;

	ValveDSCheck::forceUT = false;
}
