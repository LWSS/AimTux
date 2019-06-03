#pragma once

#include "../../SDK/definitions.h"
#include "../../settings.h"
#include "../../Utils/xorstring.h"
#include "../../ImGUI/imgui_internal.h"
#include "../atgui.h"
#include "triggerbottab.h"

namespace Aimbot
{
	void RenderTab();

    inline ItemDefinitionIndex currentWeapon = ItemDefinitionIndex::INVALID;
    inline bool enabled = false;
    inline bool silent = false;
    inline bool friendly = false;
    inline bool closestBone = false;
    inline bool desiredBones[] = {true, true, true, true, true, true, true, // center mass
                                  false, false, false, false, false, false, false, // left arm
                                  false, false, false, false, false, false, false, // right arm
                                  false, false, false, false, false, // left leg
                                  false, false, false, false, false  // right leg
    };
    inline bool engageLock = false;
    inline bool engageLockTR = false; // Target Reacquisition
    inline int engageLockTTR = 700; // Time to Target Reacquisition ( in ms )
    inline Bone bone = Bone::BONE_HEAD;
    inline ButtonCode_t aimkey = ButtonCode_t::MOUSE_MIDDLE;
    inline bool aimkeyOnly = false;
    inline bool smoothEnabled = false;
    inline float smoothValue = 0.5f;
    inline SmoothType smoothType = SmoothType::SLOW_END;
    inline bool smoothSaltEnabled = false;
    inline float smoothSaltMultiplier = 0.0f;
    inline bool errorMarginEnabled = false;
    inline float errorMarginValue = 0.0f;
    inline bool autoAimEnabled = false;
    inline float autoAimValue = 180.0f;
    inline bool aimStepEnabled = false;
    inline float aimStepMin = 25.0f;
    inline float aimStepMax = 35.0f;
    inline bool rcsEnabled = false;
    inline bool rcsAlwaysOn = false;
    inline float rcsAmountX = 2.0f;
    inline float rcsAmountY = 2.0f;
    inline bool autoPistolEnabled = false;
    inline bool autoShootEnabled = false;
    inline bool autoScopeEnabled = false;
    inline bool noShootEnabled = false;
    inline bool ignoreJumpEnabled = false;
    inline bool ignoreEnemyJumpEnabled = false;
    inline bool smokeCheck = false;
    inline bool flashCheck = false;
    inline bool spreadLimitEnabled = false;
    inline float spreadLimit = 0.1f;
    inline bool autoWallEnabled = false;
    inline float autoWallValue = 10.0f;
    inline bool autoAimRealDistance = false;
    inline bool autoSlow = false;
    inline bool predEnabled = false;
    inline bool scopeControlEnabled = false;
}
