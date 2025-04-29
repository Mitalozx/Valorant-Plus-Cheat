#include "../main.h"
#include "../blabla/icons.h"
#include "../blabla/fonthelper.h"
#include "../blabla/Images.h"

namespace Discord
{
	static int dc = 0;
}
void valthe()
{

	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowPadding = ImVec2(15, 15);
	style.WindowRounding = 5.0f;
	style.FramePadding = ImVec2(5, 5);
	style.FrameRounding = 4.0f;
	style.ItemSpacing = ImVec2(12, 8);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 3.0f;

	style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
	style.Colors[ImGuiCol_WindowBg] = ImColor(15, 15, 15, 255);
	style.Colors[ImGuiCol_ChildWindowBg] = ImColor(10, 10, 10, 255);
	style.Colors[ImGuiCol_Border] = ImColor(15, 15, 15, 255);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.15f, 0.60f, 0.78f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.24f, 0.40f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.02f, 0.60f, 0.22f);
}

int radartype = 0;

namespace ImGuiEx
{
	void KeyBindButton(int& key)
	{
		static auto b_get = false;
		static std::string sz_text = ("Click to bind.");

		if (ImGui::Button(sz_text.c_str(), ImVec2(160, 20)))
			b_get = true;

		if (b_get)
		{
			for (auto i = 1; i < 256; i++)
			{
				if (GetAsyncKeyState(i) & 0x8000)
				{
					if (i != 12)
					{
						key = i == VK_ESCAPE ? 0 : i;
						b_get = false;
					}
				}
			}
			sz_text = ("Press a Key.");
		}
		else if (!b_get && key == 0)
			sz_text = ("Click to bind.");
		else if (!b_get && key != 0)
		{
			sz_text = ("Key ~ ") + std::to_string(key);
		}
	}

	void KeyBindButton(int& key, int width, int height)
	{
		static auto b_get = false;
		static std::string sz_text = XorStr("Click to bind.");

		if (ImGui::Button(sz_text.c_str(), ImVec2(static_cast<float>(width), static_cast<float>(height))))
			b_get = true;

		if (b_get)
		{
			for (auto i = 1; i < 256; i++)
			{
				if (GetAsyncKeyState(i) & 0x8000)
				{
					if (i != 12)
					{
						key = i == VK_ESCAPE ? -1 : i;
						b_get = false;
					}
				}
			}
			sz_text = ("Press a Key.");
		}
		else if (!b_get && key == -1)
			sz_text = ("Click to bind.");
		else if (!b_get && key != -1)
		{
			sz_text = ("Key ~ ") + std::to_string(key);
		}
	}

	void* CopyFont(const unsigned int* src, std::size_t size)
	{
		void* ret = (void*)(new unsigned int[size / 4]);
		memcpy_s(ret, size, src, size);
		return ret;
	}

	void RenderTabs(std::vector<const char*> tabs, int& activetab, float w, float h, bool sameline)
	{
		bool values[8] = { false };
		values[activetab] = true;

		for (auto i = 0; i < static_cast<int>(tabs.size()); ++i)
		{
			if (ImGui::Selectable(tabs[i], &values[i], 0, ImVec2{ w, h }))
				activetab = i;

			if (sameline && i < static_cast<int>(tabs.size()) - 1)
				ImGui::SameLine();
		}
	}

	void SetTooltip(const char* text)
	{
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(("%s"), text);
	}
}

int iTab;

void ButtonColor(int r, int g, int b)
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Button] = ImColor(r, g, b);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(r, g, b);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(r, g, b);
}

void bubble()
{
    ImGui::SetCursorPos(ImVec2(5, 24));

    ImGui::BeginGroup();
    {
		ImGui::Begin("Private Store", NULL, ImVec2(840, 560), 1.f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
		{
			{
				if (iTab == 0) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);

				ImGui::Checkbox("Enable Box", &config.player_box);
				if (config.player_box)
				{
					ImGui::Combo("Box Type", &config.esptype, type, IM_ARRAYSIZE(type));
				}
				ImGui::Checkbox("HeadBox", &config.circlehead);
				ImGui::Checkbox("Skeleton", &config.player_skeleton);
				ImGui::Checkbox("Snaplines", &config.player_snapline);
				if (config.player_snapline)
				{
					ImGui::Combo("Snaplines Type", &config.linetype, linetype, IM_ARRAYSIZE(linetype));
				}
				ImGui::Checkbox("Distance", &config.player_distance);
				ImGui::Checkbox("Healthbar", &config.player_healthbar);
				ImGui::Checkbox("Radar", &config.radar);

				ImGui::Checkbox("Player View Angle", &config.player_view_angle);

				ImGui::Checkbox("Ignore Dormant", &config.player_ignore_dormant);

			}

			/*legit*/
			{
				if (iTab == 1) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Checkbox("Aimbot", &config.aimenable);
				if (config.aimenable)
				{
					ImGui::Checkbox("Draw Fov", &config.aimbot_draw_fov);
					ImGui::Text(("Aimbot Key"));
					ImGuiEx::KeyBindButton(aim_key, 100, 20);
					ImGui::Combo("Aimbot Target", &config.aimboness, aimbone, IM_ARRAYSIZE(aimbone));
					ImGui::SliderFloat("Smooth Aimbot", &config.aimbot_smooth, 1, 20);
					ImGui::SliderFloat("Size Fov", &config.aimbot_fov, 10, 200);
				}
			}

			/*visuals*/
			{
				if (iTab == 2) ButtonColor(50, 50, 50); else ButtonColor(15, 15, 15);
				ImGui::Text("Box Color");
				ImGui::ColorEdit4("##Box Color", (float*)&config.espcolor);
				ImGui::Spacing();
				ImGui::Text("Snaplines Color");
				ImGui::ColorEdit4("##Snaplines Color", (float*)&config.snapcolor);
				ImGui::Spacing();
				ImGui::Text("Distance Color");
				ImGui::ColorEdit4("##Distance Color", (float*)&config.distance);
				ImGui::Spacing();
				ImGui::Text("Skeleton Color");
				ImGui::ColorEdit4("##Skeleton Color", (float*)&config.skeleton);
				ImGui::Spacing();
				ImGui::Text("Headbox Color");
				ImGui::ColorEdit4("##Head Color", (float*)&config.headboxcolor);
				ImGui::Spacing();
				ImGui::Text("Fov Color");
				ImGui::ColorEdit4("##fov Color", (float*)&config.fov);
				ImGui::Text("   %.1f FPS", ImGui::GetIO().Framerate);
			}

            ImGui::EndTabBar();
        }
    }
    ImGui::EndGroup();

}