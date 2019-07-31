#pragma once

#include "../SDK/IInputSystem.h"
#include "../SDK/CBaseClientState.h"
#include "../Utils/entity.h"
#include <vector>


namespace LagComp
{

	struct BacktrackRecord
	{
		C_BasePlayer* entity;
		Vector head;
		Vector origin;
		matrix3x4_t boneMatrix[128];
	};
	 
	struct BacktrackTick
	{
		int tickcount;
		float SimulationTime;
		std::vector<BacktrackRecord> records;
	};
 
	void FrameStageNotify(ClientFrameStage_t stage);
	void CreateMove(CUserCmd* cmd);
	extern std::vector<LagComp::BacktrackTick> ticks;
};
