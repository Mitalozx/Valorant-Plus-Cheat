#include "sdk/theme.h"
#include "sdk/xor.h"
#include <random>

std::string RandomString(size_t length = 0)
{
	static const std::string allowed_chars{ "0123456789abcdefghjklmnoprstuvqyzA" };

	static thread_local std::default_random_engine randomEngine(std::random_device{}());
	static thread_local std::uniform_int_distribution<int> randomDistribution(0, allowed_chars.size() - 1);

	std::string id(length ? length : 32, '\0');

	for (std::string::value_type& c : id) {
		c = allowed_chars[randomDistribution(randomEngine)];
	}

	return id;
}

std::string randomoverlay = RandomString(20);
std::wstring temp = std::wstring(randomoverlay.begin(), randomoverlay.end());
LPCWSTR overlayString = temp.c_str();

auto Vsbles(DWORD_PTR mesh) -> bool
{
	float fLastSubmitTime = lexemveread<float>(mesh + 0x378);
	float fLastRenderTimeOnScreen = lexemveread<float>(mesh + 0x37C);

	const float fVisionTick = 0.06f;
	bool bVisible = fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;

	return bVisible;
}

uintptr_t LApactr;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

struct State {
	uintptr_t LApkys[7];
};

bool vis;

int LAcenter_x = GetSystemMetrics(0) / 2 - 3;
int LAcenter_y = GetSystemMetrics(1) / 2 - 3;

float LAWidth, LAHeight = 0.f;
class fvector {
public:
	fvector() : x(0.f), y(0.f), z(0.f) {}
	fvector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	~fvector() {}

	float x;
	float y;
	float z;

	inline float Dot(fvector v) {
		return x * v.x + y * v.y + z * v.z;
	}

	inline float distance(fvector v) {
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	fvector operator+(fvector v) {
		return fvector(x + v.x, y + v.y, z + v.z);
	}

	fvector operator-(fvector v) {
		return fvector(x - v.x, y - v.y, z - v.z);
	}
	fvector operator/(float flDiv) {
		return fvector(x / flDiv, y / flDiv, z / flDiv);
	}

	fvector operator*(float Scale) {

		return fvector(x * Scale, y * Scale, z * Scale);
	}
	inline float Length() {
		return sqrtf((x * x) + (y * y) + (z * z));
	}
	fvector operator-=(fvector v) {

		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
};

struct Vector2 {
public:
	float x;
	float y;

	inline Vector2() : x(0), y(0) {}
	inline Vector2(float x, float y) : x(x), y(y) {}

	inline float Distance(Vector2 v) {
		return sqrtf(((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y)));
	}

	inline Vector2 operator+(const Vector2& v) const {
		return Vector2(x + v.x, y + v.y);
	}

	inline Vector2 operator-(const Vector2& v) const {
		return Vector2(x - v.x, y - v.y);
	}
};

struct fquat {
	float x;
	float y;
	float z;
	float w;
};

struct ftransform {
	fquat rot;
	fvector translation;
	char pad[4];
	fvector scale;
	char pad1[4];
	D3DMATRIX ToMatrixWithScale() {
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};
fvector cntrlrttn;
namespace LAmth
{
	D3DMATRIX matrix(fvector rot, fvector origin = fvector(0, 0, 0)) {
		float radPitch = (rot.x * float(M_PI) / 180.f);
		float radYaw = (rot.y * float(M_PI) / 180.f);
		float radRoll = (rot.z * float(M_PI) / 180.f);

		float SP = sinf(radPitch);
		float CP = cosf(radPitch);
		float SY = sinf(radYaw);
		float CY = cosf(radYaw);
		float SR = sinf(radRoll);
		float CR = cosf(radRoll);

		D3DMATRIX matrix;
		matrix.m[0][0] = CP * CY;
		matrix.m[0][1] = CP * SY;
		matrix.m[0][2] = SP;
		matrix.m[0][3] = 0.f;

		matrix.m[1][0] = SR * SP * CY - CR * SY;
		matrix.m[1][1] = SR * SP * SY + CR * CY;
		matrix.m[1][2] = -SR * CP;
		matrix.m[1][3] = 0.f;

		matrix.m[2][0] = -(CR * SP * CY + SR * SY);
		matrix.m[2][1] = CY * SR - CR * SP * SY;
		matrix.m[2][2] = CR * CP;
		matrix.m[2][3] = 0.f;

		matrix.m[3][0] = origin.x;
		matrix.m[3][1] = origin.y;
		matrix.m[3][2] = origin.z;
		matrix.m[3][3] = 1.f;

		return matrix;
	}

	D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
	{
		D3DMATRIX pOut;
		pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
		pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
		pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
		pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
		pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
		pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
		pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
		pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
		pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
		pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
		pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
		pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
		pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
		pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
		pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
		pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

		return pOut;
	}
}

struct FMinimalViewInfo {
	struct fvector Location;
	struct fvector Rotation;
	float FOV;
};

namespace LACAMRA
{
	fvector location;
	fvector rotation;
	float fov;
}

namespace LAGRDPNT
{
	uintptr_t guard_local_pawn = 0x0;
	uintptr_t guard_controller = 0x0;
}

namespace LAPNT
{
	uintptr_t local_pawn;
	uintptr_t local_pawn_old;
	uintptr_t player_controller;
	uintptr_t camera_manager;
	fvector camera_position;
}

struct FNameEntryHandle {
	uint16_t bIsWide : 1;
	uint16_t Len : 15;
};

struct FNameEntry {

	int32_t ComparisonId;
	FNameEntryHandle Header;
	union
	{
		char    AnsiName[1024]; // ANSICHAR
		wchar_t    WideName[1024]; // WIDECHAR
	};


	wchar_t const* GetWideName() const { return WideName; }
	char const* GetAnsiName() const { return AnsiName; }
	bool IsWide() const { return Header.bIsWide; }
};

struct LAPLYR
{
	uintptr_t for_actor;
	uintptr_t for_mesh;

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

std::vector<LAPLYR> player_pawns;

inline bool operator==(const LAPLYR& a, const LAPLYR& b) {
	if (a.actor == b.actor)
		return true;

	return false;
}

float lexemveread_visible(LAPLYR _player, int num)
{
	return lexemveread<float>(_player.for_mesh + _player.mesh + num);
}

bool isVisible(LAPLYR _player) {

	int i = 848;

	float v1 = lexemveread_visible(_player, i);
	i += 0x8;
	float v2 = lexemveread_visible(_player, i);

	float difference = v1 - v2;
	if (difference < 0.f)
	{
		difference *= -1;
	}

	if (difference < 0.01f)
		return true;

	return false;
}

void LAPLAMP(fvector& Ang) {
	if (Ang.x < 0.f)
		Ang.x += 360.f;

	if (Ang.x > 360.f)
		Ang.x -= 360.f;

	if (Ang.y < 0.f) Ang.y += 360.f;
	if (Ang.y > 360.f) Ang.y -= 360.f;
	Ang.z = 0.f;
}

bool is_dormant(LAPLYR _player)
{
	return lexemveread<bool>(_player.for_actor + _player.actor + 0x100);
}

fvector w2s(fvector world_location) {
	fvector ScreenLocation;
	D3DMATRIX tempMatrix = LAmth::matrix(LACAMRA::rotation, fvector(0, 0, 0));
	fvector vAxisX, vAxisY, vAxisZ;
	vAxisX = fvector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = fvector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = fvector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
	fvector vDelta = world_location - LACAMRA::location;
	fvector vTransformed = fvector(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
	if (vTransformed.z < .1f)
		vTransformed.z = .1f;

	float ScreenCenterX = LAcenter_x;
	float ScreenCenterY = LAcenter_y;

	ScreenLocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(LACAMRA::fov * (float)M_PI / 360.f)) / vTransformed.z;
	ScreenLocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(LACAMRA::fov * (float)M_PI / 360.f)) / vTransformed.z;
	return ScreenLocation;
}

float CalculateDistance(int p1x, int p1y, int p2x, int p2y)
{
	float diffY = p1y - p2y;
	float diffX = p1x - p2x;
	return sqrt((diffY * diffY) + (diffX * diffX));
}

void LAPNRMLZE(fvector& in)
{
	if (in.x > 89.f) in.x -= 360.f;
	else if (in.x < -89.f) in.x += 360.f;

	while (in.y > 180)in.y -= 360;
	while (in.y < -180)in.y += 360;
	in.z = 0;
}

void rndforambt()
{
	while (true)
	{
		config.amcnstoff = 15.f;
		std::this_thread::sleep_for(std::chrono::milliseconds(200000));

		config.amcnstoff = 2.f;
		std::this_thread::sleep_for(std::chrono::milliseconds(200000));

		config.amcnstoff = 8.f;
		std::this_thread::sleep_for(std::chrono::milliseconds(200000));

		config.amcnstoff = 20.f;
		std::this_thread::sleep_for(std::chrono::milliseconds(200000));

		config.amcnstoff = 4.f;
		std::this_thread::sleep_for(std::chrono::milliseconds(200000));

		config.amcnstoff = 12.f;
		std::this_thread::sleep_for(std::chrono::milliseconds(200000));
	}
}

void LAPNRMLZEANGL(fvector& angle)
{
	while (angle.x > 89.0f)
		angle.x -= 180.f;

	while (angle.x < -89.0f)
		angle.x += 180.f;

	while (angle.y > 180.f)
		angle.y -= 360.f;

	while (angle.y < -180.f)
		angle.y += 360.f;
}

void Clamp(fvector& Ang) {
	if (Ang.x < 0.f)
		Ang.x += 360.f;

	if (Ang.x > 360.f)
		Ang.x -= 360.f;

	if (Ang.y < 0.f) Ang.y += 360.f;
	if (Ang.y > 360.f) Ang.y -= 360.f;
	Ang.z = 0.f;
}

float GetFov(const fvector viewAngle, const fvector aimAngle)
{
	fvector Delta = fvector(aimAngle.x - viewAngle.x, aimAngle.y - viewAngle.y, aimAngle.z - viewAngle.z);
	LAPNRMLZEANGL(Delta);
	return sqrt(pow(Delta.x, 2.0f) + pow(Delta.y, 2.0f));
}

fvector LAPSMTHAM(fvector Camera_rotation, fvector Target, float SmoothFactor)
{
	fvector diff = Target - Camera_rotation;
	LAPNRMLZE(diff);
	return Camera_rotation + diff / SmoothFactor;
}

float LAPTDGRTRDN(float degree)
{
	return degree * (M_PI / 180);
}


fvector fhgfsdhkfshdghfsd205(fvector src, fvector dst)
{
	fvector angle;
	angle.x = -atan2f(dst.x - src.x, dst.y - src.y) / M_PI * 180.0f + 180.0f;
	angle.y = asinf((dst.z - src.z) / src.distance(dst)) * 180.0f / M_PI;
	angle.z = 0.0f;

	return angle;
}

fvector CaadadalcAngle(fvector src, fvector dst)
{
	fvector angle;
	fvector delta = fvector((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));

	double hyp = sqrtf(delta.x * delta.x + delta.y * delta.y);

	angle.x = atanf(delta.z / hyp) * (180.0f / hyp);
	angle.y = atanf(delta.y / delta.x) * (180.0f / M_PI);
	angle.z = 0;
	if (delta.x >= 0.0) angle.y += 180.0f;

	return angle;
}


void LApangrtn(const fvector& angles, fvector* forward)
{
	float	sp, sy, cp, cy;

	sy = sin(LAPTDGRTRDN(angles.y));
	cy = cos(LAPTDGRTRDN(angles.y));

	sp = sin(LAPTDGRTRDN(angles.x));
	cp = cos(LAPTDGRTRDN(angles.x));

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}


fvector LABNMTRX(int index, LAPLYR _player)
{
	size_t size = sizeof(ftransform);
	ftransform first_bone, comp_to_world;

	first_bone = lexemveread<ftransform>(_player.bone_array + (0x30 * index));//0x5D8
	comp_to_world = lexemveread<ftransform>(_player.mesh + 0x250);

	D3DMATRIX matrix = LAmth::MatrixMultiplication(first_bone.ToMatrixWithScale(), comp_to_world.ToMatrixWithScale());
	return fvector(matrix._41, matrix._42, matrix._43);
}

void LADRWHLTHBR(ImVec2 min, ImVec2 max, float health, float outline_thickness)
{
	float health_percentage = health;
	health_percentage *= 0.01f;

	float length_left_to_right = max.x - min.x;
	length_left_to_right *= health_percentage;

	float healthbar_size_y = 5.f;

	float g = health_percentage * 255.f;
	float r = 255.f - g;
	float b = 0.f;

	r /= 255.f;
	g /= 255.f;
	b /= 255.f;

	// background
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(min.x, min.y - healthbar_size_y), ImVec2(max.x, max.y), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), 0.f, 15);

	// health bar
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(min.x, min.y - healthbar_size_y), ImVec2(min.x + length_left_to_right, max.y), ImGui::GetColorU32({ r, g, b, 1.f }), 0.f, 15);

	// outline
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(min.x, min.y - healthbar_size_y), ImVec2(max.x, max.y), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), 0.f, 15, outline_thickness);
}



void RCS(fvector Target, fvector Camera_rotation, float SmoothFactor) {


	fvector ConvertRotation = Camera_rotation;
	LAPNRMLZE(ConvertRotation);

	auto ControlRotation = lexemveread<fvector>(LAPNT::player_controller + 0x448);
	fvector DeltaRotation = ConvertRotation - ControlRotation;
	LAPNRMLZE(DeltaRotation);


	ConvertRotation = Target - (DeltaRotation * SmoothFactor);
	LAPNRMLZE(ConvertRotation);

	fvector Smoothed = LAPSMTHAM(Camera_rotation, ConvertRotation, SmoothFactor);
	Smoothed -= (DeltaRotation / SmoothFactor);
	LAPLAMP(Smoothed);
	LAPNRMLZE(Smoothed);
	lxmvwrte<fvector>(LAPNT::player_controller + 0x448, (fvector)Smoothed);
	return;
}

void LAPRccS(fvector Target, fvector Camera_rotation, float SmoothFactor) {


	fvector ConvertRotation = Camera_rotation;
	LAPNRMLZE(ConvertRotation);

	auto ControlRotation = lexemveread<fvector>(LAPNT::player_controller + 0x440);
	fvector DeltaRotation = ConvertRotation - ControlRotation;
	LAPNRMLZE(DeltaRotation);


	ConvertRotation = Target - (DeltaRotation * SmoothFactor);
	LAPNRMLZE(ConvertRotation);

	fvector Smoothed = LAPSMTHAM(Camera_rotation, ConvertRotation, SmoothFactor);
	Smoothed -= (DeltaRotation / SmoothFactor);
	LAPLAMP(Smoothed);
	LAPNRMLZE(Smoothed);
	lxmvwrte<fvector>(LAPNT::player_controller + 0x440, (fvector)Smoothed);
	return;
}

void LAdrw3dbx(fvector base, fvector top_reach, float wide, ImVec4 col, float thickness)
{


	fvector bottom_rect_1 = fvector(base.x + wide, base.y + wide, base.z);
	fvector bottom_rect_2 = fvector(base.x + wide, base.y - wide, base.z);
	fvector bottom_rect_3 = fvector(base.x - wide, base.y + wide, base.z);
	fvector bottom_rect_4 = fvector(base.x - wide, base.y - wide, base.z);


	fvector top_rect_1 = fvector(top_reach.x + wide, top_reach.y + wide, top_reach.z);
	fvector top_rect_2 = fvector(top_reach.x + wide, top_reach.y - wide, top_reach.z);
	fvector top_rect_3 = fvector(top_reach.x - wide, top_reach.y + wide, top_reach.z);
	fvector top_rect_4 = fvector(top_reach.x - wide, top_reach.y - wide, top_reach.z);


	bottom_rect_1 = w2s(bottom_rect_1);
	bottom_rect_2 = w2s(bottom_rect_2);
	bottom_rect_3 = w2s(bottom_rect_3);
	bottom_rect_4 = w2s(bottom_rect_4);


	top_rect_1 = w2s(top_rect_1);
	top_rect_2 = w2s(top_rect_2);
	top_rect_3 = w2s(top_rect_3);
	top_rect_4 = w2s(top_rect_4);


	ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_1.x, bottom_rect_1.y), ImVec2(bottom_rect_2.x, bottom_rect_2.y), config.espcolor, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_2.x, bottom_rect_2.y), ImVec2(bottom_rect_4.x, bottom_rect_4.y), config.espcolor, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_4.x, bottom_rect_4.y), ImVec2(bottom_rect_3.x, bottom_rect_3.y), config.espcolor, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_3.x, bottom_rect_3.y), ImVec2(bottom_rect_1.x, bottom_rect_1.y), config.espcolor, thickness);

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(top_rect_1.x, top_rect_1.y), ImVec2(top_rect_2.x, top_rect_2.y), config.espcolor, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(top_rect_2.x, top_rect_2.y), ImVec2(top_rect_4.x, top_rect_4.y), config.espcolor, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(top_rect_4.x, top_rect_4.y), ImVec2(top_rect_3.x, top_rect_3.y), config.espcolor, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(top_rect_3.x, top_rect_3.y), ImVec2(top_rect_1.x, top_rect_1.y), config.espcolor, thickness);

	//render connection lines
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_1.x, bottom_rect_1.y), ImVec2(top_rect_1.x, top_rect_1.y), config.espcolor, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_2.x, bottom_rect_2.y), ImVec2(top_rect_2.x, top_rect_2.y), config.espcolor, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_3.x, bottom_rect_3.y), ImVec2(top_rect_3.x, top_rect_3.y), config.espcolor, thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(bottom_rect_4.x, bottom_rect_4.y), ImVec2(top_rect_4.x, top_rect_4.y), config.espcolor, thickness);
}

void DrawFilledRect2(int x, int y, int w, int h, ImColor color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0.0f);
}


void DrawNormalBox(int x, int y, int w, int h, int borderPx, ImColor color)
{
	DrawFilledRect2(x + borderPx, y, w, borderPx, color);
	DrawFilledRect2(x + w - w + borderPx, y, w, borderPx, color);
	DrawFilledRect2(x, y, borderPx, h, color);
	DrawFilledRect2(x, y + h - h + borderPx * 2, borderPx, h, color);
	DrawFilledRect2(x + borderPx, y + h + borderPx, w, borderPx, color);
	DrawFilledRect2(x + w - w + borderPx, y + h + borderPx, w, borderPx, color);
	DrawFilledRect2(x + w + borderPx, y, borderPx, h, color);
	DrawFilledRect2(x + w + borderPx, y + h - h + borderPx * 2, borderPx, h, color);
}

fvector cLAmpasdp205(fvector src, fvector dst)
{
	fvector angle;
	angle.x = -atan2f(dst.x - src.x, dst.y - src.y) / M_PI * 180.0f + 180.0f;
	angle.y = asinf((dst.z - src.z) / src.distance(dst)) * 180.0f / M_PI;
	angle.z = 0.0f;

	return angle;
}

fvector LAPSNNANGLE(fvector src, fvector dst)
{
	fvector angle;
	fvector delta = fvector((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));

	double hyp = sqrtf(delta.x * delta.x + delta.y * delta.y);

	angle.x = atanf(delta.z / hyp) * (180.0f / hyp);
	angle.y = atanf(delta.y / delta.x) * (180.0f / M_PI);
	angle.z = 0;
	if (delta.x >= 0.0) angle.y += 180.0f;

	return angle;
}

void LAPDRWCRNbx(int X, int Y, int W, int H, const ImU32& color, int thickness)
{
	float lineW = (W / 3);
	float lineH = (H / 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}




void LADRWSKLTN(LAPLYR _player, ImVec4 col, float thickness)
{
	fvector bone_head, bone_neck, bone_chest, bone_pelvis, bone_rshoulder, bone_relbow, bone_rhand, bone_rthigh, bone_rknee, bone_rfoot, bone_lshoulder, bone_lelbow, bone_lhand, bone_lthigh, bone_lknee, bone_lfoot;
	bone_head = LABNMTRX(8, _player);
	bone_chest = LABNMTRX(6, _player);
	bone_pelvis = LABNMTRX(3, _player);


	if (_player.bone_count == 101) //female
	{
		bone_neck = LABNMTRX(21, _player);

		bone_lshoulder = LABNMTRX(23, _player);
		bone_lelbow = LABNMTRX(24, _player);
		bone_lhand = LABNMTRX(25, _player);

		bone_rshoulder = LABNMTRX(49, _player);
		bone_relbow = LABNMTRX(50, _player);
		bone_rhand = LABNMTRX(51, _player);

		bone_lthigh = LABNMTRX(75, _player);
		bone_lknee = LABNMTRX(76, _player);
		bone_lfoot = LABNMTRX(78, _player);

		bone_rthigh = LABNMTRX(82, _player);
		bone_rknee = LABNMTRX(83, _player);
		bone_rfoot = LABNMTRX(85, _player);
	}
	else if (_player.bone_count == 103) //npc
	{
		bone_neck = LABNMTRX(9, _player);

		bone_lshoulder = LABNMTRX(33, _player);
		bone_lelbow = LABNMTRX(30, _player);
		bone_lhand = LABNMTRX(32, _player);

		bone_rshoulder = LABNMTRX(58, _player);
		bone_relbow = LABNMTRX(55, _player);
		bone_rhand = LABNMTRX(57, _player);

		bone_lthigh = LABNMTRX(63, _player);
		bone_lknee = LABNMTRX(65, _player);
		bone_lfoot = LABNMTRX(69, _player);

		bone_rthigh = LABNMTRX(77, _player);
		bone_rknee = LABNMTRX(79, _player);
		bone_rfoot = LABNMTRX(83, _player);
	}
	else if (_player.bone_count == 104) //male
	{
		bone_neck = LABNMTRX(21, _player);

		bone_lshoulder = LABNMTRX(23, _player);
		bone_lelbow = LABNMTRX(24, _player);
		bone_lhand = LABNMTRX(25, _player);

		bone_rshoulder = LABNMTRX(49, _player);
		bone_relbow = LABNMTRX(50, _player);
		bone_rhand = LABNMTRX(51, _player);

		bone_lthigh = LABNMTRX(77, _player);
		bone_lknee = LABNMTRX(78, _player);
		bone_lfoot = LABNMTRX(80, _player);

		bone_rthigh = LABNMTRX(84, _player);
		bone_rknee = LABNMTRX(85, _player);
		bone_rfoot = LABNMTRX(87, _player);
	}


	bone_head = w2s(bone_head);
	bone_neck = w2s(bone_neck);
	bone_chest = w2s(bone_chest);
	bone_pelvis = w2s(bone_pelvis);
	bone_lshoulder = w2s(bone_lshoulder);
	bone_lelbow = w2s(bone_lelbow);
	bone_lhand = w2s(bone_lhand);
	bone_rshoulder = w2s(bone_rshoulder);
	bone_relbow = w2s(bone_relbow);
	bone_rhand = w2s(bone_rhand);
	bone_lthigh = w2s(bone_lthigh);
	bone_lknee = w2s(bone_lknee);
	bone_lfoot = w2s(bone_lfoot);
	bone_rthigh = w2s(bone_rthigh);
	bone_rknee = w2s(bone_rknee);
	bone_rfoot = w2s(bone_rfoot);

	ImDrawList* draw = ImGui::GetOverlayDrawList();

	//top stuff
	draw->AddLine(ImVec2(bone_head.x, bone_head.y), ImVec2(bone_neck.x, bone_neck.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
	draw->AddLine(ImVec2(bone_neck.x, bone_neck.y), ImVec2(bone_chest.x, bone_chest.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
	draw->AddLine(ImVec2(bone_chest.x, bone_chest.y), ImVec2(bone_pelvis.x, bone_pelvis.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);

	//right arm
	draw->AddLine(ImVec2(bone_chest.x, bone_chest.y), ImVec2(bone_rshoulder.x, bone_rshoulder.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
	draw->AddLine(ImVec2(bone_rshoulder.x, bone_rshoulder.y), ImVec2(bone_relbow.x, bone_relbow.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
	draw->AddLine(ImVec2(bone_relbow.x, bone_relbow.y), ImVec2(bone_rhand.x, bone_rhand.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);

	//left arm
	draw->AddLine(ImVec2(bone_chest.x, bone_chest.y), ImVec2(bone_lshoulder.x, bone_lshoulder.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
	draw->AddLine(ImVec2(bone_lshoulder.x, bone_lshoulder.y), ImVec2(bone_lelbow.x, bone_lelbow.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
	draw->AddLine(ImVec2(bone_lelbow.x, bone_lelbow.y), ImVec2(bone_lhand.x, bone_lhand.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);

	//right foot
	draw->AddLine(ImVec2(bone_pelvis.x, bone_pelvis.y), ImVec2(bone_rthigh.x, bone_rthigh.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
	draw->AddLine(ImVec2(bone_rthigh.x, bone_rthigh.y), ImVec2(bone_rknee.x, bone_rknee.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
	draw->AddLine(ImVec2(bone_rknee.x, bone_rknee.y), ImVec2(bone_rfoot.x, bone_rfoot.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);

	//left foot
	draw->AddLine(ImVec2(bone_pelvis.x, bone_pelvis.y), ImVec2(bone_lthigh.x, bone_lthigh.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
	draw->AddLine(ImVec2(bone_lthigh.x, bone_lthigh.y), ImVec2(bone_lknee.x, bone_lknee.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
	draw->AddLine(ImVec2(bone_lknee.x, bone_lknee.y), ImVec2(bone_lfoot.x, bone_lfoot.y), ImGui::GetColorU32({ col.x, col.y, col.z, col.w }), thickness);
}


static HWND LAWNDWWW = NULL;
IDirect3D9Ex* p_Object = NULL;
static LPDIRECT3DDEVICE9 D3dDevice = NULL;

static LPDIRECT3DVERTEXBUFFER9 TriBuf = NULL;
RECT LAGMRCT = { NULL };
D3DPRESENT_PARAMETERS d3dpp;
const MARGINS LAMRGNN = { -1 };

DWORD ScreenCenterX = 960;
DWORD ScreenCenterY = 540;
MSG LAMSSG = { NULL };

bool LAMNPON = true;
bool LAFRSTTM = true;

bool LAMGNSTRT = false;