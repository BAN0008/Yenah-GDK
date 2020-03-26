local game = require 'lua.game'
local ffi = require 'ffi'

ffi.cdef[[
	bool ProcessEvents();
	void RenderFrame();

	void BeginFrame();
	void Time(const char *description);
	bool EndFrame();

	unsigned long SDL_GetPerformanceCounter();
	unsigned long SDL_GetPerformanceFrequency();
]]

local SDL2 = ffi.load("SDL2", true)
game.init()

local running = true
local pause = false
--local prev_time = tonumber(ffi.C.SDL_GetPerformanceCounter())
local prev_time = tonumber(SDL2.SDL_GetPerformanceCounter())
while running do
	ffi.C.BeginFrame()
	running = ffi.C.ProcessEvents()
	ffi.C.Time("Event processing");
	--local current_time = tonumber(ffi.C.SDL_GetPerformanceCounter());
	local current_time = tonumber(SDL2.SDL_GetPerformanceCounter());
	--local delta_time = ((current_time - prev_time) / tonumber(ffi.C.SDL_GetPerformanceFrequency())) * 1000
	local delta_time = ((current_time - prev_time) / tonumber(SDL2.SDL_GetPerformanceFrequency())) * 1000
	prev_time = current_time
	if not pause then
		game.pre_update(delta_time)
		game.post_update(delta_time)
	end
	game.pre_draw()
	game.post_draw()
	ffi.C.Time("Lua game update");
	ffi.C.RenderFrame();
	pause = ffi.C.EndFrame();
end
game.quit()