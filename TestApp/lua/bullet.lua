local Object   = require 'object'
local Renderer = require 'renderer'
local Texture  = require 'texture'
local Input    = require 'input'
local Bullet = {}
Bullet.__index = Bullet
setmetatable(Bullet, Object)

local texture = Texture.Load("res/test.png")

function Bullet:Created()
	self.x = 0
	self.y = 0
end

function Bullet:Update(delta_time)
	self.x = self.x + (self.vx * delta_time)
	self.y = self.y + (self.vy * delta_time)
	if self.x < 0 or self.x > 1280 then
		self:Destroy()
		return
	end
	if self.y < 0 or self.y > 720 then
		self:Destroy()
	end
end

function Bullet:Draw()
	Renderer.DrawQuad(self.x - 4, self.y - 4, 8, 8, 0, 4, 4, 1, 1, 1, 1, 2, texture)
end

return Bullet