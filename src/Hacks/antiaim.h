#pragma once

#include "../SDK/IInputSystem.h"
#include "../SDK/IClientEntity.h"

namespace AntiAim
{
    extern QAngle realAngle;
    extern QAngle fakeAngle;
    extern QAngle LastTickViewAngle;

    float GetMaxDelta( CCSGOAnimState *animState );

    //Hooks
    void CreateMove(CUserCmd* cmd);
}