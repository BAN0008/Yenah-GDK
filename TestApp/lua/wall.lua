local Object   = require 'object'
local Renderer = require 'renderer'
local Texture  = require 'texture'
local Input    = require 'input'
local Bullet   = require 'bullet'
local Vector   = require 'vector'
local Physics  = require 'physics'

local Wall = {}
Wall.__index = Wall
setmetatable(Wall, Object)

local texture = Texture.Load("res/pixel.png")

function Wall:Created(space, x, y, w, h)
	self.x = x
	self.y = y
	self.w = w
	self.h = h
	self.rotation = 0
	--self.phys_body = Physics.Body.Create(1, 1)
	self.phys_body = Physics.Body.CreateStatic()
	self.phys_body:SetPos(x, y)
	self.phys_body:AddToSpace(space)
	self.phys_shape = Physics.Shape.CreateBox(self.phys_body, self.w, self.h, 0)
	self.phys_shape:SetFriction(0.4)
	self.phys_shape:AddToSpace(space)
end

function Wall:Update(delta_time)

end

function Wall:Draw()
	self.x, self.y = self.phys_body:GetPos()
	self.rotation = self.phys_body:GetRot()
	Renderer.DrawQuad(self.x - (self.w / 2), self.y - (self.h / 2), self.w, self.h, self.rotation, self.w / 2, self.h / 2, 0, 0, 0, 1, 1, texture)
	Renderer.DrawQuad(self.x - 8, self.y - 8, 16, 16, 0, 8, 8, 1, 0, 0, 1, 3, texture)
end

function Wall:Destroyed()
	self.phys_body:RemoveFromSpace()
end

return Wall