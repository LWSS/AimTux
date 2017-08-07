#pragma once

#include "../settings.h"
#include "../SDK/SDK.h"
#include "../interfaces.h"

namespace Skychanger
{
	void SetSky(const char* skyname);	
}

extern LoadSkyFn LoadSky;
