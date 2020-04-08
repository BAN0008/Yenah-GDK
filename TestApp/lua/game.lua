local Renderer = require 'renderer'
local Texture  = require 'texture'

local Object   = require 'object'
local Player   = require 'player'
local Ball     = require 'ball'
local Box      = require 'box'
local Wall     = require 'wall'

local Physics  = require 'physics'

local Game = {}

local phys_space

local ffi = require 'ffi'

local PrintAddress = function(name, addr)
	print(string.format(name .. ": 0x%x", tonumber(ffi.cast("uintptr_t", addr))))
end

local delete_object = function(space, obj_index, data)
	print("del_obj Gamer")

	local index = ffi.cast("unsigned int *", obj_index)[0]
	print(index)

	local object = Physics.ObjectRefs[index]
	object:Destroy()
	print("del_obj Gamer end")
end
local delete_object_cb = ffi.new("cpPostStepFunc", delete_object)

local bulletBeginFunc = function(arb_cdata, space, data)
	local arb = Physics.Arbiter.Create(arb_cdata)
	local shape_a, shape_b = arb:GetShapes()
	
	local bullet_shape = nil
	local other_shape = nil
	if shape_a:GetCollisionType() == 1 then
		bullet_shape = shape_a
		other_shape = shape_b
	else
		if shape_b:GetCollisionType() == 1 then
			bullet_shape = shape_b
			other_shape = shape_a
		end
	end

	if other_shape:GetCollisionType() == 1 then
		return false
	end
	if other_shape:GetCollisionType() == 2 then
		return false
	end

	-- If delete_object is passed directly instead of delete_object_cb then a new luajit ffi cb object is created every time.
	-- luajit has a limit on the number of cb objects that can exist at once.
	PrintAddress("bullet_shape.ud_ptr", bullet_shape.body:GetUserData())
	PrintAddress("bullet_shape.body.cpBody", bullet_shape.body.cpBody)
	print("bullet_shape.ud: " .. tostring(ffi.cast("unsigned int *", bullet_shape.body:GetUserData())[0]))
	Physics.Handler.AddPostStep(space, delete_object_cb, bullet_shape.body:GetUserData(), nil)
	print("Gamer")
	return true
end

-- This function is called when the game starts
function Game.init()
	phys_space = Physics.Space.Create()
	Physics.Handler.AddWildcard(phys_space, 1, bulletBeginFunc, nil, nil, nil)
	--phys_space:SetDamping(0.99)
	phys_space:SetGravity(0, 0.001)

	texture1 = Texture.Load("res/clover.png")
	Player:Create(phys_space, 64, 64)
	--Ball:Create(phys_space, 512, 640)
	Box:Create(phys_space, 1280 / 2, 512, 512, 32)
	Wall:Create(phys_space, 1280 / 2, 16, 1280, 32)
	Wall:Create(phys_space, 1280 / 2, 720 - 16, 1280, 32)
	Wall:Create(phys_space, 1280 - 16, 720 / 2, 32, 656)
	Wall:Create(phys_space, 16, 720 / 2, 32, 656)
end

-- This function is called before the game entities are updated
function Game.pre_update(delta_time)
	phys_space:Step(delta_time)
end

-- This function is called after the game entities are updated
function Game.post_update(delta_time)

end

-- This function is called before the game entities are drawn
function Game.pre_draw()
	for x=0,1280,64 do
		for y=0,720,64 do
			Renderer.DrawQuad(x, y, 64, 64, 0, 32, 32, 1, 1, 1, 1, 0, texture1)
		end
	end
end

-- This function is called after the game entities are drawn
function Game.post_draw()

end

-- This function is called when the game quits
function Game.quit()

end

return Game