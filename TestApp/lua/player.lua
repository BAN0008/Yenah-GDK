local Object   = require 'object'
local Renderer = require 'renderer'
local Texture  = require 'texture'
local Input    = require 'input'
local Bullet   = require 'bullet'
local Vector   = require 'vector'
local Physics  = require 'physics'

local Player = {}
Player.__index = Player
setmetatable(Player, Object)

local texture = Texture.Load("res/test.png")

function Player:Created(space, x, y)
	self.x = x
	self.y = y
	self.rotation = 0
	--self.phys_body = Physics.Body.Create(1, 1)
	self.phys_body = Physics.Body.Create(1, Physics.MomentForCircle(1, 32, 0, 0, 0))
	self.phys_body:SetPos(x, y)
	self.phys_body:AddToSpace(space)
	self.phys_shape = Physics.Shape.CreateCircle(self.phys_body, 32, 0, 0)
	self.phys_shape:SetFriction(1)
	--self.phys_shape = Physics.Shape.CreateBox(self.phys_body, 64, 64, 0)
	self.phys_shape:AddToSpace(space)
end

function Player:Update(delta_time)
	if Input.GetKeyState("A") > 1 then
		--self.x = self.x - (0.25 * delta_time)
		self.phys_body:ApplyForceAtLocalPoint(-0.004, 0, 0, 0)
	end
	if Input.GetKeyState("D") > 1 then
		--self.x = self.x + (0.25 * delta_time)
		self.phys_body:ApplyForceAtLocalPoint(0.004, 0, 0, 0)
	end
	if Input.GetKeyState("W") > 1 then
		--self.y = self.y - (0.25 * delta_time)
		self.phys_body:ApplyForceAtLocalPoint(0, -0.004, 0, 0)
	end
	if Input.GetKeyState("S") > 1 then
		--self.y = self.y + (0.25 * delta_time)
		self.phys_body:ApplyForceAtLocalPoint(0, 0.004, 0, 0)
	end
	if Input.GetKeyState("Left") > 1 then
		--self.rotation = self.rotation - (0.001 * delta_time)
		self.phys_body:SetTorque(-0.1)
	end
	if Input.GetKeyState("Right") > 1 then
		--self.rotation = self.rotation + (0.001 * delta_time)
		self.phys_body:SetTorque(0.1)
	end
	if Input.GetMouseButtonState("Left") then
		local bullet = Bullet:Create()
		local mx, my = Input.GetMousePosition()
		self.x, self.y = self.phys_body:GetPos()
		bullet.x = self.x
		bullet.y = self.y
		bullet.vx, bullet.vy = Vector.Normalize(mx - (self.x), my - (self.y))
	end
end

function Player:Draw()
	self.x, self.y = self.phys_body:GetPos()
	self.rotation = self.phys_body:GetRot()
	Renderer.DrawQuad(self.x - 32, self.y - 32, 64, 64, self.rotation, 32, 32, 1, 1, 1, 0.75, 3, texture)
end

function Player:Destroyed()
	self.phys_body:RemoveFromSpace()
end

return Player