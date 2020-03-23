-- This script is used by main.lua which is internal to Yenah
local Game = {}

-- This function is called when the game starts
function Game.init()
	texture1 = Texture:Load("res/clover.png");
	print("TestApp initialized")
end

-- This function is called before the game entities are updated
function Game.pre_update()

end

-- This function is called after the game entities are updated
function Game.post_update()

end

-- This function is called before the game entities are drawn
function Game.pre_draw()

end

-- This function is called after the game entities are drawn
function Game.post_draw()

end

-- This function is called when the game quits
function Game.quit()

end

return Game