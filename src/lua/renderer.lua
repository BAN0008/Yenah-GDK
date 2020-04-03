-- Yenah:renderer.lua
local ffi = require 'ffi'

ffi.cdef[[
		void DrawQuad(float x, float y, float w, float h, float radians, float origin_x, float origin_y, float r, float g, float b, float a, unsigned int layer, void *texture);
]]

local Renderer = {}

function Renderer.DrawQuad(x, y, w, h, radians, origin_x, origin_y, r, g, b, a, layer, texture)
	ffi.C.DrawQuad(x, y, w, h, radians, origin_x, origin_y, r, g, b, a, layer, texture.id)
end

return Renderer