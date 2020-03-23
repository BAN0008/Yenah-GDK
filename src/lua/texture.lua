local ffi = require 'ffi'

ffi.cdef[[
	void *CreateTexture(const char *fname);
	void DeleteTexture(void *id);
]]

--local Texture = {}
Texture = {}
Texture.__index = Texture

function Texture:Load(fname)
	local t = setmetatable({}, Texture)
	t.id = ffi.new("void *", ffi.C.CreateTexture(fname))
	t.id = ffi.gc(t.id, ffi.C.DeleteTexture)
	return t
end

--return Texture