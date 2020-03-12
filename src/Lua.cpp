#include "Lua.hpp"
#include "Log.hpp"

#include <cstring>

namespace Yenah::Lua
{
	lua_State *gL;
	struct EngineConfig::window_c EngineConfig::window;
	void ReadConfig()
	{
		// Create our engine configuration tables
		lua_newtable(gL);
		lua_setglobal(gL, "window");
		bool useDefault = false;
		if (luaL_dofile(gL, "config.lua"))
		{
			useDefault = true;
			Log::Error("problem loading and calling config.lua\n");
		}
		// Zero out our config
		EngineConfig::window = {0, 0, nullptr, nullptr};

		// Set our engine configuration values
		lua_getglobal(gL, "window");
		lua_pushnil(gL);
		while(lua_next(gL, -2) != 0)
		{
			if (!strcmp(lua_tostring(gL, -2), "width"))
				EngineConfig::window.width = lua_tonumber(gL, -1);
			else if (!strcmp(lua_tostring(gL, -2), "height"))
				EngineConfig::window.height = lua_tonumber(gL, -1);
			else if (!strcmp(lua_tostring(gL, -2), "icon"))
				EngineConfig::window.icon = (char*)lua_tostring(gL, -1);
			else if (!strcmp(lua_tostring(gL, -2), "title"))
				EngineConfig::window.title = (char*)lua_tostring(gL, -1);

			lua_pop(gL, 1);
		}
		if (EngineConfig::window.width == 0 || EngineConfig::window.height == 0)
		{
			EngineConfig::window.width = 800;
			EngineConfig::window.height = 600;
		}
		if (EngineConfig::window.title == nullptr)
			EngineConfig::window.title = (char*)"Yenah Game Engine";

	}

	bool Initialize()
	{
		// Create a new Lua State and open the STD library
		if ((gL = luaL_newstate()) == NULL)
		{
			Log::Fatal("unabled to create a Lua State\n");
			return false;
		}
		luaL_openlibs(gL);
		
		// Read our config.lua
		ReadConfig();
		return true;
	}

	void Cleanup()
	{
		lua_close(gL);
	}
}
