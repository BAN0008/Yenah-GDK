local Object   = require 'object'
local Renderer = require 'renderer'
local Texture  = require 'texture'
local Input    = require 'input'
local Bullet   = require 'bullet'
local Vector   = require 'vector'
local Player = {}
Player.__index = Player
setmetatable(Player, Object)

local texture = Texture.Load("res/test.png")

function Player:Created()
	self.x = 0
	self.y = 0
	self.rotation = 0
end

function Player:Update(delta_time)
	if Input.GetKeyState("A") > 1 then
		self.x = self.x - (0.25 * delta_time)
	end
	if Input.GetKeyState("D") > 1 then
		self.x = self.x + (0.25 * delta_time)
	end
	if Input.GetKeyState("W") > 1 then
		self.y = self.y - (0.25 * delta_time)
	end
	if Input.GetKeyState("S") > 1 then
		self.y = self.y + (0.25 * delta_time)
	end
	if Input.GetKeyState("Left") then
		self.rotation = self.rotation - (0.001 * delta_time)
	end
	if Input.GetKeyState("Right") then
		self.rotation = self.rotation + (0.001 * delta_time)
	end
	if Input.GetMouseButtonState("Left") then
		bullet = Bullet:Create()
		local mx, my = Input.GetMousePosition()
		bullet.x = self.x + 32
		bullet.y = self.y + 32
		bullet.vx, bullet.vy = Vector.Normalize(mx - (self.x + 32), my - (self.y + 32))
	end
end

function Player:Draw()
	Renderer.DrawQuad(self.x, self.y, 64, 64, self.rotation, 1, 1, 1, 0.75, 2, texture)
end

return Player