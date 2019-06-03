#include "hooks.h"

#include "../interfaces.h"

typedef void (*BeginFrameFn)(void *, float);

void Hooks::BeginFrame(void *thisptr, float frameTime) {
    ClanTagChanger::BeginFrame(frameTime);
    NameChanger::BeginFrame(frameTime);
    NameStealer::BeginFrame(frameTime);
    Spammer::BeginFrame(frameTime);
    Radar::BeginFrame();
    DisablePostProcessing::BeginFrame();

    if (!engine->IsInGame())
        CreateMove::sendPacket = true;

    Skins::Localize();

    return materialVMT->GetOriginalMethod<BeginFrameFn>(42)(thisptr, frameTime);
}
