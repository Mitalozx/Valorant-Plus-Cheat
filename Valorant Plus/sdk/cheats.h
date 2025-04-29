#include "structs_funcs.h"

int S_width = GetSystemMetrics(SM_CXSCREEN);
int S_height = GetSystemMetrics(SM_CYSCREEN);

float LAphlth;

uintptr_t LAp_rot;

uintptr_t LAppwn;
bool hitsound;

std::string response;

namespace LAGMMEEE
{
	void qweqweqweqweqwe()
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFont* font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahoma.ttf ", 14);
		static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
		ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
		ImFont* FontAwesome = io.Fonts->AddFontFromMemoryCompressedTTF(fa6_solid_compressed_data, fa6_solid_compressed_size, 14.f, &icons_config, icons_ranges);
		ImFont* FontAwesomeBig = io.Fonts->AddFontFromMemoryCompressedTTF(fa6_solid_compressed_data, fa6_solid_compressed_size, 19.f, nullptr, icons_ranges);
		ImFont* TitleFont = io.Fonts->AddFontFromMemoryCompressedTTF(trebucbd_compressed_data, trebucbd_compressed_size, 30, nullptr, io.Fonts->GetGlyphRangesDefault());

		while (true)
		{
			Sleep(5);

			world = lexemveread<uintptr_t>(lexemvevirtualaddy + 0x60);
			world = check::validate_pointer(world);
			if (!world) continue;

			game_instance = lexemveread2<uintptr_t>(world + 0x1A0);//offset 0x1a0
			if (!game_instance) continue;

			persistent_level = lexemveread2<uintptr_t>(world + 0x38);
			persistent_level = check::validate_pointer(persistent_level);
			if (!persistent_level) continue;

			uintptr_t local_players = lexemveread2<uintptr_t>(game_instance + 0x40);//offset 0x40
			if (!local_players) continue;

			local_player = lexemveread2<uintptr_t>(local_players);
			if (!local_player) continue;

			Sleep(500);

			LAPNT::player_controller = lexemveread2<uintptr_t>(local_player + 0x38);

			cntrlrttn = lexemveread<fvector>(LAPNT::player_controller + 0x448);

			LAppwn = lexemveread2<DWORD_PTR>(LAPNT::player_controller + 0x468);
			playerstate = lexemveread2<uintptr_t>(LAppwn + 0x3f8);//offset
			teamComponent = lexemveread2<uintptr_t>(playerstate + 0x630);//offset
			teamID = lexemveread2<int>(teamComponent + 0xf8);


			uintptr_t local_pawn = lexemveread2<uintptr_t>(LAPNT::player_controller + 0x468);

			LAPNT::local_pawn = local_pawn;

			LAPNT::camera_manager = lexemveread2<uintptr_t>(LAPNT::player_controller + 0x480);//offsets player_camera 0x478
			LAPNT::camera_position = lexemveread<fvector>(LAPNT::camera_manager + 0x1280);


			uintptr_t actor_array = lexemveread2<uintptr_t>(persistent_level + 0xa0);//offset 0xa0
			if (!actor_array) continue;

			actor_count = lexemveread2<INT32>(persistent_level + 0xa8);
			if (!actor_count) continue;


			for (int x = 0; x < actor_count; x++)
			{

				LApactr = lexemveread2<uintptr_t>(actor_array + (x * 0x8));
				if (!LApactr) continue;

				uintptr_t for_actor = lexemveread2<uintptr_t>(lexemvevirtualaddy + actor_array + (x * 0x8));

				INT32 unique_id = lexemveread2<INT32>(LApactr + 0x38);
				if (unique_id != 18743553) continue;

				uintptr_t mesh = lexemveread2<uintptr_t>(LApactr + 0x438);//offset 0x430
				if (!mesh) continue;

				VsblesA = Vsbles(mesh);

				LAp_rot = lexemveread2<uintptr_t>(LApactr + 0x238);// offsets 0x230
				if (!LAp_rot) continue;

				uintptr_t damage_handler = lexemveread2<uintptr_t>(LApactr + 0xa08);
				if (!damage_handler) continue;

				LAphlth = lexemveread2<float>(damage_handler + 0x1B0);

				uintptr_t playerstate = lexemveread2<uintptr_t>(LApactr + 0x3F8);
				uintptr_t team_component = lexemveread2<uintptr_t>(playerstate + 0x630);
				int team_id = lexemveread2<int>(team_component + 0xF8);
				if (team_id == teamID) continue;

				if (LAphlth <= 0) continue;

				uintptr_t bone_array = lexemveread2<uintptr_t>(mesh + 0x5D8);
				if (!bone_array) continue;

				INT32 bone_count = lexemveread2<INT32>(mesh + 0x5E0);
				if (!bone_count) continue;


				{
					uintptr_t actor;
					uintptr_t mesh;
					uintptr_t bone_array;
					uintptr_t root_component;
					uintptr_t damage_handler;

					INT32 bone_count;
					INT32 ammo_count;

					std::string weapon_name;
					std::string agent_name;
					std::string player_name;

					float distance;
					float health;
					float shield;

					bool is_valid;
					bool is_damage_handler_guarded;
					bool is_mesh_guarded;
				};
				uintptr_t for_mesh = 0x1;
				bool is_damage_handler_guarded = false, is_mesh_guarded = false;
				//define player
				LAPLYR this_player{
					for_actor, //guarded region ptr
					for_mesh, //guarded region ptr
					LApactr,
					mesh,
					bone_array,
					LAp_rot,
					damage_handler,
					bone_count,
					0, //ammo count
					"", //weapon name
					"", //agent name
					"", //player name
					0.f, //distance
					LAphlth, //health
					0.f, //shleid
					true,
					is_damage_handler_guarded,
					is_mesh_guarded
				};

				//pushback player (if he isnt in the actor list yet)
				if (!player_pawns.empty()) {
					auto found_player = std::find(player_pawns.begin(), player_pawns.end(), this_player);
					if (found_player == player_pawns.end())
					{
						player_pawns.push_back(this_player);
					}


				}
				else
				{
					player_pawns.push_back(this_player);
				}

			}
			Sleep(500);
		}
	}

#define DegreeToRadian( Degree )	( ( Degree ) * ( M_PI / 180.0f ) )



	static fvector pRadar;

	std::string get_fname(int key)
	{
		UINT chunkOffset = (UINT)((int)(key) >> 16);
		USHORT nameOffset = (USHORT)key;
		std::uint64_t namePoolChunk = lexemveread<std::uint64_t>((std::uintptr_t)(mem::lexemvefind_image() + 0xA4B9B80 + ((chunkOffset + 2) * 8)));
		std::uint64_t entryOffset = namePoolChunk + (ULONG)(4 * nameOffset);
		FNameEntry nameEntry = lexemveread<FNameEntry>(entryOffset);

		auto name = nameEntry.AnsiName; //just ansiname fuck widename
		std::uintptr_t nameKey = lexemveread2<uintptr_t>(lexemvevirtualaddy + 0x0);

		for (std::uint16_t i = 0; i < nameEntry.Header.Len; i++)
		{
			BYTE b = i & 3;
			name[i] ^= nameEntry.Header.Len ^ *((LPBYTE)&nameKey + b);
		}

		return name;
	}


	Vector2 WorldRadar(fvector srcPos, fvector distPos, float yaw, float radarX, float radarY, float size)
	{
		auto cosYaw = cos(DegreeToRadian(yaw));
		auto sinYaw = sin(DegreeToRadian(yaw));

		auto deltaX = srcPos.x - distPos.x;
		auto deltaY = srcPos.y - distPos.y;

		auto locationX = (float)(deltaY * cosYaw - deltaX * sinYaw) / 45.f;
		auto locationY = (float)(deltaX * cosYaw + deltaY * sinYaw) / 45.f;

		if (locationX > (size - 2.f))
			locationX = (size - 2.f);
		else if (locationX < -(size - 2.f))
			locationX = -(size - 2.f);

		if (locationY > (size - 6.f))
			locationY = (size - 6.f);
		else if (locationY < -(size - 6.f))
			locationY = -(size - 6.f);

		return Vector2((int)(-locationX + radarX), (int)(locationY + radarY));
	}
	void DrawRadar(fvector EntityPos)
	{
		auto radar_posX = pRadar.x + 135;
		auto radar_posY = pRadar.y + 135;
		uint64_t LocalRootComp = lexemveread2<uint64_t>(LAPNT::local_pawn + 0x238);
		fvector LocalPos = lexemveread<fvector>(LocalRootComp + 0x164);
		auto Radar2D = WorldRadar(LocalPos, EntityPos, LACAMRA::rotation.y, radar_posX, radar_posY, 135.f);
		ImVec4 S4 = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
		DrawCircleRadar(Radar2D.x, Radar2D.y, 4, S4); //R1);
	}

	auto LATMID(uintptr_t APawn) -> int {
		auto PlayerState = lexemveread<uintptr_t>(APawn + 0x3F8);//offset
		auto TeamComponent = lexemveread<uintptr_t>(PlayerState + 0x630);//offset
		return lexemveread<int>(TeamComponent + 0xF8);//offset
	};

	void LAPTLARE()
	{
		auto ViewInfo = lexemveread<FMinimalViewInfo>(LAPNT::camera_manager + 0x1FB0);
		LACAMRA::location = ViewInfo.Location;
		LACAMRA::rotation = ViewInfo.Rotation;
		LACAMRA::fov = ViewInfo.FOV;
	}

	void DrawFilledRect(int x, int y, int w, int h, RGBA* color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 153.0, color->B / 51.0, color->A / 255.0)), 0, 0);
	}

	auto DrawHealthBar(fvector RootPositionn, float Width, float Height, float Health, float RelativeDistance) -> void
	{
		auto HPBoxWidth = 1 / RelativeDistance;

		auto HPBox_X = RootPositionn.x - Width / 2 - 5 - HPBoxWidth;
		auto HPBox_Y = RootPositionn.y - Height / 2 + (Height - Height * (Health / 100));

		int HPBoxHeight = Height * (Health / 100);

		if (Health >= 80)
		{
			DrawFilledRect(HPBox_X, HPBox_Y, HPBoxWidth, HPBoxHeight, &Col.green);
		}
		else
		{
			if (Health <= 80 && Health >= 50)
			{
				DrawFilledRect(HPBox_X, HPBox_Y, HPBoxWidth, HPBoxHeight, &Col.yellow);
			}

			if (Health <= 50 && Health >= 30)
			{
				DrawFilledRect(HPBox_X, HPBox_Y, HPBoxWidth, HPBoxHeight, &Col.orange);
			}

			if (Health <= 30)
			{
				DrawFilledRect(HPBox_X, HPBox_Y, HPBoxWidth, HPBoxHeight, &Col.red);
			}
		}

		DrawRect(HPBox_X - 1, HPBox_Y - 1, HPBoxWidth + 2, HPBoxHeight + 2, &Col.black, 1);
	}

	auto Draw2DBox(fvector RootPositionn, float Width, float Height, ImColor Color) -> void
	{
		DrawNormalBox(RootPositionn.x - Width / 2, RootPositionn.y - Height / 2, Width, Height, 0.7f, Color);
	}

	auto RelativeLocation(uintptr_t APawn) -> fvector {
		auto RootComponent = lexemveread<uintptr_t>(APawn + 0x238);
		return lexemveread<fvector>(RootComponent + 0x164);
	}

	auto DrawLine(const ImVec2& x, const ImVec2 y, ImU32 color, const FLOAT width) -> void
	{
		ImGui::GetOverlayDrawList()->AddLine(x, y, color, width);
	}

	void DrawCircleFilled(int x, int y, int radius, ImVec4 color, float segments)
	{
		ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(color), segments);
	}

	auto draw_health_bar(ImVec2 min, ImVec2 max, float health) -> void
	{
		float health_percentage = health;
		health_percentage *= 0.01f;

		float lenght_left_to_right = max.x - min.x;
		lenght_left_to_right *= health_percentage;

		float healthbar_size_y = 5.f;

		float g = health_percentage * 255.f;
		float r = 255.f - g;
		float b = 0.f;

		r /= 255.f;
		g /= 255.f;
		b /= 255.f;

		//background
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(min.x, min.y - healthbar_size_y), ImVec2(max.x, max.y), ImGui::GetColorU32({ 0.1f, 0.1f, 0.1f, 1.f }), 0.f, 15);

		//health bar
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(min.x, min.y - healthbar_size_y), ImVec2(min.x + lenght_left_to_right, max.y), ImGui::GetColorU32({ r, g, b, 1.f }), 0.f, 15);

		//outline
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(min.x, min.y - healthbar_size_y), ImVec2(max.x, max.y), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), 0.f, 15, 1.f);
	}

	void DrawFilledBox(float x, float y, float w, float h, ImColor color) {
#define M_PI 3.14159265358979323846f
		ImDrawList* DrawList = ImGui::GetOverlayDrawList();
		ImVec2 a = ImVec2(x, y);
		ImVec2 b = ImVec2(x + w, y + h);

		// Saydamlık ayarı
		ImU32 transparentColor = IM_COL32(ImColor(color).Value.x, ImColor(color).Value.y, ImColor(color).Value.z, 80); // 100 alpha değeri

		DrawList->AddRectFilled(a, b, transparentColor);

		ImDrawCornerFlags rounding_corners = ImDrawCornerFlags_All;
		float Rounding = 6.0f;

		Rounding = std::min<float>(Rounding, fabsf(w) * (((rounding_corners & ImDrawCornerFlags_Top) == ImDrawCornerFlags_Top) || ((rounding_corners & ImDrawCornerFlags_Bot) == ImDrawCornerFlags_Bot) ? 0.5f : 1.0f) - 1.0f);
		Rounding = std::min<float>(Rounding, fabsf(h) * (((rounding_corners & ImDrawCornerFlags_Left) == ImDrawCornerFlags_Left) || ((rounding_corners & ImDrawCornerFlags_Right) == ImDrawCornerFlags_Right) ? 0.5f : 1.0f) - 1.0f);

		if (Rounding <= 0.0f || rounding_corners == 0) {
			DrawList->AddRectFilled(a, b, transparentColor);
		}
		else {
			DrawList->PathArcTo(ImVec2(a.x + Rounding, a.y + Rounding), Rounding, M_PI, M_PI / 2.f * 3.f, 12);
			DrawList->PathArcTo(ImVec2(b.x - Rounding, a.y + Rounding), Rounding, M_PI / 2.f * 3.f, M_PI * 2.f, 12);
			DrawList->PathArcTo(ImVec2(b.x - Rounding, b.y - Rounding), Rounding, 0.f, M_PI / 2.f, 12);
			DrawList->PathArcTo(ImVec2(a.x + Rounding, b.y - Rounding), Rounding, M_PI / 2.f, M_PI, 12);
			DrawList->PathFillConvex(transparentColor);
		}
	}

	float LACALDISTNC(int p1x, int p1y, int p2x, int p2y)
	{
		float diffY = p1y - p2y;
		float diffX = p1x - p2x;
		return sqrt((diffY * diffY) + (diffX * diffX));
	}

	fvector bone, head, chest, pelvis;

	void LARNDRPLYRSS()
	{
		LAPTLARE();
		auto isFrames = ImGui::GetFrameCount();

		static float isRed = 0.0f, isGreen = 0.01f, isBlue = 0.0f;

		ImVec4 isRGB = ImVec4(isRed, isGreen, isBlue, 1.0f);


		if (isFrames % 1 == 0)
		{

			if (isGreen == 0.01f && isBlue == 0.0f)
			{
				isRed += 0.01f;

			}

			if (isRed > 0.99f && isBlue == 0.0f)
			{
				isRed = 1.0f;

				isGreen += 0.01f;

			}

			if (isGreen > 0.99f && isBlue == 0.0f)
			{
				isGreen = 1.0f;

				isRed -= 0.01f;

			}

			if (isRed < 0.01f && isGreen == 1.0f)
			{
				isRed = 0.0f;

				isBlue += 0.01f;

			}

			if (isBlue > 0.99f && isRed == 0.0f)
			{
				isBlue = 1.0f;

				isGreen -= 0.01f;

			}

			if (isGreen < 0.01f && isBlue == 1.0f)
			{
				isGreen = 0.0f;

				isRed += 0.01f;

			}

			if (isRed > 0.99f && isGreen == 0.0f)
			{
				isRed = 1.0f;

				isBlue -= 0.01f;

			}

			if (isBlue < 0.01f && isGreen == 0.0f)
			{
				isBlue = 0.0f;

				isRed -= 0.01f;

				if (isRed < 0.01f)
					isGreen = 0.01f;

			}

		}

		int closestplayer = 1337;
		float closest_distance = FLT_MAX;

		for (int x = 0; x < player_pawns.size(); x++)
		{
			LAPLYR this_player = player_pawns[x];

			if (player_pawns.empty()) {
				return;
			}

			float health = 0;
			health = lexemveread<float>(this_player.damage_handler + 0x1B0);

			if (health <= 0.f || health > 999.f)
			{
				player_pawns[x].is_valid = false;
			}

			if (!this_player.is_valid)
			{
				auto erase_player = std::find(player_pawns.begin(), player_pawns.end(), this_player);
				player_pawns.erase(erase_player);
				continue;
			}

			fvector zero = LABNMTRX(0, this_player);
			fvector head = LABNMTRX(8, this_player);

			fvector zero_r = fvector(zero.x, zero.y, zero.z - 5);

			fvector vBaseBoneOut = w2s(fvector(zero.x, zero.y, zero.z));
			fvector vBaseBoneOut2 = w2s(fvector(zero.x, zero.y, zero.z - 15));

			fvector vHeadBoneOut = w2s(fvector(head.x, head.y, head.z));

			fvector vHeadBoneOut2 = w2s(fvector(head.x, head.y, head.z + 15));
			fvector vHeadBoneOut3 = w2s(fvector(head.x, head.y, head.z + 40));

			float BoxHeight = abs(vHeadBoneOut2.y - vBaseBoneOut.y);
			float BoxWidth = BoxHeight * 0.55;
			float BoxWidth3 = BoxHeight * 0.40;

			fvector head_r = fvector(head.x, head.y, head.z + 20);
			fvector head_r_2 = fvector(head.x, head.y, head.z + 30);

			fvector zero_w2s = w2s(zero);
			fvector head_w2s = w2s(head);

			fvector zero_w2s_r = w2s(zero_r);
			fvector head_w2s_r = w2s(head_r);

			fvector head_w2s_r_2 = w2s(head_r_2);

			struct FLinearColor {
				float R; // 0x00(0x04)
				float G; // 0x04(0x04)
				float B; // 0x08(0x04)
				float A; // 0x0c(0x04)
			};

			int Width = GetSystemMetrics(SM_CXSCREEN);
			int Height = GetSystemMetrics(SM_CYSCREEN);

			pRadar.x = (Width / 2) + 550;
			pRadar.y = Width / 2 - Height / 2 - 300;

			auto RelativeLocationn = RelativeLocation(this_player.actor);
			auto RelativePosition = RelativeLocationn - LACAMRA::location;
			auto RelativeDistance = RelativePosition.Length() / 10000 * 2;
			auto RelativeLocationProjected = w2s(RelativeLocationn);

			bool dormant_check_bool = is_dormant(this_player);
			if (!dormant_check_bool)continue;

			float distance = LACAMRA::location.distance(zero) / 100.f;

			if (config.distancecontrol && (float)config.max_distance < distance)
				continue;

			if (config.circlehead == true)
			{
				ImGui::GetOverlayDrawList()->AddCircle(ImVec2(vHeadBoneOut.x, vHeadBoneOut.y), BoxWidth / 7, ImColor(config.headboxcolor), 64, 1.5f);
			}

			if (config.glow)
				lxmvwrte<float>(this_player.actor + 0x6f0, 300);

			int bottom_text_offset = 2;

			ImGuiIO& io = ImGui::GetIO();
			ImFont* espfont = io.Fonts->AddFontFromFileTTF("C:\Windows\Fonts\Calibri.ttf", 14);
			ImGui::PushFont(espfont);
			ImGui::PopFont();

			if (config.player_healthbar)
			{
				DrawHealthBar(RelativeLocationProjected, BoxWidth, BoxHeight, health, RelativeDistance);
			}

			ImVec4 S4 = to_vec4(2, 160, 115, (int)Alpha);
			//ImVec4 S4 = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

			if (config.radar)
			{
				ImGui::GetOverlayDrawList()->AddRect(ImVec2(pRadar.x, pRadar.y), ImVec2(pRadar.x + 270, pRadar.y + 270), ImGui::ColorConvertFloat4ToU32(ImVec4(255, 255, 255, 255)), 2);
				auto radar_posX = pRadar.x + 135;
				auto radar_posY = pRadar.y + 135;
				DrawLine(ImVec2(radar_posX, radar_posY), ImVec2(radar_posX, radar_posY + 135), ImGui::ColorConvertFloat4ToU32(ImVec4(236, 236, 236, 255)), 2);
				DrawLine(ImVec2(radar_posX, radar_posY), ImVec2(radar_posX, radar_posY - 135), ImGui::ColorConvertFloat4ToU32(ImVec4(236, 236, 236, 255)), 2);
				DrawLine(ImVec2(radar_posX, radar_posY), ImVec2(radar_posX + 135, radar_posY), ImGui::ColorConvertFloat4ToU32(ImVec4(236, 236, 236, 255)), 2);
				DrawLine(ImVec2(radar_posX, radar_posY), ImVec2(radar_posX - 135, radar_posY), ImGui::ColorConvertFloat4ToU32(ImVec4(236, 236, 236, 255)), 2);
				DrawCircleFilled(radar_posX + 1, radar_posY + 1, 3, S4, 10);

				fvector pos = lexemveread<fvector>(this_player.root_component + 0x164);
				DrawRadar(pos);
			}

			if (config.player_box)
			{
				if (config.esptype == 0)
				{
					float BoxHeight = zero_w2s_r.y - head_w2s_r.y;
					float BoxWidth = BoxHeight / 2.f;
					LAPDRWCRNbx(zero_w2s_r.x - (BoxWidth / 2), head_w2s_r.y, BoxWidth, BoxHeight, config.espcolor, 0.6f);
				}

				if (config.esptype == 1)
				{
					DrawNormalBox(zero_w2s.x - (BoxWidth / 2), vHeadBoneOut2.y, BoxWidth, BoxHeight, 2.0f, config.espcolor);
				}

				if (config.esptype == 2)
				{
					LAdrw3dbx(zero, fvector(head.x, head.y, head.z + 20), 38, config.espcolor, 0.7f);
				}
			}

			if (config.glow)
				lxmvwrte<float>(this_player.actor + 0x6f0, 300);

			if (config.player_skeleton)
			{
				LADRWSKLTN(this_player, ImVec4(config.skeleton), 0.3f);
			}

			if (config.player_distance)
			{
				char distance_text[256];
				sprintf_s(distance_text, "[ %.fm ]", distance);
				ImVec2 text_size = ImGui::CalcTextSize(distance_text);
				ImGui::GetOverlayDrawList()->AddText(ImVec2(zero_w2s_r.x - (text_size.x / 2), zero_w2s_r.y + bottom_text_offset), config.distance, distance_text);
				bottom_text_offset += 14;
			}

			if (config.player_snapline)
			{
				if (config.linetype == 0)
				{
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(LAcenter_x, Height * 2), ImVec2(zero_w2s_r.x, zero_w2s_r.y + bottom_text_offset), config.snapcolor, 1.f);
				}

				if (config.linetype == 1)
				{
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(LAcenter_x, LAcenter_y), ImVec2(zero_w2s_r.x, zero_w2s_r.y + bottom_text_offset), config.snapcolor, 1.f);
				}

				if (config.linetype == 2)
				{
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(LAcenter_x, LAcenter_y / 2), ImVec2(zero_w2s_r.x, zero_w2s_r.y + bottom_text_offset), config.snapcolor, 1.f);
				}
			}

			if (config.agentnames == true)
			{

				int keyy = lexemveread<int>(this_player.actor + 0x18);
				std::string namee = get_fname(keyy);


				if (namee.find("None") != std::string::npos)
				{
					namee = "Lobi";
				}

				if (namee.find("Wushu") != std::string::npos)
				{
					namee = "Jett";
				}

				if (namee.find("Rift") != std::string::npos)
				{
					namee = "Astra";
				}

				if (namee.find("Grenadier") != std::string::npos)
				{
					namee = "Kay/O";
				}

				if (namee.find("Breach") != std::string::npos)
				{
					namee = "Breach";
				}

				if (namee.find("Sarge") != std::string::npos)
				{
					namee = "Brimstone";
				}

				if (namee.find("Deadeye") != std::string::npos)
				{
					namee = "Chamber";
				}

				if (namee.find("Gumshoe") != std::string::npos)
				{
					namee = "Cypher";
				}

				if (namee.find("Killjoy") != std::string::npos)
				{
					namee = "Killjoy";
				}

				if (namee.find("Sprinter") != std::string::npos)
				{
					namee = "Neon";
				}

				if (namee.find("Wraith") != std::string::npos)
				{
					namee = "Omen";
				}

				if (namee.find("Phoenix") != std::string::npos)
				{
					namee = "Phoenix";
				}

				if (namee.find("Clay") != std::string::npos)
				{
					namee = "Raze";
				}

				if (namee.find("Vampire") != std::string::npos)
				{
					namee = "Reyna";
				}

				if (namee.find("Thorne") != std::string::npos)
				{
					namee = "Sage";
				}

				if (namee.find("Guide") != std::string::npos)
				{
					namee = "Skye";
				}

				if (namee.find("Hunter_PC_C") != std::string::npos)
				{
					namee = "Sova";
				}

				if (namee.find("Pandemic") != std::string::npos)
				{
					namee = "Viper";
				}

				if (namee.find("Stealth") != std::string::npos)
				{
					namee = "Yoru";
				}

				if (namee.find("BountyHunter") != std::string::npos)
				{
					namee = "Fade";
				}

				if (namee.find("TrainingBot") != std::string::npos)
				{
					namee = "Bot";
				}

				if (namee.find("AggroBot") != std::string::npos)
				{
					namee = "Gekko";
				}

				if (namee.find("Mage") != std::string::npos)
				{
					namee = "Harbor";
				}

				if (namee.find("Cable") != std::string::npos)
				{
					namee = "Deadlock";
				}

				namee = namee;
				ImVec2 TextSize2 = ImGui::CalcTextSize(namee.c_str());

				ImGui::GetOverlayDrawList()->AddText(ImVec2(vHeadBoneOut3.x - (TextSize2.x / 2), vHeadBoneOut3.y + bottom_text_offset), ImGui::GetColorU32({ 0.3f, 0.7f, 1.f, 1.f }), namee.c_str());
				bottom_text_offset += 14;
			}

			if (config.player_view_angle)
			{
				fvector view_angle = lexemveread<fvector>(this_player.root_component + 0x170);

				fvector test2, headpos;

				headpos = head;

				LApangrtn(view_angle, &test2);
				test2.x *= 260;
				test2.y *= 260;
				test2.z *= 260;

				fvector end = headpos + test2;
				fvector test1, test3;
				test1 = w2s(headpos);
				test3 = w2s(end);

				ImGui::GetOverlayDrawList()->AddLine(ImVec2(test1.x, test1.y), ImVec2(test3.x, test3.y), ImGui::GetColorU32({ 0.0f, 1.0f, 0.0f, 1.0f }), 1.f);
				ImGui::GetOverlayDrawList()->AddCircle(ImVec2(test3.x, test3.y), BoxWidth / 7, ImGui::GetColorU32({ 0.33f, 0.33f, 0.33f, 1.f }), 32, 2.f);
			}

			float delta_x = head_w2s.x - (LAWidth / 2.f);
			float delta_y = head_w2s.y - (LAHeight / 2.f);
			float dist = sqrtf(delta_x * delta_x + delta_y * delta_y);
			float fovdist = LACALDISTNC(LAWidth / 2, LAHeight / 2, head_w2s.x, head_w2s.y);
			if ((dist < closest_distance) && fovdist < config.aimbot_fov) {
				closest_distance = dist;
				closestplayer = x;
			}

		}

		if (config.aimenable && closestplayer != 1337)
		{
			LAPLYR LAthsplyer = player_pawns[closestplayer];
			fvector LAhed = LABNMTRX(8, LAthsplyer);
			fvector LAbody = LABNMTRX(7, LAthsplyer);
			fvector LAplvs = LABNMTRX(5, LAthsplyer);
			fvector LAbne;

			if (config.aimboness == 0)
			{
				LAbne = LAhed;
			}

			if (config.aimboness == 1)
			{
				LAbne = LAbody;
			}

			if (config.aimboness == 2)
			{
				LAbne = LAplvs;
			}

			fvector rootpos = lexemveread<fvector>(LAthsplyer.root_component + 0x164);

			if (LAbne.z <= rootpos.z)
			{
				return;
			}

			fvector localView = lexemveread<fvector>(LAPNT::player_controller + 0x448);
			fvector vecCaclculatedAngles = cLAmpasdp205(LACAMRA::location, LAbne);
			fvector angleEx = LAPSNNANGLE(LACAMRA::location, LAbne);
			fvector fin = fvector(vecCaclculatedAngles.y, angleEx.y, 0);
			fvector delta = fin - localView;
			LAPNRMLZEANGL(delta);

			fvector TargetAngle = localView + (delta / config.aimbot_smooth);
			fvector TargetAngle2 = localView + delta;
			LAPNRMLZEANGL(TargetAngle);
			LAPNRMLZEANGL(TargetAngle2);

			if (GetAsyncKeyState(aim_key) & 0x8000)
			{
				if (config.visiblecheck == true)
				{
					if (VsblesA)
					{
						lxmvwrte<fvector>(LAPNT::player_controller + 0x448, TargetAngle);

					}
				}
				else
				{
					lxmvwrte<fvector>(LAPNT::player_controller + 0x448, TargetAngle);

				}

			}
		}

		if (config.aimbot_draw_fov)
		{
			ImGui::GetOverlayDrawList()->AddCircle(ImVec2(LAcenter_x, LAcenter_y), config.aimbot_fov, config.fov), 64, 2.f;
		}


	}

	void LARNNDDDRR() {

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (GetAsyncKeyState(VK_INSERT) & 1)
			LAMNPON = !LAMNPON;
		valthe();
		if (LAMNPON)
		{
			ImGui::GetIO().MouseDrawCursor = 1;
			if (ImGui::Begin("Private Script", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize))
			{
				bubble();
			}ImGui::End();
		}
		else
			ImGui::GetIO().MouseDrawCursor = 0;

		LARNDRPLYRSS();

		D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
		D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

		if (D3dDevice->BeginScene() >= 0) {
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			D3dDevice->EndScene();
		}
		HRESULT LARSLT = D3dDevice->Present(NULL, NULL, NULL, NULL);

		if (LARSLT == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
			ImGui_ImplDX9_InvalidateDeviceObjects();
			D3dDevice->Reset(&d3dpp);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
	}

	RECT rc;

	static void SetWindowToTarget()
	{
		RECT GameRect;
		while (1)
		{
			HWND XGameWnd = FindWindowA(0, _("VALORANT  ")); // D3D11TEST / VALORANT  
			if (XGameWnd)
			{
				ZeroMemory(&GameRect, sizeof(GameRect));
				GetWindowRect(XGameWnd, &GameRect);
				DWORD dwStyle = GetWindowLong(XGameWnd, GWL_STYLE);
				MoveWindow(LAWNDWWW, GameRect.left, GameRect.top, LAWidth, LAHeight, true);
			}
			Sleep(5);
		}
	}

	LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
			return true;

		switch (Message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			exit(4);
			break;
		case WM_SIZE:
			if (D3dDevice != NULL && wParam != SIZE_MINIMIZED)
			{
				ImGui_ImplDX9_InvalidateDeviceObjects();
				d3dpp.BackBufferWidth = LOWORD(lParam);
				d3dpp.BackBufferHeight = HIWORD(lParam);
				HRESULT hr = D3dDevice->Reset(&d3dpp);
				if (hr == D3DERR_INVALIDCALL)
					IM_ASSERT(0);
				ImGui_ImplDX9_CreateDeviceObjects();
			}
			break;
		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);
			break;
		}
		return 0;
	}

	void LACRTWND0W() {
		WNDCLASSEXA wc;

		MSG Msg;
		HINSTANCE hInstance = 0;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WinProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = (HINSTANCE)hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(RGB(0, 0, 0));
		wc.lpszMenuName = NULL;
		wc.lpszClassName = "Private Script";
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		RegisterClassExA(&wc);

		if (LAHND)
		{
			GetClientRect(LAHND, &LAGMRCT);
			POINT LAXXYY;
			ClientToScreen(LAHND, &LAXXYY);
			LAGMRCT.left = LAXXYY.x;
			LAGMRCT.top = LAXXYY.y;

			LAWidth = LAGMRCT.right;
			LAHeight = LAGMRCT.bottom;
		}
		else
			exit(0);

		LAWNDWWW = CreateWindowExW(NULL, L"Private Script", L"Private Script", 0x80000000L | 0x10000000L, 2, 2, LAWidth - 1, LAHeight - 1, 0, 0, 0, 0);
		SetWindowLong(LAWNDWWW, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
		SetLayeredWindowAttributes(LAWNDWWW, RGB(0, 0, 0), 255, LWA_ALPHA);
		MARGINS Margin = { -1 };
		DwmExtendFrameIntoClientArea(LAWNDWWW, &Margin);
		ShowWindow(LAWNDWWW, SW_SHOW);
		UpdateWindow(LAWNDWWW);
	}

	void LARNDRLPP() {
		static RECT old_rc;
		ZeroMemory(&LAMSSG, sizeof(MSG));

		while (LAMSSG.message != WM_QUIT)
		{
			if (PeekMessage(&LAMSSG, LAWNDWWW, 0, 0, 0x0001))
			{
				TranslateMessage(&LAMSSG);
				DispatchMessage(&LAMSSG);
			}

			HWND hwnd_active = GetForegroundWindow();

			if (hwnd_active == LAHND) {
				HWND hwndtest = GetWindow(hwnd_active, 3);
				SetWindowPos(LAWNDWWW, hwndtest, 2, 2, -3, -3, 0x0002 | 0x0001);
			}

			POINT xy;

			ZeroMemory(&rc, sizeof(RECT));
			ZeroMemory(&xy, sizeof(POINT));
			GetClientRect(LAHND, &rc);
			ClientToScreen(LAHND, &xy);
			rc.left = xy.x;
			rc.top = xy.y;

			ImGuiIO& io = ImGui::GetIO();
			io.ImeWindowHandle = LAHND;
			io.DeltaTime = 1.0f / 60.0f;

			POINT p;
			GetCursorPos(&p);
			io.MousePos.x = p.x - xy.x;
			io.MousePos.y = p.y - xy.y;

			if (GetAsyncKeyState(VK_LBUTTON)) {
				io.MouseDown[0] = true;
				io.MouseClicked[0] = true;
				io.MouseClickedPos[0].x = io.MousePos.x;
				io.MouseClickedPos[0].x = io.MousePos.y;
			}
			else
				io.MouseDown[0] = false;

			if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
			{
				old_rc = rc;

				LAWidth = rc.right;
				LAHeight = rc.bottom;

				d3dpp.BackBufferWidth = LAWidth;
				d3dpp.BackBufferHeight = LAHeight;
				SetWindowPos(LAWNDWWW, (HWND)0, xy.x + 2, xy.y + 2, LAWidth - 3, LAHeight - 3, 0x0008);
				D3dDevice->Reset(&d3dpp);
			}

			LARNNDDDRR();

		}
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		DestroyWindow(LAWNDWWW);
	}

	void LASTPRNDR() {
		TriBuf->Release();
		D3dDevice->Release();
		p_Object->Release();

		UnregisterClassW(L"Private Script", NULL);
	}

	bool LASTRTDRX() {

		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);

		if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
			return false;

		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.BackBufferWidth = LAWidth;
		d3dpp.BackBufferHeight = LAHeight;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.hDeviceWindow = LAWNDWWW;
		d3dpp.Windowed = TRUE;

		p_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, LAWNDWWW, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3dDevice);

		IMGUI_CHECKVERSION();

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();


		ImGui_ImplWin32_Init(LAWNDWWW);
		ImGui_ImplDX9_Init(D3dDevice);

		p_Object->Release();

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)qweqweqweqweqwe, NULL, NULL, NULL);

		LARNDRLPP();
		LASTPRNDR();
		return true;
	}

	void LASTRTC() {
		LAHND = FindWindowA(0, _("VALORANT  "));

		LACRTWND0W();

		LASTRTDRX();
	}
}
