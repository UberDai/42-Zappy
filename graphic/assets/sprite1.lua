--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:sprite1
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-02 19:59:18
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-02 20:24:51
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

local sprite1 = {}

sprite1.image = love.graphics.newImage('assets/sprite1.png')

sprite1.listQuads = Quadlist:new({
	image = sprite1.image,
	imagewidth = 80,
	imageheight = 100
})

sprite1.new = function (self)
	local t = {}

	t.delay = 0
	t.maxdelay = 0.3
	t.quad = 1
	t.quadmax = 4
	t.orientation = 'north'
	t.listQuads = self.listQuads
	t.update = self.update
	t.draw = self.draw
	return t
end

sprite1.update = function (self, dt)
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

sprite1.draw = function (self, x, y)
	if self.orientation == 'north' then
		love.graphics.draw(self.listQuads[0], self.listQuads[self.quad + 8], x * zappy.scale, y * zappy.scale, 0, zappy.scale, zappy.scale, 0, 0)
	elseif self.orientation == 'east' then
		love.graphics.draw(self.listQuads[0], self.listQuads[self.quad + 8], x * zappy.scale, y * zappy.scale, 0, zappy.scale * -1, zappy.scale, 80, 0)
	elseif self.orientation == 'south' then
		love.graphics.draw(self.listQuads[0], self.listQuads[self.quad], x * zappy.scale, y * zappy.scale, 0, zappy.scale, zappy.scale, 0, 0)
	elseif self.orientation == 'west' then
		love.graphics.draw(self.listQuads[0], self.listQuads[self.quad], x * zappy.scale, y * zappy.scale, 0, zappy.scale * -1, zappy.scale, 80, 0)
	end
end

return sprite1
