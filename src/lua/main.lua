package.path = package.path .. ";./lua/?.lua"

local game   = require 'game'
local ffi    = require 'ffi'
local Object = require 'object'

ffi.cdef[[
	bool ProcessEvents();
	void RenderFrame();

	void BeginFrame();
	void Time(const char *description);
	void SetGameObjects(unsigned int number);
	bool EndFrame();

	unsigned long SDL_GetPerformanceCounter();
	unsigned long SDL_GetPerformanceFrequency();
]]

local SDL2 = ffi.load("SDL2", true)
game.init()

local running = true
local pause = false
local prev_time = tonumber(SDL2.SDL_GetPerformanceCounter())
while running do
	ffi.C.BeginFrame()
	running = ffi.C.ProcessEvents()
	ffi.C.Time("Event processing")

	-- Calculate delta time
	local current_time = tonumber(SDL2.SDL_GetPerformanceCounter())
	local delta_time = ((current_time - prev_time) / tonumber(SDL2.SDL_GetPerformanceFrequency())) * 1000
	prev_time = current_time

	-- Update game
	if not pause then
		game.pre_update(delta_time)

		-- Update all objects
		object = Object.objects.front
		while object ~= nil do
			object:Update(delta_time)
			object = object._next
		end
		game.post_update(delta_time)
	end

	ffi.C.Time("Lua game update")

	-- Render game
	game.pre_draw()

	-- Draw all objects
	object = Object.objects.front
	while object ~= nil do
		object:Draw()
		object = object._next
	end

	game.post_draw()

	ffi.C.SetGameObjects(Object.objects.count)
	ffi.C.Time("Lua game draw")
	ffi.C.RenderFrame()
	pause = ffi.C.EndFrame()
end
game.quit()
while (Object.objects.count > 0) do
	Object.objects:Remove(Object.objects.front)
end