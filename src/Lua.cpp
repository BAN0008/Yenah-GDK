#include "Lua.hpp"
#include "Log.hpp"
#include "Config.hpp"
#include <texture_lua.h>
#include <main_lua.h>
#include <SDL.h>

namespace Yenah
{
	namespace Lua
	{
		lua_State *gL;

		bool Initialize()
		{
			// Create a new Lua State and open the STD library
			if ((gL = luaL_newstate()) == NULL)
			{
				Log::Fatal("Unable to create a Lua State");
				return false;
			}
			luaL_openlibs(gL);

			return true;
		}

		void ReadConfig()
		{
			Config::window_title  = "Yenah Engine";
			Config::window_width  = 1280;
			Config::window_height = 720;
			Config::window_icon   = nullptr;

			// Create engine configuration tables
			lua_newtable(gL);
			lua_setglobal(gL, "window");
			lua_newtable(gL);
			lua_setglobal(gL, "debug_mode");

			// Read configuration from config.lua
			if (luaL_dofile(gL, "lua/config.lua"))
			{
				Log::Error("Failed to execute config.lua");
				Log::Error(lua_tostring(gL, -1));
				lua_pop(gL, 1);
				return;
			}

			// Read window settings
			lua_getglobal(gL, "window");
			lua_getfield(gL, -1, "title");
			if (lua_isstring(gL, -1)) Config::window_title = (char *)lua_tostring(gL, -1);
			lua_pop(gL, 1);
			lua_getfield(gL, -1, "width");
			if (lua_isnumber(gL, -1)) Config::window_width = lua_tointeger(gL, -1);
			lua_pop(gL, 1);
			lua_getfield(gL, -1, "height");
			if (lua_isnumber(gL, -1)) Config::window_height = lua_tointeger(gL, -1);
			lua_pop(gL, 1);
			lua_getfield(gL, -1, "icon");
			if (lua_isstring(gL, -1)) Config::window_icon = (char *)lua_tostring(gL, -1);
			lua_pop(gL, 1);
			lua_pop(gL, 1); // Pop table

			// Read debug overlay settings
			lua_getglobal(gL, "debug_mode");
			lua_getfield(gL, -1, "enable_overlay");
			if (lua_isboolean(gL, -1)) Config::debug_enable_overlay = lua_toboolean(gL, -1);
			lua_pop(gL, 1);
			lua_getfield(gL, -1, "overlay_toggle_key");
			if (lua_isstring(gL, -1)) Config::debug_overlay_toggle_key = SDL_GetKeyFromName(lua_tostring(gL, -1));
			lua_pop(gL, 1);
			lua_pop(gL, 1); //Pop table
		}

		void Start()
		{
			if (luaL_dostring(gL, texture_lua_code)) {
				Log::Error("Failed to execute texture.lua");
				Log::Error(lua_tostring(gL, -1));
				lua_pop(gL, 1);
			}

			if (luaL_dostring(gL, main_lua_code)) {
				Log::Error("Failed to execute main.lua");
				Log::Error(lua_tostring(gL, -1));
				lua_pop(gL, 1);
			}
		}

		void Cleanup()
		{
			lua_close(gL);
		}
	}
}