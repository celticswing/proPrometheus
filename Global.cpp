#include "SDK.h"

bool				G::Aimbotting;
bool				G::InAntiAim;
bool				G::Return;
HWND				G::Window;
bool				G::PressedKeys[256] = {};
char				G::AnimatedClantag[16];
float				G::FOV;
int					G::ChamMode = -1;
bool				G::SendPacket = true;
int					G::BestTarget = -1;
char				G::buf3[128];
char				G::extra_flags;
bool                G::d3dinit = false;
float				G::hitmarkeralpha;
bool                G::unload;
WNDPROC             G::OldWindow = nullptr;
using msg_t = void(__cdecl*)(const char*, ...);
msg_t				G::Msg = reinterpret_cast< msg_t >(GetProcAddress(GetModuleHandleA("tier0.dll"), "Msg"));





namespace Global
{
	std::vector<ColorP>ColorsForPicker1;
}