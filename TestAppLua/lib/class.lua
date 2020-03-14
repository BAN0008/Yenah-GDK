local function include(other,base)
	for k,v in pairs(base) do
		other[k] = base[k]
	end
end

local function new(class)
	local inc = {class._inherit} or {}
	for _,base in ipairs(inc) do
		include(class,base)
	end

	class.__index = class
	class._init = class._init or function() end
	class._inherit = class._inherit or include

	-- Call constructor
	return setmetatable(class,{__call = function(c,...)
			local o = setmetatable({},c)
			o:_init(...)
			return o
		end})
end

return setmetatable(
	{new = new, include = include},
	{__call = function(_, ...) return new(...) end})