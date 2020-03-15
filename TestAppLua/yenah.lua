local Player = require 'game.player'

function yenah.start()
	local p = Player(4,7)
	p:state()

	local t = yenah.Test(420)
	print(t:getX())
	t:setX(69)
	print(t:getX())
	
end

function yenah.update(dt)
	-- loop through the objects and update them
end

function yenah.draw()
	-- loop through the objects and draw them
end