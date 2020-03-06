#pragma once
extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}
#include <lua.hpp>

namespace Yeno
{
	namespace Scripting
	{
		lua_State *L;

		void Initialize ();
	}
}