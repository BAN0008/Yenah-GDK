#include <Yeno/Config.hpp>

namespace Yeno
{
	int  Config::batch_size = 1000000;
	bool Config::use_persistent_mapping = false;
	bool Config::vsync = true;
	bool Config::antialiasing = false;
	
	bool Config::GetVSync()
	{
		return vsync;
	}
	
	void Config::SetVSync(bool value)
	{
		vsync = value;
	}
	
	bool Config::GetAntialiasing()
	{
		return antialiasing;
	}
	
	void Config::SetAntialiasing(bool value)
	{
		antialiasing = value;
	}
}