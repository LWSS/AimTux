#include "fakelag.h"

#include "../settings.h"
#include "../interfaces.h"
#include "../Hooks/hooks.h"

bool Settings::FakeLag::enabled = false;
int Settings::FakeLag::value = 9;
bool Settings::FakeLag::adaptive = false;

bool FakeLag::lagSpike = false;

static int ticks = 0;
int ticksMax = 16;

void FakeLag::CreateMove(CUserCmd* cmd)
{
	if (!Settings::FakeLag::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (Settings::AntiAim::Fake::enabled && localplayer->GetVelocity().Length() < 0.0f)
		return;

	if (!localplayer || !localplayer->GetAlive())
		return;

	if (cmd->buttons & IN_ATTACK)
	{
		CreateMove::sendPacket = true;
		return;
	}

	if (ticks >= ticksMax)
	{
		CreateMove::sendPacket = true;
		ticks = 0;
	}
	else if (Settings::FakeLag::adaptive && FakeLag::lagSpike)
	{
		CreateMove::sendPacket = false;
	}
	else
	{
		CreateMove::sendPacket = ticks < 16 - Settings::FakeLag::value;
	}

	ticks++;
}
