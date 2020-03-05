#include <Yeno/Scripting.hpp>

namespace Yeno
{
	void Scripting::Initialize ()
	{
		L = luaL_newstate();
	}
}