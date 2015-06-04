--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:sprite1
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-02 19:59:18
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-04 21:48:13
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

Object = require 'libs.classic'

sprite1 = Object:extend()
sprite1.image = love.graphics.newImage('assets/sprite1.png')
sprite1.listQuads = Quadlist({
	image = sprite1.image,
	imagewidth = 80,
	imageheight = 100
})

function sprite1:new()
	self.delay = 0
	self.maxdelay = 0.3
	self.quad = 1
	self.quadmax = 8
	self.orientation = 'north'
	self.listQuads = self.listQuads
	self.update = self.update
	self.draw = self.draw
	self.effect = Pop(self)
end

function sprite1:update(dt)
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

function sprite1:draw(x, y)
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
