#include "Lua.hpp"
#include "Log.hpp"
#include <lua_ffi.h>

#include <cstring>

namespace Yenah
{
	namespace Lua
	{
		lua_State *gL;
		EngineConfig::window_c EngineConfig::window;

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
			EngineConfig::window = {1280, 720, (char*)"Yenah Engine", nullptr};

			// Create engine configuration tables
			lua_newtable(gL);
			lua_setglobal(gL, "window");

			// Read configuration from config.lua
			if (luaL_dofile(gL, "config.lua"))
			{
				Log::Error("Failed to execute config.lua");
				Log::Error(lua_tostring(gL, -1));
				lua_pop(gL, 1);
				return;
			}

			lua_getglobal(gL, "window");

			lua_getfield(gL, -1, "title");
			if (lua_isstring(gL, -1)) EngineConfig::window.title = (char *)lua_tostring(gL, -1);
			lua_pop(gL, 1);

			lua_getfield(gL, -1, "width");
			if (lua_isnumber(gL, -1)) EngineConfig::window.width = lua_tointeger(gL, -1);
			lua_pop(gL, 1);

			lua_getfield(gL, -1, "height");
			if (lua_isnumber(gL, -1)) EngineConfig::window.height = lua_tointeger(gL, -1);
			lua_pop(gL, 1);

			lua_getfield(gL, -1, "icon");
			if (lua_isstring(gL, -1)) EngineConfig::window.icon = (char *)lua_tostring(gL, -1);
			lua_pop(gL, 1);

			lua_pop(gL, 1); // Pop table

			//Log::Info("Window Title: %s", EngineConfig::window.title);
			//Log::Info("Window Width: %d", EngineConfig::window.width);
			//Log::Info("Window Height: %d", EngineConfig::window.height);
			//Log::Info("Window Icon: %s", EngineConfig::window.icon);
		}

		void Start()
		{
			lua_newtable(gL);
			lua_setglobal(gL, "yenah");

			// Load our FFI bindings
			if (luaL_loadstring(gL, lua_ffi_code) || lua_pcall(gL, 0, 0, 0))
			{
				Log::Fatal("Failed to execute internal ffi.lua");
				Log::Fatal(lua_tostring(gL, -1));
				lua_pop(gL, 1);
				return;
			}

			// Load yenah.lua
			if (luaL_dofile(gL, "yenah.lua"))
			{
				Log::Fatal("Failed to execute yenah.lua");
				Log::Fatal(lua_tostring(gL, -1));
				lua_pop(gL, 1);
				return;
			}

			lua_getglobal(gL, "yenah");

			// Call yenah.start
			lua_getfield(gL, -1, "start");
			if (lua_pcall(gL, 0, 0, 0))
			{
				Log::Error("Failed to run yenah.start()");
				Log::Error(lua_tostring(gL, -1));
				lua_pop(gL, 1);
			}
		}

		void UpdateObjects(double dt)
		{
			lua_getfield(gL, -1, "update");
			lua_pushnumber(gL, dt);
			if (lua_pcall(gL, 1, 0, 0))
			{
				Log::Fatal("Failed to run yenah.update()");
				Log::Fatal(lua_tostring(gL, -1));
				lua_pop(gL, 1);
			}
		}

		void DrawObjects()
		{
			lua_getfield(gL, -1, "draw");
			if (lua_pcall(gL, 0, 0, 0))
			{
				Log::Fatal("Failed to run yenah.draw()");
				Log::Fatal(lua_tostring(gL, -1));
				lua_pop(gL, 1);
			}
		}

		void Cleanup()
		{
			lua_close(gL);
		}
	}
}