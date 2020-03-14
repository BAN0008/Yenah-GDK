#pragma once

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
	#include <luajit.h>
}

namespace Yenah 
{
	namespace Lua
	{
		extern lua_State *gL;

		bool Initialize();
		void ReadConfig();
		void Start();

		void UpdateObjects(double dt);
		void DrawObjects();

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
