local Player = require 'game.player'

function yenah.start()
	local p = Player(4,7)
	p:state()

	-- if you can get this to work right, the god damn
	--local t = setmetatable(yenah.Test(420), {__index = yenah.Test})
	--print(t:getX())
	local t = yenah.Test(420)
	print(yenah.Test.getX(t))
	
end

function yenah.update(dt)
	-- loop through the objects and update them
end

function yenah.draw()
	-- loop through the objects and draw them
end