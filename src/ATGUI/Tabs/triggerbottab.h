#pragma once

#include "../../SDK/SDK.h"

namespace Triggerbot
{
	void RenderTab();

	inline bool enabled = false;
	inline ButtonCode_t key;
	inline bool enemies = false;
	inline bool allies = false;
	inline bool walls = false;
	inline bool smokeCheck = true;
	inline bool flashCheck = true;
	inline bool head = false;
	inline bool chest = false;
	inline bool stomach = false;
	inline bool arms = false;
	inline bool legs = false;
	inline bool randomDelay = false;
	inline int lowBound = 5; // in ms
	inline int highBound = 100; // in ms
	inline int lastRoll;
}