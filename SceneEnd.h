#include "HookIncludes.h"
#include "Global.h"

typedef void(__thiscall *SceneEnd_t)(void *pEcx);

void __fastcall Hooked_SceneEnd(void *pEcx, void *pEdx) {

	static auto ofunc = hooks::viewrender.get_original<SceneEnd_t>(9);

	// Ghost Chams
	if (g_Options.Visuals.FakeAngleChams)
	{
		C_BaseEntity* pLocal = g_EntityList->GetClientEntity(g_Engine->GetLocalPlayer());
		if (pLocal)
		{
			static  IMaterial* ghost_mat = CreateMaterial(false, true, false); //creating a material identical to wireframe
			if (ghost_mat)
			{
				Vector OriginalAngle;
				OriginalAngle = *pLocal->GetEyeAngles();
				pLocal->SetAngle2(Vector(0, Globals::FakeAngle, 0));

				g_RenderView->SetColorModulation(g_Options.Colors.FakeAngleChams);
				g_ModelRender->ForcedMaterialOverride(ghost_mat);
				pLocal->draw_model(1, 200);
				g_ModelRender->ForcedMaterialOverride(nullptr);
				pLocal->SetAngle2(OriginalAngle);
			}
		}
	}
	ofunc(pEcx);

}