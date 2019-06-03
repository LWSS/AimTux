#include "fakelag.h"

#include "../settings.h"
#include "../interfaces.h"
#include "../Hooks/hooks.h"

FakeLagType Settings::FakeLag::type = FakeLagType::STATIC;
bool Settings::FakeLag::enabled = false;
int Settings::FakeLag::value = 9;
bool FakeLag::lagSpikeActive = false;

static int ticks = 0;
int ticksMax = 16;

void FakeLag::CreateMove(CUserCmd* cmd)
{
	if (!Settings::FakeLag::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	if (localplayer->GetFlags() & FL_ONGROUND && Settings::FakeLag::type == FakeLagType::ADAPTIVE)
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
	else
	{
        switch (Settings::FakeLag::type)
        {
            case FakeLagType::ADAPTIVE:
                int packetsToChoke;
                if (localplayer->GetVelocity().Length() > 0.f)
                {
                    packetsToChoke = (int)((64.f / globalVars->interval_per_tick) / localplayer->GetVelocity().Length()) + 1;
                    if (packetsToChoke >= 15)
                        packetsToChoke = 14;
                    if (packetsToChoke < Settings::FakeLag::value)
                        packetsToChoke = Settings::FakeLag::value;
                }
                else
                    packetsToChoke = 0;

                CreateMove::sendPacket = ticks < 16 - packetsToChoke;
                break;

            case FakeLagType::STATIC:
                CreateMove::sendPacket = ticks < 16 - Settings::FakeLag::value;
                break;

            case FakeLagType::LAGSPIKE:
                if (FakeLag::lagSpikeActive)
                    CreateMove::sendPacket = false;
                else
                    CreateMove::sendPacket = true;
                break;

            default:
                break;
        }
	}

	ticks++;
}
