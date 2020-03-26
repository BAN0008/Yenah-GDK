-- This script is used by main.lua which is internal to Yenah
local Game = {}

-- This function is called when the game starts
function Game.init()
	texture1 = Texture:Load("res/clover.png");
	texture2 = Texture:Load("res/test.png");
	print("TestApp initialized")
	Camera.SetOrigin(1280 / 2, 720 / 2)
end

-- This function is called before the game entities are updated
function Game.pre_update(delta_time)

end

-- This function is called after the game entities are updated
function Game.post_update(delta_time)
		-- Rotate
		if Input.GetKeyState("Right") then
			Camera.Rotate(0.002 * delta_time)
		end
		if Input.GetKeyState("Left") then
			Camera.Rotate(-0.002 * delta_time)
		end

		-- Scale
		if Input.GetKeyState("Up") then
			x, y = Camera.GetScale()
			Camera.SetScale(x + (delta_time * 0.001), y + (delta_time * 0.001))
		end
		if Input.GetKeyState("Down") then
			x, y = Camera.GetScale()
			Camera.SetScale(x - (delta_time * 0.001), y - (delta_time * 0.001))
		end

		-- Move
		if Input.GetKeyState("D") then
			Camera.Move(0.5 * delta_time, 0);
		end
		if Input.GetKeyState("A") then
			Camera.Move(-0.5 * delta_time, 0);
		end
		if Input.GetKeyState("W") then
			Camera.Move(0, -0.5 * delta_time);
		end
		if Input.GetKeyState("S") then
			Camera.Move(0, 0.5
			 * delta_time);
		end
end

-- This function is called before the game entities are drawn
function Game.pre_draw()
	mx, my = Input.GetMousePosition()
	if Input.GetMouseButtonState("Left") then
		Renderer.DrawQuad(mx - 16, my - 16, 32, 32, 0, 1, 1, 1, 1, 1, texture2)
	else
		Renderer.DrawQuad(mx - 16, my - 16, 32, 32, 0, 1, 1, 1, 1, 1, texture1)
	end
	Renderer.DrawQuad((1280 / 2) - 128, (720 / 2) - 128, 256, 256, 0, 1, 1, 1, 1, 2, texture2)
	for x=0,1280,128 do
		for y=0,720,64 do
			Renderer.DrawQuad(x, y, 64, 64, 0, 1, 1, 1, 1, 0, texture1)
			Renderer.DrawQuad(x + 64, y, 64, 64, 0, 1, 1, 1, 1, 0, texture2)
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