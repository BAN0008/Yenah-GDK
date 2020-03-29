#pragma once
#include "Lua.hpp"

namespace Yenah
{
	namespace Camera
	{
		FFI_EXPORT void UpdateCamera(float x, float y, float scale_x, float scale_y, float radians, float origin_x, float origin_y);
	}
}