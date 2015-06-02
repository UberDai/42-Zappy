--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:lib
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-01 18:38:23
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-02 20:26:16
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

sprite1 = require 'assets.sprite1'
test1 = require 'assets.test1'

function newPlayer(team)
	local player = {}
	player.x = math.random(0, zappy.widthMap)
	player.y = math.random(0, zappy.heightMap)
	if team == 'sprite1' then
		player.sprite = sprite1:new()
	else
		player.sprite = test1:new()
	end
	player.update = function (self, dt) self.sprite:update(dt) end
	player.draw = function (self, x, y) self.sprite:draw(x, y) end
	return player
end
