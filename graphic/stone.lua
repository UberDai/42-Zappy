--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:stone
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-01 19:02:59
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-01 22:33:39
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

function drawStone(self, offx, offy)
	if self.id == 0 then
		love.graphics.draw(self.image, offx * scale, offy * scale, 0, scale * 0.5, scale * 0.5, -50, -50)
	elseif self.id == 1 then
		love.graphics.draw(self.image, offx * scale, offy * scale, 0, scale * 0.5, scale * 0.5, -55, -30)
	elseif self.id == 2 then
		love.graphics.draw(self.image, offx * scale, offy * scale, 0, scale * 0.5, scale * 0.5, -75, -35)
	elseif self.id == 3 then
		love.graphics.draw(self.image, offx * scale, offy * scale, 0, scale * 0.5, scale * 0.5, -95, -40)
	elseif self.id == 4 then
		love.graphics.draw(self.image, offx * scale, offy * scale, 0, scale * 0.5, scale * 0.5, -75, -10)
	elseif self.id == 5 then
		love.graphics.draw(self.image, offx * scale, offy * scale, 0, scale * 0.5, scale * 0.5, -95, -15)
	elseif self.id == 6 then
		love.graphics.draw(self.image, offx * scale, offy * scale, 0, scale * 0.5, scale * 0.5, -115, -20)
	end
end

function love.newStone(x, y, id)
	local stone = {}
	stone.id = tonumber(id)
	stone.x = tonumber(x)
	stone.y = tonumber(y)
	stone.image = stones_img[tonumber(id)]
	stone.draw = drawStone
	return stone
end
