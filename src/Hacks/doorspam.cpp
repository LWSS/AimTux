#include "doorspam.h"

#include "../settings.h"
#include "../interfaces.h"

bool Settings::DoorSpam::enabled = false;
static bool ShouldSpamDoors = false;

void DoorSpam::CreateMove(CUserCmd* cmd)
{
	if (!Settings::DoorSpam::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (cmd->buttons & IN_USE){	

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
