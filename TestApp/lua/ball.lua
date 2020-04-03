local Object   = require 'object'
local Renderer = require 'renderer'
local Texture  = require 'texture'
local Input    = require 'input'
local Bullet   = require 'bullet'
local Vector   = require 'vector'
local Physics  = require 'physics'

local Ball = {}
Ball.__index = Ball
setmetatable(Ball, Object)

local texture = Texture.Load("res/test.png")

function Ball:Created(space, x, y)
	self.x = x
	self.y = y
	self.rotation = 0
	--self.phys_body = Physics.Body.Create(1, 1)
	self.phys_body = Physics.Body.CreateStatic()
	self.phys_body:SetPos(x, y)
	self.phys_body:AddToSpace(space)
	--self.phys_shape = Physics.Shape.CreateCircle(self.phys_body, 32, 0, 0)
	self.phys_shape = Physics.Shape.CreateBox(self.phys_body, 64, 64, 0)
	self.phys_shape:AddToSpace(space)
end

function Ball:Update(delta_time)

end

function Ball:Draw()
	self.x, self.y = self.phys_body:GetPos()
	self.rotation = self.phys_body:GetRot()
	Renderer.DrawQuad(self.x, self.y, 64, 64, self.rotation, 32, 32, 1, 1, 1, 0.75, 3, texture)
end

function Ball:Destroyed()
	self.phys_body:RemoveFromSpace()
end

return Ball