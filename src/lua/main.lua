local game = require 'lua.game'
local ffi = require 'ffi'

ffi.cdef[[
	bool ProcessEvents();
	void RenderFrame();

	void BeginFrame();
	void Time(const char *description);
	bool EndFrame();
]]

game.init()
local running = true
local pause = false
local prev_time = os.clock()
while running do
	ffi.C.BeginFrame()
	running = ffi.C.ProcessEvents()
	ffi.C.Time("Event processing");
	local current_time = os.clock();
	local delta_time = current_time - prev_time
	prev_time = current_time
	ffi.C.Time("Calculate delta time");
	if not pause then
		game.pre_update()
		game.post_update()
	end
	game.pre_draw()
	game.post_draw()
	ffi.C.Time("Lua game update");
	ffi.C.RenderFrame();
	pause = ffi.C.EndFrame();
end
game.quit()