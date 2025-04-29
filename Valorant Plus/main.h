
#define M_PI (double)3.1415926535
#define actor_player 4
static bool silentaimm = false;
static bool writehealth = false;
static bool ammowarning = false;
static int customwarning = 1;
static bool showammo = false;
static bool radar = false;
static bool showname = true;

static bool legitt = false;
static bool legitcheck = false;
bool genderesp = false;
bool fovchanger = false;


int AimKeyList[] = { VK_LBUTTON , VK_RBUTTON , VK_MBUTTON , VK_MENU , VK_CONTROL , VK_SHIFT , VK_XBUTTON1, VK_XBUTTON2 };

const char* optKey[] = { "Left Click", "Right Click", "MClick", "Alt", "Ctrl", "Shift", "Mouse Button 4", "Mouse Button 5" };

const char* aimbone[] = { "Head", "Pelvis", "Body" }; //0,1,2 = bone number

const char* colors2[] = { "Red", "Black", "Cyan", "Green", "Rainbow" };

const char* radart[] = { "Square", "Circle" };

const char* type[] = { "Corner",  "2D", "3D" };

const char* aimtype[] = { "Legit Settings",  "Rage Settings" };

const char* linetype[] = { "Bottom",  "Center", "Top" };

static int keyint = 0;
static int colorint = 0;


static int aim_key = -1;

static bool recoilcontrol = false;



std::vector<const char*> config_files = { "legit.ini", "rage.ini", "special.ini" };
int selected_config_file = 0;

std::string file_path = "C:\\PrivateScript\\" + std::string(config_files[selected_config_file]);
struct Config {

	INT aimbotkey;
	// Aimbot settings
	bool aimenable = false;
	bool visiblecheck = false;
	bool circlehead = false;
	bool distancecontrol = false;
	bool rcs = false;
	bool aimbot_constant = false;
	bool aimbot_mode_silent = false;
	bool aimbot_draw_fov = false;
	bool aimbot_draw_target_line = false;
	bool aimbot_ignore_with_useless_weapons = false;
	float aimbot_fov = 20.f;
	float aimbot_smooth = 10.f;
	float amcnstoff = 0.f;
	float silent_fov = 1.f;
	float silent_smooth = 1.f;
	float fovchangervalue = 100.f;
	float legit_smooth = 5.f;
	int max_distance = 5;

	// ESP settings
	bool player_box = false;
	bool player_box_3d = false;
	bool player_skeleton = false;
	bool player_snapline = false;
	bool player_view_angle = false;
	bool player_distance = false;
	bool player_healthbar = false;
	bool player_agent = false;
	bool radar;
	bool player_weapon = false;
	bool glow = false;
	bool fovchanger = false;
	bool player_ignore_dormant = false;
	bool agentnames = false;
	bool spiketimer = false;
	int aimboness = 0;
	int bonees = 0;
	int aimtype = 0;
	int linetype = 0;

	int esptype = 0;

	ImColor headboxcolor = ImColor(255, 0, 0, 255);
	ImColor espcolor = ImColor(0, 255, 0, 255);
	ImColor snapcolor = { 255,255,255,255 }; // snapline renk
	ImColor distance = { 255,255,255,255 }; // snapline renk
	ImVec4 skeleton = { 1.0f, 0.3f, 0.7f, 1.0f }; // skeleton renk
	ImColor fov = ImColor(255, 255, 255, 255);
};

// Sample usage
Config config;
ImVec4 to_vec4(float r, float g, float b, float a)
{
	return ImVec4(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
}

INT legitkey;
INT legitbone;
INT silentKey;
INT silentbone;


bool VsblesA;

float silent_smooth = 5.f;



DWORD_PTR LocalPawn;
uintptr_t playerstate;
uintptr_t teamComponent;
int teamID;
uintptr_t world;
uintptr_t game_instance;
uintptr_t persistent_level;
uintptr_t local_player;
INT32 actor_count;

int customX;
int customY;

//typedef PVOID(*name)();

uintptr_t base;


typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;

class Color
{
public:
	RGBA moi_blue = { 0, 143, 209,255 };
	RGBA moi_red = { 241,34,34,255 };
	RGBA moi_green = { 0,209,91,255 };

	RGBA red = { 255,0,0,255 };
	RGBA Magenta = { 255,0,255,255 };
	RGBA yellow = { 255,255,0,255 };
	RGBA grayblue = { 128,128,255,255 };
	RGBA green = { 128,224,0,255 };
	RGBA darkgreen2 = { 26, 128, 0, 255 };
	RGBA darkgreen3 = { 6, 68, 0, 255 };
	RGBA darkgreen = { 0,224,128,255 };
	RGBA brown = { 192,96,0,255 };
	RGBA pink = { 255,168,255,255 };
	RGBA DarkYellow = { 216,216,0,255 };
	RGBA SilverWhite = { 236,236,236,255 };
	RGBA purple = { 144,0,255,255 };
	RGBA Navy = { 88,48,224,255 };
	RGBA skyblue = { 0,136,255,255 };
	RGBA graygreen = { 128,160,128,255 };
	RGBA blue = { 0,96,192,255 };

	RGBA orange = { 255,128,0,255 };
	RGBA peachred = { 255,80,128,255 };
	RGBA reds = { 255,128,192,255 };
	RGBA darkgray = { 96,96,96,255 };
	RGBA Navys = { 0,0,128,255 };
	RGBA darkgreens = { 0,128,0,255 };
	RGBA darkblue = { 0,128,128,255 };
	RGBA redbrown = { 128,0,0,255 };
	RGBA red4 = { 255, 24, 101, 255 };
	RGBA purplered = { 128,0,128,255 };
	RGBA greens = { 0,255,0,255 };
	RGBA envy = { 0,255,255,255 };
	RGBA black = { 0,0,0,255 };
	RGBA gray = { 128,128,128,255 };
	RGBA white = { 255,255,255,255 };
	RGBA blues = { 30,144,255,255 };
	RGBA lightblue = { 135,206,250,160 };
	RGBA Scarlet = { 220, 20, 60, 160 };
	RGBA white_ = { 255,255,255,200 };
	RGBA gray_ = { 128,128,128,200 };
	RGBA black_ = { 0,0,0,200 };
	RGBA red_ = { 255,0,0,200 };
	RGBA Magenta_ = { 255, 95, 96, 255 };
	RGBA yellow_ = { 255,255,0,200 };
	RGBA grayblue_ = { 128,128,255,200 };
	RGBA green_ = { 128,224,0,200 };
	RGBA darkgreen_ = { 0,224,128,200 };
	RGBA brown_ = { 192,96,0,200 };
	RGBA pink_ = { 255,168,255,200 };
	RGBA darkyellow_ = { 216,216,0,200 };
	RGBA silverwhite_ = { 236,236,236,200 };
	RGBA purple_ = { 144,0,255,200 };
	RGBA Blue_ = { 88,48,224,200 };
	RGBA skyblue_ = { 0,136,255,200 };
	RGBA graygreen_ = { 128,160,128,200 };
	RGBA blue_ = { 0,96,192,180 };
	RGBA orange_ = { 255,128,0,200 };
	RGBA orange2_ = { 255,100,0,180 };
	RGBA pinks_ = { 255,80,128,200 };
	RGBA Fuhong_ = { 255,128,192,200 };
	RGBA darkgray_ = { 96,96,96,200 };
	RGBA Navy_ = { 0,0,128,200 };
	RGBA darkgreens_ = { 0,128,0,200 };
	RGBA darkblue_ = { 0,128,128,200 };
	RGBA redbrown_ = { 128,0,0,200 };
	RGBA purplered_ = { 128,0,128,200 };
	RGBA greens_ = { 0,255,0,200 };
	RGBA envy_ = { 0,255,255,200 };

	RGBA glassblack = { 0, 0, 0, 180 };
	RGBA GlassBlue = { 65,105,225,80 };
	RGBA glassyellow = { 255,255,0,160 };
	RGBA glass = { 200,200,200,60 };


	RGBA Plum = { 221,160,221,160 };

};
Color Col;

class FLinearColor {
public:
	FLinearColor() : red(0.f), green(0.f), blue(0.f), alpha(0.f) {}
	FLinearColor(float red, float green, float blue, float alpha) : red(red), green(green), blue(blue), alpha(alpha) {}

public:
	float red;
	float green;
	float blue;
	float alpha;
};


inline auto DrawLineNew(int x1, int y1, int x2, int y2, RGBA* color, int thickness) -> void
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
}

static auto DrawRect(int x, int y, int w, int h, RGBA* color, int thickness) -> void
{
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0, thickness);
}

inline auto DrawFilledRect2(float x, float y, float w, float h, ImColor color) -> void
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, NULL, NULL);
}

inline auto DrawFilledRect3(int x, int y, int w, int h, RGBA* color) -> void
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0);
}

inline auto DrawFilledRect4(float x, float y, float w, float h, ImColor color) -> void
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, NULL, NULL);
}

inline auto DrawBorder(float x, float y, float w, float h, float px, RGBA* BorderColor) -> void
{
	DrawRect(x, (y + h - px), w, px, BorderColor, 1 / 2);
	DrawRect(x, y, px, h, BorderColor, 1 / 2);
	DrawRect(x, y, w, px, BorderColor, 1 / 2);
	DrawRect((x + w - px), y, px, h, BorderColor, 1 / 2);
}


void DrawCircleRadar(int x, int y, int radius, ImVec4 color)
{
	ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(color));
}
inline auto DrawCircleFilled2(int x, int y, int radius, RGBA* color) -> void
{
	ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
}

static float Alpha = 255;


ImVec4 R1 = to_vec4(3, 168, 245, (int)Alpha);
ImVec4 Renk5 = to_vec4(153, 176, 189, 255);


bool TracesB = false;
void vmdedect();

bool IsProcessRunning(const TCHAR* const executableName) {
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (!Process32First(snapshot, &entry)) {
		CloseHandle(snapshot);
		return false;
	}

	do {
		if (!_tcsicmp(entry.szExeFile, executableName)) {
			CloseHandle(snapshot);
			return true;
		}
	} while (Process32Next(snapshot, &entry));

	CloseHandle(snapshot);
	return false;
}

void detect(std::string msg)
{
	if (TracesB)
	{
		std::ofstream Trace01;
		Trace01.open("C:\\Program Files\\Win32Log.txt");
		Trace01 << "windows";
		Trace01.close();
	}
	std::ofstream outfile("Error.txt");
	outfile << "Detected: " + msg << std::endl;
	outfile.close();
	exit(1337);
}