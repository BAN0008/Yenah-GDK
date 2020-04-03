-- Yenah:object.lua
local LinkedList = require 'linked_list'

local Object = {}
Object.__index = Object
Object.objects = LinkedList.New()

function Object:Create(...)
	local t = setmetatable({}, self)
	t.destroyed = false
	Object.objects:PushFront(t)
	t:Created(unpack({...}))
	return t
end

function Object:Destroy()
	self.destroyed = true
	Object.objects:Remove(self)
	self:Destroyed()
end

local ObjectReferenceMT = {}
ObjectReferenceMT.__mode = "kv"
ObjectReferenceMT.__call = function(self)
	if self._object ~= nil then
		if self._object.destroyed == false then
			return self._object
		else
			return nil
		end
	end
	return self._object
end

function Object:GetRef()
	local t = setmetatable({}, ObjectReferenceMT)
	t._object = self
	return t
end

function Object:Created()

end

function Object:Update(delta_time)

end

function Object:Draw()

end

function Object:Destroyed()

end

return Object