local Object   = require 'object'
local Renderer = require 'renderer'
local Texture  = require 'texture'
local Input    = require 'input'
local Physics  = require 'physics'
local ffi      = require 'ffi'
local Bullet = {}
Bullet.__index = Bullet
setmetatable(Bullet, Object)

local texture = Texture.Load("res/test.png")

local PrintAddress = function(name, addr)
	print(string.format(name .. ": 0x%x", tonumber(ffi.cast("uintptr_t", addr))))
end

function Bullet:Created(space, x, y, vx, vy)
	self.x = x
	self.y = y
	self.vx = vx
	self.vy = vy
	self.phys_body  = Physics.Body.CreateKinematic()
	self.phys_body:SetPos(x, y)
	self.phys_body:AddToSpace(space)
	self.phys_shape = Physics.Shape.CreateCircle(self.phys_body, 4, 0, 0)
	self.phys_shape:SetCollisionType(1)
	self.phys_shape:SetSensor(true)
	self.phys_shape:AddToSpace(space)
	self.phys_body:SetVelocity(vx, vy)
	self.index = Physics.ObjectRefs_Add(self)
	print("new b index: ", tostring(self.index))
	-- Stored in self because otherwise it would be garbage collected
	self.userdata = ffi.new("unsigned int[1]")
	self.userdata[0] = self.index
	self.phys_body:SetUserData(self.userdata)
	PrintAddress("new bullet body", self.phys_body.cpBody)
	local ud = self.phys_body:GetUserData()
	PrintAddress("new ud", ud)
	print("derefed new b index: " .. tostring(ffi.cast("unsigned int *", ud)[0]))
end

function Bullet:Update(delta_time)
	--self.x = self.x + (self.vx * delta_time)
	--self.y = self.y + (self.vy * delta_time)
	self.x, self.y = self.phys_body:GetPos()
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

function Bullet:Destroyed()
	self.phys_shape:RemoveFromSpace()
	self.phys_body:RemoveFromSpace()
	Physics.ObjectRefs[self.index] = nil
end

return Bullet