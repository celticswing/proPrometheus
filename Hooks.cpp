#include "HookIncludes.h"
#include "HooksList.h"
#include "Listener.h"
#include "WelcomeMessage.h"

UCHAR szFileSys[255], szVolNameBuff[255];
DWORD dwMFL, dwSysFlags;
DWORD dwSerial;
LPCTSTR szHD = "C:\\";

namespace hooks
{
    vfunc_hook panel;
    vfunc_hook client;
    vfunc_hook clientmode;
    vfunc_hook modelrender;
    vfunc_hook prediction;
    vfunc_hook surface;
    vfunc_hook eventmanager;
    vfunc_hook viewrender;
    vfunc_hook engine;
	vfunc_hook d3d;


    void initialize()
    {
		GetVolumeInformation(szHD, (LPTSTR)szVolNameBuff, 255, &dwSerial, &dwMFL, &dwSysFlags, (LPTSTR)szFileSys, 255);
        client.setup(g_CHLClient);
        client.hook_index(36, hkFrameStageNotify);
        client.hook_index(21, hkCreateMove);


        clientmode.setup(g_ClientMode);
        clientmode.hook_index(18, hkOverrideView);
        clientmode.hook_index(35, hkGetViewModelFOV);
        clientmode.hook_index(44, hkDoPostScreenSpaceEffects);

        panel.setup(g_Panel);
        panel.hook_index(41, hkPaintTraverse);

        modelrender.setup(g_ModelRender);
        modelrender.hook_index(21, hkDrawModelExecute);
//		modelrender.hook_index(84, hkFindMaterial);

		viewrender.setup(g_RenderView);
		viewrender.hook_index(9, Hooked_SceneEnd);

        surface.setup(g_Surface);
        surface.hook_index(82, hkPlaySound);

		engine.setup(g_Engine);
		engine.hook_index(27, IsConnected);

		initializeskins();

		g_Engine->ClientCmd_Unrestricted("toggleconsole");
		Sleep(100);
		g_Engine->ClientCmd_Unrestricted("clear");
		Sleep(100);

		g_CVar->ConsoleColorPrintf(Color(255, 0, 0), "[Promethe.us] ");
		Sleep(100);
		g_Engine->ClientCmd_Unrestricted("echo has successfully injected.\n");
		PlaySoundA(WelcomeMessage, NULL, SND_ASYNC | SND_MEMORY);
		

		window = FindWindow("Valve001", NULL);
		G::OldWindow = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)handlers::Hooked_WndProc);


		if (g_D3DDevice9)
		{
			d3d.setup(g_D3DDevice9);
			d3d.hook_index(16, handlers::Hooked_Reset);
			d3d.hook_index(42, handlers::Hooked_EndScene);
		}



		item_purchase::singleton()->initialize();


    }

    void cleanup()
    {

        item_purchase::singleton()->remove();
        client.unhook_all();
        prediction.unhook_all();
        clientmode.unhook_all();
        panel.unhook_all();
        modelrender.unhook_all();
        surface.unhook_all();
        viewrender.unhook_all();
        engine.unhook_all();
		d3d.unhook_all();
    }

}