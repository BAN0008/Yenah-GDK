local Class = require "lib.class"

local Entity = Class
{
	_init = function(self,x,y)
		self.x = x
		self.y = y

		self.destroyCb = nil;
		self.levelPersistant = false;
	end
}

function Entity:update(dt)
end

function Entity:draw()
end

function Entity:destroy()
	if self.destroyCb then
		self.destroyCb()
	end
end

function Entity:move(x,y)
	self.x = self.x + x;
	self.y = self.y + y;
end

function Entity:onCollide(other)
end

function Entity:onDestroy(fn)
	assert(type(fn) == 'function', "The callback must be a function")
	self.destroyCb = fn
end

return Entity