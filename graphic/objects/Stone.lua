--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:Stone
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-04 21:14:32
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-04 21:19:54
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

Object = require 'libs.classic'

Stone = Object:extend()
Stone.image = {}
Stone.image[0] = love.graphics.newImage("assets/00.png")
Stone.image[1] = love.graphics.newImage("assets/01.png")
Stone.image[2] = love.graphics.newImage("assets/02.png")
Stone.image[3] = love.graphics.newImage("assets/03.png")
Stone.image[4] = love.graphics.newImage("assets/04.png")
Stone.image[5] = love.graphics.newImage("assets/05.png")
Stone.image[6] = love.graphics.newImage("assets/06.png")

function Stone:draw(x, y)
	if self.id == 0 then
		love.graphics.draw(self.image, zappy.scale * x, zappy.scale * y, 0, zappy.scale * 0.5, zappy.scale * 0.5, -50, -50)
	elseif self.id == 1 then
		love.graphics.draw(self.image, zappy.scale * x, zappy.scale * y, 0, zappy.scale * 0.5, zappy.scale * 0.5, -55, -30)
	elseif self.id == 2 then
		love.graphics.draw(self.image, zappy.scale * x, zappy.scale * y, 0, zappy.scale * 0.5, zappy.scale * 0.5, -75, -35)
	elseif self.id == 3 then
		love.graphics.draw(self.image, zappy.scale * x, zappy.scale * y, 0, zappy.scale * 0.5, zappy.scale * 0.5, -95, -40)
	elseif self.id == 4 then
		love.graphics.draw(self.image, zappy.scale * x, zappy.scale * y, 0, zappy.scale * 0.5, zappy.scale * 0.5, -75, -10)
	elseif self.id == 5 then
		love.graphics.draw(self.image, zappy.scale * x, zappy.scale * y, 0, zappy.scale * 0.5, zappy.scale * 0.5, -95, -15)
	elseif self.id == 6 then
		love.graphics.draw(self.image, zappy.scale * x, zappy.scale * y, 0, zappy.scale * 0.5, zappy.scale * 0.5, -115, -20)
	end
end

function Stone:new(x, y, id)
	self.id = tonumber(id)
	self.x = tonumber(x)
	self.y = tonumber(y)
	self.image = Stone.image[tonumber(id)]
	self.draw = drawStone
end
