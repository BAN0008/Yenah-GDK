#pragma once

namespace Yeno
{
	namespace Config
	{
		extern int  batch_size;
		extern bool use_persistent_mapping;
		extern bool vsync;
		extern bool antialiasing;
		
		bool GetVSync();
		void SetVSync(bool value);
		bool GetAntialiasing();
		void SetAntialiasing(bool value);
	}
}