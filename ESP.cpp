#include "ESP.h"
#include "Interfaces.h"
#include "Render.h"
#include <ctime>
#include <iostream>
#include <algorithm>
#include "GrenadePrediction.h"
#include "memoryfonts.h"
#include "LagComp.h"
#include "Autowall.h"
#include "Hooks.h"


namespace ColorAlpha
{
	VisualsStruct ESP_ctx;
	RECT bbox;
	float ESP_Fade[64];
}

visuals::visuals()
{
	BombCarrier = nullptr;
}


int width = 0;
int height = 0;
bool done = false;
float damage;
char bombdamagestringdead[24];
char bombdamagestringalive[24];

void visuals::OnPaintTraverse(C_BaseEntity* local)
{
	CViewSetup* g_ViewSetup;

	CInput::CUserCmd* pCmd;

	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(local->GetActiveWeaponHandle());

	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());

	Spoof(); // b1g Memory Leak
	NightMode();
	DoAsusWalls();
	renderBeams();
	SkyChanger();

	CCSGrenadeHint::instance().Paint();

	static class Text
	{
	public:
		std::string text;
		int side;
		int Font;
		Color color;

		Text(std::string text, int side, int Font, Color color) : text(text), side(side), Font(Font), color(color)
		{
		}
	};
	std::vector< Text > texts;
	if (local->IsAlive())
	{
		if (g_Options.Visuals.RecoilCrosshair && g_Options.Visuals.Enabled)
		{
			g_Engine->GetScreenSize(width, height);
			if (local && local->IsAlive())
			{

				static auto cl_crosshair_recoil = g_CVar->FindVar("cl_crosshair_recoil");


				static Vector ViewAngles;

				g_Engine->GetViewAngles(ViewAngles);
				ViewAngles += local->localPlayerExclusive()->GetAimPunchAngle() * 2.f;

				Vector fowardVec;
				AngleVectors(ViewAngles, &fowardVec);
				fowardVec *= 10000;

				Vector start = local->GetVecOrigin() + local->GetViewOffset();
				Vector end = start + fowardVec, endScreen;

				Color recoil_color(int(g_Options.Colors.color_recoil[0] * 255.f), int(g_Options.Colors.color_recoil[1] * 255.f), int(g_Options.Colors.color_recoil[2] * 255.f));
				if (g_Render->WorldToScreen(end, endScreen) && local->IsAlive())
				{
					switch (g_Options.Visuals.RecoilCrosshair2)
					{
					case 0:
						cl_crosshair_recoil->SetValue(0);
						break;
					case 1:
						g_Engine->ClientCmd_Unrestricted("crosshair 0");
						g_Render->Line(endScreen.x - 4, endScreen.y, endScreen.x + 4, endScreen.y, recoil_color);
						g_Render->Line(endScreen.x, endScreen.y - 4, endScreen.x, endScreen.y + 4, recoil_color);
						cl_crosshair_recoil->SetValue(0);
						break;
					case 2:
						g_Engine->ClientCmd_Unrestricted("crosshair 0");
						g_Render->OutlineCircle(endScreen.x, endScreen.y, 3, 50, recoil_color);
						cl_crosshair_recoil->SetValue(0);
						break;
					case 3:
						g_Engine->ClientCmd_Unrestricted("crosshair 1");
						cl_crosshair_recoil->SetValue(1);
						break;

					}
				}
			}
		}

		if (g_Options.Visuals.AWallCrosshair && g_Options.Visuals.Enabled)
		{
			RECT View = g_Render->GetViewport();
			int xs = View.right / 2;
			int ys = View.bottom / 2;

			int damage;

			if (MiscFunctions::IsKnife(pWeapon) || MiscFunctions::IsGrenade(pWeapon) || MiscFunctions::IsBomb(pWeapon))
			{
				g_Render->DrawFilledCircle2(xs, xs, 5, 50, Color(101, 101, 101, 170));
			}
			else if (MiscFunctions::IsSniper(pWeapon) && g_Options.Visuals.noscopeborder && local->IsScoped())
			{

			}
			else if (pWeapon->AWall())
			{
				g_Render->DrawFilledCircle2(xs, xs, 5, 50, CanWallbang(damage) ? Color(130, 241, 13) : Color(255, 102, 102));
			}
		}

		if (g_Options.Visuals.SpreadCrosshair && g_Options.Visuals.Enabled)
		{
			RECT View = g_Render->GetViewport();
			int xs = View.right / 2;
			int ys = View.bottom / 2;

			if (local && local->IsAlive())
			{
				auto accuracy = pWeapon->GetInaccuracy() * 550.f; //3000

				ColorAlpha::ESP_ctx.clr_fill.SetAlpha(g_Options.Visuals.spread_crosshair_amount * 255.f);

				Color color(int(g_Options.Colors.color_spread[0] * 255.f), int(g_Options.Colors.color_spread[1] * 255.f), int(g_Options.Colors.color_spread[2] * 255.f), g_Options.Visuals.spread_crosshair_amount);

				g_Render->DrawFilledCircle2(xs, ys, accuracy, 100, color);

			}

		}

		int W, H, cW, cH;
		g_Engine->GetScreenSize(W, H);
		cW = W / 2;
		cH = H / 2;

		if (g_Options.Visuals.SniperCrosshair && g_Options.Visuals.Enabled)
		{
			Color color(int(g_Options.Colors.color_sniper[0] * 255.f), int(g_Options.Colors.color_sniper[1] * 255.f), int(g_Options.Colors.color_sniper[2] * 255.f), 150);
			int damage;
			RECT View = g_Render->GetViewport();
			int pXs = View.right / 2;
			int pYs = View.bottom / 2;
			if (MiscFunctions::IsSniper(pWeapon))
			{
				switch (g_Options.Visuals.SniperCrosshairType)
				{

				case 1:
					g_Surface->DrawSetColor(color);
					g_Surface->DrawFilledRect(cW - 6, cH - 1, cW - 3 + 9, cH - 1 + 2);
					g_Surface->DrawFilledRect(cW - 1, cH - 6, cW - 1 + 2, cH - 3 + 9);
					break;
				case 2:
					if (CanWallbang(damage))
					{
						g_Surface->DrawSetColor(0, 255, 0, 150);
						g_Surface->DrawFilledRect(cW - 6, cH - 1, cW - 3 + 9, cH - 1 + 2);
						g_Surface->DrawFilledRect(cW - 1, cH - 6, cW - 1 + 2, cH - 3 + 9);
					}
					else
					{
						g_Surface->DrawSetColor(255, 0, 0, 150);
						g_Surface->DrawFilledRect(cW - 6, cH - 1, cW - 3 + 9, cH - 1 + 2);
						g_Surface->DrawFilledRect(cW - 1, cH - 6, cW - 1 + 2, cH - 3 + 9);
					}
					break;
				case 3:
					g_Render->Line(pXs - 10, pYs, pXs + 10, pYs, color);
					g_Render->Line(pXs, pYs - 10, pXs, pYs + 10, color);
					break;
				case 4:
					if (CanWallbang(damage))
					{
						g_Render->Line(pXs - 10, pYs, pXs + 10, pYs, Color(0, 255, 0));
						g_Render->Line(pXs, pYs - 10, pXs, pYs + 10, Color(0, 255, 0));
					}
					else
					{
						g_Render->Line(pXs - 10, pYs, pXs + 10, pYs, Color(255, 0, 0));
						g_Render->Line(pXs, pYs - 10, pXs, pYs + 10, Color(255, 0, 0));
					}
					break;
				}

			}
		}

		if (g_Options.Visuals.angleLines && g_Input->m_fCameraInThirdPerson)
		{
			DrawAngles();
		}

	}



	if (g_Options.Misc.Hitmarker)
		Hitmarker();

	Color pColor;
	for (int i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
	{

		C_BaseEntity *entity = g_EntityList->GetClientEntity(i);

		if (entity == nullptr)
			continue;
		if (entity == local)
			continue;
		if (entity->IsDormant())
			continue;

		

		player_info_t pinfo;
		Vector max = entity->GetCollideable()->OBBMaxs();
		Vector pos, pos3D;
		pos3D = entity->GetVecOrigin();

		if (g_Options.Visuals.OffscreenIndicator && entity->IsAlive())
		{
			auto pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());

			if (pLocal->GetTeamNum() != entity->GetTeamNum())
			{
				Vector eyeangles, poopvec;
				int screen_w, screen_h;
				g_Engine->GetScreenSize(screen_w, screen_h);
				g_Engine->GetViewAngles(eyeangles);
				Vector newangle = CalcAngle(Vector(pLocal->GetAbsOrigin3().x, pLocal->GetAbsOrigin3().y, 0), Vector(entity->GetAbsOrigin3().x, entity->GetAbsOrigin3().y, 0));
				AngleVectors(Vector(0, 270, 0) - newangle + Vector(0, eyeangles.y, 0), &poopvec);
				auto circlevec = Vector(screen_w / 2, screen_h / 2, 0) + (poopvec * 250.f);

				g_Render->DrawFilledCircle(Vector2D(circlevec.x, circlevec.y), Color(255, 0, 0, 100), g_Options.Visuals.OffscreenIndicatorSize, 50);
			}
		}

		int owner = 0;
		ClientClass* cClass = (ClientClass*)entity->GetClientClass();

		if (!g_Render->WorldToScreen(pos3D, pos))
			continue;


		if (g_Options.Visuals.DroppedGuns && g_Options.Visuals.Enabled &&  cClass->m_ClassID != (int)ClassID::CBaseWeaponWorldModel && ((strstr(cClass->m_pNetworkName, "Weapon") || cClass->m_ClassID == (int)ClassID::CDEagle || cClass->m_ClassID == (int)ClassID::CAK47)))
		{
			Color clr = Color(int(g_Options.Colors.droppedguns[0] * 255.f), int(g_Options.Colors.droppedguns[1] * 255.f), int(g_Options.Colors.droppedguns[2] * 255.f));

			RenderWeapon(entity, clr);
		}


		if (g_Options.Visuals.C4World && g_Options.Visuals.Enabled)
		{
			if (cClass->m_ClassID == (int)ClassID::CPlantedC4)
				DrawBombPlanted(entity, local);
		}
		if (cClass->m_ClassID == (int)ClassID::CC4)
		{
			DrawBomb(entity, cClass);
		}
		if (g_Options.Visuals.Hostage)
		{
			Color clr = Color(255, 255, 255);
			if (cClass->m_ClassID == (int)ClassID::CHostage || cClass->m_ClassID == (int)ClassID::CHostageCarriableProp)
			{
//				texts.push_back(Text("Hostage", 0, g_Render->font.ESP, Color(255, 255, 255, 255)));

				if (g_Options.Visuals.HostageBox)
				{
					ThreeDBox(entity->GetCollideable()->OBBMins(), entity->GetCollideable()->OBBMaxs(), entity->GetVecOrigin(), clr);
				}
			}
		}
		if (g_Options.Visuals.Chicken)
		{
			Color clr = Color(255, 255, 255);
			if (cClass->m_ClassID == (int)ClassID::CChicken)
			{
//				texts.push_back(Text("Chicken", 0, g_Render->font.ESP, Color(255, 255, 255, 255)));

				if (g_Options.Visuals.ChickenBox)
				{
					ThreeDBox(entity->GetCollideable()->OBBMins(), entity->GetCollideable()->OBBMaxs(), entity->GetVecOrigin(), clr);
				}
			}
		}
		if (g_Options.Visuals.Grenades && g_Options.Visuals.Enabled)
		{
			if (!g_Render->WorldToScreen(pos3D, pos))
				continue;

			Color GrenadeColor = Color(0, 0, 0, 0);
			char* szModelName = "Unknown Projectile";
			char* szModelIcon = "";
			if (strstr(cClass->m_pNetworkName, XorStr("Projectile")))
			{
				const model_t* pModel = entity->GetModel();
				if (!pModel)
					return;


				const studiohdr_t* pHdr = g_ModelInfo->GetStudiomodel(pModel);

				if (!pHdr)
					return;

				if (!strstr(pHdr->name, XorStr("thrown")) && !strstr(pHdr->name, XorStr("dropped")))
					return;


				IMaterial* mats[32];
				g_ModelInfo->GetModelMaterials(pModel, pHdr->numtextures, mats);

				for (int i = 0; i < pHdr->numtextures; i++)
				{
					IMaterial* mat = mats[i];
					if (!mat)
						continue;

					if (strstr(mat->GetName(), "flashbang"))
					{
						GrenadeColor = Color(255, 255, 0, 255);
						szModelName = "Flashbang";
						szModelIcon = "i";
					}
					else if (strstr(mat->GetName(), "m67_grenade") || strstr(mat->GetName(), "hegrenade"))
					{
						szModelName = "Grenade";
						szModelIcon = "j";
						GrenadeColor = Color(255, 0, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "smoke"))
					{
						szModelName = "Smoke";
						szModelIcon = "k";
						GrenadeColor = Color(0, 255, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "decoy"))
					{
						szModelName = "Decoy";
						szModelIcon = "m";
						GrenadeColor = Color(0, 255, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "incendiary"))
					{
						szModelName = "Incendiary";
						szModelIcon = "n";
						GrenadeColor = Color(255, 0, 0, 255);
						break;
					}
					else if (strstr(mat->GetName(), "molotov"))
					{
						szModelName = "Molotov";
						szModelIcon = "l";
						GrenadeColor = Color(255, 0, 0, 255);
						break;
					}
				}
				switch (g_Options.Visuals.Grenades)
				{
				case 0:
					if (g_Options.Visuals.GrenadeBox)
					{
						ThreeDBox(entity->GetCollideable()->OBBMins(), entity->GetCollideable()->OBBMaxs(), entity->GetVecOrigin(), GrenadeColor);
					}
					break;
				case 1:
					if (!g_Options.Visuals.GrenadeBox)
					{
						g_Render->DrawString2(g_Render->font.ESP, (int)pos.x, (int)pos.y, GrenadeColor, FONT_CENTER, "%s", szModelName);
					}
					else if (g_Options.Visuals.GrenadeBox)
					{
//						g_Render->DrawOutlinedRect((int)pos.x - 10, (int)pos.y - 10, 20, 20, GrenadeColor);
						g_Render->DrawString2(g_Render->font.ESP, (int)pos.x, (int)pos.y + 15, GrenadeColor, FONT_CENTER, "%s", szModelName);
						ThreeDBox(entity->GetCollideable()->OBBMins(), entity->GetCollideable()->OBBMaxs(), entity->GetVecOrigin(), GrenadeColor);
					}
					break;
				case 2:
					if (!g_Options.Visuals.GrenadeBox)
					{
						g_Render->DrawString2(g_Render->font.Icon, (int)pos.x, (int)pos.y, GrenadeColor, FONT_CENTER, "%s", szModelIcon);
					}
					
					else if (g_Options.Visuals.GrenadeBox)
					{
//						g_Render->DrawOutlinedRect((int)pos.x - 10, (int)pos.y - 10, 20, 20, GrenadeColor);
						g_Render->DrawString2(g_Render->font.Icon, (int)pos.x, (int)pos.y + 15, GrenadeColor, FONT_CENTER, "%s", szModelIcon);
						ThreeDBox(entity->GetCollideable()->OBBMins(), entity->GetCollideable()->OBBMaxs(), entity->GetVecOrigin(), GrenadeColor);
					}
					break;
				}
			}
		}
		if (g_Engine->GetPlayerInfo(i, &pinfo) && entity->IsAlive())
		{
			Color color(int(g_Options.Colors.backtrackdots_color[0] * 255.f), int(g_Options.Colors.backtrackdots_color[1] * 255.f), int(g_Options.Colors.backtrackdots_color[2] * 255.f));
			if (g_Options.Backtrack.backtrackenable)
			{
				if (local->IsAlive())
				{
					for (int t = 0; t < g_Options.Backtrack.backtrackticks; ++t)
					{
						Vector screenbacktrack[64][12];

						if (headPositions[i][t].simtime && headPositions[i][t].simtime + 1 > local->GetSimulationTime())
						{
							if (g_Render->WorldToScreen(headPositions[i][t].hitboxPos, screenbacktrack[i][t]))
							{
								switch (g_Options.Backtrack.BacktrackType)
								{
								case 1:
									g_Surface->DrawSetColor(color);
									g_Surface->DrawOutlinedRect(screenbacktrack[i][t].x, screenbacktrack[i][t].y, screenbacktrack[i][t].x + 2, screenbacktrack[i][t].y + 2);
									break;
								}
							}
						}
					}
				}
				else
				{
					memset(&headPositions[0][0], 0, sizeof(headPositions));
				}
			}
			if (g_Options.Ragebot.FakeLagFix)
			{
				if (local->IsAlive())
				{
					Vector screenbacktrack[64];

					if (backtracking->records[i].tick_count + 12 > g_Globals->tickcount)
					{
						if (g_Render->WorldToScreen(backtracking->records[i].headPosition, screenbacktrack[i]))
						{

							g_Surface->DrawSetColor(Color(int(g_Options.Colors.backtrackdots_color[0] * 255.f), int(g_Options.Colors.backtrackdots_color[1] * 255.f), int(g_Options.Colors.backtrackdots_color[2] * 255.f)));
							g_Surface->DrawLine(screenbacktrack[i].x, screenbacktrack[i].y, screenbacktrack[i].x + 2, screenbacktrack[i].y + 2);

						}
					}
				}
				else
				{
					memset(&backtracking->records[0], 0, sizeof(backtracking->records));
				}
			}

			if (!g_Render->WorldToScreen(pos3D, pos))
				continue;

			Color clr = entity->GetTeamNum() == local->GetTeamNum() ?
				Color(g_Options.Colors.TeamESP[0] * 255, g_Options.Colors.TeamESP[1] * 255, g_Options.Colors.TeamESP[2] * 255, 255) :
				Color(g_Options.Colors.EnemyESP[0] * 255, g_Options.Colors.EnemyESP[1] * 255, g_Options.Colors.EnemyESP[2] * 255, 255);
			if (entity->GetTeamNum() == local->GetTeamNum() && !g_Options.Visuals.TeamESP)
				continue;
			if (!entity->IsAlive())
				continue;

			bool PVS = false;
			RECT rect = DynamicBox(entity, PVS, local);

			DrawInfo(rect, entity, local);

			if (g_Options.Visuals.Box && g_Options.Visuals.Enabled)
			{
				switch (g_Options.Visuals.BoxType)
				{
				case 0:
					DrawBox(rect, clr);
					break;
				case 1:
					DrawCorners(rect, clr);
					break;
				case 2:
					ThreeDBox(entity->GetCollideable()->OBBMins(), entity->GetCollideable()->OBBMaxs(), entity->GetVecOrigin(), clr);
					break;
				}
			}
			if (g_Options.Visuals.fill && g_Options.Visuals.Enabled)
			{

				if (entity->GetTeamNum() == local->GetTeamNum())
				{
					g_Surface->DrawSetColor(Color(int(g_Options.Colors.fill_color_team[0] * 255.f), int(g_Options.Colors.fill_color_team[1] * 255.f), int(g_Options.Colors.fill_color_team[2] * 255.f), g_Options.Visuals.esp_fill_amount));
					ColorAlpha::ESP_ctx.clr_fill.SetAlpha(g_Options.Visuals.esp_fill_amount * 255.f);
					RenderFill(rect);
				}
				else if (entity->GetTeamNum() != local->GetTeamNum())
				{
					ColorAlpha::ESP_ctx.clr_fill.SetAlpha(g_Options.Visuals.esp_fill_amount * 255.f);
					g_Surface->DrawSetColor(Color(int(g_Options.Colors.fill_color_enemy[0] * 255.f), int(g_Options.Colors.fill_color_enemy[1] * 255.f), int(g_Options.Colors.fill_color_enemy[2] * 255.f), g_Options.Visuals.esp_fill_amount));

					RenderFill(rect);
				}
			}
			if (g_Options.Visuals.AimLine && g_Options.Visuals.Enabled)
			{
				DrawSnapLine(rect);
			}
			if (g_Options.Visuals.skeletonenbl && g_Options.Visuals.Enabled)
			{
				switch (g_Options.Visuals.skeletonopts)
				{
				case 0:
					Skeleton(entity, Color(int(g_Options.Colors.color_skeleton[0] * 255.f), int(g_Options.Colors.color_skeleton[1] * 255.f), int(g_Options.Colors.color_skeleton[2] * 255.f)));
					break;
				case 1:
					FingerSkeleton(entity, Color(int(g_Options.Colors.color_skeleton[0] * 255.f), int(g_Options.Colors.color_skeleton[1] * 255.f), int(g_Options.Colors.color_skeleton[2] * 255.f)));
					break;
				case 2:
					HealthSkeleton(entity);
					break;
				}
			}
			if (g_Options.Visuals.health && g_Options.Visuals.Enabled)
			{
				switch (g_Options.Visuals.healthtype)
				{
				case 0:
					DrawHealth(rect, entity);
					break;
				case 1:
					edgyHealthBar(rect, entity);
					break;
				}
			}
			if (g_Options.Visuals.armor && g_Options.Visuals.Enabled)
			{
				armorbar(rect, entity);
			} 
			if (g_Options.Visuals.barrel && g_Options.Visuals.Enabled)
			{
				BulletTrace(entity, Color(int(g_Options.Colors.BulletTraceColor[0] * 255.f), int(g_Options.Colors.BulletTraceColor[1] * 255.f), int(g_Options.Colors.BulletTraceColor[2] * 255.f)));
			}
			if (g_Options.Misc.radaringame)
			{
				Radar(entity);
			}
//			if (g_Options.Visuals.AmmoBox)
//			{
//				AmmoBox(rect, entity, pColor);
//			}
		}
	}
}

void visuals::Spoof()
{
	static auto sv_cheats = g_CVar->FindVar("sv_cheats");
	static auto spoof_cheats = new SpoofedConvar(sv_cheats);
	spoof_cheats->SetInt(1);

	static auto mat_postprocess_enable = g_CVar->FindVar("mat_postprocess_enable");

	if (g_Options.Visuals.NoPostProcess && g_Options.Visuals.Enabled)
	{
		mat_postprocess_enable->SetValue(0);
	}
	else
	{
		mat_postprocess_enable->SetValue(1);
	}

	static auto mat_drawgray = g_CVar->FindVar("mat_drawgray");

	if (g_Options.Visuals.snowmode && g_Options.Visuals.Enabled)
	{
		mat_drawgray->SetValue(1);
	}
	else
	{
		mat_drawgray->SetValue(0);
	}


	static auto mat_showmiplevels = g_CVar->FindVar("mat_showmiplevels");


	if (g_Options.Visuals.lsdmode && g_Options.Visuals.Enabled)
	{

		mat_showmiplevels->SetValue(1);
	}
	else
	{
		mat_showmiplevels->SetValue(0);
	}


	static auto r_showenvcubemap = g_CVar->FindVar("r_showenvcubemap");


	if (g_Options.Visuals.chromemode && g_Options.Visuals.Enabled)
	{
		r_showenvcubemap->SetValue(1);
	}
	else
	{
		r_showenvcubemap->SetValue(0);
	}


	static auto mat_showlowresimage = g_CVar->FindVar("mat_showlowresimage");


	if (g_Options.Visuals.minecraftmode && g_Options.Visuals.Enabled)
	{
		mat_showlowresimage->SetValue(1);
	}
	else
	{
		mat_showlowresimage->SetValue(0);
	}


	if (g_Options.Visuals.ambientlight && g_Options.Visuals.Enabled)
	{



		float AmbientRedAmount = g_Options.Colors.ambientlightcolor[0];
		float AmbientGreenAmount = g_Options.Colors.ambientlightcolor[1];
		float AmbientBlueAmount = g_Options.Colors.ambientlightcolor[2];



		ConVar* AmbientRedCvar = g_CVar->FindVar("mat_ambient_light_r");
		*(float*)((DWORD)&AmbientRedCvar->fnChangeCallback + 0xC) = NULL;
		AmbientRedCvar->SetValue(AmbientRedAmount);

		ConVar* AmbientGreenCvar = g_CVar->FindVar("mat_ambient_light_g");
		*(float*)((DWORD)&AmbientGreenCvar->fnChangeCallback + 0xC) = NULL;
		AmbientGreenCvar->SetValue(AmbientGreenAmount);

		ConVar* AmbientBlueCvar = g_CVar->FindVar("mat_ambient_light_b");
		*(float*)((DWORD)&AmbientBlueCvar->fnChangeCallback + 0xC) = NULL;
		AmbientBlueCvar->SetValue(AmbientBlueAmount);
	}

	else if (!g_Options.Visuals.ambientlight || !g_Options.Visuals.Enabled)
	{
		ConVar* AmbientRedCvar = g_CVar->FindVar("mat_ambient_light_r");
		*(float*)((DWORD)&AmbientRedCvar->fnChangeCallback + 0xC) = NULL;
		AmbientRedCvar->SetValue(0.f);

		ConVar* AmbientGreenCvar = g_CVar->FindVar("mat_ambient_light_g");
		*(float*)((DWORD)&AmbientGreenCvar->fnChangeCallback + 0xC) = NULL;
		AmbientGreenCvar->SetValue(0.f);

		ConVar* AmbientBlueCvar = g_CVar->FindVar("mat_ambient_light_b");
		*(float*)((DWORD)&AmbientBlueCvar->fnChangeCallback + 0xC) = NULL;
		AmbientBlueCvar->SetValue(0.f);
	}

}

void visuals::DrawBombPlanted(C_BaseEntity* entity, C_BaseEntity* local)
{
	BombCarrier = nullptr;

	float damage;
	char bombdamagestringdead[24];
	char bombdamagestringalive[24];

	Vector vOrig; Vector vScreen;
	vOrig = entity->GetVecOrigin();
	CCSBomb* Bomb = (CCSBomb*)entity;
	float flBlow = Bomb->GetC4BlowTime();
	float lifetime = flBlow - (g_Globals->interval_per_tick * local->GetTickBase());
	if (g_Render->WorldToScreen(vOrig, vScreen))
	{
		if (local->IsAlive())
		{
			float flDistance = local->GetEyePosition().DistTo(entity->GetEyePosition());
			float a = 450.7f;
			float b = 75.68f;
			float c = 789.2f;
			float d = ((flDistance - b) / c);
			float flDamage = a * exp(-d * d);

			damage = float((std::max)((int)ceilf(CSGO_Armor(flDamage, local->ArmorValue())), 0));

			sprintf_s(bombdamagestringdead, sizeof(bombdamagestringdead) - 1, "Health Left: 0");
			sprintf_s(bombdamagestringalive, sizeof(bombdamagestringalive) - 1, "Health Left: %.0f", local->GetHealth() - damage);
			if (lifetime > -2.f)
			{
				if (damage >= local->GetHealth())
				{
					g_Render->Text((int)vScreen.x, int(vScreen.y + 10), Color(250, 42, 42, 255), g_Render->font.ESP, bombdamagestringdead);
				}
				else if (local->GetHealth() > damage)
				{
					g_Render->Text((int)vScreen.x, int(vScreen.y + 10), Color(0, 255, 0, 255), g_Render->font.ESP, bombdamagestringalive);
				}
			}
		}
		char buffer[64];
		if (lifetime > 0.01f && !Bomb->IsBombDefused())
		{
			sprintf_s(buffer, "Bomb: %.1f", lifetime);
			g_Render->Text((int)vScreen.x, (int)vScreen.y, Color(250, 42, 42, 255), g_Render->font.ESP, buffer);
		}


	}

	g_Engine->GetScreenSize(width, height);
	int halfX = width / 2;
	int halfY = height / 2;


	if (Bomb->GetBombDefuser() > 0)
	{
		float countdown = Bomb->GetC4DefuseCountDown() - (local->GetTickBase() * g_Globals->interval_per_tick);
		if (countdown > 0.01f)
		{
			if (lifetime > countdown)
			{
				char defuseTimeString[24];
				sprintf_s(defuseTimeString, sizeof(defuseTimeString) - 1, "Defusing: %.1f", countdown);
				g_Render->Text(halfX - 50, halfY + 200, Color(0, 255, 0, 255), g_Render->font.ESP, defuseTimeString);
			}
			else
			{
				g_Render->Text(halfX - 50, halfY + 200, Color(255, 0, 0, 255), g_Render->font.ESP, "No Time! Run!");
			}
		}

	}
}

void visuals::DrawBomb(C_BaseEntity* entity, ClientClass* cClass)
{
	// Null it out incase bomb has been dropped or planted
	BombCarrier = nullptr;
	CBaseCombatWeapon *BombWeapon = (CBaseCombatWeapon *)entity;
	Vector vOrig; Vector vScreen;
	vOrig = entity->GetVecOrigin();
	bool adopted = true;
	auto parent = BombWeapon->GetOwnerHandle();
	if (parent || (vOrig.x == 0 && vOrig.y == 0 && vOrig.z == 0))
	{
		C_BaseEntity* pParentEnt = (g_EntityList->GetClientEntityFromHandle(parent));
		if (pParentEnt && pParentEnt->IsAlive())
		{
			BombCarrier = pParentEnt;
			adopted = false;
		}
	}
	if (g_Options.Visuals.C4World)
	{
		if (adopted)
		{
			if (g_Render->WorldToScreen(vOrig, vScreen))
			{
				g_Render->Text((int)vScreen.x, (int)vScreen.y, Color(255, 20, 20, 255), g_Render->font.ESP, "Bomb");
			}
		}

	}


}
void visuals::edgyHealthBar(RECT rect, C_BaseEntity* pEntity)
{

	float top = 1.4;
	float right = 0;
	float left = 0;

	float HealthValue = pEntity->GetHealth();
	int iHealthValue = HealthValue;
	int Red = 255 - (HealthValue * 2.00);
	int Green = HealthValue * 2.00;
	float flBoxes = std::ceil(pEntity->GetHealth() / 10.f);

	float height = (rect.bottom - rect.top) * (HealthValue / 100);
	float height2 = (rect.bottom - rect.top) * (100 / 100);
	float flHeight = height2 / 10.f;


	g_Render->DrawRect(rect.left - 5, rect.top - 1, rect.left - 1, rect.bottom + 1, Color(0, 0, 0, 150));
	g_Render->DrawRect(rect.left - 4, rect.bottom - height, rect.left - 2, rect.bottom, Color(Red, Green, 0, 255));

	for (int i = 0; i < 10; i++)
		g_Render->Line(rect.left - 5, rect.top + i * flHeight, rect.left - 2, rect.top + i * flHeight, Color(0, 0, 0, 255));


}

void visuals::Hitbox(int index)
{
	if (g_Options.Visuals.HitboxDuration == 0.f || !g_Options.Visuals.Hitbox)
		return;

	C_BaseEntity* pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());

	float duration = g_Options.Visuals.HitboxDuration;

	if (index < 0)
		return;

	Color color = Color(int(g_Options.Colors.hitbox[0] * 255.f), int(g_Options.Colors.hitbox[1] * 255.f), int(g_Options.Colors.hitbox[2] * 255.f));

	auto entity = reinterpret_cast<C_BaseEntity*>(g_EntityList->GetClientEntity(index));

	if (!entity)
		return;

	studiohdr_t* pStudioModel = g_ModelInfo->GetStudiomodel(entity->GetModel());

	if (!pStudioModel)
		return;

	static matrix3x4 pBoneToWorldOut[128];

	if (!entity->SetupBones(pBoneToWorldOut, MAXSTUDIOBONES, 256, g_Globals->curtime))
		return;

	mstudiohitboxset_t* pHitboxSet = pStudioModel->GetHitboxSet(0);
	if (!pHitboxSet)
		return;

	for (int i = 0; i < pHitboxSet->numhitboxes; i++)
	{
		mstudiobbox_t* pHitbox = pHitboxSet->pHitbox(i);
		if (!pHitbox)
			continue;

		Vector vMin, vMax;
		VectorTransform(pHitbox->bbmin, pBoneToWorldOut[pHitbox->bone], vMin); //nullptr???
		VectorTransform(pHitbox->bbmax, pBoneToWorldOut[pHitbox->bone], vMax);

		if (pHitbox->m_flRadius > -1)
		{
			g_DebugOverlay->AddCapsuleOverlay(vMin, vMax, pHitbox->m_flRadius, color.r(), color.g(), color.b(), 100, duration);
		}
	}
}

void visuals::armorbar(RECT rect, C_BaseEntity* pEntity)
{
	float ArmorValue = pEntity->ArmorValue();
	int iArmorValue = ArmorValue;
	int red = 255 - (ArmorValue * 2.0);
	int blue = ArmorValue * 2.0;

	float height = (rect.right - rect.left) * (ArmorValue / 100);

	g_Render->DrawRect(rect.left - 1, rect.bottom + 1, rect.right + 1, rect.bottom + 5, Color(10, 10, 10, 0));
	g_Render->DrawRect(rect.left, rect.bottom + 2, rect.left + height, rect.bottom + 4, Color(red, blue, blue, 0));

	if (g_Options.Visuals.armor && g_Options.Visuals.Enabled)
	{
		g_Render->DrawRect(rect.left - 1, rect.bottom + 1, rect.right + 1, rect.bottom + 5, Color(10, 10, 10, 165));
		g_Render->DrawRect(rect.left, rect.bottom + 2, rect.left + height, rect.bottom + 4, Color(red, blue, blue, 255));
	}

	int Armor = pEntity->ArmorValue();

}

void visuals::DrawBox(RECT rect, Color Col)
{
	g_Render->DrawOutlinedRect(rect.left - 1, rect.top - 1, rect.right - rect.left + 2, rect.bottom - rect.top + 2, Color(0, 0, 0, 150));
	g_Render->DrawOutlinedRect(rect.left + 1, rect.top + 1, rect.right - rect.left - 2, rect.bottom - rect.top - 2, Color(0, 0, 0, 125));
	g_Render->DrawOutlinedRect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, Col);
}

void visuals::RenderFill(RECT rect)
{
	g_Surface->DrawFilledRect(rect.left + 2, rect.top + 2, rect.right - 2, rect.bottom - 2);

}

void visuals::DrawCorners(RECT rect, Color Col)
{
	int x1, y1, x2, y2, w, h;
	x1 = rect.left;
	y1 = rect.top;
	x2 = rect.right;
	y2 = rect.bottom;

	w = x2;
	h = y2;

	int Line_Size = (y1 - h) / 6;
	int Line_Size2 = (y1 - h) / 6;

	int red = 0;
	int green = 0;
	int blue = 0;
	int alpha = 0;
	Col.GetColor(red, green, blue, alpha);
	g_Surface->DrawSetColor(red, green, blue, alpha);

	//top inwards
	g_Surface->DrawLine(w, y1, w + Line_Size, y1);
	g_Surface->DrawLine(x1, y1, x1 - Line_Size, y1);

	//top downwards
	g_Surface->DrawLine(x1, y1, x1, y1 - Line_Size);
	g_Surface->DrawLine(w, y1, w, y1 - Line_Size);

	//bottom inwards
	g_Surface->DrawLine(x1, h, x1 - Line_Size, h);
	g_Surface->DrawLine(w, h, w + Line_Size, h);

	//bottom upwards
	g_Surface->DrawLine(x1, h, x1, h + Line_Size);
	g_Surface->DrawLine(w, h, w, h + Line_Size);

	//outlines

	g_Surface->DrawSetColor(0, 0, 0, 200);

	//top inwards
	g_Surface->DrawLine(w, y1 - 1, w + Line_Size, y1 - 1);
	g_Surface->DrawLine(x1, y1 - 1, x1 - Line_Size, y1 - 1);
	//inlines
	g_Surface->DrawLine(w - 1, y1 + 1, w + Line_Size, y1 + 1);
	g_Surface->DrawLine(x1 + 1, y1 + 1, x1 - Line_Size, y1 + 1);

	// top downwards
	g_Surface->DrawLine(x1 - 1, y1 - 1, x1 - 1, y1 - Line_Size);
	g_Surface->DrawLine(w + 1, y1 - 1, w + 1, y1 - Line_Size);
	//inlines
	g_Surface->DrawLine(x1 + 1, y1, x1 + 1, y1 - Line_Size);
	g_Surface->DrawLine(w - 1, y1, w - 1, y1 - Line_Size);

	//bottom inwards
	g_Surface->DrawLine(x1, h + 1, x1 - Line_Size, h + 1);
	g_Surface->DrawLine(w, h + 1, w + Line_Size, h + 1);
	//inlines
	g_Surface->DrawLine(x1 + 1, h - 1, x1 - Line_Size, h - 1);
	g_Surface->DrawLine(w - 1, h - 1, w + Line_Size, h - 1);

	//bottom upwards
	g_Surface->DrawLine(x1 - 1, h + 1, x1 - 1, h + Line_Size);
	g_Surface->DrawLine(w + 1, h + 1, w + 1, h + Line_Size);
	//inlines
	g_Surface->DrawLine(x1 + 1, h, x1 + 1, h + Line_Size);
	g_Surface->DrawLine(w - 1, h, w - 1, h + Line_Size);
}

void visuals::ThreeDBox(Vector minin, Vector maxin, Vector pos, Color Col)
{
	Vector min = minin + pos;
	Vector max = maxin + pos;

	Vector corners[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(min.x, min.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(max.x, max.y, max.z),
		Vector(max.x, min.y, max.z) };

	int edges[12][2] = { { 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 4 },{ 0, 4 },{ 1, 5 },{ 2, 6 },{ 3, 7 }, };

	for (const auto edge : edges)
	{
		Vector p1, p2;
		if (!g_Render->WorldToScreen(corners[edge[0]], p1) || !g_Render->WorldToScreen(corners[edge[1]], p2))
			return;
		int red = 0;
		int green = 0;
		int blue = 0;
		int alpha = 0;
		Col.GetColor(red, green, blue, alpha);
		g_Surface->DrawSetColor(red, green, blue, alpha);
		g_Surface->DrawLine(p1.x, p1.y, p2.x, p2.y);
	}

}

void visuals::DrawInfo(RECT rect, C_BaseEntity* entity, C_BaseEntity* local)
{
	player_info_t info;
	static class Text
	{
	public:
		std::string text;
		int side;
		int Font;
		Color color;

		Text(std::string text, int side, int Font, Color color) : text(text), side(side), Font(Font), color(color)
		{
		}
	};
	std::vector< Text > texts;
	if (g_Engine->GetPlayerInfo(entity->GetIndex(), &info))
	{
		if (entity == BombCarrier && g_Options.Visuals.BombCarrier &&  g_Options.Visuals.Enabled)
		{
			texts.push_back(Text("Bomb Carrier", 1, g_Render->font.ESP, Color(255, 220, 220, 255)));
		}

		if (g_Options.Visuals.Flashed && entity->IsFlashed() && g_Options.Visuals.Enabled)
		{
			texts.push_back(Text("Flashed", 1, g_Render->font.ESP, Color(255, 255, 183, 255)));
		}

		if (g_Options.Visuals.IsHasDefuser && entity->hasDefuser() && g_Options.Visuals.Enabled)
		{
			texts.push_back(Text("r", 1, g_Render->font.Icon, Color(255, 255, 183, 255))); //b1g defuser icon
		}

		if (g_Options.Visuals.IsDefusing &&  entity->IsDefusing() && g_Options.Visuals.Enabled)
		{
			texts.push_back(Text("Defusing", 1, g_Render->font.ESP, Color(255, 255, 183, 255)));
		}

		if (g_Options.Visuals.Name && g_Options.Visuals.Enabled)
		{
			texts.push_back(Text(info.name, 0, g_Render->font.ESP, Color(255, 255, 255, 255)));
		}

		switch (g_Options.Visuals.Armor2)
		{
		case 0:
			break;
		case 1:
			texts.push_back(Text(entity->GetArmorName(), 1, g_Render->font.ESP, Color(255, 255, 255, 255)));
			break;
		case 2:
			texts.push_back(Text(entity->GetArmorIcon(), 1, g_Render->font.Icon, Color(255, 255, 255, 255)));
			break;
		default:
			break;
		}

		if (g_Options.Visuals.Distance && g_Options.Visuals.Enabled)
		{
			texts.push_back(Text(std::to_string(flGetDistance(local->GetVecOrigin(), entity->GetVecOrigin())) + std::string("FT"), 2, g_Render->font.ESP, Color(255, 255, 255, 255)));
		}

		if (g_Options.Visuals.resolveMode && g_Options.Visuals.Enabled)
		{
			if (Globals::resolvemode == 1)
			{
				texts.push_back(Text(std::string("Resolver: Bruteforce"), 0, g_Render->font.ESP, Color(255, 255, 183, 255)));
			}
			else if (Globals::resolvemode == 2)
			{
				texts.push_back(Text(std::string("Resolver: Predicting LBY"), 0, g_Render->font.ESP, Color(255, 255, 183, 255)));
			}
			else if (Globals::resolvemode == 3)
			{
				texts.push_back(Text(std::string("Resolver: LBY Update"), 0, g_Render->font.ESP, Color(255, 255, 183, 255)));
			}
			else if (Globals::resolvemode == 4)
			{
				texts.push_back(Text(std::string("Resolver: Legit Player"), 0, g_Render->font.ESP, Color(255, 255, 183, 255)));
			}
		}

		CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(entity->GetActiveWeaponHandle());
		if (weapon)
		{
			switch (g_Options.Visuals.Weapon)
			{
			case 0:
				break;
			case 1:
				if (MiscFunctions::IsKnife(weapon) || MiscFunctions::IsGrenade(weapon))
				{
					texts.push_back(Text(weapon->GetGunName(), 2, g_Render->font.ESP, Color(255, 255, 255, 255)));
				}

				else
					texts.push_back(Text(weapon->GetGunName() + std::string("[") + std::to_string(weapon->ammo()) + std::string("|") + std::to_string(weapon->ammo2()) + std::string("]"), 2, g_Render->font.ESP, Color(255, 255, 255, 255)));
				break;
			case 2:
				texts.push_back(Text(weapon->GetGunIcon(), 2, g_Render->font.Icon, Color(255, 255, 255, 255)));
				break;
			default:
				break;
			}
		}

		if (g_Options.Visuals.Scoped && entity->IsScoped() && g_Options.Visuals.Enabled)
		{
			texts.push_back(Text("SCOPE", 1, g_Render->font.ESPan, Color(0, 202, 247, 255)));
		}

		//		if (g_Options.Visuals.Reloading && weapon->IsInReload() && g_Options.Visuals.Enabled)
		//		{
		//			texts.push_back(Text("*Reloading*", 0, g_Render->font.ESP, Color(255, 255, 183, 255)));
		//		}


		if (g_Options.Visuals.Money && g_Options.Visuals.Enabled)
		{
			texts.push_back(Text(std::string("$") + std::to_string(entity->iAccount()), 1, g_Render->font.ESP, Color(71, 132, 60, 255)));
		}

	}


	int middle = ((rect.right - rect.left) / 2) + rect.left;
	int Top[3] = { rect.top,rect.top, rect.bottom };
	for (auto text : texts)
	{
		RECT nameSize = g_Render->GetTextSize(text.Font, (char*)text.text.c_str());
		switch (text.side)
		{
		case 0:
			Top[0] -= nameSize.bottom + 1;
			g_Render->DrawString2(text.Font, middle, Top[0] + 8, text.color, FONT_CENTER, (char*)text.text.c_str());
			break;
		case 1:
			g_Render->DrawString2(text.Font, rect.right + 2, Top[1] + 8, text.color, FONT_LEFT, (char*)text.text.c_str());
			Top[1] += nameSize.bottom - 4;
			break;
		case 2:
			g_Render->DrawString2(text.Font, middle, Top[2] + 8, text.color, FONT_CENTER, (char*)text.text.c_str());
			Top[2] += nameSize.bottom - 4;
			break;
		}
	}

}
/*void visuals::AmmoBox(RECT rect, C_BaseEntity* pPlayer, Color color)
{
	auto AnimLayer = &pPlayer->GetAnimationOverlay()[1];

	if (!AnimLayer->m_pOwner)
		return;

	auto activity = pPlayer->GetSequenceActivity(AnimLayer->m_nSequence); //g_ModelInfo->GetStudiomodel(pPlayer->GetModel())

	if (CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)g_EntityList->GetClientEntityFromHandle(pPlayer->GetActiveWeaponHandle()))
	{

		if (CSWeaponInfo* winfo = weapon->GetCSWpnData())
		{
			CCSWeaponInfo* oof;
			float currentammo = weapon->ammo();
			float maxammo = oof->GetMaxClip();
			g_Render->DrawRect(rect.left - 1, rect.bottom + 2, rect.right + 1, rect.bottom + 6, Color(0, 0, 0, 255));

			static float ammob4reload[64]; // for the aesthetic so it doesnt jump to the current ammo before reload animation
			if (activity == 967 && AnimLayer->m_flWeight != 0.f) // if reloading
			{
				float amount = ammob4reload[pPlayer->GetIndex()] / maxammo;
				float cycle = AnimLayer->m_flCycle;
				int length = (rect.right - rect.left) * amount;
				int reloadX = ((rect.right - rect.left) - length) * cycle;
				g_Render->DrawRect(rect.left, rect.bottom + 3, rect.left + length + reloadX, rect.bottom + 5, color);
				g_Render->DrawString2(g_Render->font.ESP, rect.left + length + reloadX, rect.bottom - 1, Color(255, 255, 255, 255), false, "RELOADING");
			}
			else // if not reloading
			{
				if (currentammo < 0) // draw a bar for weapons that do not have ammo (grenades, knives) for the aesthetic
				{
					g_Render->DrawRect(rect.left, rect.bottom + 3, rect.right, rect.bottom + 5, color);
				}
				if (currentammo >= 0) // if the bitch got bullets its probably a gun and we shud display the ammo count if it aint full also draw that sexy bar MMMMMM
				{
					float amount = currentammo / maxammo;
					int length = (rect.right - rect.left) * amount;
					ammob4reload[pPlayer->GetIndex()] = currentammo;
					if (currentammo != 0)
						g_Render->DrawRect(rect.left, rect.bottom + 3, rect.left + length, rect.bottom + 5, color);

					if (currentammo != maxammo)
						g_Render->DrawString2(g_Render->font.ESP, rect.left + length, rect.bottom - 1, Color(255, 255, 255), true, "%.0f", currentammo);
				}
			}
		}
	}
} */
void visuals::DrawAngles()
{
	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());

	Vector src3D, dst3D, forward, src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	filter.pSkip = pLocal;
	src3D = pLocal->GetVecOrigin();

	AngleVectors(QAngle(0, Globals::RealAngle, 0), &forward);
	dst3D = src3D + (forward * 45.f);

	ray.Init(src3D, dst3D);

	g_EngineTrace->TraceRay(ray, 0, &filter, &tr);

	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
		return;

	g_Render->Line(src.x, src.y, dst.x, dst.y, Color(0, 255, 0, 255));

	if (g_Options.Visuals.angleLinesName)
		g_Render->Text(dst.x, dst.y, Color(0, 255, 0, 255), g_Render->font.ESP, "REAL");

	AngleVectors(QAngle(0, Globals::FakeAngle, 0), &forward);
	dst3D = src3D + (forward * 45.f);

	ray.Init(src3D, dst3D);

	g_EngineTrace->TraceRay(ray, 0, &filter, &tr);

	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
		return;

	g_Render->Line(src.x, src.y, dst.x, dst.y, Color(255, 0, 0, 255));

	if (g_Options.Visuals.angleLinesName)
		g_Render->Text(dst.x, dst.y, Color(255, 0, 0, 255), g_Render->font.ESP, "FAKE");

	AngleVectors(QAngle(0, pLocal->GetLowerBodyYaw(), 0), &forward);
	dst3D = src3D + (forward * 45.f);

	ray.Init(src3D, dst3D);

	g_EngineTrace->TraceRay(ray, 0, &filter, &tr);

	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
		return;

	g_Render->Line(src.x, src.y, dst.x, dst.y, Color(255, 127, 0, 255));

	if (g_Options.Visuals.angleLinesName)
		g_Render->Text(dst.x, dst.y, Color(255, 0, 0, 255), g_Render->font.ESP, "LBY");

}

void visuals::Radar(C_BaseEntity* entity)
{
	DWORD m_bSpotted = offsetz.DT_BaseEntity.m_bSpotted;
	*(char*)((DWORD)(entity)+m_bSpotted) = 1;
}

RECT visuals::DynamicBox(C_BaseEntity* pPlayer, bool& PVS, C_BaseEntity* local)
{
	Vector trans = pPlayer->GetVecOrigin();

	Vector min;
	Vector max;

	min = pPlayer->GetCollideable()->OBBMins();
	max = pPlayer->GetCollideable()->OBBMaxs();

	Vector pointList[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	Vector Distance = pointList[0] - pointList[1];
	int dst = Distance.Length();
	dst /= 1.3f;
	Vector angs;
	CalcAngle(trans, local->GetEyePosition(), angs);

	Vector all[8];
	angs.y += 45;
	for (int i = 0; i < 4; i++)
	{
		AngleVectors(angs, &all[i]);
		all[i] *= dst;
		all[i + 4] = all[i];
		all[i].z = max.z;
		all[i + 4].z = min.z;
		VectorAdd(all[i], trans, all[i]);
		VectorAdd(all[i + 4], trans, all[i + 4]);
		angs.y += 90;
	}

	Vector flb, brt, blb, frt, frb, brb, blt, flt;
	PVS = true;

	if (!g_DebugOverlay->ScreenPosition(all[3], flb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[0], blb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[2], frb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[6], blt))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[5], brt))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[4], frt))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[1], brb))
		PVS = false;
	if (!g_DebugOverlay->ScreenPosition(all[7], flt))
		PVS = false;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (int i = 0; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
	}
	RECT rect;
	rect.left = left;
	rect.bottom = bottom;
	rect.right = right;
	rect.top = top;

	return rect;
}
bool visuals::GetBBox(C_BaseEntity* entity, visuals::ESPBox &result)
{

	// Variables
	Vector  vOrigin, min, max, sMin, sMax, sOrigin,
		flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;


	vOrigin = entity->GetAbsOrigin2();
	min = entity->collisionProperty()->GetMins() + vOrigin;
	max = entity->collisionProperty()->GetMaxs() + vOrigin;

	// Points of a 3d bounding box
	Vector points[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z) };

	// Get screen positions
	if (!g_Render->WorldToScreen(points[3], flb) || !g_Render->WorldToScreen(points[5], brt)
		|| !g_Render->WorldToScreen(points[0], blb) || !g_Render->WorldToScreen(points[4], frt)
		|| !g_Render->WorldToScreen(points[2], frb) || !g_Render->WorldToScreen(points[1], brb)
		|| !g_Render->WorldToScreen(points[6], blt) || !g_Render->WorldToScreen(points[7], flt))
		return false;

	// Put them in an array (maybe start them off in one later for speed?)
	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	// Init this shit
	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	// Find the bounding corners for our box
	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;

	// Width / height
	result.x = left;
	result.y = top;
	result.w = right - left;
	result.h = bottom - top;
	return true;
}
void visuals::RenderWeapon(C_BaseEntity* entity, Color color)
{

	if (entity)
	{
		CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)entity;

		auto owner = pWeapon->GetOwnerHandle();

		if (owner > -1)
			return;

		Vector pos3D = entity->GetAbsOrigin2();

		if (pos3D.x == 0.0f && pos3D.y == 0.0f && pos3D.z == 0.0f)
			return;

		Vector pos;


		if (!g_Render->WorldToScreen(pos3D, pos))
			return;

		int weaponID = pWeapon->m_AttributeManager()->m_Item()->GetItemDefinitionIndex();
		auto weaponName = ItemDefinitionIndexToString(weaponID);
		auto weaponIcon = ItemDefinitionIndexToString2(weaponID);

		switch (g_Options.Visuals.DroppedGunsType)
		{
		case 0:
			break;
		case 1:
			g_Render->Text(pos.x, pos.y, color, g_Render->font.Guns, weaponName);
			break;
		case 2:
			g_Render->Text(pos.x, pos.y, color, g_Render->font.Icon, weaponIcon);
			break;
		default:
			break;
		}

	}
}

void visuals::BulletTrace(C_BaseEntity* pEntity, Color color)
{
	Vector src3D, dst3D, forward, src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;
	Vector eyes = *pEntity->GetEyeAngles();

	AngleVectors(eyes, &forward);
	filter.pSkip = pEntity;
	src3D = pEntity->GetBonePos(6) - Vector(0, 0, 0);
	dst3D = src3D + (forward * g_Options.Visuals.barrelL);

	ray.Init(src3D, dst3D);

	g_EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

	if (!g_Render->WorldToScreen(src3D, src) || !g_Render->WorldToScreen(tr.endpos, dst))
		return;


	g_Render->Line(src.x, src.y, dst.x, dst.y, color);
	g_Render->DrawOutlinedRect(dst.x - 3, dst.y - 3, 6, 6, color);

};

void visuals::Skeleton(C_BaseEntity* pEntity, Color Col)
{
	studiohdr_t* pStudioHdr = g_ModelInfo->GetStudiomodel(pEntity->GetModel());

	if (!pStudioHdr)
		return;

	Vector vParent, vChild, sParent, sChild;

	for (int j = 0; j < pStudioHdr->numbones; j++)
	{
		mstudiobone_t* pBone = pStudioHdr->GetBone(j);

		if (pBone && pBone->flags & BONE_USED_BY_HITBOX && (pBone->parent != -1))
		{
			vChild = pEntity->GetBonePos(j);
			vParent = pEntity->GetBonePos(pBone->parent);

			int iChestBone = 6;  // Parameter of relevant Bone number
			Vector vBreastBone; // New reference Point for connecting many bones
			Vector vUpperDirection = pEntity->GetBonePos(iChestBone + 1) - pEntity->GetBonePos(iChestBone); // direction vector from chest to neck
			vBreastBone = pEntity->GetBonePos(iChestBone) + vUpperDirection / 2;
			Vector vDeltaChild = vChild - vBreastBone; // Used to determine close bones to the reference point
			Vector vDeltaParent = vParent - vBreastBone;

			// Eliminating / Converting all disturbing bone positions in three steps.
			if ((vDeltaParent.Length() < 9 && vDeltaChild.Length() < 9))
				vParent = vBreastBone;

			if (j == iChestBone - 1)
				vChild = vBreastBone;

			if (abs(vDeltaChild.z) < 5 && (vDeltaParent.Length() < 5 && vDeltaChild.Length() < 5) || j == iChestBone)
				continue;

			g_DebugOverlay->ScreenPosition(vParent, sParent);
			g_DebugOverlay->ScreenPosition(vChild, sChild);

			g_Surface->DrawSetColor(Color(int(g_Options.Colors.color_skeleton[0] * 255.f), int(g_Options.Colors.color_skeleton[1] * 255.f), int(g_Options.Colors.color_skeleton[2] * 255.f)));
			g_Surface->DrawLine(sParent[0], sParent[1], sChild[0], sChild[1]);
		}
	}
}

void visuals::FingerSkeleton(C_BaseEntity* pEntity, Color Col)
{
	studiohdr_t* pStudioHdr = g_ModelInfo->GetStudiomodel(pEntity->GetModel());

	if (!pStudioHdr)
		return;

	Vector vParent, vChild, sParent, sChild;

	for (int j = 0; j < pStudioHdr->numbones; j++)
	{
		mstudiobone_t* pBone = pStudioHdr->GetBone(j);

		if (pBone && pBone->flags & BONE_USED_BY_HITBOX | BONE_USED_BY_ATTACHMENT && (pBone->parent != -1))
		{
			vChild = pEntity->GetBonePos(j);
			vParent = pEntity->GetBonePos(pBone->parent);

			int iChestBone = 6;  // Parameter of relevant Bone number
			Vector vBreastBone; // New reference Point for connecting many bones
			Vector vUpperDirection = pEntity->GetBonePos(iChestBone + 1) - pEntity->GetBonePos(iChestBone); // direction vector from chest to neck
			vBreastBone = pEntity->GetBonePos(iChestBone) + vUpperDirection / 2;
			Vector vDeltaChild = vChild - vBreastBone; // Used to determine close bones to the reference point
			Vector vDeltaParent = vParent - vBreastBone;

			// Eliminating / Converting all disturbing bone positions in three steps.
			if ((vDeltaParent.Length() < 9 && vDeltaChild.Length() < 9))
				vParent = vBreastBone;

			if (j == iChestBone - 1)
				vChild = vBreastBone;

			if (abs(vDeltaChild.z) < 5 && (vDeltaParent.Length() < 5 && vDeltaChild.Length() < 5) || j == iChestBone)
				continue;

			if ((pBone->flags & BONE_USED_BY_HITBOX ^ BONE_USED_BY_HITBOX) && (vDeltaParent.Length() < 19 && vDeltaChild.Length() < 19))
				continue;

			g_DebugOverlay->ScreenPosition(vParent, sParent);
			g_DebugOverlay->ScreenPosition(vChild, sChild);

			g_Surface->DrawSetColor(Color(int(g_Options.Colors.color_skeleton[0] * 255.f), int(g_Options.Colors.color_skeleton[1] * 255.f), int(g_Options.Colors.color_skeleton[2] * 255.f)));
			g_Surface->DrawLine(sParent[0], sParent[1], sChild[0], sChild[1]);
		}
	}
}

void visuals::HealthSkeleton(C_BaseEntity* pEntity)
{

	studiohdr_t* pStudioHdr = g_ModelInfo->GetStudiomodel(pEntity->GetModel());

	if (!pStudioHdr)
		return;

	Vector vParent, vChild, sParent, sChild;

	for (int j = 0; j < pStudioHdr->numbones; j++)
	{
		mstudiobone_t* pBone = pStudioHdr->GetBone(j);


		if (pBone && (pBone->flags & BONE_USED_BY_HITBOX) && (pBone->parent != -1))
		{
			vChild = pEntity->GetBonePos(j);
			vParent = pEntity->GetBonePos(pBone->parent);

			int iChestBone = 6;  // Parameter of relevant Bone number
			Vector vBreastBone; // New reference Point for connecting many bones
			Vector vUpperDirection = pEntity->GetBonePos(iChestBone + 1) - pEntity->GetBonePos(iChestBone); // direction vector from chest to neck
			vBreastBone = pEntity->GetBonePos(iChestBone) + vUpperDirection / 2;
			Vector vDeltaChild = vChild - vBreastBone; // Used to determine close bones to the reference point
			Vector vDeltaParent = vParent - vBreastBone;

			// Eliminating / Converting all disturbing bone positions in three steps.
			if ((vDeltaParent.Length() < 9 && vDeltaChild.Length() < 9))
				vParent = vBreastBone;

			if (j == iChestBone - 1)
				vChild = vBreastBone;

			if (abs(vDeltaChild.z) < 5 && (vDeltaParent.Length() < 5 && vDeltaChild.Length() < 5) || j == iChestBone)
				continue;

			if (pEntity->GetHealth() == 100)
			{
				g_DebugOverlay->ScreenPosition(vParent, sParent);
				g_DebugOverlay->ScreenPosition(vChild, sChild);
				g_Render->Line(sParent[0], sParent[1], sChild[0], sChild[1], Color(0, 255, 0));
			}

			if (pEntity->GetHealth() < 100 & pEntity->GetHealth() > 85 || pEntity->GetHealth() == 85)
			{
				g_DebugOverlay->ScreenPosition(vParent, sParent);
				g_DebugOverlay->ScreenPosition(vChild, sChild);
				g_Render->Line(sParent[0], sParent[1], sChild[0], sChild[1], Color(114, 255, 00));

			}
			else if (pEntity->GetHealth() < 85 & pEntity->GetHealth() > 60 || pEntity->GetHealth() == 60)
			{
				g_DebugOverlay->ScreenPosition(vParent, sParent);
				g_DebugOverlay->ScreenPosition(vChild, sChild);
				g_Render->Line(sParent[0], sParent[1], sChild[0], sChild[1], Color(178, 255, 0));
			}
			else if (pEntity->GetHealth() < 60 & pEntity->GetHealth() > 45 || pEntity->GetHealth() == 45)
			{
				g_DebugOverlay->ScreenPosition(vParent, sParent);
				g_DebugOverlay->ScreenPosition(vChild, sChild);
				g_Render->Line(sParent[0], sParent[1], sChild[0], sChild[1], Color(255, 229, 0));
			}
			else if (pEntity->GetHealth() < 45 & pEntity->GetHealth() > 30 || pEntity->GetHealth() == 30)
			{
				g_DebugOverlay->ScreenPosition(vParent, sParent);
				g_DebugOverlay->ScreenPosition(vChild, sChild);
				g_Render->Line(sParent[0], sParent[1], sChild[0], sChild[1], Color(255, 127, 0));
			}
			else  if (pEntity->GetHealth() < 30 & pEntity->GetHealth() > 15 || pEntity->GetHealth() == 15)
			{
				g_DebugOverlay->ScreenPosition(vParent, sParent);
				g_DebugOverlay->ScreenPosition(vChild, sChild);
				g_Render->Line(sParent[0], sParent[1], sChild[0], sChild[1], Color(255, 55, 0));
			}
			else  if (pEntity->GetHealth() < 15 & pEntity->GetHealth() > 0)
			{
				g_DebugOverlay->ScreenPosition(vParent, sParent);
				g_DebugOverlay->ScreenPosition(vChild, sChild);
				g_Render->Line(sParent[0], sParent[1], sChild[0], sChild[1], Color(191, 0, 0));
			}
		}
	}
}

void visuals::DrawSnapLine(RECT rect)
{
	Color color = Color(int(g_Options.Colors.AimLineColor[0] * 255.f), int(g_Options.Colors.AimLineColor[1] * 255.f), int(g_Options.Colors.AimLineColor[2] * 255.f));

	int width, height;
	g_Engine->GetScreenSize(width, height);

	int screen_x = width * 0.5f,
		screen_y = height,
		target_x = rect.left + (rect.right - rect.left) * 0.5,
		target_y = rect.bottom,
		max_length = height * 0.3f;

	if (target_x == 0 ||
		target_y == 0)
		return;

	float length = sqrt(pow(target_x - screen_x, 2) + pow(target_y - screen_y, 2));
	if (length > max_length)
	{
		float
			x_normalized = (target_x - screen_x) / length,
			y_normalized = (target_y - screen_y) / length;
		target_x = screen_x + x_normalized * max_length;
		target_y = screen_y + y_normalized * max_length;
		g_Render->OutlineCircle(target_x + x_normalized * 3.5f, target_y + y_normalized * 3.5f, 8.f, 80, color);
	}

	g_Surface->DrawSetColor(color);
	g_Surface->DrawLine(screen_x, screen_y, target_x, target_y);

	/*	int width = 0;
	int height = 0;
	g_Engine->GetScreenSize(width, height);
	Vector From((width / 2), height - 1, 0);
	g_Render->Line(From.x, From.y, to.x, to.y, clr); */
}

void visuals::DrawHealth(RECT rect, C_BaseEntity* pPlayer)
{
	float HealthValue = pPlayer->GetHealth();

	float HealthValue2 = pPlayer->GetHealth();
	if (HealthValue2 > 100)
		HealthValue2 = 100;

//	char hp[256];
//	sprintf(hp, "%.0f", HealthValue);
	int Red = 255 - (HealthValue2 * 2.55);
	int Green = HealthValue2 * 2.55;
	float height = (rect.bottom - rect.top) * (HealthValue2 / 100);
	g_Render->GradientH(rect.left - 9, rect.top - 1, 6, rect.bottom - rect.top + 2, Color(0, 0, 0, 150), Color(0, 0, 0, 150));
	g_Render->GradientH(rect.left - 8, rect.bottom - height, 4, height, Color(Red, Green, 0, 255), Color(Red, Green, 0, 255));
	g_Render->DrawOutlinedRect(rect.left - 9, rect.top - 1, 6, rect.bottom - rect.top + 2, Color(0, 0, 0, 255));
//	g_Render->DrawString2(g_Render->font.ESP, rect.left - 6, rect.bottom - height + 1, Color(255, 255, 255, 255), FONT_CENTER, hp);
}

void visuals::Hitmarker()
{
	if (G::hitmarkeralpha < 0.f)
		G::hitmarkeralpha = 0.f;
	else if (G::hitmarkeralpha > 0.f)
		G::hitmarkeralpha -= 0.01f;

	int W, H;
	g_Engine->GetScreenSize(W, H);

	if (G::hitmarkeralpha > 0.f)
	{
		g_Render->Line(W / 2 - 5, H / 2 - 5, W / 2 - 3, H / 2 - 3, Color(int(g_Options.Colors.hitmarker_color[0] * 255.f), int(g_Options.Colors.hitmarker_color[1] * 255.f), int(g_Options.Colors.hitmarker_color[2] * 255.f), (G::hitmarkeralpha * 255.f)));
		g_Render->Line(W / 2 - 5, H / 2 + 5, W / 2 - 3, H / 2 + 3, Color(int(g_Options.Colors.hitmarker_color[0] * 255.f), int(g_Options.Colors.hitmarker_color[1] * 255.f), int(g_Options.Colors.hitmarker_color[2] * 255.f), (G::hitmarkeralpha * 255.f)));
		g_Render->Line(W / 2 + 5, H / 2 - 5, W / 2 + 3, H / 2 - 3, Color(int(g_Options.Colors.hitmarker_color[0] * 255.f), int(g_Options.Colors.hitmarker_color[1] * 255.f), int(g_Options.Colors.hitmarker_color[2] * 255.f), (G::hitmarkeralpha * 255.f)));
		g_Render->Line(W / 2 + 5, H / 2 + 5, W / 2 + 3, H / 2 + 3, Color(int(g_Options.Colors.hitmarker_color[0] * 255.f), int(g_Options.Colors.hitmarker_color[1] * 255.f), int(g_Options.Colors.hitmarker_color[2] * 255.f), (G::hitmarkeralpha * 255.f)));

	}
}

void visuals::SkyChanger()
{
	static auto sv_skyname = g_CVar->FindVar("sv_skyname");

	switch (g_Options.Visuals.SkyboxChanger)
	{
	case 1: //Baggage
		sv_skyname->SetValue("cs_baggage_skybox_");
		break;
	case 2: //Tibet
		sv_skyname->SetValue("cs_tibet");
		break;
	case 3: //Clear Sky
		sv_skyname->SetValue("clearsky");
		break;
	case 4: //Clear Sky HD
		sv_skyname->SetValue("clearsky_hdr");
		break;
	case 5: //Embassy
		sv_skyname->SetValue("embassy");
		break;
	case 6: //Italy
		sv_skyname->SetValue("italy");
		break;
	case 7: //Daylight 1
		sv_skyname->SetValue("sky_cs15_daylight01_hdr");
		break;
	case 8: //Daylight 2
		sv_skyname->SetValue("sky_cs15_daylight02_hdr");
		break;
	case 9: //Daylight 3
		sv_skyname->SetValue("sky_cs15_daylight03_hdr");
		break;
	case 10: //Daylight 4
		sv_skyname->SetValue("sky_cs15_daylight04_hdr");
		break;
	case 11: //Cloudy
		sv_skyname->SetValue("sky_csgo_cloudy01");
		break;
	case 12: //Night 1
		sv_skyname->SetValue("sky_csgo_night02");
		break;
	case 13: //Night 2
		sv_skyname->SetValue("sky_csgo_night02b");
		break;
	case 14: //Night Flat
		sv_skyname->SetValue("sky_csgo_night_flat");
		break;
	case 15: //Day HD
		sv_skyname->SetValue("sky_day02_05_hdr");
		break;
	case 16: //Day
		sv_skyname->SetValue("sky_day02_05");
		break;
	case 17: //Black
		sv_skyname->SetValue("sky_l4d_rural02_ldr");
		break;
	case 18: //Vertigo HD
		sv_skyname->SetValue("vertigo_hdr");
		break;
	case 19: //Vertigo Blue HD
		sv_skyname->SetValue("vertigoblue_hdr");
		break;
	case 20: //Vertigo
		sv_skyname->SetValue("vertigo");
		break;
	case 21: //Vietnam
		sv_skyname->SetValue("vietnam");
		break;
	case 22: //Dusty Sky
		sv_skyname->SetValue("sky_dust");
		break;
	case 23: //Jungle
		sv_skyname->SetValue("jungle");
		break;
	case 24: //Nuke
		sv_skyname->SetValue("nukeblank");
		break;
	case 25: //Office
		sv_skyname->SetValue("office");
		break;
	}
}

void visuals::NightMode()
{		
	static auto sv_skyname = g_CVar->FindVar("sv_skyname");
	if (g_Options.Visuals.nightMode)
	{

		if (!done)
		{

			sv_skyname->SetValue("sky_csgo_night02");

			for (MaterialHandle_t i = g_MaterialSystem->FirstMaterial(); i != g_MaterialSystem->InvalidMaterial(); i = g_MaterialSystem->NextMaterial(i))
			{
				IMaterial *pMaterial = g_MaterialSystem->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, "World textures"))
				{
					pMaterial->ColorModulate(0.10, 0.10, 0.10);
				}
				if (strstr(group, "StaticProp"))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}

				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				done = true;
			}

		}
	}
	else
	{
		if (done)
		{
			for (MaterialHandle_t i = g_MaterialSystem->FirstMaterial(); i != g_MaterialSystem->InvalidMaterial(); i = g_MaterialSystem->NextMaterial(i))
			{
				sv_skyname->SetValue("nukeblank");
				IMaterial *pMaterial = g_MaterialSystem->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, "World textures"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, "StaticProp"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
			}
			done = false;
		}
	}

}

float wallAlpha;
float modelalpha;
float propAlpha;
bool prepared;

void visuals::DoAsusWalls()
{

	C_BaseEntity *pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());


	if (!pLocal || !g_Engine->IsConnected() || !g_Engine->IsInGame())
		return;

	if (g_Options.Visuals.wallalpha != wallAlpha) {
		for (MaterialHandle_t i = g_MaterialSystem->FirstMaterial(); i != g_MaterialSystem->InvalidMaterial(); i = g_MaterialSystem->NextMaterial(i))
		{
			IMaterial *pMaterial = g_MaterialSystem->GetMaterial(i);

			if (!pMaterial)
				continue;

			if (strstr(pMaterial->GetTextureGroupName(), "World textures"))
				pMaterial->AlphaModulate(g_Options.Visuals.wallalpha);
		}
		wallAlpha = g_Options.Visuals.wallalpha;
	}

	if (g_Options.Visuals.propalpha != propAlpha) {
		for (MaterialHandle_t i = g_MaterialSystem->FirstMaterial(); i != g_MaterialSystem->InvalidMaterial(); i = g_MaterialSystem->NextMaterial(i))
		{
			IMaterial *pMaterial = g_MaterialSystem->GetMaterial(i);

			if (!pMaterial)
				continue;

			if (strstr(pMaterial->GetTextureGroupName(), "StaticProp textures")) {
				pMaterial->AlphaModulate(g_Options.Visuals.propalpha);
			}
		}
		propAlpha = g_Options.Visuals.propalpha;
	}

	if (g_Options.Visuals.modelalpha != modelalpha) {
		for (MaterialHandle_t i = g_MaterialSystem->FirstMaterial(); i != g_MaterialSystem->InvalidMaterial(); i = g_MaterialSystem->NextMaterial(i))
		{
			IMaterial *pMaterial = g_MaterialSystem->GetMaterial(i);

			if (!pMaterial)
				continue;

			if (strstr(pMaterial->GetTextureGroupName(), "Model textures"))
				pMaterial->AlphaModulate(g_Options.Visuals.modelalpha);
		}
		modelalpha = g_Options.Visuals.modelalpha;
	}

}

void visuals::renderBeams()
{

	if (g_Options.Visuals.bulletshow && g_Options.Visuals.Enabled)
		return;

	auto local = static_cast<C_BaseEntity*>(g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer()));
	if (!local)
		return;

	for (size_t i = 0; i < logs.size(); i++)
	{

		auto current = logs.at(i);

		current.color = Color(g_Options.Colors.flTracers);

		if (g_Options.Visuals.bulletshow && g_Options.Visuals.Enabled)
			g_DebugOverlay->AddLineOverlay(current.src, current.dst, current.color.r(), current.color.g(), current.color.b(), true, -1.f);


		g_DebugOverlay->AddBoxOverlay(current.dst, Vector(-2, -2, -2), Vector(2, 2, 2), Vector(0, 0, 0), current.color.r(), current.color.g(), current.color.b(), 127, -1.f);

		if (fabs(g_Globals->curtime - current.time) > 5.f)
			logs.erase(logs.begin() + i);
	}
}
