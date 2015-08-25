--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:Player
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-04 02:48:32
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-11 21:56:57
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

Object = require 'libs.classic'

Player = Object:extend()
function Player:new(id, team, x, y, orientation)
	if not zappy.teams[team] then
		zappy.teams[team] = {
			nbr = 1,
			color = {math.random(0, 255), math.random(0, 255), math.random(0, 255), 255}
		}
	else
		zappy.teams[team].nbr = zappy.teams[team].nbr + 1
	end

	print("New player", id, team, x, y, orientation)
	self.id = tonumber(id)
	self.x = tonumber(x)
	self.y = tonumber(y)
	self.team = team
	self.sprite = test1()
	self.sprite.orientation = noraml(orientation)
end

function Player:update(dt)
	self.sprite:update(dt)
end

function Player:draw(x, y)
	self.sprite:draw(x, y)
end