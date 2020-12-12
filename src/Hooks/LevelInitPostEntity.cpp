#include "hooks.h"

#include "../interfaces.h"
#include "../Utils/bonemaps.h"
#include "../Hacks/models.h"

typedef void (* LevelInitPostEntityFn)( void );

/* Called when loading a new level */
void Hooks::LevelInitPostEntity( ) {
    BoneMaps::BuildAllBonemaps();
	Models::LevelInitPostEntity();

    clientVMT->GetOriginalMethod<LevelInitPostEntityFn>( 6 )();
}
