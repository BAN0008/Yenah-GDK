#include <Yeno/Log.hpp>
#include <cstdarg>
#include <cstdio>

namespace Yeno
{
	void Log::Info(const char *message, ...)
	{
		va_list args;
		va_start(args, message);
		vprintf(message, args);
		va_end(args);
	}

	void Log::Warn(const char *message, ...)
	{
		va_list args;
		va_start(args, message);
		vprintf(message, args);
		va_end(args);
	}

	void Log::Error(const char *message, ...)
	{
		va_list args;
		va_start(args, message);
		vprintf(message, args);
		va_end(args);
	}

	void Log::Fatal(const char *message, ...)
	{
		va_list args;
		va_start(args, message);
		vprintf(message, args);
		va_end(args);
	}	
}