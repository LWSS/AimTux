#include "skychanger.h"

bool Settings::SkyChanger::enabled = false;
char Settings::SkyChanger::skyName[127] = "vertigoblue_hdr";

void Skychanger::SetSky(const char* skyname)
{
	LoadSky(skyname);
}
