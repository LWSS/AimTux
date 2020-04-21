#include "chams.h"

#include "../Utils/xorstring.h"
#include "../Utils/entity.h"
#include "../settings.h"
#include "../interfaces.h"
#include "../Hooks/hooks.h"

IMaterial* materialChams;
IMaterial* materialChamsIgnorez;
IMaterial* materialChamsFlat;
IMaterial* materialChamsFlatIgnorez;
IMaterial* materialChamsGlow;
IMaterial* materialChamsGlowIgnorez;
IMaterial* materialChamsArms;
IMaterial* materialChamsArmsGlow;
IMaterial* materialChamsWeapons;
IMaterial* materialChamsWeaponsGlow;

//For Custom Materials Per Localplayer Relation
IMaterial* local_material = nullptr;
IMaterial* local_material_hidden = nullptr;
IMaterial* enemy_material = nullptr;
IMaterial* enemy_material_hidden = nullptr;
IMaterial* ally_material = nullptr;
IMaterial* ally_material_hidden = nullptr;

typedef void (*DrawModelExecuteFn) (void*, void*, void*, const ModelRenderInfo_t&, matrix3x4_t*);

static void DrawPlayer(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld)
{
	if (!Settings::ESP::Chams::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	C_BasePlayer* entity = (C_BasePlayer*) entityList->GetClientEntity(pInfo.entity_index);
	if (!entity || entity->GetDormant() || !entity->GetAlive()) {
		return;
	}

	if (entity == localplayer && !Settings::ESP::Filters::localplayer)
		return;

	if (!Entity::IsTeamMate(entity, localplayer) && !Settings::ESP::Filters::enemies)
		return;

	if (entity != localplayer && Entity::IsTeamMate(entity,localplayer) && !Settings::ESP::Filters::allies)
		return;

	IMaterial* visible_material = nullptr;
	IMaterial* hidden_material = nullptr;

	switch (Settings::ESP::Chams::type)
	{
		case ChamsType::CHAMS:
		case ChamsType::CHAMS_XQZ:
			visible_material = materialChams;
			hidden_material = materialChamsIgnorez;
			Settings::ESP::Chams::Custom::enabled = false;
			break;
		case ChamsType::CHAMS_FLAT:
		case ChamsType::CHAMS_FLAT_XQZ:
			visible_material = materialChamsFlat;
			hidden_material = materialChamsFlatIgnorez;
			Settings::ESP::Chams::Custom::enabled = false;
			break;
		case ChamsType::CHAMS_GLOW:
		case ChamsType::CHAMS_GLOW_XQZ:
			visible_material = materialChamsGlow;
			hidden_material = materialChamsGlowIgnorez;
			Settings::ESP::Chams::Custom::enabled = false;
			break;
		case ChamsType::CUSTOM:
			Settings::ESP::Chams::Custom::enabled = true;
	}

	if (Settings::ESP::Chams::Custom::enabled) {
		visible_material = materialChams;
		hidden_material = materialChamsIgnorez;

		//Local
		switch (Settings::ESP::Chams::local) {
			case ChamsTypeCustom::CHAMS:
			case ChamsTypeCustom::CHAMS_XQZ:
				local_material = materialChams;
				local_material_hidden = materialChamsIgnorez;
				break;
			case ChamsTypeCustom::CHAMS_FLAT:
			case ChamsTypeCustom::CHAMS_FLAT_XQZ:
				local_material = materialChamsFlat;
				local_material_hidden = materialChamsFlatIgnorez;
				break;
			case ChamsTypeCustom::CHAMS_GLOW:
			case ChamsTypeCustom::CHAMS_GLOW_XQZ:
				local_material = materialChamsGlow;
				local_material_hidden = materialChamsGlowIgnorez;
				break;
		}
		//End Local

		//Enemy
		switch (Settings::ESP::Chams::enemy) {
			case ChamsTypeCustom::CHAMS:
			case ChamsTypeCustom::CHAMS_XQZ:
				enemy_material = materialChams;
				enemy_material_hidden = materialChamsIgnorez;
				break;
			case ChamsTypeCustom::CHAMS_FLAT:
			case ChamsTypeCustom::CHAMS_FLAT_XQZ:
				enemy_material = materialChamsFlat;
				enemy_material_hidden = materialChamsFlatIgnorez;
				break;
			case ChamsTypeCustom::CHAMS_GLOW:
			case ChamsTypeCustom::CHAMS_GLOW_XQZ:
				enemy_material = materialChamsGlow;
				enemy_material_hidden = materialChamsGlowIgnorez;
				break;
		}
		//End Enemy

		//Ally
		switch (Settings::ESP::Chams::ally) {
			case ChamsTypeCustom::CHAMS:
			case ChamsTypeCustom::CHAMS_XQZ:
				ally_material = materialChams;
				ally_material_hidden = materialChamsIgnorez;
				break;
			case ChamsTypeCustom::CHAMS_FLAT:
			case ChamsTypeCustom::CHAMS_FLAT_XQZ:
				ally_material = materialChamsFlat;
				ally_material_hidden = materialChamsFlatIgnorez;
				break;
			case ChamsTypeCustom::CHAMS_GLOW:
			case ChamsTypeCustom::CHAMS_GLOW_XQZ:
				ally_material = materialChamsGlow;
				ally_material_hidden = materialChamsGlowIgnorez;
				break;
		}
		//End Ally
	}

	visible_material->AlphaModulate(1.0f);
	hidden_material->AlphaModulate(1.0f);

	if (entity == localplayer)
	{

		if (Settings::ESP::Chams::type == ChamsType::CHAMS || Settings::ESP::Chams::type == ChamsType::CHAMS_XQZ || Settings::ESP::Chams::type == ChamsType::CHAMS_FLAT || Settings::ESP::Chams::type == ChamsType::CHAMS_FLAT_XQZ) {
			Color visColor = Color::FromImColor(Settings::ESP::Chams::localplayerColor.Color(entity));
			Color color = visColor;
			color *= 0.45f;

			visible_material->ColorModulate(visColor);
			hidden_material->ColorModulate(color);

			visible_material->AlphaModulate(Settings::ESP::Chams::localplayerColor.Color(entity).Value.w);
			hidden_material->AlphaModulate(Settings::ESP::Chams::localplayerColor.Color(entity).Value.w);
		}

		if (Settings::ESP::Chams::type == ChamsType::CHAMS_GLOW || Settings::ESP::Chams::type == ChamsType::CHAMS_GLOW_XQZ) {			
			bool isFoundVis;
			bool isFoundHidden;
			IMaterialVar* pVarVis = visible_material->FindVar("$envmaptint", &isFoundVis, false);
			IMaterialVar* pVarHidden = hidden_material->FindVar("$envmaptint", &isFoundHidden, false);
	    	ImVec4 viscolor = Settings::ESP::Chams::localplayerColor.Color(entity).Value;
			ImVec4 hiddencolor = Settings::ESP::Chams::localplayerColor.Color(entity).Value;

			if (isFoundVis) {
            	pVarVis->SetVecValue(viscolor.x, viscolor.y, viscolor.z);
			}
			if (isFoundHidden) {
            	pVarHidden->SetVecValue(hiddencolor.x, hiddencolor.y, hiddencolor.z);
			}

			visible_material->SetMaterialVarFlag(MATERIAL_VAR_ADDITIVE, false);
	   		visible_material->SetMaterialVarFlag(MATERIAL_VAR_VERTEXCOLOR, false);
       		visible_material->SetMaterialVarFlag(MATERIAL_VAR_VERTEXALPHA, false);
       		visible_material->SetMaterialVarFlag(MATERIAL_VAR_NOFOG, false);
			hidden_material->SetMaterialVarFlag(MATERIAL_VAR_ADDITIVE, false);
        	hidden_material->SetMaterialVarFlag(MATERIAL_VAR_VERTEXCOLOR, false);
       		hidden_material->SetMaterialVarFlag(MATERIAL_VAR_VERTEXALPHA, false);
       		hidden_material->SetMaterialVarFlag(MATERIAL_VAR_NOFOG, false);

			visible_material->AlphaModulate(Settings::ESP::Chams::localplayerColor.Color(entity).Value.w);
			hidden_material->AlphaModulate(Settings::ESP::Chams::localplayerColor.Color(entity).Value.w);

			if (!Settings::ESP::Filters::legit && (Settings::ESP::Chams::type == ChamsType::CHAMS_XQZ || Settings::ESP::Chams::type == ChamsType::CHAMS_FLAT_XQZ || Settings::ESP::Chams::type == ChamsType::CHAMS_GLOW_XQZ))
			{
				hidden_material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
			}
			else
			{
				hidden_material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
			}
		}
	}
	else if (Entity::IsTeamMate(entity, localplayer))
	{
		if (Settings::ESP::Chams::type == ChamsType::CHAMS || Settings::ESP::Chams::type == ChamsType::CHAMS_XQZ || Settings::ESP::Chams::type == ChamsType::CHAMS_FLAT || Settings::ESP::Chams::type == ChamsType::CHAMS_FLAT_XQZ) {
			Color visColor = Color::FromImColor(Settings::ESP::Chams::allyVisibleColor.Color(entity));
			Color color = Color::FromImColor(Settings::ESP::Chams::allyColor.Color(entity));

			visible_material->ColorModulate(visColor);
			hidden_material->ColorModulate(color);

			visible_material->AlphaModulate(Settings::ESP::Chams::allyVisibleColor.Color(entity).Value.w);
			hidden_material->AlphaModulate(Settings::ESP::Chams::allyColor.Color(entity).Value.w);
		}

		if (Settings::ESP::Chams::type == ChamsType::CHAMS_GLOW || Settings::ESP::Chams::type == ChamsType::CHAMS_GLOW_XQZ) {
			bool isFoundVis;
			bool isFoundHidden;
			IMaterialVar* pVarVis = visible_material->FindVar("$envmaptint", &isFoundVis, false);
			IMaterialVar* pVarHidden = hidden_material->FindVar("$envmaptint", &isFoundHidden, false);
	    	ImVec4 visColor = Settings::ESP::Chams::allyVisibleColor.Color(entity).Value;
			ImVec4 color = Settings::ESP::Chams::allyColor.Color(entity).Value;

			if (isFoundVis) {
            	pVarVis->SetVecValue(visColor.x, visColor.y, visColor.z);
			}
			if (isFoundHidden) {
            	pVarHidden->SetVecValue(color.x, color.y, color.z);
			}

			visible_material->SetMaterialVarFlag(MATERIAL_VAR_ADDITIVE, false);
	   		visible_material->SetMaterialVarFlag(MATERIAL_VAR_VERTEXCOLOR, false);
       		visible_material->SetMaterialVarFlag(MATERIAL_VAR_VERTEXALPHA, false);
       		visible_material->SetMaterialVarFlag(MATERIAL_VAR_NOFOG, false);
			hidden_material->SetMaterialVarFlag(MATERIAL_VAR_ADDITIVE, false);
        	hidden_material->SetMaterialVarFlag(MATERIAL_VAR_VERTEXCOLOR, false);
       		hidden_material->SetMaterialVarFlag(MATERIAL_VAR_VERTEXALPHA, false);
       		hidden_material->SetMaterialVarFlag(MATERIAL_VAR_NOFOG, false);

			visible_material->AlphaModulate(Settings::ESP::Chams::allyVisibleColor.Color(entity).Value.w);
			hidden_material->AlphaModulate(Settings::ESP::Chams::allyColor.Color(entity).Value.w);

			if (!Settings::ESP::Filters::legit && (Settings::ESP::Chams::type == ChamsType::CHAMS_XQZ || Settings::ESP::Chams::type == ChamsType::CHAMS_FLAT_XQZ || Settings::ESP::Chams::type == ChamsType::CHAMS_GLOW_XQZ))
			{
				hidden_material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
			}
			else
			{
				hidden_material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
			}
		}
	}
	else if (!Entity::IsTeamMate(entity, localplayer))
	{
		if (Settings::ESP::Chams::type == ChamsType::CHAMS || Settings::ESP::Chams::type == ChamsType::CHAMS_XQZ || Settings::ESP::Chams::type == ChamsType::CHAMS_FLAT || Settings::ESP::Chams::type == ChamsType::CHAMS_FLAT_XQZ) {
			Color visColor = Color::FromImColor(Settings::ESP::Chams::enemyVisibleColor.Color(entity));
			Color color = Color::FromImColor(Settings::ESP::Chams::enemyColor.Color(entity));

			visible_material->ColorModulate(visColor);
			hidden_material->ColorModulate(color);

			visible_material->AlphaModulate(Settings::ESP::Chams::enemyVisibleColor.Color(entity).Value.w);
			hidden_material->AlphaModulate(Settings::ESP::Chams::enemyColor.Color(entity).Value.w);
		}

		if (Settings::ESP::Chams::type == ChamsType::CHAMS_GLOW || Settings::ESP::Chams::type == ChamsType::CHAMS_GLOW_XQZ) {
			bool isFoundVis;
			bool isFoundHidden;
			IMaterialVar* pVarVis = visible_material->FindVar("$envmaptint", &isFoundVis, false);
			IMaterialVar* pVarHidden = hidden_material->FindVar("$envmaptint", &isFoundHidden, false);
	    	ImVec4 visColor = Settings::ESP::Chams::enemyVisibleColor.Color(entity).Value;
			ImVec4 color = Settings::ESP::Chams::enemyColor.Color(entity).Value;

			if (isFoundVis) {
            	pVarVis->SetVecValue(visColor.x, visColor.y, visColor.z);
			}
			if (isFoundHidden) {
        		pVarHidden->SetVecValue(color.x, color.y, color.z);
			}

			visible_material->SetMaterialVarFlag(MATERIAL_VAR_ADDITIVE, false);
	   		visible_material->SetMaterialVarFlag(MATERIAL_VAR_VERTEXCOLOR, false);
       		visible_material->SetMaterialVarFlag(MATERIAL_VAR_VERTEXALPHA, false);
       		visible_material->SetMaterialVarFlag(MATERIAL_VAR_NOFOG, false);
			hidden_material->SetMaterialVarFlag(MATERIAL_VAR_ADDITIVE, false);
        	hidden_material->SetMaterialVarFlag(MATERIAL_VAR_VERTEXCOLOR, false);
       		hidden_material->SetMaterialVarFlag(MATERIAL_VAR_VERTEXALPHA, false);
       		hidden_material->SetMaterialVarFlag(MATERIAL_VAR_NOFOG, false);

			visible_material->AlphaModulate(Settings::ESP::Chams::enemyVisibleColor.Color(entity).Value.w);
			hidden_material->AlphaModulate(Settings::ESP::Chams::enemyColor.Color(entity).Value.w);

			if (!Settings::ESP::Filters::legit && (Settings::ESP::Chams::type == ChamsType::CHAMS_XQZ || Settings::ESP::Chams::type == ChamsType::CHAMS_FLAT_XQZ || Settings::ESP::Chams::type == ChamsType::CHAMS_GLOW_XQZ))
			{
				hidden_material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
			}
			else
			{
				hidden_material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
			}
		}
	}
	else
	{
		return;
	}

	if (entity->GetImmune())
	{
		visible_material->AlphaModulate(0.5f);
		hidden_material->AlphaModulate(0.5f);
	}

	if (!Settings::ESP::Filters::legit && (Settings::ESP::Chams::type == ChamsType::CHAMS_XQZ || Settings::ESP::Chams::type == ChamsType::CHAMS_FLAT_XQZ || Settings::ESP::Chams::type == ChamsType::CHAMS_GLOW_XQZ))
	{
		modelRender->ForcedMaterialOverride(hidden_material);
		modelRenderVMT->GetOriginalMethod<DrawModelExecuteFn>(21)(thisptr, context, state, pInfo, pCustomBoneToWorld);
	}

	modelRender->ForcedMaterialOverride(visible_material);
	// No need to call DME again, it already gets called in DrawModelExecute.cpp
}

static void DrawWeapon(const ModelRenderInfo_t& pInfo)
{
	if (!Settings::ESP::Chams::Weapon::enabled) {
		return;
	}

	std::string modelName = modelInfo->GetModelName(pInfo.pModel);
	IMaterial* mat = materialChamsWeapons;

	if (Settings::ESP::Chams::Weapon::type == WeaponType::DEFAULT || Settings::ESP::Chams::Weapon::type == WeaponType::WIREFRAME) {
		mat = materialChamsWeapons;

		mat->ColorModulate(Settings::ESP::Chams::Weapon::color.Color());
		mat->AlphaModulate(Settings::ESP::Chams::Weapon::color.Color().Value.w);
	}

	if (Settings::ESP::Chams::Weapon::type == WeaponType::GLOW) {
		mat = materialChamsWeaponsGlow;
		bool isFound;
		IMaterialVar* pVar = mat->FindVar("$envmaptint", &isFound, false);

		if (isFound) {
			ImVec4 color = Settings::ESP::Chams::Weapon::color.Color().Value;
			pVar->SetVecValue(color.x, color.y, color.z);
			mat->AlphaModulate(Settings::ESP::Chams::Weapon::color.Color().Value.w);
		}

		mat->SetMaterialVarFlag(MATERIAL_VAR_ADDITIVE, false);
        mat->SetMaterialVarFlag(MATERIAL_VAR_VERTEXCOLOR, false);
        mat->SetMaterialVarFlag(MATERIAL_VAR_VERTEXALPHA, false);
        mat->SetMaterialVarFlag(MATERIAL_VAR_NOFOG, false);
	}

	if (Settings::ESP::Chams::Weapon::type == WeaponType::NONE) {
		mat = material->FindMaterial(modelName.c_str(), TEXTURE_GROUP_MODEL);
	}

	if (!Settings::ESP::Chams::Weapon::enabled) {
		mat = material->FindMaterial(modelName.c_str(), TEXTURE_GROUP_MODEL);
	}

	mat->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, Settings::ESP::Chams::Weapon::type == WeaponType::WIREFRAME);
	mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, Settings::ESP::Chams::Weapon::type == WeaponType::NONE);
	modelRender->ForcedMaterialOverride(mat);
}

static void DrawArms(const ModelRenderInfo_t& pInfo)
{
	if (!Settings::ESP::Chams::Arms::enabled) {
		return;
	}

	std::string modelName = modelInfo->GetModelName(pInfo.pModel);
	IMaterial* mat = material->FindMaterial(modelName.c_str(), TEXTURE_GROUP_MODEL);;

	if (Settings::ESP::Chams::Arms::type == ArmsType::DEFAULT || Settings::ESP::Chams::Arms::type == ArmsType::WIREFRAME) {
		mat = materialChamsArms;

		mat->ColorModulate(Settings::ESP::Chams::Arms::color.Color());
		mat->AlphaModulate(Settings::ESP::Chams::Arms::color.Color().Value.w);
	}

	if (Settings::ESP::Chams::Arms::type == ArmsType::GLOW) {
		mat = materialChamsArmsGlow;
		bool isFound;
		IMaterialVar* pVar = mat->FindVar("$envmaptint", &isFound, false);
		
		if (isFound) {
			ImVec4 color = Settings::ESP::Chams::Arms::color.Color().Value;
			pVar->SetVecValue(color.x, color.y, color.z);
			mat->AlphaModulate(Settings::ESP::Chams::Arms::color.Color().Value.w);
		}

		mat->SetMaterialVarFlag(MATERIAL_VAR_ADDITIVE, false);
		mat->SetMaterialVarFlag(MATERIAL_VAR_VERTEXCOLOR, false);
		mat->SetMaterialVarFlag(MATERIAL_VAR_VERTEXALPHA, false);
		mat->SetMaterialVarFlag(MATERIAL_VAR_NOFOG, false);
	}

	if (Settings::ESP::Chams::Arms::type == ArmsType::NONE) {
		mat = material->FindMaterial(modelName.c_str(), TEXTURE_GROUP_MODEL);
	}

	if (!Settings::ESP::Chams::Arms::enabled) {
		mat = material->FindMaterial(modelName.c_str(), TEXTURE_GROUP_MODEL);
	}

	mat->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, Settings::ESP::Chams::Arms::type == ArmsType::WIREFRAME);
	mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, Settings::ESP::Chams::Arms::type == ArmsType::NONE);
	modelRender->ForcedMaterialOverride(mat);
}

void Chams::DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld)
{
	if (!engine->IsInGame())
		return;

	if (!Settings::ESP::enabled)
		return;

	if (!pInfo.pModel)
		return;

	static bool materialsCreated = false;
	if (!materialsCreated)
	{
		materialChams = Util::CreateMaterial(XORSTR("VertexLitGeneric"), XORSTR("VGUI/white_additive"), false, true, true, true, true);
		materialChamsIgnorez = Util::CreateMaterial(XORSTR("VertexLitGeneric"), XORSTR("VGUI/white_additive"), true, true, true, true, true);
		materialChamsFlat = Util::CreateMaterial(XORSTR("UnlitGeneric"), XORSTR("VGUI/white_additive"), false, true, true, true, true);
		materialChamsFlatIgnorez = Util::CreateMaterial(XORSTR("UnlitGeneric"), XORSTR("VGUI/white_additive"), true, true, true, true, true);
		materialChamsGlow = material->FindMaterial(XORSTR("dev/glow_armsrace.vmt"), TEXTURE_GROUP_OTHER);
		materialChamsGlowIgnorez = material->FindMaterial(XORSTR("dev/glow_rim3d.vmt"), TEXTURE_GROUP_OTHER);
		materialChamsArms = Util::CreateMaterial(XORSTR("VertexLitGeneric"), XORSTR("VGUI/white_additive"), false, true, true, true, true);
		materialChamsArmsGlow = material->FindMaterial(XORSTR("dev/glow_armsrace.vmt"), TEXTURE_GROUP_OTHER);
		materialChamsWeapons = Util::CreateMaterial(XORSTR("VertexLitGeneric"), XORSTR("VGUI/white_additive"), false, true, true, true, true);
		materialChamsWeaponsGlow = material->FindMaterial(XORSTR("dev/glow_armsrace.vmt"), TEXTURE_GROUP_OTHER);
		materialsCreated = true;
	}

	std::string modelName = modelInfo->GetModelName(pInfo.pModel);

	if (modelName.find(XORSTR("models/player")) != std::string::npos)
		DrawPlayer(thisptr, context, state, pInfo, pCustomBoneToWorld);
	else if (modelName.find(XORSTR("arms")) != std::string::npos)
		DrawArms(pInfo);
	else if (modelName.find(XORSTR("weapon")) != std::string::npos)
		DrawWeapon(pInfo);
}
