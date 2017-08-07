#pragma once

#include "../settings.h"
#include "../SDK/SDK.h"
#include "../Utils/draw.h"
#include "../interfaces.h"
#include "../Utils/pstring.h"
#include "../Utils/entity.h"
#include "backtracking.h"

class CResolveInfo {
	public:
    	std::deque<CTickRecord> m_sRecords;
    	bool	m_bEnemyShot; //priority
    	bool	m_bLowerBodyYawChanged;
    	bool	m_bBacktrackThisTick;
};

namespace Resolver
{
	extern std::vector<int64_t> Players;
	extern std::array<CResolveInfo, 32> m_arrInfos;

	void Resolve(C_BasePlayer* ent);

	void FrameStageNotify(ClientFrameStage_t stage);
	void PostFrameStageNotify(ClientFrameStage_t stage);
	void FireGameEvent(IGameEvent* event);

	CTickRecord GetShotRecord(C_BasePlayer*);
	
    bool HasStaticRealAngle(int index, float tolerance = 15.f);
    bool HasStaticRealAngle(const std::deque<CTickRecord>& l, float tolerance = 15.f);
    bool HasStaticYawDifference(const std::deque<CTickRecord>& l, float tolerance = 15.f);
    bool HasSteadyDifference(const std::deque<CTickRecord>& l, float tolerance = 15.f);
    int GetDifferentDeltas(const std::deque<CTickRecord>& l, float tolerance = 15.f);
    int GetDifferentLBYs(const std::deque<CTickRecord>& l, float tolerance = 15.f);
    float GetLBYByComparingTicks(const std::deque<CTickRecord>& l);
    float GetDeltaByComparingTicks(const std::deque<CTickRecord>& l);
    bool DeltaKeepsChanging(const std::deque<CTickRecord>& cur, float tolerance = 15.f);
    bool LBYKeepsChanging(const std::deque<CTickRecord>& cur, float tolerance = 15.f);
    bool IsEntityMoving(C_BasePlayer* ent);
	bool& LowerBodyYawChanged(C_BasePlayer* ent);
	void StoreVars(C_BasePlayer* ent);
	void StoreVars(C_BasePlayer* ent, QAngle ang, float lby, float simtime, float tick);
	bool& BacktrackThisTick(C_BasePlayer* ent);
}

const inline float GetDelta(float a, float b) {
    return abs(Math::ClampYaw(a - b));
}

const inline float LBYDelta(const CTickRecord& v) {
    return v.m_angEyeAngles.y - v.m_flLowerBodyYawTarget;
}

const inline bool IsDifferent(float a, float b, float tolerance = 10.f) {
    return (GetDelta(a, b) > tolerance);
}
