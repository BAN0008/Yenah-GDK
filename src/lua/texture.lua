local ffi = require 'ffi'

ffi.cdef[[
	void *CreateTexture(const char *fname);
	void DeleteTexture(void *id);
]]

local Texture = {}
Texture.__index = Texture
Texture._cache = {}

function Texture.Load(fname)
	if Texture._cache[fname] ~= nil then
		return Texture._cache[fname]
	end

	local t = setmetatable({}, Texture)
	t.id = ffi.new("void *", ffi.C.CreateTexture(fname))
	--t.id = ffi.gc(t.id, ffi.C.DeleteTexture)

	local delete_texture = function(id)
		for k, v in pairs(Texture._cache) do
			if v.id == id then
				Texture._cache[k] = nil
				break
			end
		end
		ffi.C.DeleteTexture(id)
	end

	t.id = ffi.gc(t.id, delete_texture)

	Texture._cache[fname] = t
	return t
end

return Texture