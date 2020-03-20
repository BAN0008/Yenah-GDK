#pragma once
#define FFI_EXPORT extern "C" __attribute__ ((visibility ("default")))

namespace Yenah
{
	namespace Window
	{
		bool Create(const char *title, int width, int height);
		void Destroy();

		FFI_EXPORT bool ProcessEvents();
	};
}