#pragma once

#include "../SDK/IInputSystem.h"

namespace FakeLag
{
    extern bool lagSpikeActive;

	//Hooks
	void CreateMove(CUserCmd* cmd);
};
