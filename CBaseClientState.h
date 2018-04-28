#pragma once
#include <cstdint>

class CBaseClientState
{
public:
	void ForceFullUpdate()
	{
		*(uint32_t*)((uintptr_t)this + 0x174) = -1;
//		*reinterpret_cast<int*>(std::uintptr_t(this) + 0x174) = -1; //g_ClientState
//		*reinterpret_cast< int * >(g_ClientState + 0x174) = -1;
	};
};
