#pragma once

#include "../ImGUI/imgui.h"
#include "../SDK/IClientEntity.h"
#include "../SDK/vector.h"
#include "../SDK/IVModelRender.h"
#include "../SDK/IClientString.h"

namespace Models
{
	bool PrecacheModel(const char* model);
	void UpdateModels();

	// Hook
	void MDLCache(char* FilePath);
	void FrameStageNotify(ClientFrameStage_t stage);
}
