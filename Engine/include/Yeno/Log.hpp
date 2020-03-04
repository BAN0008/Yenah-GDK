#pragma once

namespace Yeno
{
	namespace Log
	{
		void  Info(const char *message, ...);
		void  Warn(const char *message, ...);
		void Error(const char *message, ...);
		void Fatal(const char *message, ...);
	}
}