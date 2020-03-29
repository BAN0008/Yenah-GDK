#pragma once
#include "Lua.hpp"

namespace Yenah
{
	namespace Profiler
	{
		extern bool show_profiler;

		FFI_EXPORT void BeginFrame();
		FFI_EXPORT void Time(const char *description);
		void SetDrawCalls(unsigned int number);
		void SetVertices(unsigned int number);
		void SetTextures(unsigned int number);
		FFI_EXPORT void SetGameObjects(unsigned int number);
		FFI_EXPORT bool EndFrame();

		void Show();
	}
}