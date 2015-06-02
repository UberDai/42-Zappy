--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:Event
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-02 17:38:23
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-02 20:30:01
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

local e = {}

e['w'] = function ()
	if zappy.players[1].sprite.orientation ~= 'north' then
		zappy.players[1].sprite.orientation = 'north'
	else
		zappy.players[1].x = zappy.players[1].x - 1
	end
end

e['s'] = function ()
	if zappy.players[1].sprite.orientation ~= 'south' then
		zappy.players[1].sprite.orientation = 'south'
	else
		zappy.players[1].x = zappy.players[1].x + 1
	end
end

e['a'] = function ()
		if zappy.players[1].sprite.orientation ~= 'east' then
			zappy.players[1].sprite.orientation = 'east'
		else
			zappy.players[1].y = zappy.players[1].y - 1
		end
end

e['d'] = function ()
		if zappy.players[1].sprite.orientation ~= 'west' then
			zappy.players[1].sprite.orientation = 'west'
		else
			zappy.players[1].y = zappy.players[1].y + 1
		end
end

e['0'] = function () table.insert(Stones, love.newStone(love.math.random(0, 9), love.math.random(0, 9), 0)) end
e['1'] = function () table.insert(Stones, love.newStone(love.math.random(0, 9), love.math.random(0, 9), 1)) end
e['2'] = function () table.insert(Stones, love.newStone(love.math.random(0, 9), love.math.random(0, 9), 2)) end
e['3'] = function () table.insert(Stones, love.newStone(love.math.random(0, 9), love.math.random(0, 9), 3)) end
e['4'] = function () table.insert(Stones, love.newStone(love.math.random(0, 9), love.math.random(0, 9), 4)) end
e['5'] = function () table.insert(Stones, love.newStone(love.math.random(0, 9), love.math.random(0, 9), 5)) end
e['6'] = function () table.insert(Stones, love.newStone(love.math.random(0, 9), love.math.random(0, 9), 6)) end


return e
