#pragma once

namespace Yenah
{
	namespace Window
	{
		bool Create(const char *title, int width, int height);
		void Destroy();

		bool ProcessEvents(); // Return false if application should quit
		void SwapBuffers();
	};
}