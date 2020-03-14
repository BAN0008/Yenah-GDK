local Class = require "lib.class"
local Entity = require "lib.entity"

local Player = Class
{
	-- We inherit from the Entity class
	_inherit = Entity,
	-- Our contructor function
	_init = function(self,x,y)
		Entity._init(self,x,y)
		self.type = "player"
	end,
}

-- A class method
function Player:state()
	print("Player is at: ",self.x,self.y)
end

function Player:update(dt)
	print("from player ", dt)
end

return Player