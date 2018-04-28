#include "Render.h"


void speclist()
{
			auto& style = ImGui::GetStyle();
			style.Colors[ImGuiCol_TitleBg] = ImColor(21, 21, 21, 255);
			style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(21, 21, 21, 255);
			style.Colors[ImGuiCol_TitleBgActive] = ImColor(21, 21, 21, 255);
			style.Colors[ImGuiCol_CloseButton] = ImColor(0, 0, 0, 0);
			style.Colors[ImGuiCol_CloseButtonHovered] = ImColor(0, 0, 0, 0);
			style.Colors[ImGuiCol_CloseButtonActive] = ImColor(0, 0, 0, 0);

			if (ImGui::Begin("Spectator List", &g_Options.Misc.SpecList, ImVec2(200.f, 150.f), 0.0f, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse));
			{

				C_BaseEntity *local = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
				RECT scrn = g_Render->GetViewport();
				if (local)
				{
					for (int i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
					{
						// Get the entity
						C_BaseEntity *pEntity = g_EntityList->GetClientEntity(i);
						player_info_t pinfo;
						if (pEntity && pEntity != local)
						{
							if (g_Engine->GetPlayerInfo(i, &pinfo) && !pEntity->IsAlive() && !pEntity->IsDormant())
							{
								HANDLE obs = pEntity->GetObserverTargetHandle();
								if (obs)
								{
									C_BaseEntity *pTarget = g_EntityList->GetClientEntityFromHandle(obs);
									player_info_t pinfo2;

									if (pTarget && pTarget->GetIndex() == local->GetIndex())
									{
										if (g_Engine->GetPlayerInfo(pTarget->GetIndex(), &pinfo2))
										{

											pinfo.name[16] = 0, pinfo2.name[16] = 0;
											strcat(pinfo.name, "..."), strcat(pinfo2.name, "...");
											puts(pinfo.name), puts(pinfo2.name);



											char buf[255]; sprintf(buf, "%s <= Spec => %s", pinfo.name, pinfo2.name);
											ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), pinfo.name);
											ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), pinfo2.name);
										}
									}
								}
							}
						}
					}
				}
			}
					
			ImGui::End();

}
