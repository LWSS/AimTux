#include "triggerbottab.h"

void Triggerbot::RenderTab()
{
	ImGui::Checkbox(XORSTR("Enabled"), &Settings::Triggerbot::enabled);
	ImGui::Separator();
	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild(XORSTR("TRIG1"), ImVec2(0, 0), true);
		{
			ImGui::Text("%s", XORSTR("Keybind"));
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Text("%s", XORSTR("Trigger Key"));
			}
			ImGui::NextColumn();
			{
				UI::KeyBindButton(&Settings::Triggerbot::key);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("%s", XORSTR("Random Delay"));
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox(XORSTR("Enabled"), &Settings::Triggerbot::RandomDelay::enabled);
				if( Settings::Triggerbot::RandomDelay::lastRoll != 0 )
				{
				    ImGui::Text(XORSTR("Last delay: %dms"), Settings::Triggerbot::RandomDelay::lastRoll);
				}
			}
			ImGui::NextColumn();
			{
				ImGui::Text("%s", XORSTR("Minimum ms"));
				ImGui::SliderInt(XORSTR("##TRIGGERRANDOMLOW"), &Settings::Triggerbot::RandomDelay::lowBound, 5, 220);
				if( Settings::Triggerbot::RandomDelay::lowBound >= Settings::Triggerbot::RandomDelay::highBound )
				{
					Settings::Triggerbot::RandomDelay::highBound = Settings::Triggerbot::RandomDelay::lowBound + 1;
				}
				ImGui::Text("%s", XORSTR("Maximum ms"));
				ImGui::SliderInt(XORSTR("##TRIGGERRANDOMHIGH"), &Settings::Triggerbot::RandomDelay::highBound, (Settings::Triggerbot::RandomDelay::lowBound+1), 225);
			}
			ImGui::Columns(1);
			ImGui::Separator();

			ImGui::Text("%s", XORSTR("Auto Knife & Zeus"));
 			ImGui::Separator();
 			ImGui::Columns(2, NULL, true);
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
			ImGui::Text("%s", XORSTR("Filter"));
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox(XORSTR("Enemies"), &Settings::Triggerbot::Filters::enemies);
				ImGui::Checkbox(XORSTR("Walls"), &Settings::Triggerbot::Filters::walls);
				ImGui::Checkbox(XORSTR("Head"), &Settings::Triggerbot::Filters::head);
				ImGui::Checkbox(XORSTR("Chest"), &Settings::Triggerbot::Filters::chest);
				ImGui::Checkbox(XORSTR("Legs"), &Settings::Triggerbot::Filters::legs);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox(XORSTR("Allies"), &Settings::Triggerbot::Filters::allies);
				ImGui::Checkbox(XORSTR("Smoke check"), &Settings::Triggerbot::Filters::smokeCheck);
				ImGui::Checkbox(XORSTR("Flash check"), &Settings::Triggerbot::Filters::flashCheck);
				ImGui::Checkbox(XORSTR("Stomach"), &Settings::Triggerbot::Filters::stomach);
				ImGui::Checkbox(XORSTR("Arms"), &Settings::Triggerbot::Filters::arms);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
}
