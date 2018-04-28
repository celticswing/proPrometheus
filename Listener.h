#pragma once
#include "singleton.hpp"
#include "MiscClasses.h"
#include "Interfaces.h"
#include "Interface.h"
#include "Sounds.h"
#include "DamageIndicator.h"

char* HitgroupToName(int hitgroup)
{
	switch (hitgroup)
	{
	case 1:
		return "head";
	case 6:
		return "arm";
	case 7:
		return "leg";
	case 3:
		return "stomach";
	default:
		return "body";
	}
}


std::vector<cbullet_tracer_info> logs;

#pragma comment(lib, "winmm.lib")
class item_purchase

	: public singleton<item_purchase>
{
	class item_purchase_listener
		: public IGameEventListener2
	{
	public:
		void start()
		{
			g_EventManager->AddListener(this, "item_purchase", false);
			g_EventManager->AddListener(this, "player_hurt", false);
			g_EventManager->AddListener(this, "bullet_impact", false);
		}
		void stop()
		{
			g_EventManager->RemoveListener(this);
		}
		void FireGameEvent(IGameEvent *event) override
		{
			singleton()->on_fire_event(event);
		}
		int GetEventDebugID(void) override
		{
			return 42 /*0x2A*/;
		}
	};

public:

	static item_purchase* singleton()
	{
		static item_purchase* instance = new item_purchase;
		return instance;
	}

	void initialize()
	{
		listener.start();
	}

	void remove()
	{
		listener.stop();
	}

	void on_fire_event(IGameEvent* event)
	{

		if (!strcmp(event->GetName(), "item_purchase"))
		{

			C_BaseEntity* local = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
			auto buyer = event->GetInt("userid");
			std::string gun = event->GetString("weapon");

			if (strstr(gun.c_str(), "molotov")
				|| strstr(gun.c_str(), "nade")
				|| strstr(gun.c_str(), "kevlar")
				|| strstr(gun.c_str(), "decoy")
				|| strstr(gun.c_str(), "suit")
				|| strstr(gun.c_str(), "flash")
				|| strstr(gun.c_str(), "vest")
				|| strstr(gun.c_str(), "cutter")
				|| strstr(gun.c_str(), "defuse")
				)  return;

			auto player_index = g_Engine->GetPlayerForUserID(buyer);
			C_BaseEntity* player = (C_BaseEntity*)g_EntityList->GetClientEntity(player_index);
			player_info_t pinfo;

			if (player && local && g_Engine->GetPlayerInfo(player_index, &pinfo))
			{
	
				if (g_Options.Misc.eventlogs2)
				{
					gun.erase(gun.find("weapon_"), 7);
					if (player->GetTeamNum() != local->GetTeamNum())
					{
/*						if (g_ChatElement)
						{
							g_ChatElement->ChatPrintf(0, 0, " ""\x04""[ENEMY]  %s bought %s\n", pinfo.name, gun.c_str());
						} */
						G::Msg("[ENEMY]  %s bought %s\n", pinfo.name, gun.c_str());
					}
				}
			}

		}
		if (!strcmp(event->GetName(), "player_hurt"))
		{
			if (g_Engine->GetPlayerForUserID(event->GetInt("attacker")) == g_Engine->GetLocalPlayer() &&
				g_Engine->GetPlayerForUserID(event->GetInt("userid")) != g_Engine->GetLocalPlayer())
			{
				if (g_Options.Visuals.Hitbox)
					visuals::Hitbox(g_Engine->GetPlayerForUserID(event->GetInt("userid")));
			}

			auto bitch = event->GetInt("userid");
			auto coolguy49 = event->GetInt("attacker");
			int dmg = event->GetInt("dmg_health");

			C_BaseEntity* local = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
			auto bitch_index = g_Engine->GetPlayerForUserID(bitch);
			auto coolguy49_index = g_Engine->GetPlayerForUserID(coolguy49);
			C_BaseEntity* bitch_ = (C_BaseEntity*)g_EntityList->GetClientEntity(bitch_index);
			C_BaseEntity* coolguy49_ = (C_BaseEntity*)g_EntityList->GetClientEntity(coolguy49_index);

			if (coolguy49_ == local)
			{
				G::hitmarkeralpha = 1.f;
				switch (g_Options.Misc.Hitsound)
				{
				case 0: break;
				case 1: PlaySoundA(rawData, NULL, SND_ASYNC | SND_MEMORY); break; // COD
				case 2:	PlaySoundA(roblox, NULL, SND_ASYNC | SND_MEMORY); break; // Anime
				case 3:	PlaySoundA(china, NULL, SND_ASYNC | SND_MEMORY); break; // CHINA
				case 4: g_Engine->ClientCmd_Unrestricted("play buttons\\arena_switch_press_02.wav"); // Zeus/Metal
				}

			}

			if (g_Options.Visuals.DamageIndicator)
			{
				DamageIndicator_t DmgIndicator;
				DmgIndicator.iDamage = dmg;
				DmgIndicator.Player = bitch_;
				DmgIndicator.flEraseTime = local->GetTickBase() * g_Globals->interval_per_tick + 3.f;
				DmgIndicator.bInitialized = false;
				damage_indicators.data.push_back(DmgIndicator);
			}


			if (g_Options.Misc.eventlogs)
			{

				int iAttacker = g_Engine->GetPlayerForUserID(event->GetInt("attacker"));
				int iVictim = g_Engine->GetPlayerForUserID(event->GetInt("userid"));

				if (iAttacker == g_Engine->GetLocalPlayer() && iVictim != g_Engine->GetLocalPlayer())
				{

					auto pVictim = reinterpret_cast<C_BaseEntity*>(g_EntityList->GetClientEntity(iVictim));
					player_info_t pinfo;
					g_Engine->GetPlayerInfo(iVictim, &pinfo);
					
					g_CVar->ConsoleColorPrintf(Color(255, 0, 0, 255), "[Promethe.us] ");
					G::Msg("Hit %s in the %s for %d (%d health remaining) \n", pinfo.name, HitgroupToName(event->GetInt("hitgroup")), event->GetInt("dmg_health"), event->GetInt("health"));
			
				}
			}

		}
		if (!strcmp(event->GetName(), "bullet_impact"))
		{		
			C_BaseEntity* LocalPlayer = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());

			if (LocalPlayer)
			{
				auto index = g_Engine->GetPlayerForUserID(event->GetInt("userid"));

				if (index != g_Engine->GetLocalPlayer())
					return;

				auto local = static_cast<C_BaseEntity*>(g_EntityList->GetClientEntity(index));
				if (!local)
					return;

				Vector position(event->GetFloat("x"), event->GetFloat("y"), event->GetFloat("z"));

				Ray_t ray;
				ray.Init(local->GetEyePosition(), position);

				CTraceFilter filter;
				filter.pSkip = local;

				trace_t tr;
				g_EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

				logs.push_back(cbullet_tracer_info(local->GetEyePosition(), position, g_Globals->curtime, g_Options.Colors.flTracers));
					

				if (!local)
					return;

				for (size_t i = 0; i < logs.size(); i++)
				{
					auto current = logs.at(i);
					current.color = Color(g_Options.Colors.flTracers); //color of local player's tracers
					BeamInfo_t beamInfo;
					beamInfo.m_nType = TE_BEAMPOINTS;
					beamInfo.m_pszModelName = "sprites/physbeam.vmt";
					beamInfo.m_nModelIndex = -1;
					beamInfo.m_flHaloScale = 0.0f;
					beamInfo.m_flLife = g_Options.Visuals.flTracersDuration;
					beamInfo.m_flWidth = g_Options.Visuals.flTracersWidth;
					beamInfo.m_flEndWidth = g_Options.Visuals.flTracersWidth;
					beamInfo.m_flFadeLength = 0.0f;
					beamInfo.m_flAmplitude = 2.0f;
					beamInfo.m_flBrightness = 255.f;
					beamInfo.m_flSpeed = 0.2f;
					beamInfo.m_nStartFrame = 0;
					beamInfo.m_flFrameRate = 0.f;
					beamInfo.m_flRed = current.color.r();
					beamInfo.m_flGreen = current.color.g();
					beamInfo.m_flBlue = current.color.b();
					beamInfo.m_nSegments = 2;
					beamInfo.m_bRenderable = true;
					beamInfo.m_nFlags = FBEAM_ONLYNOISEONCE | FBEAM_NOTILE | FBEAM_HALOBEAM;

					beamInfo.m_vecStart = LocalPlayer->GetEyePosition();
					beamInfo.m_vecEnd = current.dst;
					if (g_Options.Visuals.bulletshow && g_Options.Visuals.Enabled)
					{
						auto beam = g_pViewRenderBeams->CreateBeamPoints(beamInfo);
						if (beam)
							g_pViewRenderBeams->DrawBeam(beam);
					}

					logs.erase(logs.begin() + i);
				}
			}
		
		}
	
	}

	

private:
	item_purchase_listener  listener;
};

item_purchase purchase;