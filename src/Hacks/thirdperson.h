#pragma once

#include "../interfaces.h"
#include "../settings.h"

namespace ThirdPerson
{
	//Hooks
	void OverrideView(CViewSetup* pSetup);
	void FrameStageNotify(ClientFrameStage_t stage);
}
