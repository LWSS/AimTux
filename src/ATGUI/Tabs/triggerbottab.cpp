#include "triggerbottab.h"

#include "../../Utils/xorstring.h"
#include "../../settings.h"
#include "../../ImGUI/imgui_internal.h"
#include "../atgui.h"
#include "aimbottab.h"

void Triggerbot::RenderTab() {
    if (ImGui::Checkbox(XORSTR("Enabled"), &Triggerbot::enabled)) {
        UI::UpdateWeaponSettings();
    }
    ImGui::Separator();
    ImGui::Columns(2, nullptr, true);
    {
        ImGui::BeginChild(XORSTR("TRIG1"), ImVec2(0, 0), true);
        {
            ImGui::Text(XORSTR("Current weapon: %s"), Util::Items::GetItemDisplayName(Aimbot::currentWeapon).c_str());

            ImGui::Text(XORSTR("Keybind"));
            ImGui::Separator();
            ImGui::Columns(2, nullptr, true);
            {
                ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
                ImGui::Text(XORSTR("Trigger Key"));
            }
            ImGui::NextColumn();
            {
                UI::KeyBindButton(&Triggerbot::key);
            }
            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::Text(XORSTR("Random Delay"));
            ImGui::Separator();
            ImGui::Columns(2, nullptr, true);
            {
                if (ImGui::Checkbox(XORSTR("Enabled"), &Triggerbot::randomDelay)) {
                    UI::UpdateWeaponSettings();
                }
                if (Triggerbot::randomDelay != 0) {
                    ImGui::Text(XORSTR("Last delay: %dms"), Triggerbot::lastRoll);
                }
            }
            ImGui::NextColumn();
            {
                ImGui::Text(XORSTR("Minimum ms"));
                if (ImGui::SliderInt(XORSTR("##TRIGGERRANDOMLOW"), &Triggerbot::lowBound, 5, 220)) {
                    UI::UpdateWeaponSettings();
                }
                if (Triggerbot::lowBound >= Triggerbot::highBound) {
                    Triggerbot::highBound = Triggerbot::lowBound + 1;
                    UI::UpdateWeaponSettings();
                }
                ImGui::Text(XORSTR("Maximum ms"));
                if (ImGui::SliderInt(XORSTR("##TRIGGERRANDOMHIGH"), &Triggerbot::highBound, (Triggerbot::lowBound + 1),
                                     225)) {
                    UI::UpdateWeaponSettings();
                }
            }
            ImGui::Columns(1);
            ImGui::Separator();

            ImGui::Text(XORSTR("Auto Knife & Zeus"));
            ImGui::Separator();
            ImGui::Columns(2, nullptr, true);
            {
                ImGui::PushItemWidth(-1);
                ImGui::Checkbox(XORSTR("Auto Knife"), &Settings::AutoKnife::enabled);
                ImGui::Checkbox(XORSTR("On Key"), &Settings::AutoKnife::onKey);

            }
            ImGui::NextColumn();
            {
                ImGui::PushItemWidth(-1);
                ImGui::Checkbox(XORSTR("Enemies"), &Settings::AutoKnife::Filters::enemies);
                ImGui::Checkbox(XORSTR("Allies"), &Settings::AutoKnife::Filters::allies);
            }

            ImGui::EndChild();
        }
    }
    ImGui::NextColumn();
    {
        ImGui::BeginChild(XORSTR("TRIG2"), ImVec2(0, 0), true);
        {
            ImGui::Text(XORSTR("Filter"));
            ImGui::Separator();
            ImGui::Columns(2, nullptr, true);
            {
                if (ImGui::Checkbox(XORSTR("Enemies"), &Triggerbot::enemies)) {
                    UI::UpdateWeaponSettings();
                }
                if (ImGui::Checkbox(XORSTR("Walls"), &Triggerbot::walls)) {
                    UI::UpdateWeaponSettings();
                }
                if (ImGui::Checkbox(XORSTR("Head"), &Triggerbot::head)) {
                    UI::UpdateWeaponSettings();
                }
                if (ImGui::Checkbox(XORSTR("Chest"), &Triggerbot::chest)) {
                    UI::UpdateWeaponSettings();
                }
                if (ImGui::Checkbox(XORSTR("Legs"), &Triggerbot::legs)) {
                    UI::UpdateWeaponSettings();
                }
            }
            ImGui::NextColumn();
            {

                if (ImGui::Checkbox(XORSTR("Allies"), &Triggerbot::allies)) {
                    UI::UpdateWeaponSettings();
                }
                if (ImGui::Checkbox(XORSTR("Smoke check"), &Triggerbot::smokeCheck)) {
                    UI::UpdateWeaponSettings();
                }
                if (ImGui::Checkbox(XORSTR("Flash check"), &Triggerbot::flashCheck)) {
                    UI::UpdateWeaponSettings();
                }
                if (ImGui::Checkbox(XORSTR("Stomach"), &Triggerbot::stomach)) {
                    UI::UpdateWeaponSettings();
                }
                if (ImGui::Checkbox(XORSTR("Arms"), &Triggerbot::arms)) {
                    UI::UpdateWeaponSettings();
                }
                ImGui::Columns(1);
                ImGui::Separator();
                ImGui::EndChild();
            }
        }
    }
}