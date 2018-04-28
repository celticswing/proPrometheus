#pragma once
#include "HookIncludes.h"
static CreateClientClassFn GetWearableCreateFn()
{
	auto clazz = g_CHLClient->GetAllClasses();

	while (strcmp(clazz->m_pNetworkName, "CEconWearable"))
		clazz = clazz->m_pNext;

	return clazz->m_pCreateFn;
}
IClientNetworkable* CL_CreateDLLEntity(int iEnt, int iClass, int iSerialNum)
{
	ClientClass* pClient = g_CHLClient->GetAllClasses();
	if (!pClient)
		return false;

	while (pClient)
	{
		if (pClient->m_ClassID == iClass)
			return pClient->m_pCreateFn(iEnt, iSerialNum);
		pClient = pClient->m_pNext;
	}
	return false;
}

int GetGloveSkinByMenu(int gloveIndex, int skinIndex)
{
	if (gloveIndex == 0) // bloudhound
	{
		switch (skinIndex)
		{
		case 0:
			return 10006; //Charred
		case 1:
			return 10007; //Snakebite
		case 2:
			return 10008; //Bronzed
		case 3:
			return 10039; //Guerrilla
		default:
			return 0;
		}
	}
	else if (gloveIndex == 1) // Sport
	{
		switch (skinIndex)
		{
		case 0:
			return 10038; //Hedge Maze
		case 1:
			return 10037; //Pandora's Box
		case 2:
			return 10018; //Supercondutor
		case 3:
			return 10019; //Arid
		case 4:
			return 10048; //Vice
		case 5:
			return 10047; //Omega
		case 6:
			return 10045; //Amphibious
		case 7:
			return 10046; //Bronze Morph
		default:
			return 0;
		}
	}
	else if (gloveIndex == 2) // Driver
	{
		switch (skinIndex)
		{
		case 0:
			return 10013; //Lunar Weave
		case 1:
			return 10015; //Convoy
		case 2:
			return 10016; //Crimson Weave
		case 3:
			return 10040; //Diamond Back
		case 4:
			return 10043; //Overtake
		case 5:
			return 10044; //Racing Green
		case 6:
			return 10041; //King Snake
		case 7:
			return 10042; //Imperial Plaid
		default:
			return 0;
		}
	}
	else if (gloveIndex == 3) // Wraps
	{
		switch (skinIndex)
		{
		case 0:
			return 10009; //Leather
		case 1:
			return 10010; //Spruce DDPAT
		case 2:
			return 10021; //Slaughter
		case 3:
			return 10036; //Badlands
		case 4:
			return 10053; //Cobalt Skulls
		case 5:
			return 10054; //Overprint
		case 6:
			return 10055; //Duct Tape
		case 7:
			return 10056; //Arboreal
		default:
			return 0;
		}
	}
	else if (gloveIndex == 4) // Moto
	{
		switch (skinIndex)
		{
		case 0:
			return 10024; //Eclipse
		case 1:
			return 10026; //Spearmint
		case 2:
			return 10027; //BOOM!
		case 3:
			return 10028; //Cool Mint
		case 4:
			return 10050; //Turtle
		case 5:
			return 10051; //Transport
		case 6:
			return 10052; //Polygon
		case 7:
			return 10049; //POW!
		default:
			return 0;
		}
	}
	else if (gloveIndex == 5) // Specialist
	{
		switch (skinIndex)
		{
		case 0:
			return 10030; //Forest DDPAT
		case 1:
			return 10033; //Crimson Komono
		case 2:
			return 10034; //Emerald Web
		case 3:
			return 10035; //Foundation
		case 4:
			return 10061; //Crimson Web
		case 5:
			return 10062; //Buckshot
		case 6:
			return 10063; //Fade
		case 7:
			return 10064; //Mogul
		default:
			return 0;
		}
	}
	else if (gloveIndex == 6) //hydra
	{
		switch (skinIndex)
		{
		case 0:
			return 10060; //Hardened
		case 1:
			return 10059; //Rattler
		case 2:
			return 10058; //Mangrove
		case 3:
			return 10057; //Emerald
		default:
			return 0;
		}
	}
	else
		return 0;
}

bool isKnife(int id)
{
	switch (id)
	{
	case 42:
	case 500:
	case 506:
	case 505:
	case 508:
	case 507:
	case 515:
	case 514:
	case 512:
	case 516:
	case 59:
		return true;
	}
	return false;
}


void GloveChanger()
{
	C_BaseEntity *local = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
	player_info_t localPlayerInfo;
	if (!g_Engine->GetPlayerInfo(g_Engine->GetLocalPlayer(), &localPlayerInfo)) return;


	CBaseHandle* wearables = (CBaseHandle*)local->GetWearables(); // auto wearables = local->GetWearables();

	static CBaseHandle glove_handle = 0;

	auto glove = reinterpret_cast<CGloves*>(g_EntityList->GetClientEntityFromHandle(wearables[0]));

	if (!glove) // There is no glove
	{
		// Try to get our last created glove
		auto our_glove = reinterpret_cast<CGloves*>(g_EntityList->GetClientEntityFromHandle(glove_handle));

		if (our_glove) // Our glove still exists
		{
			wearables[0] = glove_handle;
			glove = our_glove;
		}
	}

	if (!local->IsAlive())
	{
		// We are dead but we have a glove, destroy it
		if (glove)
		{
			glove->SetDestroyedOnRecreateEntities();
			glove->Release();
		}

		return;
	}



	if (!glove)
	{
		int iEnt = g_EntityList->GetHighestEntityIndex() + 1;
		int iSerialNumber = RandomInt(0x0, 0xFFF);

		CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)CL_CreateDLLEntity(iEnt, (int)ClassID::CEconWearable, iSerialNumber);
		if (pWeapon)
		{
			auto m_Index = iEnt | (iSerialNumber << 16);
			glove_handle = m_Index;
			*(DWORD*)((DWORD)local + offsetz.DT_BaseCombatCharacter.m_hMyWearables) = m_Index;
			glove = (CGloves*)g_EntityList->GetClientEntity(iEnt);
		}

		{
			static auto set_abs_origin_fn = reinterpret_cast<void(__thiscall*)(void*, const Vector&)>
				(U::FindPattern("client.dll", (BYTE*)"\x55\x8B\xEC\x83\xE4\xF8\x51\x53\x56\x57\x8B\xF1", "xxxxxxxxxxxx"));

			static const Vector new_pos = { 10000.f, 10000.f, 10000.f };

			set_abs_origin_fn(glove, new_pos);
		}
	}



	*reinterpret_cast<int*>(uintptr_t(glove) + 0x64) = -1;


	if (glove)
	{
		switch (g_Options.Skinchanger.glove)
		{
		case 1: //Bloodhound Gloves
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5027 || *glove->FallbackPaintKit() != GetGloveSkinByMenu(0, g_Options.Skinchanger.gloveskin))
			{
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5027;
				*glove->FallbackPaintKit() = GetGloveSkinByMenu(0, g_Options.Skinchanger.gloveskin);
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl"));
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 2: //Sport Gloves
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5030 || *glove->FallbackPaintKit() != GetGloveSkinByMenu(1, g_Options.Skinchanger.gloveskin))
			{
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl"));
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5030;
				*glove->FallbackPaintKit() = GetGloveSkinByMenu(1, g_Options.Skinchanger.gloveskin);
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;

				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 3://SLICK GLOVES
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5031 || *glove->FallbackPaintKit() != GetGloveSkinByMenu(2, g_Options.Skinchanger.gloveskin))
			{
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl"));
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5031;
				*glove->FallbackPaintKit() = GetGloveSkinByMenu(2, g_Options.Skinchanger.gloveskin);
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;

				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 4://LEATHER HANDWRAPS
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5032 || *glove->FallbackPaintKit() != GetGloveSkinByMenu(3, g_Options.Skinchanger.gloveskin))
			{
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl"));
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5032;
				*glove->FallbackPaintKit() = GetGloveSkinByMenu(3, g_Options.Skinchanger.gloveskin);
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;

				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 5://MOTORCYCLE GLOVES
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5033 || *glove->FallbackPaintKit() != GetGloveSkinByMenu(4, g_Options.Skinchanger.gloveskin))
			{
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl"));
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5033;
				*glove->FallbackPaintKit() = GetGloveSkinByMenu(4, g_Options.Skinchanger.gloveskin);
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;

				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 6://SPECIALIST GLOVES
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5034 || *glove->FallbackPaintKit() != GetGloveSkinByMenu(5, g_Options.Skinchanger.gloveskin))
			{
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5034;
				*glove->FallbackPaintKit() = GetGloveSkinByMenu(5, g_Options.Skinchanger.gloveskin);
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;

				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		case 7://HYDRA GLOVES
		{
			if (*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() != 5035 || *glove->FallbackPaintKit() != GetGloveSkinByMenu(6, g_Options.Skinchanger.gloveskin))
			{
				glove->SetGloveModelIndex(g_ModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl"));
				*glove->m_AttributeManager()->m_Item()->ItemDefinitionIndex() = 5035;
				*glove->FallbackPaintKit() = GetGloveSkinByMenu(6, g_Options.Skinchanger.gloveskin);
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->m_AttributeManager()->m_Item()->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;

				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
		break;
		}
	}
}