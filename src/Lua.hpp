#pragma once

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}
//#include <lua.hpp>

namespace Yenah 
{
	namespace Lua
	{
		extern lua_State *gL;

		bool Initialize();
		void ReadConfig();
		void PopulateEngineCalls();
		void Cleanup();

		namespace EngineConfig
		{
			struct window_c
			{
				int width, height;
				char *title, *icon;
			};
			extern struct window_c window;
		}
	}
}
