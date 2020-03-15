local ffi = require 'ffi'

ffi.cdef[[
	typedef struct Test Test;

	Test* Test_new(int x_);
	void Test_delete(Test* __this);
	int Test_getX(const Test* __this);
	void Test_setX(Test* __this, int x_);
]]

local Test = {}

function Test:getX()
	return ffi.C.Test_getX(self.raw)
end

function Test:setX(x)
	ffi.C.Test_setX(self.raw, x)
end

Test = setmetatable({}, {
	__index = Test,
	__call = function(_,x)
		local self = {raw = ffi.C.Test_new(x)}
		ffi.gc(self.raw, ffi.C.Test_delete)
		return setmetatable(self, {__index = Test})
	end})

yenah.Test = Test