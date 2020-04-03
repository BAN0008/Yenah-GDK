local Renderer = require 'renderer'
local Texture  = require 'texture'

local Object   = require 'object'
local Player   = require 'player'
local Ball     = require 'ball'
local Box      = require 'box'
local Wall      = require 'wall'

local Physics  = require 'physics'

local Game = {}

local phys_space

-- This function is called when the game starts
function Game.init()
	phys_space = Physics.Space.Create()
	--phys_space:SetDamping(0.99)
	phys_space:SetGravity(0, 0.001)

	texture1 = Texture.Load("res/clover.png")
	Player:Create(phys_space, 64, 64)
	--Ball:Create(phys_space, 512, 640)
	Box:Create(phys_space, 1280 / 2, 512, 512, 32)
	Wall:Create(phys_space, 1280 / 2, 16, 1280, 32)
	Wall:Create(phys_space, 1280 / 2, 720 - 16, 1280, 32)
	Wall:Create(phys_space, 1280 - 16, 720 / 2, 32, 656)
	Wall:Create(phys_space, 16, 720 / 2, 32, 656)
end

-- This function is called before the game entities are updated
function Game.pre_update(delta_time)
	phys_space:Step(delta_time)
end

-- This function is called after the game entities are updated
function Game.post_update(delta_time)

end

-- This function is called before the game entities are drawn
function Game.pre_draw()
	for x=0,1280,64 do
		for y=0,720,64 do
			Renderer.DrawQuad(x, y, 64, 64, 0, 32, 32, 1, 1, 1, 1, 0, texture1)
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