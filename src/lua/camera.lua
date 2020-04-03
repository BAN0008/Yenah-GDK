-- Yenah:camera.lua
local ffi = require 'ffi'

ffi.cdef[[
		void UpdateCamera(float x, float y, float scale_x, float scale_y, float radians, float origin_x, float origin_y);
]]

local Camera = {}
Camera.x = 0
Camera.y = 0
Camera.scale_x = 1
Camera.scale_y = 1
Camera.origin_x = 0
Camera.origin_y = 0
Camera.radians = 0

function Camera.SetPosition(x, y)
	Camera.x = x
	Camera.y = y
	Camera._Update()
end

function Camera.GetPosition()
	return Camera.x, Camera.y
end

function Camera.Move(x, y)
	Camera.x = Camera.x + x
	Camera.y = Camera.y + y
	Camera._Update()
end

function Camera.SetRotation(radians)
	Camera.radians = radians
	Camera._Update()
end

function Camera.GetRotation()
	return Camera.radians
end

function Camera.Rotate(radians)
	Camera.radians = Camera.radians + radians
	Camera._Update()
end

function Camera.SetScale(x, y)
	Camera.scale_x = x
	Camera.scale_y = y
	Camera._Update()
end

function Camera.GetScale()
	return Camera.scale_x, Camera.scale_y
end

function Camera.SetOrigin(x, y)
	Camera.origin_x = x
	Camera.origin_y = y
	Camera._Update()
end

function Camera._Update()
	if Camera.radians > 2 * math.pi then
		Camera.radians = Camera.radians - (2 * math.pi)
	end
	if Camera.radians < -2 * math.pi then
		Camera.radians = Camera.radians + (2 * math.pi)
	end
	ffi.C.UpdateCamera(Camera.x, Camera.y, Camera.scale_x, Camera.scale_y, Camera.radians, Camera.origin_x, Camera.origin_y)
end

return Camera