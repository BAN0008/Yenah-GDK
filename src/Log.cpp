#include "Log.hpp"
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace Yenah
{
	void Log::Info(const char *message, ...)
	{
		char *buffer = (char *)malloc(strlen(message) + strlen("Information: \n"));
		sprintf(buffer, "Information: %s\n", message);
		va_list args;
		va_start(args, message);
		vprintf(buffer, args);
		va_end(args);
	}

	void Log::Warn(const char *message, ...)
	{
		char *buffer = (char *)malloc(strlen(message) + strlen("Warning: \n"));
		sprintf(buffer, "Warning: %s\n", message);
		va_list args;
		va_start(args, message);
		vprintf(buffer, args);
		va_end(args);
	}

	void Log::Error(const char *message, ...)
	{
		char *buffer = (char *)malloc(strlen(message) + strlen("Error: \n"));
		sprintf(buffer, "Error: %s\n", message);
		va_list args;
		va_start(args, message);
		vprintf(buffer, args);
		va_end(args);
	}

	void Log::Fatal(const char *message, ...)
	{
		char *buffer = (char *)malloc(strlen(message) + strlen("Fatal Error: \n"));
		sprintf(buffer, "Fatal Error: %s\n", message);
		va_list args;
		va_start(args, message);
		vprintf(buffer, args);
		va_end(args);
	}	
}