#pragma once

#include "../SDK/IInputSystem.h"

namespace FakeLag
{
	extern bool active;

	//Hooks
	void CreateMove(CUserCmd* cmd);
};
