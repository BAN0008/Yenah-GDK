local Renderer = require 'renderer'
local Texture  = require 'texture'

local Player   = require 'player'

-- This script is used by main.lua which is internal to Yenah
local Game = {}

-- This function is called when the game starts
function Game.init()
	texture1 = Texture.Load("res/clover.png")
	print("TestApp initialized")
	Player:Create()
end

-- This function is called before the game entities are updated
function Game.pre_update(delta_time)

end

-- This function is called after the game entities are updated
function Game.post_update(delta_time)

end

-- This function is called before the game entities are drawn
function Game.pre_draw()
	for x=0,1280,64 do
		for y=0,720,64 do
			Renderer.DrawQuad(x, y, 64, 64, 0, 1, 1, 1, 1, 0, texture1)
		end
	end
end

-- This function is called after the game entities are drawn
function Game.post_draw()

end

-- This function is called when the game quits
function Game.quit()

end

return Game