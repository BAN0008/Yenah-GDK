#include "Log.hpp"
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace Yenah
{
	void Log::Info(const char *message, ...)
	{
		char *buffer = (char *)malloc(strlen(message) + strlen("Information: \n") + 2);
		sprintf(buffer, "Information: %s\n", message);
		va_list args;
		va_start(args, message);
		vprintf(buffer, args);
		va_end(args);
		free(buffer);
	}

	void Log::Warn(const char *message, ...)
	{
		char *buffer = (char *)malloc(strlen(message) + strlen("Warning: \n") + 2);
		sprintf(buffer, "Warning: %s\n", message);
		va_list args;
		va_start(args, message);
		vprintf(buffer, args);
		va_end(args);
		free(buffer);
	}

	void Log::Error(const char *message, ...)
	{
		char *buffer = (char *)malloc(strlen(message) + strlen("Error: \n") + 2);
		sprintf(buffer, "Error: %s\n", message);
		va_list args;
		va_start(args, message);
		vprintf(buffer, args);
		va_end(args);
		free(buffer);
	}

	void Log::Fatal(const char *message, ...)
	{
		char *buffer = (char *)malloc(strlen(message) + strlen("Fatal Error: \n") + 2);
		sprintf(buffer, "Fatal Error: %s\n", message);
		va_list args;
		va_start(args, message);
		vprintf(buffer, args);
		va_end(args);
		free(buffer);
	}	
}