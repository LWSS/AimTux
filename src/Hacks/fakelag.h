#pragma once

#include "../SDK/IInputSystem.h"

namespace FakeLag
{
	extern bool lagSpike;

	//Hooks
	void CreateMove(CUserCmd* cmd);
};
