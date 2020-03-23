#pragma once

#ifdef UNIX
	#define FFI_EXPORT extern "C" __attribute__ ((visibility ("default")))
#endif
#ifdef WIN32
	#define FFI_EXPORT extern "C" __declspec(dllexport)
#endif

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
		void Cleanup();
	}
}
