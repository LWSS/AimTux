#include "autoblock.h"

#include "../Utils/math.h"
#include "../settings.h"
#include "../interfaces.h"
void Autoblock::CreateMove(CUserCmd* cmd)
{
	if (!Settings::Autoblock::enabled)
		return;

	if (!inputSystem->IsButtonDown(Settings::Autoblock::key))
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	float bestdist = 250.f;
	int index = -1;

	for (int i = 1; i < engine->GetMaxClients(); i++)
	{
		C_BasePlayer* entity = (C_BasePlayer*) entityList->GetClientEntity(i);

		if (!entity)
			continue;

		if (!entity->GetAlive() || entity->GetDormant() || entity == localplayer)
			continue;

		float dist = localplayer->GetVecOrigin().DistTo(entity->GetVecOrigin());

		if (dist < bestdist)
		{
			bestdist = dist;
			index = i;
		}
	}

	if (index == -1)
		return;

	C_BasePlayer* target = (C_BasePlayer*) entityList->GetClientEntity(index);

	if (!target)
		return;

	bool crouchBlock = false;
	if (localplayer->GetAbsOrigin().z - target->GetAbsOrigin().z >= target->GetCollideable()->OBBMaxs().z)
		crouchBlock = true;

	QAngle angles = Math::CalcAngle(localplayer->GetVecOrigin(), target->GetVecOrigin());

	angles.y -= localplayer->GetEyeAngles()->y;
	Math::NormalizeAngles(angles);

	if (crouchBlock)
	{
		Vector forward = target->GetAbsOrigin() - localplayer->GetAbsOrigin();
		float angle = localplayer->GetVAngles()->y;

		cmd->forwardmove = Math::Clamp((
				(sin(DEG2RAD(angle)) * forward.y) +
				(cos(DEG2RAD(angle)) * forward.x)) * 250.f,
				-250.f, 250.f);
		cmd->sidemove = Math::Clamp((
				(cos(DEG2RAD(angle)) * -forward.y) +
				(sin(DEG2RAD(angle)) * forward.x)) * 250.f,
				-250.f, 250.f);
	}
	else
	{
		if (angles.y < 0.f)
			cmd->sidemove = 250.f;
		else if (angles.y > 0.f)
			cmd->sidemove = -250.f;
	}
}
