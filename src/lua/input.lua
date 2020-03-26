--[[
	TODO:
		Add set cursor texture function using SDL_CreateCursor()
]]

local ffi = require 'ffi'

ffi.cdef[[
	unsigned int SDL_GetMouseState(int *x, int *y);
	char *GetKeyboardStatePtr();
	int SDL_ShowCursor(int show_cursor);
]]

local SDL2 = ffi.load("SDL2", true)
--local Input = {}
Input = {}
Input._keys = ffi.C.GetKeyboardStatePtr();
Input._key_names = {}

PopulateKeyNames(Input._key_names)

function Input.GetKeyState(key)
	return Input._keys[Input._key_names[key]] == 1
end

function Input.SetMousePosition(x, y)

end

function Input.GetMousePosition()
	local x = ffi.new("int[1]", 0);
	local y = ffi.new("int[1]", 0);
	--ffi.C.SDL_GetMouseState(x, y);
	SDL2.SDL_GetMouseState(x, y);
	return tonumber(x[0]), tonumber(y[0]);
end

function Input.ShowCursor(show_cursor)
	--ffi.C.SDL_ShowCursor(show_cursor);
	SDL2.SDL_ShowCursor(show_cursor);
end

--return Input