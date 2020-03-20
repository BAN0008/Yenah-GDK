local game = require 'lua.game'
local ffi = require 'ffi'

ffi.cdef[[
	bool ProcessEvents();
]]

game.init()
local running = true
local prev_time = os.clock()
while running do
	local current_time = os.clock();
	local delta_time = current_time - prev_time
	prev_time = current_time
	running = ffi.C.ProcessEvents()
	game.pre_update()
	game.post_update()
	game.pre_draw()
	game.post_draw()
end
game.quit()