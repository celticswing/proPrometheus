#pragma once
#include "HookIncludes.h"
#include "Interfaces.h"
#include <ctime>
#include "ESP.h"
#include "Listener.h"

std::vector<const char*> vistasmoke_mats =
{
	"particle/vistasmokev1/vistasmokev1_fire",
	"particle/vistasmokev1/vistasmokev1_smokegrenade",
	"particle/vistasmokev1/vistasmokev1_emods",
	"particle/vistasmokev1/vistasmokev1_emods_impactdust",
};

typedef void(__thiscall* paint_traverse_t)(PVOID, unsigned int, bool, bool);
bool once = true;
bool once1 = false;
int width1 = 0;
int height1 = 0;

void __fastcall hkPaintTraverse(PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	int w, h;
	int centerW, centerh, topH;
	g_Engine->GetScreenSize(w, h);
	centerW = w / 2;

	static auto ofunc = hooks::panel.get_original<paint_traverse_t>(41);
	C_BaseEntity* local = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
	if (local != nullptr && local->IsAlive() && g_Options.Visuals.noscopeborder && g_Options.Visuals.Enabled && !strcmp("HudZoom", g_Panel->GetName(vguiPanel)))
	{
		return;
	}
	ofunc(pPanels, vguiPanel, forceRepaint, allowForce);
	static unsigned int FocusOverlayPanel = 0;
	static bool FoundPanel = false;
	if (!FoundPanel)
	{
		PCHAR szPanelName = (PCHAR)g_Panel->GetName(vguiPanel);
		if (strstr(szPanelName, "FocusOverlayPanel"))
		{
			FocusOverlayPanel = vguiPanel;
			FoundPanel = true;
		}
	}
	else if (FocusOverlayPanel == vguiPanel)
	{
	
		if (g_Engine->IsConnected() && g_Engine->IsInGame())
		{
			

			static auto linegoesthrusmoke = U::FindPattern("client.dll", (PBYTE)"\x55\x8B\xEC\x83\xEC\x08\x8B\x15\x00\x00\x00\x00\x0F\x57\xC0", "xxxxxxxx????xxx");
			static auto smokecout = *(DWORD*)(linegoesthrusmoke + 0x8);
			switch (g_Options.Visuals.Smoke)
			{
			case 0:
				for (auto mat_s : vistasmoke_mats)
				{
					IMaterial* mat = g_MaterialSystem->FindMaterial(mat_s, TEXTURE_GROUP_OTHER);
					mat->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
				}
				break;
			case 1:
				for (auto mat_s : vistasmoke_mats)
				{
					IMaterial* mat = g_MaterialSystem->FindMaterial(mat_s, TEXTURE_GROUP_OTHER);
					mat->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
				}
				*(int*)(smokecout) = 0;
				break;
			case 2:
				*(int*)(smokecout) = 0;
				break;
			default:
				break;
			}
			Color color(int(g_Options.Colors.ScopeLine[0] * 255.f), int(g_Options.Colors.ScopeLine[1] * 255.f), int(g_Options.Colors.ScopeLine[2] * 255.f));
			visuals::instance().OnPaintTraverse(local);
			damage_indicators.paint();

			auto m_flFlashDuration = NetVarManager->GetOffset("DT_CSPlayer", "m_flFlashDuration");
			auto m_flFlashMaxAlpha = NetVarManager->GetOffset("DT_CSPlayer", "m_flFlashMaxAlpha");
			if (local != nullptr )
			{
				CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(local->GetActiveWeaponHandle());
				if (g_Options.Visuals.NoFlash && g_Options.Visuals.Enabled)
				{
					*MakePtr(float*, local, m_flFlashDuration) = 0.f;
					*MakePtr(float*, local, m_flFlashMaxAlpha) = 0.f;
				}
				if (local && local->IsScoped() && g_Options.Visuals.noscopeborder && MiscFunctions::IsSniper(pWeapon) && g_Options.Visuals.Enabled)
				{
					int width = 0;
					int height = 0;
					g_Engine->GetScreenSize(width, height);

					int centerX = static_cast<int>(width * 0.5f);
					int centerY = static_cast<int>(height * 0.5f);
					g_Render->Line(0, centerY, width, centerY, color);
					g_Render->Line(centerX, 0, centerX, height, color);
				}

			}
	
		}
		if (!g_Engine->IsInGame()) {
			g_Options.Misc.namePrometheus = false;
			g_Options.Misc.spammeron = false;


		}

		if (g_Options.Ragebot.MainSwitch && !once)
		{
//			g_Options.LegitBot.Enable = false;
			once = !once;
		}
		if (g_Options.LegitBot.Enable && once)
		{
//			g_Options.Ragebot.MainSwitch = false;
			once = !once;
		}

		if (g_Options.Misc.Watermark)
		{
			static float rainbow;
			rainbow += 0.005f;
			if (rainbow > 1.f) rainbow = 0.f;

			if (g_Engine->IsInGame() && g_Engine->IsConnected())
			{
				static int u = 0;
				if (u <= 100)                 g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "          T          ");
				if (u > 100 && u <= 200)      g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "         ETH         ");
				if (u > 200 && u <= 300)      g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "        E T H        ");
				if (u > 300 && u <= 400)      g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "       ME T HE       ");
				if (u > 400 && u <= 500)      g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "      M E T H E      ");
				if (u > 500 && u <= 600)      g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "     OM E T H E.     ");
				if (u > 600 && u <= 700)      g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "    O M E T H E .    ");
				if (u > 700 && u <= 800)      g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "   RO M E T H E .U   ");
				if (u > 800 && u <= 900)      g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "  R O M E T H E . U  ");
				if (u > 900 && u <= 1000)     g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, " PR O M E T H E . US ");
				if (u > 1000 && u <= 1100)    g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "P R O M E T H E . U S");
				if (u > 1100 && u <= 1200)    g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "  R O M E T H E . U  ");;
				if (u > 1200 && u <= 1300)    g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "   RO M E T H E .U   ");
				if (u > 1300 && u <= 1400)    g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "    O M E T H E .    ");
				if (u > 1400 && u <= 1500)    g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "     OM E T H E.     ");
				if (u > 1500 && u <= 1600)    g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "      M E T H E      ");
				if (u > 1600 && u <= 1700)    g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "       ME T HE       ");
				if (u > 1700 && u <= 1800)    g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "        E T H        ");
				if (u > 1800 && u <= 1900)    g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "         ETH         ");
				u += 2.5;
				if (u > 1900) u = 0;
			}
			else // I do an else because of fps being < 1000 and it would look really weird
			{
				g_Render->Textf(centerW - 65, 15, Color::FromHSB(rainbow, 1.f, 1.f), g_Render->font.Watermark, "P R O M E T H E . U S");
			}
		}
			
		if (!g_Options.Misc.antiuntrusted)
		{
			g_Render->Text(10, 10, Color(255, 10, 10, 255), g_Render->font.Watermark, "ANTI-UNTRUSTED IS DISABLED");
			g_Render->Text(10, 25, Color(255, 10, 10, 255), g_Render->font.Watermark, "YOU WILL GET BANNED FOR JOINING A MATCH (OFFLINE & ONLINE)");
			g_Render->Text(10, 40, Color(255, 10, 10, 255), g_Render->font.Watermark, "DO NOT JOIN A MATCH/SERVER");
		}

		if (g_Options.Visuals.Enabled)
		{
			int width = 0;
			int height = 0;
			g_Engine->GetScreenSize(width, height);
	
			if (g_Engine->IsInGame() && g_Engine->IsConnected())
			{
				if (local->IsAlive())
				{
					if (g_Options.Visuals.RageDraw)
					{
						g_Render->Textf(1, 50, Color(255, 0, 0, 255), g_Render->font.ESP, "Shots Fired: %i", Globals::Shots);
						g_Render->Textf(1, 70, Color(255, 0, 0, 255), g_Render->font.ESP, "Missed Shots: %i", Globals::missedshots);
						g_Render->Textf(1, 90, Color(255, 0, 0, 255), g_Render->font.ESP, "Tick Base: %f", Globals::NextTime);
					}
					if (g_Options.Visuals.LBYIndicator)
					{
						if (local->GetEyeAngles()->y - local->GetLowerBodyYaw() > 35)
						{
							g_Render->Textf(10, height / 2, Color(0, 255, 0, 255), g_Render->font.LBY, "LBY");
						}
						else
						{
							g_Render->Textf(10, height / 2, Color(255, 0, 0, 255), g_Render->font.LBY, "LBY");
						}
					}
				}
			}
		}
	}
}
