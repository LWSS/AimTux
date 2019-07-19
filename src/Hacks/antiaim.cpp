#include "antiaim.h"

#include "aimbot.h"
#include "../settings.h"
#include "../Hooks/hooks.h"
#include "../Utils/math.h"
#include "../Utils/entity.h"
#include "../interfaces.h"
#include "valvedscheck.h"

bool Settings::AntiAim::Yaw::enabled = false;
bool Settings::AntiAim::Fake::enabled = false;
bool Settings::AntiAim::Pitch::enabled = false;

AntiAimYaw_Real Settings::AntiAim::Yaw::type = AntiAimYaw_Real::BACKWARDS;
AntiAimYaw_Fake Settings::AntiAim::Fake::type = AntiAimYaw_Fake::JITTER;
AntiAimType_X Settings::AntiAim::Pitch::type = AntiAimType_X::STATIC_DOWN;

bool Settings::AntiAim::HeadEdge::enabled = false;

bool Settings::AntiAim::AutoDisable::noEnemy = false;
bool Settings::AntiAim::AutoDisable::knifeHeld = false;
bool Settings::AntiAim::LBYBreaker::enabled = false;
float Settings::AntiAim::LBYBreaker::offset = 180.0f;
bool Settings::AntiAim::LBYBreaker::manual = false;

QAngle AntiAim::realAngle;
QAngle AntiAim::fakeAngle;

static bool manualSwitch = true;

float AntiAim::GetMaxDelta( CCSGOAnimState *animState ) {

    float speedFraction = std::max(0.0f, std::min(animState->feetShuffleSpeed, 1.0f));

    float speedFactor = std::max(0.0f, std::min(1.0f, animState->feetShuffleSpeed2));

    float unk1 = ((animState->runningAccelProgress * -0.30000001) - 0.19999999) * speedFraction;
    float unk2 = unk1 + 1.0f;
    float delta;

    if (animState->duckProgress > 0)
    {
        unk2 += ((animState->duckProgress * speedFactor) * (0.5f - unk2));// - 1.f
    }

    delta = *(float*)((uintptr_t)animState + 0x3A4) * unk2;

    return delta - 0.5f;
}

// Pasted from space!hook
static bool GetBestHeadAngle(QAngle& angle)
{
	float b, r, l;

	Vector src3D, dst3D, forward, right, up, src, dst;

	trace_t tr;
	Ray_t ray, ray2, ray3, ray4, ray5;
	CTraceFilter filter;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return false;

	QAngle viewAngles;
	engine->GetViewAngles(viewAngles);

	viewAngles.x = 0;

	Math::AngleVectors(viewAngles, forward, right, up);

	auto GetTargetEntity = [ & ] ( void )
	{
		float bestFov = FLT_MAX;
		C_BasePlayer* bestTarget = NULL;

		for( int i = 0; i < engine->GetMaxClients(); ++i )
		{
			C_BasePlayer* player = (C_BasePlayer*) entityList->GetClientEntity(i);

			if (!player
				|| player == localplayer
				|| player->GetDormant()
				|| !player->GetAlive()
				|| player->GetImmune()
				|| player->GetTeam() == localplayer->GetTeam())
				continue;

			float fov = Math::GetFov(viewAngles, Math::CalcAngle(localplayer->GetEyePosition(), player->GetEyePosition()));

			if( fov < bestFov )
			{
				bestFov = fov;
				bestTarget = player;
			}
		}

		return bestTarget;
	};

	auto target = GetTargetEntity();
	filter.pSkip = localplayer;
	src3D = localplayer->GetEyePosition();
	dst3D = src3D + (forward * 384);

	if (!target)
		return false;

	ray.Init(src3D, dst3D);
	trace->TraceRay(ray, MASK_SHOT, &filter, &tr);
	b = (tr.endpos - tr.startpos).Length();

	ray2.Init(src3D + right * 35, dst3D + right * 35);
	trace->TraceRay(ray2, MASK_SHOT, &filter, &tr);
	r = (tr.endpos - tr.startpos).Length();

	ray3.Init(src3D - right * 35, dst3D - right * 35);
	trace->TraceRay(ray3, MASK_SHOT, &filter, &tr);
	l = (tr.endpos - tr.startpos).Length();

	if (b < r && b < l && l == r)
		return true; //if left and right are equal and better than back

	if (b > r && b > l)
		angle.y -= 180; //if back is the best angle
	else if (r > l && r > b)
		angle.y += 90; //if right is the best angle
	else if (r > l && r == b)
		angle.y += 135; //if right is equal to back
	else if (l > r && l > b)
		angle.y -= 90; //if left is the best angle
	else if (l > r && l == b)
		angle.y -= 135; //if left is equal to back
	else
		return false;

	return true;
}

static bool HasViableEnemy()
{
    C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());

    for (int i = 1; i < engine->GetMaxClients(); ++i)
    {
        C_BasePlayer* entity = (C_BasePlayer*) entityList->GetClientEntity(i);

        if (!entity
            || entity == localplayer
            || entity->GetDormant()
            || !entity->GetAlive()
            || entity->GetImmune())
            continue;

        if( !Aimbot::friends.empty() ) // check for friends, if any
        {
            IEngineClient::player_info_t entityInformation;
            engine->GetPlayerInfo(i, &entityInformation);

            if (std::find(Aimbot::friends.begin(), Aimbot::friends.end(), entityInformation.xuid) != Aimbot::friends.end())
                continue;
        }

        if (Settings::Aimbot::friendly || !Entity::IsTeamMate(entity, localplayer))
            return true;
    }

    return false;
}
static void DoAntiAimY(QAngle& angle, bool& clamp, CCSGOAnimState* animState)
{
	if (!animState)
		return;

	AntiAimYaw_Real aa_type = Settings::AntiAim::Yaw::type;

	static bool yFlip;
	float temp;
	double factor;
	static float trigger;
	QAngle temp_qangle;
	int random;
	int maxJitter;

	switch (aa_type)
	{
		case AntiAimYaw_Real::SPIN_FAST:
			factor =  360.0 / M_PHI;
			factor *= 25;
			angle.y = fmodf(globalVars->curtime * factor, 360.0);
			break;
		case AntiAimYaw_Real::SPIN_SLOW:
			factor =  360.0 / M_PHI;
			angle.y = fmodf(globalVars->curtime * factor, 360.0);
			break;
		case AntiAimYaw_Real::JITTER:
			yFlip ? angle.y -= 90.0f : angle.y -= 270.0f;
			break;
		case AntiAimYaw_Real::BACKJITTER:
			angle.y -= 180;
			random = rand() % 100;
			maxJitter = rand() % (85 - 70 + 1) + 70;
			temp = maxJitter - (rand() % maxJitter);
			if (random < 35 + (rand() % 15))
				angle.y -= temp;
			else if (random < 85 + (rand() % 15 ))
				angle.y += temp;
			break;
		case AntiAimYaw_Real::SIDE:
			yFlip ? angle.y += 90.f : angle.y -= 90.0f;
			break;
		case AntiAimYaw_Real::BACKWARDS:
			angle.y -= 180.0f;
			break;
		case AntiAimYaw_Real::FORWARDS:
			angle.y -= 0.0f;
			break;
		case AntiAimYaw_Real::LEFT:
			angle.y += 90.0f;
			break;
		case AntiAimYaw_Real::RIGHT:
			angle.y -= 90.0f;
			break;
		case AntiAimYaw_Real::STATICAA:
			angle.y = 0.0f;
			break;
		case AntiAimYaw_Real::STATICJITTER:
			trigger += 15.0f;
			angle.y = trigger > 50.0f ? 150.0f : -150.0f;

			if (trigger > 100.0f)
				trigger = 0.0f;
			break;
		case AntiAimYaw_Real::STATICSMALLJITTER:
			trigger += 15.0f;
			angle.y = trigger > 50.0f ? -30.0f : 30.0f;

			if (trigger > 100.0f)
				trigger = 0.0f;
			break;
		case AntiAimYaw_Real::LISP:
			clamp = false;
			yFlip ? angle.y += 323210000.0f : angle.y -= 323210000.0f;
			break;
		case AntiAimYaw_Real::LISP_SIDE:
			clamp = false;
			temp = angle.y + 90.0f;
			temp_qangle = QAngle(0.0f, temp, 0.0f);
			Math::NormalizeAngles(temp_qangle);
			temp = temp_qangle.y;

			if (temp > -45.0f)
				temp < 0.0f ? temp = -90.0f : temp < 45.0f ? temp = 90.0f : temp = temp;

			temp += 1800000.0f;
			angle.y = temp;
			break;
		case AntiAimYaw_Real::LISP_JITTER:
			clamp = false;
			temp = angle.y - 155.0f;

			if (globalVars->tickcount % 2)
			{
				temp = angle.y + 58.0f;
				temp += 1800000.0f;
			}

			angle.y = temp;
			break;
		case AntiAimYaw_Real::ANGEL_BACKWARD:
			clamp = false;
			angle.y += 36000180.0f;
			break;
		case AntiAimYaw_Real::ANGEL_INVERSE:
			clamp = false;
			angle.y = 36000180.0f;
			break;
		case AntiAimYaw_Real::LOWERBODY:
			angle.y = *((C_BasePlayer*)entityList->GetClientEntity(engine->GetLocalPlayer()))->GetLowerBodyYawTarget() + rand()%35 + 165;
			break;
		case AntiAimYaw_Real::ANGEL_SPIN:
			clamp = false;
			factor = (globalVars->curtime * 5000.0f);
			angle.y = factor + 36000000.0f;
			break;
		case AntiAimYaw_Real::CASUAL:
			yFlip ? angle.y -= 35.0f : angle.y += 35.0f;
			break;
		case AntiAimYaw_Real::LBYONGROUND:
			static C_BasePlayer* player = ((C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer()));
			if (player->GetFlags() & FL_ONGROUND)
				angle.y = *((C_BasePlayer*)entityList->GetClientEntity(engine->GetLocalPlayer()))->GetLowerBodyYawTarget() + rand()%35 + 165;
			else
			{
				static int aimType = rand() % 4;
				switch (aimType)
				{
					case 1:
						yFlip ? angle.y += 90.f : angle.y -= 90.0f;
						break;
					case 2:
						yFlip ? angle.y -= 120.0f : angle.y -= 210.0f;
						break;
					case 3:
						factor =  360.0 / M_PHI;
						factor *= 25;
						angle.y = fmodf(globalVars->curtime * factor, 360.0);
						break;
					default:
						angle.y -= 180.0f;
				}
			}
			break;
		default:
			angle.y -= 0.0f;
			break;
	}
}

static void DoAntiAimX(QAngle& angle, bool bFlip, bool& clamp)
{
    static float pDance = 0.0f;
    AntiAimType_X aa_type = Settings::AntiAim::Pitch::type;

    switch (aa_type)
    {
        case AntiAimType_X::STATIC_UP:
            angle.x = -89.0f;
            break;
        case AntiAimType_X::STATIC_DOWN:
            angle.x = 89.0f;
            break;
        case AntiAimType_X::DANCE:
            pDance += 45.0f;
            if (pDance > 100)
                pDance = 0.0f;
            else if (pDance > 75.f)
                angle.x = -89.f;
            else if (pDance < 75.f)
                angle.x = 89.f;
            break;
        case AntiAimType_X::FRONT:
            angle.x = 0.0f;
            break;
        case AntiAimType_X::STATIC_UP_FAKE:
            angle.x = bFlip ? 89.0f : -89.0f;
            break;
        case AntiAimType_X::STATIC_DOWN_FAKE:
            angle.x = bFlip ? -89.0f : 89.0f;
            break;
        case AntiAimType_X::LISP_DOWN:
            clamp = false;
            angle.x = 1800089.0f;
            break;
        case AntiAimType_X::ANGEL_DOWN:
            clamp = false;
            angle.x = 36000088.0f;
            break;
        case AntiAimType_X::ANGEL_UP:
            clamp = false;
            angle.x = 35999912.0f;
            break;
        default:
            break;
    }
}

static void DoAntiAimFake(QAngle &angle, CCSGOAnimState* animState)
{
	if (!animState)
		return;

	float maxDelta = AntiAim::GetMaxDelta(animState);
	static bool yFlip = false;

	switch (Settings::AntiAim::Fake::type)
	{
		case AntiAimYaw_Fake::STATIC_LEFT:
			angle.y += maxDelta;
			break;

		case AntiAimYaw_Fake::STATIC_RIGHT:
			angle.y -= maxDelta;
			break;

		case AntiAimYaw_Fake::JITTER:
			angle.y += yFlip ? maxDelta : -1 * maxDelta;
			yFlip = !yFlip;
			break;

        case AntiAimYaw_Fake::MANUAL:
            angle.y += manualSwitch ? maxDelta : -maxDelta;
            break;
	}
}

void AntiAim::CreateMove(CUserCmd* cmd)
{
    if (!Settings::AntiAim::Yaw::enabled && !Settings::AntiAim::Pitch::enabled && !Settings::AntiAim::LBYBreaker::enabled)
        return;

    if (Settings::Aimbot::AimStep::enabled && Aimbot::aimStepInProgress)
        return;

    QAngle oldAngle = cmd->viewangles;
    float oldForward = cmd->forwardmove;
    float oldSideMove = cmd->sidemove;
    
    AntiAim::realAngle = AntiAim::fakeAngle = CreateMove::lastTickViewAngles;

    QAngle angle = cmd->viewangles;

    C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
    if (!localplayer || !localplayer->GetAlive())
        return;

    C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
    if (!activeWeapon)
        return;

    if (activeWeapon->GetCSWpnData()->GetWeaponType() == CSWeaponType::WEAPONTYPE_GRENADE)
    {
        C_BaseCSGrenade* csGrenade = (C_BaseCSGrenade*) activeWeapon;

        if (csGrenade->GetThrowTime() > 0.f)
            return;
    }

    if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK || (cmd->buttons & IN_ATTACK2 && *activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER))
        return;

    if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
        return;

    // Knife
    if (Settings::AntiAim::AutoDisable::knifeHeld && localplayer->GetAlive() && activeWeapon->GetCSWpnData()->GetWeaponType() == CSWeaponType::WEAPONTYPE_KNIFE)
        return;

    if (Settings::AntiAim::AutoDisable::noEnemy && localplayer->GetAlive() && !HasViableEnemy())
        return;

    QAngle edge_angle = angle;
    bool edging_head = Settings::AntiAim::HeadEdge::enabled && GetBestHeadAngle(edge_angle);

    static bool bSend = true;
    bSend = !bSend;

    bool should_clamp = true;

    bool needToFlick = false;
    float tempangle = 0.f;
    static bool lbyBreak = false;
    static float lastCheck;
    static float nextUpdate = FLT_MAX;
    float vel2D = localplayer->GetVelocity().Length2D();//localplayer->GetAnimState()->verticalVelocity + localplayer->GetAnimState()->horizontalVelocity;

    if (Settings::AntiAim::LBYBreaker::enabled)
    {
        if (vel2D >= 0.1f || !(localplayer->GetFlags() & FL_ONGROUND) || localplayer->GetFlags() & FL_FROZEN && CreateMove::sendPacket)
        {
            lbyBreak = false;
            lastCheck = globalVars->curtime;
            nextUpdate = globalVars->curtime + 0.22;
        } 
        else 
        {
            if (!lbyBreak && (globalVars->curtime - lastCheck) > 0.22)
            {
                tempangle = Settings::AntiAim::LBYBreaker::manual ? manualSwitch ? 57.5f + Settings::AntiAim::LBYBreaker::offset : 
                    -57.5f + -Settings::AntiAim::LBYBreaker::offset : 
                    Settings::AntiAim::LBYBreaker::offset;

                lbyBreak = true;
                lastCheck = globalVars->curtime;
                nextUpdate = globalVars->curtime + 1.1;
                needToFlick = true;
            } 
            else if (lbyBreak && (globalVars->curtime - lastCheck) > 1.1)
            {
                tempangle = Settings::AntiAim::LBYBreaker::manual ? manualSwitch ? 57.5f + Settings::AntiAim::LBYBreaker::offset : 
                    -57.5f + -Settings::AntiAim::LBYBreaker::offset : 
                    Settings::AntiAim::LBYBreaker::offset;

                lbyBreak = true;
                lastCheck = globalVars->curtime;
                nextUpdate = globalVars->curtime + 1.1;
                needToFlick = true;
            }
        }
    }

	CCSGOAnimState* animState = localplayer->GetAnimState();

    if (Settings::AntiAim::Yaw::enabled && !needToFlick)
    {
        DoAntiAimY(angle, should_clamp, animState);

        if ((nextUpdate - globalVars->interval_per_tick) >= globalVars->curtime && nextUpdate <= globalVars->curtime)
        	CreateMove::sendPacket = false;

        if (needToFlick)
        {
            CreateMove::sendPacket = false;
            angle.y += tempangle;
    	}

        if (Settings::AntiAim::HeadEdge::enabled && edging_head && !bSend)
            angle.y = edge_angle.y;

        Math::NormalizeAngles(angle);
    }

	if (Settings::AntiAim::Fake::enabled && Settings::FakeLag::enabled ? !CreateMove::sendPacket : !bSend && !needToFlick)
    {
	    DoAntiAimFake(angle, animState);
        Math::NormalizeAngles(angle);
    }

    if (!ValveDSCheck::forceUT && (*csGameRules) && (*csGameRules)->IsValveDS())
    {
        if (Settings::AntiAim::Pitch::type >= AntiAimType_X::STATIC_UP_FAKE)
            Settings::AntiAim::Pitch::type = AntiAimType_X::STATIC_UP;
    }

    if (Settings::AntiAim::Pitch::enabled)
        DoAntiAimX(angle, bSend, should_clamp);

    if( should_clamp ){
        Math::NormalizeAngles(angle);
        Math::ClampAngles(angle);
    }

    if (!Settings::FakeLag::enabled && !needToFlick)
    {
        CreateMove::sendPacket = bSend;

        if (bSend)
            AntiAim::realAngle = CreateMove::lastTickViewAngles;
        else
            AntiAim::fakeAngle = angle;
    }
    else
    {
        if (CreateMove::sendPacket)
            AntiAim::realAngle = CreateMove::lastTickViewAngles;
        else
            AntiAim::fakeAngle = angle;
    }

    cmd->viewangles = angle;

    Math::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);
}
