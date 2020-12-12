#include "hooks.h"

#include "../interfaces.h"
#include "../Hacks/models.h"

typedef MDLHandle_t (*FindMDLFn)(void*, char*);

MDLHandle_t Hooks::MDLCache(void* thisptr, char* FilePath)
{
	Models::MDLCache(FilePath);

	return mdlCacheVMT->GetOriginalMethod<FindMDLFn>(10)(thisptr, FilePath);
}
