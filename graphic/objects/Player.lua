--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:Player
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-04 02:48:32
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-09 17:21:46
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

Object = require 'libs.classic'

Player = Object:extend()
function Player:new(id, team, x, y, orientation)
	print("New player", id, team, x, y, orientation)
	self.id = tonumber(id)
	self.x = tonumber(x)
	self.y = tonumber(y)
	if team == 'sprite1' then
		self.sprite = sprite1()
	else
		self.sprite = test1()
	end
end

function Player:update(dt)
	self.sprite:update(dt)
end

function Player:draw(x, y)
	self.sprite:draw(x, y)
end
