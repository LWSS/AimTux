#pragma once

#include "../settings.h"
#include "../SDK/SDK.h"
#include "../Hooks/hooks.h"
#include "../interfaces.h"
#include "../Utils/math.h"
#include "aimbot.h"

namespace AntiAim
{
	//Hooks
	void CreateMove(CUserCmd* cmd);

	float GetMaxDelta( CCSGOAnimState *animState );
	extern QAngle real;
	extern QAngle fake;
}
