#include "doorspam.h"

#include "../settings.h"
#include "../interfaces.h"

bool Settings::DoorSpam::enabled = false;
static bool ShouldSpamDoors = false;
ButtonCode_t Settings::DoorSpam::key = ButtonCode_t::KEY_E;

void DoorSpam::CreateMove(CUserCmd* cmd)
{
	if (!Settings::DoorSpam::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (inputSystem->IsButtonDown(Settings::DoorSpam::key)){	

		for (int i = 1; i < entityList->GetHighestEntityIndex(); i++)
		{			
			C_BaseEntity* entity = entityList->GetClientEntity(i);
			if (!entity)
				continue;

			ClientClass* client = entity->GetClientClass();

			if (client->m_ClassID == EClassIds::CPropDoorRotating){
				if (localplayer->GetVecOrigin().DistTo(entity->GetVecOrigin()) < 100){
					if (ShouldSpamDoors){
						cmd->buttons &= ~IN_USE;
					} else {
						cmd->buttons |= IN_USE;				
					}
					ShouldSpamDoors = !ShouldSpamDoors;	
				}
			}
		}

	}
}
