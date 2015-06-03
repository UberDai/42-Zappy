--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:sprite1
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-02 19:59:18
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-03 23:17:36
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
	t.quadmax = 8
	t.orientation = 'north'
	t.listQuads = self.listQuads
	t.update = self.update
	t.draw = self.draw
	t.effect = Effect:newPop(t)
	return t
end

sprite1.update = function (self, dt)
	self.delay = self.delay - dt
	if self.delay <= 0 then
		self.quad = self.quad + 1
		self.delay = self.maxdelay
		if self.quad >= self.quadmax then
			self.quad = 1
		end
	end
	if self.effect then
		self.effect:update(dt)
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

	if self.effect then
		self.effect:draw(x, y, 80, 0)
	end
end

return sprite1
