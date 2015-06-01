--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:lib
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-01 18:38:23
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-01 20:38:13
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

function love.newCell(image, size)
	local vertices = {
		{
			size / 2, 0,
			0, 0,
			255, 255, 255,
		},
		{
			size, size / 4,
			1, 0,
			255, 255, 255
		},
		{
			size / 2, size / 2,
			1, 1,
			255, 255, 255
		},
		{
			0, size / 4,
			0, 1,
			255, 255, 255
		},
	}
	return love.graphics.newMesh(vertices, image, "fan")
end

function love.newMap(img, size)
	Map = {}
	local x,y = 0,0
	for i = 1,widthMap * heightMap do
		table.insert(Map, {mesh = love.newCell(img, size), x = x, y = y})
		x = x + 1
		if x % widthMap == 0 then
			x = 0
			y = y + 1
		end
	end
	return Map
end

function love.newPlayer(team)
	local player = {}
	player.x = 5
	player.y = 5
	player.orientation = 'north'
	player.listQuads = Quadlist:new({
		image = 'assets/test1.png',
		imagewidth = 80,
		imageheight = 104
	})
	player.delay = 0
	player.maxdelay = 0.3
	player.quad = 1
	player.quadmax = 4
	player.update = function (self, dt)
		-- print(dt, inspect(self))
		self.delay = self.delay - dt
		if self.delay <= 0 then
			self.quad = self.quad + 1
			self.delay = self.maxdelay
			if self.quad >= self.quadmax then
				self.quad = 1
				if love.math.random(0, 3) ~= 3 then
					self.quadmax = 4
				else
					self.quadmax = 8
				end
			end
		end
	end
	player.draw = function (self, offx, offy)
		if self.orientation == 'north' then
			love.graphics.draw(self.listQuads[0], self.listQuads[self.quad + 8], offx * scale, offy * scale, 0, scale, scale, 0, self.listQuads[0]:getHeight() / 3.25)
		elseif self.orientation == 'east' then
			love.graphics.draw(self.listQuads[0], self.listQuads[self.quad + 8], offx * scale, offy * scale, 0, scale * -1, scale, 80, self.listQuads[0]:getHeight() / 3.25)
		elseif self.orientation == 'south' then
			love.graphics.draw(self.listQuads[0], self.listQuads[self.quad], offx * scale, offy * scale, 0, scale, scale, 0, self.listQuads[0]:getHeight() / 3.25)
		elseif self.orientation == 'west' then
			love.graphics.draw(self.listQuads[0], self.listQuads[self.quad], offx * scale, offy * scale, 0, scale * -1, scale, 80, self.listQuads[0]:getHeight() / 3.25)
		end
	end
	return player
end
