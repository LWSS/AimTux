#include "models.h"
#include "../Utils/xorstring.h"
#include "../interfaces.h"
#include "../settings.h"

INetworkStringTable* modelPrecacheTable = nullptr;

static bool PrecacheModel(const char* model)
{
	if (!modelPrecacheTable)
		modelPrecacheTable = networkString->FindTable(XORSTR("modelprecache"));
	if (!modelPrecacheTable)
		return false;

	modelInfo->FindOrLoadModel(model);
	if (modelPrecacheTable->AddString(false, model) == INVALID_STRING_TABLE)
		return false;

	return true;
}

void Models::MDLCache(char* FilePath)
{
}
