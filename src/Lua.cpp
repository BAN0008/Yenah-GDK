#include "Lua.hpp"
#include "Log.hpp"
#include "Config.hpp"
#include <main_lua.h>
#include <input_lua.h>
#include <texture_lua.h>
#include <renderer_lua.h>
#include <camera_lua.h>
#include <vector_lua.h>
#include <object_lua.h>
#include <physics_lua.h>
#include <linked_list_lua.h>
#include <SDL.h>
#include <string.h>

namespace Yenah
{
	namespace Lua
	{
		lua_State *gL;
		bool reload = false;

		int PopulateKeyNames(lua_State *L)
		{
			for (int i = 0; i < 255; i++) {
				const char *name = SDL_GetKeyName(SDL_GetKeyFromScancode((SDL_Scancode)i));
				if (name != "") {
					lua_pushnumber(L, i);
					lua_setfield(L, -2, name);
				}
			}
			return 0;
		}

		int ModuleLoader(lua_State *L)
		{
			const char *module_name = lua_tostring(L, -1);
			if (strcmp(module_name, "vector") == 0) {
				luaL_loadstring(L, vector_lua_code);
				return 1;
			}
			if (strcmp(module_name, "object") == 0) {
				luaL_loadstring(L, object_lua_code);
				return 1;
			}
			if (strcmp(module_name, "physics") == 0) {
				luaL_loadstring(L, physics_lua_code);
				return 1;
			}
			if (strcmp(module_name, "texture") == 0) {
				luaL_loadstring(L, texture_lua_code);
				return 1;
			}
			if (strcmp(module_name, "camera") == 0) {
				luaL_loadstring(L, camera_lua_code);
				return 1;
			}
			if (strcmp(module_name, "renderer") == 0) {
				luaL_loadstring(L, renderer_lua_code);
				return 1;
			}
			if (strcmp(module_name, "input") == 0) {
				luaL_loadstring(L, input_lua_code);
				return 1;
			}
			if (strcmp(module_name, "linked_list") == 0) {
				luaL_loadstring(L, linked_list_lua_code);
				return 1;
			}

			char buffer[2048];
			snprintf(buffer, 2048, "\n\tno module '%s', Lua.cpp:Yenah::Lua::ModuleLoader", module_name);
			lua_pushstring(L, buffer);
			//lua_pushnil(L);
			return 1;
		}

		bool Initialize()
		{
			// Create a new Lua State and open the STD library
			if ((gL = luaL_newstate()) == nullptr)
			{
				Log::Fatal("Unable to create a Lua State");
				return false;
			}
			luaL_openlibs(gL);

			lua_register(gL, "PopulateKeyNames", PopulateKeyNames);

			//Setup module loader
			lua_getglobal(gL, "package");
			lua_getfield(gL, -1, "loaders");
			if (!lua_istable(gL, -1)) Log::Error("package.loaders not a table");
			int i = 1;
			while (true) {
				lua_pushnumber(gL, i);
				lua_gettable(gL, -2);
				if (lua_isnil(gL, -1)) break;
				i++;
				lua_pop(gL, 1);
			}
			lua_pop(gL, 1);
			lua_pushnumber(gL, i);
			lua_pushcfunction(gL, ModuleLoader);
			lua_settable(gL, -3);
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
			if (lua_isstring(gL, -1)) Config::debug_overlay_toggle_key = SDL_GetScancodeFromName(lua_tostring(gL, -1));
			lua_pop(gL, 1);
			lua_pop(gL, 1); //Pop table
		}

		void Start()
		{
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