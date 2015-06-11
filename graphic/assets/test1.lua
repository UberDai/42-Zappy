--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:test1
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-02 20:24:40
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-11 21:41:46
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

Object = require 'libs.classic'

test1 = Object:extend()
test1.image = love.graphics.newImage('assets/test1.png')
test1.listQuads = Quadlist({
	image = test1.image,
	imagewidth = 80,
	imageheight = 100
})

function test1:new()
	self.delay = 0
	self.maxdelay = 0.3
	self.quad = 1
	self.quadmax = 4
	self.orientation = 'north'
	self.listQuads = self.listQuads
	self.update = self.update
	self.draw = self.draw
	self.effect = Pop(self)
end

function test1:update(dt)
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

	if self.effect then
		self.effect:update(dt)
	end
end

function test1:draw(x, y)
	if self.orientation == 'west' then
		love.graphics.draw(self.listQuads[0], self.listQuads[self.quad + 8], x * zappy.scale, y * zappy.scale, 0, zappy.scale, zappy.scale, -5, 20)
	elseif self.orientation == 'north' then
		love.graphics.draw(self.listQuads[0], self.listQuads[self.quad + 8], x * zappy.scale, y * zappy.scale, 0, zappy.scale * -1, zappy.scale, 80, 20)
	elseif self.orientation == 'east' then
		love.graphics.draw(self.listQuads[0], self.listQuads[self.quad], x * zappy.scale, y * zappy.scale, 0, zappy.scale, zappy.scale, -5, 15)
	elseif self.orientation == 'south' then
		love.graphics.draw(self.listQuads[0], self.listQuads[self.quad], x * zappy.scale, y * zappy.scale, 0, zappy.scale * -1, zappy.scale, 80, 15)
	end

	if self.effect then
		self.effect:draw(x, y, 85, 30)
	end
end
