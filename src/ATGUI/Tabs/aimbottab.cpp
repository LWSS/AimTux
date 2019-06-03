#include "aimbottab.h"

void UI::ReloadWeaponSettings() {
    ItemDefinitionIndex index = ItemDefinitionIndex::INVALID;
    if (Settings::Aimbot::weapons.find(Aimbot::currentWeapon) != Settings::Aimbot::weapons.end())
        index = Aimbot::currentWeapon;

    Aimbot::enabled = Settings::Aimbot::weapons.at(index).enabled;
    Aimbot::silent = Settings::Aimbot::weapons.at(index).silent;
    Aimbot::friendly = Settings::Aimbot::weapons.at(index).friendly;
    Aimbot::closestBone = Settings::Aimbot::weapons.at(index).closestBone;
    Aimbot::engageLock = Settings::Aimbot::weapons.at(index).engageLock;
    Aimbot::engageLockTR = Settings::Aimbot::weapons.at(index).engageLockTR;
    Aimbot::engageLockTTR = Settings::Aimbot::weapons.at(index).engageLockTTR;
    Aimbot::bone = Settings::Aimbot::weapons.at(index).bone;
    Aimbot::aimkey = Settings::Aimbot::weapons.at(index).aimkey;
    Aimbot::aimkeyOnly = Settings::Aimbot::weapons.at(index).aimkeyOnly;
    Aimbot::smoothEnabled = Settings::Aimbot::weapons.at(index).smoothEnabled;
    Aimbot::smoothValue = Settings::Aimbot::weapons.at(index).smoothAmount;
    Aimbot::smoothType = Settings::Aimbot::weapons.at(index).smoothType;
    Aimbot::smoothSaltEnabled = Settings::Aimbot::weapons.at(index).smoothSaltEnabled;
    Aimbot::smoothSaltMultiplier = Settings::Aimbot::weapons.at(index).smoothSaltMultiplier;
    Aimbot::errorMarginEnabled = Settings::Aimbot::weapons.at(index).errorMarginEnabled;
    Aimbot::errorMarginValue = Settings::Aimbot::weapons.at(index).errorMarginValue;
    Aimbot::autoAimEnabled = Settings::Aimbot::weapons.at(index).autoAimEnabled;
    Aimbot::autoAimValue = Settings::Aimbot::weapons.at(index).autoAimFov;
    Aimbot::aimStepEnabled = Settings::Aimbot::weapons.at(index).aimStepEnabled;
    Aimbot::aimStepMin = Settings::Aimbot::weapons.at(index).aimStepMin;
    Aimbot::aimStepMax = Settings::Aimbot::weapons.at(index).aimStepMax;
    Aimbot::rcsEnabled = Settings::Aimbot::weapons.at(index).rcsEnabled;
    Aimbot::rcsAlwaysOn = Settings::Aimbot::weapons.at(index).rcsAlwaysOn;
    Aimbot::rcsAmountX = Settings::Aimbot::weapons.at(index).rcsAmountX;
    Aimbot::rcsAmountY = Settings::Aimbot::weapons.at(index).rcsAmountY;
    Aimbot::autoPistolEnabled = Settings::Aimbot::weapons.at(index).autoPistolEnabled;
    Aimbot::autoShootEnabled = Settings::Aimbot::weapons.at(index).autoShootEnabled;
    Aimbot::autoScopeEnabled = Settings::Aimbot::weapons.at(index).autoScopeEnabled;
    Aimbot::noShootEnabled = Settings::Aimbot::weapons.at(index).noShootEnabled;
    Aimbot::ignoreJumpEnabled = Settings::Aimbot::weapons.at(index).ignoreJumpEnabled;
    Aimbot::ignoreEnemyJumpEnabled = Settings::Aimbot::weapons.at(index).ignoreEnemyJumpEnabled;
    Aimbot::smokeCheck = Settings::Aimbot::weapons.at(index).smokeCheck;
    Aimbot::flashCheck = Settings::Aimbot::weapons.at(index).flashCheck;
    Aimbot::spreadLimitEnabled = Settings::Aimbot::weapons.at(index).spreadLimitEnabled;
    Aimbot::spreadLimit = Settings::Aimbot::weapons.at(index).spreadLimit;
    Aimbot::autoWallEnabled = Settings::Aimbot::weapons.at(index).autoWallEnabled;
    Aimbot::autoWallValue = Settings::Aimbot::weapons.at(index).autoWallValue;
    Aimbot::autoAimRealDistance = Settings::Aimbot::weapons.at(index).autoAimRealDistance;
    Aimbot::autoSlow = Settings::Aimbot::weapons.at(index).autoSlow;
    Aimbot::predEnabled = Settings::Aimbot::weapons.at(index).predEnabled;
    Aimbot::scopeControlEnabled = Settings::Aimbot::weapons.at(index).scopeControlEnabled;

    Triggerbot::enabled = Settings::Aimbot::weapons.at(index).Triggerbot.enabled,
    Triggerbot::key = Settings::Aimbot::weapons.at(index).Triggerbot.key,
    Triggerbot::flashCheck = Settings::Aimbot::weapons.at(index).Triggerbot.flashCheck,
    Triggerbot::smokeCheck = Settings::Aimbot::weapons.at(index).Triggerbot.smokeCheck,
    Triggerbot::allies = Settings::Aimbot::weapons.at(index).Triggerbot.allies,
    Triggerbot::enemies = Settings::Aimbot::weapons.at(index).Triggerbot.enemies,
    Triggerbot::head = Settings::Aimbot::weapons.at(index).Triggerbot.head,
    Triggerbot::chest = Settings::Aimbot::weapons.at(index).Triggerbot.chest,
    Triggerbot::stomach = Settings::Aimbot::weapons.at(index).Triggerbot.stomach,
    Triggerbot::arms = Settings::Aimbot::weapons.at(index).Triggerbot.arms,
    Triggerbot::legs = Settings::Aimbot::weapons.at(index).Triggerbot.legs,
    Triggerbot::walls = Settings::Aimbot::weapons.at(index).Triggerbot.walls,
    Triggerbot::lowBound = Settings::Aimbot::weapons.at(index).Triggerbot.lowBound,
    Triggerbot::highBound = Settings::Aimbot::weapons.at(index).Triggerbot.highBound,
    Triggerbot::lastRoll = Settings::Aimbot::weapons.at(index).Triggerbot.lastRoll;

    for (int bone = (int) DesiredBones::BONE_PELVIS; bone <= (int) DesiredBones::BONE_RIGHT_SOLE; bone++)
        Aimbot::desiredBones[bone] = Settings::Aimbot::weapons.at(index).desiredBones[bone];
}

void UI::UpdateWeaponSettings() {
    if (Settings::Aimbot::weapons.find(Aimbot::currentWeapon) == Settings::Aimbot::weapons.end())
        Settings::Aimbot::weapons[Aimbot::currentWeapon] = AimbotWeapon_t();
    AimbotWeapon_t settings = {
            {
                    .enabled = Triggerbot::enabled,
                    .key = Triggerbot::key,
                    .enemies = Triggerbot::enemies,
                    .allies = Triggerbot::allies,
                    .walls = Triggerbot::walls,
                    .smokeCheck = Triggerbot::smokeCheck,
                    .flashCheck = Triggerbot::flashCheck,
                    .head = Triggerbot::head,
                    .chest = Triggerbot::chest,
                    .stomach = Triggerbot::stomach,
                    .arms = Triggerbot::arms,
                    .legs = Triggerbot::legs,
                    .lowBound = Triggerbot::lowBound,
                    .highBound = Triggerbot::highBound,
                    .lastRoll = Triggerbot::lastRoll
            },
            .enabled = Aimbot::enabled,
            .silent = Aimbot::silent,
            .friendly = Aimbot::friendly,
            .closestBone = Aimbot::closestBone,
            .engageLock = Aimbot::engageLock,
            .engageLockTR = Aimbot::engageLockTR,
            .aimkeyOnly = Aimbot::aimkeyOnly,
            .smoothEnabled = Aimbot::smoothEnabled,
            .smoothSaltEnabled = Aimbot::smoothSaltEnabled,
            .errorMarginEnabled = Aimbot::errorMarginEnabled,
            .autoAimEnabled = Aimbot::autoAimEnabled,
            .aimStepEnabled = Aimbot::aimStepEnabled,
            .rcsEnabled = Aimbot::rcsEnabled,
            .rcsAlwaysOn = Aimbot::rcsAlwaysOn,
            .spreadLimitEnabled = Aimbot::spreadLimitEnabled,
            .autoPistolEnabled = Aimbot::autoPistolEnabled,
            .autoShootEnabled = Aimbot::autoShootEnabled,
            .autoScopeEnabled = Aimbot::autoScopeEnabled,
            .noShootEnabled = Aimbot::noShootEnabled,
            .ignoreJumpEnabled = Aimbot::ignoreJumpEnabled,
            .ignoreEnemyJumpEnabled = Aimbot::ignoreEnemyJumpEnabled,
            .smokeCheck = Aimbot::smokeCheck,
            .flashCheck = Aimbot::flashCheck,
            .autoWallEnabled = Aimbot::autoWallEnabled,
            .autoAimRealDistance = Aimbot::autoAimRealDistance,
            .autoSlow = Aimbot::autoSlow,
            .predEnabled = Aimbot::predEnabled,
            .scopeControlEnabled = Aimbot::scopeControlEnabled,
            .engageLockTTR = Aimbot::engageLockTTR,
            .bone = Aimbot::bone,
            .smoothType = Aimbot::smoothType,
            .aimkey = Aimbot::aimkey,
            .smoothAmount = Aimbot::smoothValue,
            .smoothSaltMultiplier = Aimbot::smoothSaltMultiplier,
            .errorMarginValue = Aimbot::errorMarginValue,
            .autoAimFov = Aimbot::autoAimValue,
            .aimStepMin = Aimbot::aimStepMin,
            .aimStepMax = Aimbot::aimStepMax,
            .rcsAmountX = Aimbot::rcsAmountX,
            .rcsAmountY = Aimbot::rcsAmountY,
            .autoWallValue = Aimbot::autoWallValue,
            .spreadLimit = Aimbot::spreadLimit,
    };


    for (int bone = (int) DesiredBones::BONE_PELVIS; bone <= (int) DesiredBones::BONE_RIGHT_SOLE; bone++)
        settings.desiredBones[bone] = Aimbot::desiredBones[bone];

    Settings::Aimbot::weapons.at(Aimbot::currentWeapon) = settings;

    if (Settings::Aimbot::weapons.at(Aimbot::currentWeapon) ==
        Settings::Aimbot::weapons.at(ItemDefinitionIndex::INVALID) &&
        Aimbot::currentWeapon != ItemDefinitionIndex::INVALID) {
        Settings::Aimbot::weapons.erase(Aimbot::currentWeapon);
        UI::ReloadWeaponSettings();
    }
}

void Aimbot::RenderTab() {
    const char *targets[] = {"PELVIS", "", "", "HIP", "LOWER SPINE", "MIDDLE SPINE", "UPPER SPINE", "NECK", "HEAD"};
    const char *smoothTypes[] = {"Slow Near End", "Constant Speed", "Fast Near End"};
    static char filterWeapons[32];

    if (ImGui::Checkbox(XORSTR("Enabled"), &enabled))
        UI::UpdateWeaponSettings();
    ImGui::Separator();

    ImGui::Columns(3, nullptr, true);
    {
        ImGui::SetColumnOffset(1, 200);
        ImGui::PushItemWidth(-1);
        ImGui::InputText(XORSTR("##FILTERWEAPONS"), filterWeapons, IM_ARRAYSIZE(filterWeapons));
        ImGui::PopItemWidth();
        ImGui::ListBoxHeader(XORSTR("##GUNS"), ImVec2(-1, -1));
        for (auto it : ItemDefinitionIndexMap) {
            bool isDefault = (int) it.first < 0;
            if (!isDefault && !Util::Contains(Util::ToLower(std::string(filterWeapons)),
                                              Util::ToLower(Util::Items::GetItemDisplayName(it.first).c_str())))
                continue;

            if (Util::Items::IsKnife(it.first) || Util::Items::IsGlove(it.first) || Util::Items::IsUtility(it.first))
                continue;

            const bool item_selected = ((int) it.first == (int) currentWeapon);
            ImGui::PushID((int) it.first);
            std::string formattedName;
            char changeIndicator = ' ';
            bool isChanged = Settings::Aimbot::weapons.find(it.first) != Settings::Aimbot::weapons.end();
            if (!isDefault && isChanged)
                changeIndicator = '*';
            formattedName = changeIndicator + (isDefault ? Util::Items::GetItemDisplayName(it.first).c_str()
                                                         : Util::Items::GetItemDisplayName(it.first));
            if (ImGui::Selectable(formattedName.c_str(), item_selected)) {
                currentWeapon = it.first;
                UI::ReloadWeaponSettings();
            }
            ImGui::PopID();
        }
        ImGui::ListBoxFooter();
    }
    ImGui::NextColumn();
    {
        ImGui::SetColumnOffset(2, ImGui::GetWindowWidth() / 2 + 75);
        ImGui::BeginChild(XORSTR("COL1"), ImVec2(0, 0), true);
        {
            ImGui::Text(XORSTR("Target"));
            ImGui::Separator();
            ImGui::Columns(2, nullptr, false);
            {
                if (ImGui::Checkbox(XORSTR("FriendlyFire"), &friendly))
                    UI::UpdateWeaponSettings();
            }
            ImGui::NextColumn();
            {
                ImGui::PushItemWidth(-1);
                ImGui::Text(XORSTR("Aimbot Target"));
                if (!closestBone) {
                    if (ImGui::Combo(XORSTR("##AIMTARGET"), (int *) &bone, targets, IM_ARRAYSIZE(targets)))
                        UI::UpdateWeaponSettings();
                }
                if (closestBone) {
                    if (ImGui::Button(XORSTR("Bones"), ImVec2(-1, 0)))
                        ImGui::OpenPopup(XORSTR("optionBones"));
                    ImGui::SetNextWindowSize(ImVec2((ImGui::GetWindowWidth() / 1.25f), ImGui::GetWindowHeight()),
                                             ImGuiSetCond_Always);
                    if (ImGui::BeginPopup(XORSTR("optionBones"))) {
                        ImGui::PushItemWidth(-1);
                        ImGui::Text(XORSTR("Center Mass"));
                        if (ImGui::Checkbox(XORSTR("Head"), &desiredBones[(int) DesiredBones::BONE_HEAD]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Neck"), &desiredBones[(int) DesiredBones::BONE_NECK]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Upper Spine"),
                                            &desiredBones[(int) DesiredBones::BONE_UPPER_SPINAL_COLUMN]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Middle Spine"),
                                            &desiredBones[(int) DesiredBones::BONE_MIDDLE_SPINAL_COLUMN]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Lower Spine"),
                                            &desiredBones[(int) DesiredBones::BONE_LOWER_SPINAL_COLUMN]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Pelvis"), &desiredBones[(int) DesiredBones::BONE_PELVIS]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Hip"), &desiredBones[(int) DesiredBones::BONE_HIP]))
                            UI::UpdateWeaponSettings();
                        ImGui::Separator();

                        ImGui::Columns(2, nullptr, false);
                        {
                            ImGui::Text(XORSTR("Player's Right Arm"));
                            if (ImGui::Checkbox(XORSTR("Collarbone"),
                                                &desiredBones[(int) DesiredBones::BONE_RIGHT_COLLARBONE]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Shoulder"),
                                                &desiredBones[(int) DesiredBones::BONE_RIGHT_SHOULDER]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Armpit"), &desiredBones[(int) DesiredBones::BONE_RIGHT_ARMPIT]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Bicep"), &desiredBones[(int) DesiredBones::BONE_RIGHT_BICEP]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Elbow"), &desiredBones[(int) DesiredBones::BONE_RIGHT_ELBOW]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Forearm"),
                                                &desiredBones[(int) DesiredBones::BONE_RIGHT_FOREARM]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Wrist"), &desiredBones[(int) DesiredBones::BONE_RIGHT_WRIST]))
                                UI::UpdateWeaponSettings();
                            ImGui::Text(XORSTR("Player's Right Leg"));
                            if (ImGui::Checkbox(XORSTR("Buttcheek"),
                                                &desiredBones[(int) DesiredBones::BONE_RIGHT_BUTTCHEEK]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Thigh"), &desiredBones[(int) DesiredBones::BONE_RIGHT_THIGH]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Knee"), &desiredBones[(int) DesiredBones::BONE_RIGHT_KNEE]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Ankle"), &desiredBones[(int) DesiredBones::BONE_RIGHT_ANKLE]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Sole"), &desiredBones[(int) DesiredBones::BONE_RIGHT_SOLE]))
                                UI::UpdateWeaponSettings();
                        }
                        ImGui::NextColumn();
                        {   // these spaces are here in the strings because checkboxes can't have duplicate titles.
                            ImGui::Text(XORSTR("Player's Left Arm"));
                            if (ImGui::Checkbox(XORSTR("Collarbone "),
                                                &desiredBones[(int) DesiredBones::BONE_LEFT_COLLARBONE]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Shoulder "),
                                                &desiredBones[(int) DesiredBones::BONE_LEFT_SHOULDER]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Armpit "), &desiredBones[(int) DesiredBones::BONE_LEFT_ARMPIT]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Bicep "), &desiredBones[(int) DesiredBones::BONE_LEFT_BICEP]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Elbow "), &desiredBones[(int) DesiredBones::BONE_LEFT_ELBOW]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Forearm "),
                                                &desiredBones[(int) DesiredBones::BONE_LEFT_FOREARM]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Wrist "), &desiredBones[(int) DesiredBones::BONE_LEFT_WRIST]))
                                UI::UpdateWeaponSettings();

                            ImGui::Text(XORSTR("Player's Left Leg"));
                            if (ImGui::Checkbox(XORSTR("Buttcheek "),
                                                &desiredBones[(int) DesiredBones::BONE_LEFT_BUTTCHEEK]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Thigh "), &desiredBones[(int) DesiredBones::BONE_LEFT_THIGH]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Knee "), &desiredBones[(int) DesiredBones::BONE_LEFT_KNEE]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Ankle "), &desiredBones[(int) DesiredBones::BONE_LEFT_ANKLE]))
                                UI::UpdateWeaponSettings();
                            if (ImGui::Checkbox(XORSTR("Sole "), &desiredBones[(int) DesiredBones::BONE_LEFT_SOLE]))
                                UI::UpdateWeaponSettings();
                        }
                        ImGui::PopItemWidth();
                        ImGui::EndPopup();
                    }
                }
                if (ImGui::Checkbox(XORSTR("ClosestBone"), &closestBone))
                    UI::UpdateWeaponSettings();

                if (ImGui::Checkbox(XORSTR("EngageLock"), &engageLock))
                    UI::UpdateWeaponSettings();
                if (engageLock) {
                    if (ImGui::Checkbox(XORSTR("Target Reacquisition"), &engageLockTR))
                        UI::UpdateWeaponSettings();
                    if (engageLockTR) {
                        if (ImGui::SliderInt(XORSTR("##TTR"), &engageLockTTR, 0, 1000))
                            UI::UpdateWeaponSettings();
                    }
                }
                ImGui::PopItemWidth();
            }
            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::Text(XORSTR("Accuracy"));
            ImGui::Separator();
            ImGui::Columns(2, nullptr, true);
            {
                if (ImGui::Checkbox(XORSTR("Auto Aim"), &autoAimEnabled))
                    UI::UpdateWeaponSettings();
                if (ImGui::Checkbox(XORSTR("Recoil Control"), &rcsEnabled))
                    UI::UpdateWeaponSettings();
                if (ImGui::Checkbox(XORSTR("Distance-Based FOV"), &autoAimRealDistance))
                    UI::UpdateWeaponSettings();
            }
            ImGui::NextColumn();
            {
                ImGui::PushItemWidth(-1);
                if (ImGui::SliderFloat(XORSTR("##AA"), &autoAimValue, 0, 180))
                    UI::UpdateWeaponSettings();
                ImGui::PopItemWidth();
                if (ImGui::Button(XORSTR("RCS Settings"), ImVec2(-1, 0)))
                    ImGui::OpenPopup(XORSTR("optionRCSAmount"));
                ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Always);
                if (ImGui::BeginPopup(XORSTR("optionRCSAmount"))) {
                    ImGui::PushItemWidth(-1);
                    if (ImGui::Checkbox(XORSTR("RCS Always on"), &rcsAlwaysOn))
                        UI::UpdateWeaponSettings();
                    if (ImGui::SliderFloat(XORSTR("##RCSX"), &rcsAmountX, 0, 2, XORSTR("Pitch: %0.3f")))
                        UI::UpdateWeaponSettings();
                    if (ImGui::SliderFloat(XORSTR("##RCSY"), &rcsAmountY, 0, 2, XORSTR("Yaw: %0.3f")))
                        UI::UpdateWeaponSettings();
                    ImGui::PopItemWidth();

                    ImGui::EndPopup();
                }
            }
            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::Text(XORSTR("Humanizing"));
            ImGui::Separator();
            ImGui::Columns(2, nullptr, true);
            {
                if (ImGui::Checkbox(XORSTR("Smoothing"), &smoothEnabled))
                    UI::UpdateWeaponSettings();
                if (ImGui::Checkbox(XORSTR("Smooth Salting"), &smoothSaltEnabled))
                    UI::UpdateWeaponSettings();
                if (ImGui::Checkbox(XORSTR("Error Margin"), &errorMarginEnabled))
                    UI::UpdateWeaponSettings();
                ImGui::PushItemWidth(-1);
                if (ImGui::Combo(XORSTR("##SMOOTHTYPE"), (int *) &smoothType, smoothTypes, IM_ARRAYSIZE(smoothTypes)))
                    UI::UpdateWeaponSettings();
                ImGui::PopItemWidth();
            }
            ImGui::NextColumn();
            {
                ImGui::PushItemWidth(-1);
                if (ImGui::SliderFloat(XORSTR("##SMOOTH"), &smoothValue, 0, 1))
                    UI::UpdateWeaponSettings();
                if (ImGui::SliderFloat(XORSTR("##SALT"), &smoothSaltMultiplier, 0, smoothValue))
                    UI::UpdateWeaponSettings();
                if (ImGui::SliderFloat(XORSTR("##ERROR"), &errorMarginValue, 0, 2))
                    UI::UpdateWeaponSettings();
                ImGui::PopItemWidth();
            }
            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::Text(XORSTR("Autoshoot"));
            ImGui::Separator();
            if (ImGui::Checkbox(XORSTR("Auto Shoot"), &autoShootEnabled))
                UI::UpdateWeaponSettings();
            ImGui::Checkbox(XORSTR("Velocity Check"), &Settings::Aimbot::AutoShoot::velocityCheck);
            if (ImGui::Checkbox(XORSTR("Spread Limit"), &spreadLimitEnabled))
                UI::UpdateWeaponSettings();
            if (ImGui::SliderFloat(XORSTR("##SPREADLIMIT"), &spreadLimit, 0, 0.1))
                UI::UpdateWeaponSettings();
            ImGui::EndChild();
        }
    }
    ImGui::NextColumn();
    {
        ImGui::BeginChild(XORSTR("COL2"), ImVec2(0, 0), true);
        {
            ImGui::Text(XORSTR("Aimkey Only"));
            ImGui::Separator();
            ImGui::Columns(2, nullptr, true);
            {
                if (ImGui::Checkbox(XORSTR("Enabled"), &aimkeyOnly))
                    UI::UpdateWeaponSettings();
            }
            ImGui::NextColumn();
            {
                UI::KeyBindButton(&aimkey);
            }
            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::Text(XORSTR("Casual / DM Only"));
            ImGui::Separator();
            ImGui::Columns(2, nullptr, true);
            {
                if (ImGui::Checkbox(XORSTR("Aim Step"), &aimStepEnabled))
                    UI::UpdateWeaponSettings();
            }
            ImGui::NextColumn();
            {
                ImGui::PushItemWidth(-1);
                ImGui::Text(XORSTR("Min"));
                if (ImGui::SliderFloat(XORSTR("##STEPMIN"), &aimStepMin, 5, 35))
                    UI::UpdateWeaponSettings();
                ImGui::Text(XORSTR("Max"));
                if (ImGui::SliderFloat(XORSTR("##STEPMAX"), &aimStepMax, (aimStepMin) + 1.0f, 35))
                    UI::UpdateWeaponSettings();
                ImGui::PopItemWidth();
            }
            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::Text(XORSTR("Other"));
            ImGui::Separator();
            ImGui::Columns(2, nullptr, true);
            {

                switch (currentWeapon) {
                    case ItemDefinitionIndex::INVALID:
                    case ItemDefinitionIndex::WEAPON_DEAGLE:
                    case ItemDefinitionIndex::WEAPON_ELITE:
                    case ItemDefinitionIndex::WEAPON_FIVESEVEN:
                    case ItemDefinitionIndex::WEAPON_GLOCK:
                    case ItemDefinitionIndex::WEAPON_TEC9:
                    case ItemDefinitionIndex::WEAPON_HKP2000:
                    case ItemDefinitionIndex::WEAPON_USP_SILENCER:
                    case ItemDefinitionIndex::WEAPON_P250:
                    case ItemDefinitionIndex::WEAPON_CZ75A:
                    case ItemDefinitionIndex::WEAPON_REVOLVER:
                        if (ImGui::Checkbox(XORSTR("Auto Pistol"), &autoPistolEnabled))
                            UI::UpdateWeaponSettings();
                        break;
                    default:
                        break;
                }

                if (ImGui::Checkbox(XORSTR("Silent Aim"), &silent))
                    UI::UpdateWeaponSettings();
                if (ImGui::Checkbox(XORSTR("Smoke Check"), &smokeCheck))
                    UI::UpdateWeaponSettings();
                if (ImGui::Checkbox(XORSTR("Prediction"), &predEnabled))
                    UI::UpdateWeaponSettings();
            }
            ImGui::NextColumn();
            {
                if (ImGui::Checkbox(XORSTR("No Shoot"), &noShootEnabled))
                    UI::UpdateWeaponSettings();

                switch (currentWeapon) {
                    case ItemDefinitionIndex::WEAPON_DEAGLE:
                    case ItemDefinitionIndex::WEAPON_ELITE:
                    case ItemDefinitionIndex::WEAPON_FIVESEVEN:
                    case ItemDefinitionIndex::WEAPON_GLOCK:
                    case ItemDefinitionIndex::WEAPON_TEC9:
                    case ItemDefinitionIndex::WEAPON_HKP2000:
                    case ItemDefinitionIndex::WEAPON_USP_SILENCER:
                    case ItemDefinitionIndex::WEAPON_P250:
                    case ItemDefinitionIndex::WEAPON_CZ75A:
                    case ItemDefinitionIndex::WEAPON_REVOLVER:
                        break;
                    default:
                        if (ImGui::Checkbox(XORSTR("Auto Scope"), &autoScopeEnabled))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Scope Control"), &scopeControlEnabled))
                            UI::UpdateWeaponSettings();
                }

                if (ImGui::Checkbox(XORSTR("Flash Check"), &flashCheck))
                    UI::UpdateWeaponSettings();
                if (ImGui::Checkbox(XORSTR("Ignore Jump (Self)"), &ignoreJumpEnabled))
                    UI::UpdateWeaponSettings();
                if (ImGui::Checkbox(XORSTR("Ignore Jump (Enemies)"), &ignoreEnemyJumpEnabled))
                    UI::UpdateWeaponSettings();
            }


            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::Text(XORSTR("AutoSlow"));
            ImGui::Separator();
            if (ImGui::Checkbox(XORSTR("Enabled##AUTOSLOW"), &autoSlow))
                UI::UpdateWeaponSettings();

            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::Text(XORSTR("AutoWall"));
            ImGui::Separator();
            ImGui::Columns(2, nullptr, true);
            {
                if (ImGui::Checkbox(XORSTR("Enabled##AUTOWALL"), &autoWallEnabled))
                    UI::UpdateWeaponSettings();
                if (ImGui::Button(XORSTR("Autowall Bones"), ImVec2(-1, 0)))
                    ImGui::OpenPopup(XORSTR("optionBones"));
                ImGui::SetNextWindowSize(ImVec2((ImGui::GetWindowWidth() / 1.25f), ImGui::GetWindowHeight()),
                                         ImGuiSetCond_Always);
                if (ImGui::BeginPopup(XORSTR("optionBones"))) {
                    ImGui::PushItemWidth(-1);
                    ImGui::Text(XORSTR("Center Mass"));
                    if (ImGui::Checkbox(XORSTR("Head"), &desiredBones[(int) DesiredBones::BONE_HEAD]))
                        UI::UpdateWeaponSettings();
                    if (ImGui::Checkbox(XORSTR("Neck"), &desiredBones[(int) DesiredBones::BONE_NECK]))
                        UI::UpdateWeaponSettings();
                    if (ImGui::Checkbox(XORSTR("Upper Spine"),
                                        &desiredBones[(int) DesiredBones::BONE_UPPER_SPINAL_COLUMN]))
                        UI::UpdateWeaponSettings();
                    if (ImGui::Checkbox(XORSTR("Middle Spine"),
                                        &desiredBones[(int) DesiredBones::BONE_MIDDLE_SPINAL_COLUMN]))
                        UI::UpdateWeaponSettings();
                    if (ImGui::Checkbox(XORSTR("Lower Spine"),
                                        &desiredBones[(int) DesiredBones::BONE_LOWER_SPINAL_COLUMN]))
                        UI::UpdateWeaponSettings();
                    if (ImGui::Checkbox(XORSTR("Pelvis"), &desiredBones[(int) DesiredBones::BONE_PELVIS]))
                        UI::UpdateWeaponSettings();
                    if (ImGui::Checkbox(XORSTR("Hip"), &desiredBones[(int) DesiredBones::BONE_HIP]))
                        UI::UpdateWeaponSettings();
                    ImGui::Separator();

                    ImGui::Columns(2, nullptr, false);
                    {
                        ImGui::Text(XORSTR("Player's Right Arm"));
                        if (ImGui::Checkbox(XORSTR("Collarbone"),
                                            &desiredBones[(int) DesiredBones::BONE_RIGHT_COLLARBONE]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Shoulder"), &desiredBones[(int) DesiredBones::BONE_RIGHT_SHOULDER]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Armpit"), &desiredBones[(int) DesiredBones::BONE_RIGHT_ARMPIT]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Bicep"), &desiredBones[(int) DesiredBones::BONE_RIGHT_BICEP]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Elbow"), &desiredBones[(int) DesiredBones::BONE_RIGHT_ELBOW]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Forearm"), &desiredBones[(int) DesiredBones::BONE_RIGHT_FOREARM]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Wrist"), &desiredBones[(int) DesiredBones::BONE_RIGHT_WRIST]))
                            UI::UpdateWeaponSettings();
                        ImGui::Text(XORSTR("Player's Right Leg"));
                        if (ImGui::Checkbox(XORSTR("Buttcheek"),
                                            &desiredBones[(int) DesiredBones::BONE_RIGHT_BUTTCHEEK]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Thigh"), &desiredBones[(int) DesiredBones::BONE_RIGHT_THIGH]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Knee"), &desiredBones[(int) DesiredBones::BONE_RIGHT_KNEE]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Ankle"), &desiredBones[(int) DesiredBones::BONE_RIGHT_ANKLE]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Sole"), &desiredBones[(int) DesiredBones::BONE_RIGHT_SOLE]))
                            UI::UpdateWeaponSettings();
                    }
                    ImGui::NextColumn();
                    {
                        ImGui::Text(XORSTR("Player's Left Arm"));
                        if (ImGui::Checkbox(XORSTR("Collarbone "),
                                            &desiredBones[(int) DesiredBones::BONE_LEFT_COLLARBONE]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Shoulder "), &desiredBones[(int) DesiredBones::BONE_LEFT_SHOULDER]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Armpit "), &desiredBones[(int) DesiredBones::BONE_LEFT_ARMPIT]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Bicep "), &desiredBones[(int) DesiredBones::BONE_LEFT_BICEP]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Elbow "), &desiredBones[(int) DesiredBones::BONE_LEFT_ELBOW]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Forearm "), &desiredBones[(int) DesiredBones::BONE_LEFT_FOREARM]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Wrist "), &desiredBones[(int) DesiredBones::BONE_LEFT_WRIST]))
                            UI::UpdateWeaponSettings();

                        ImGui::Text(XORSTR("Player's Left Leg"));
                        if (ImGui::Checkbox(XORSTR("Buttcheek "),
                                            &desiredBones[(int) DesiredBones::BONE_LEFT_BUTTCHEEK]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Thigh "), &desiredBones[(int) DesiredBones::BONE_LEFT_THIGH]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Knee "), &desiredBones[(int) DesiredBones::BONE_LEFT_KNEE]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Ankle "), &desiredBones[(int) DesiredBones::BONE_LEFT_ANKLE]))
                            UI::UpdateWeaponSettings();
                        if (ImGui::Checkbox(XORSTR("Sole "), &desiredBones[(int) DesiredBones::BONE_LEFT_SOLE]))
                            UI::UpdateWeaponSettings();
                    }
                    ImGui::PopItemWidth();
                    ImGui::EndPopup();
                }
            }
            ImGui::NextColumn();
            {
                ImGui::PushItemWidth(-1);
                if (ImGui::SliderFloat(XORSTR("##AUTOWALLDMG"), &autoWallValue, 0, 100, XORSTR("Min Damage: %f")))
                    UI::UpdateWeaponSettings();
                ImGui::PopItemWidth();
            }


            ImGui::Columns(1);
            ImGui::Separator();
            if (currentWeapon > ItemDefinitionIndex::INVALID &&
                Settings::Aimbot::weapons.find(currentWeapon) != Settings::Aimbot::weapons.end()) {
                if (ImGui::Button(XORSTR("Clear Weapon Settings"), ImVec2(-1, 0))) {
                    Settings::Aimbot::weapons.erase(currentWeapon);
                    UI::ReloadWeaponSettings();
                }
            }
            ImGui::EndChild();
        }
    }
}
