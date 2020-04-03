-- Yenah:linked_list.lua
local LinkedList = {}
LinkedList.__index = LinkedList

function LinkedList.New()
	return setmetatable({count=0}, LinkedList)
end

-- Inserts new_value after existing_value. Returns new_value
function LinkedList:Insert(new_value, existing_value)
	new_value._next = existing_value._next
	if new_value._next ~= nil then
		new_value._next._prev = new_value
	end
	new_value._prev = existing_value
	existing_value._next = new_value
	self.count = self.count + 1
	return new_value
end

-- Removes value
function LinkedList:Remove(value)
	if value._removed ~= nil then
		print("LinkedList: Tried to remove an item twice")
		print(debug.traceback())
		return
	end
	value._removed = true
	if value._prev ~= nil then
		value._prev._next = value._next 
	end
	if value._next ~= nil then
		value._next._prev = value._prev
	end
	if self.front == value then
		self.front = value._next
	end
	if self.back == value then
		self.back = value._prev
	end
	self.count = self.count - 1
end

-- Inserts new_value at the front. Returns new_value
function LinkedList:PushFront(new_value)
	new_value._next = self.front
	if self.front ~= nil then
		self.front._prev = new_value
	end
	self.front = new_value
	if self.back == nil then
		self.back = new_value
	end
	self.count = self.count + 1
	return new_value
end

-- Adds new_value at the end. Returns new_value
function LinkedList:PushBack(new_value)
	new_value._prev = self.back
	if self.back ~= nil then
		self.back._next = new_value
	end
	self.back = new_value
	if self.front == nil then
		self.front = new_value
	end
	self.count = self.count + 1
	return new_value
end

return LinkedList