--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:Pop
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-04 21:21:25
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-04 21:24:57
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

Object = require 'libs.classic'

Pop = Object:extend()
Pop.image = love.graphics.newImage('assets/Pop.png')
Pop.listQuads = Quadlist({
	image = Pop.image,
	imagewidth = 80,
	imageheight = 100
})

function Pop:new(parent)
	self.image = Pop.image
	self.listQuads = Pop.listQuads
	self.count = 0
	self.maxcount = 4
	self.delay = 0
	self.maxdelay = 0.2
	self.quad = 1
	self.quadmax = 4
	self.parent = parent
end

function Pop:update(dt)
	if self.count >= self.maxcount then
		self.parent.effect = nil
		return
	end

	self.delay = self.delay - dt
	if self.delay <= 0 then
		self.quad = self.quad + 1
		self.delay = self.maxdelay
		if self.quad >= self.quadmax then
			self.quad = 1
			self.count = self.count + 1
		end
	end
end

function Pop:draw(x, y, offset_x, offset_y)
	love.graphics.draw(self.listQuads[0], self.listQuads[self.quad], x * zappy.scale, y * zappy.scale, 0, zappy.scale * -1, zappy.scale, offset_x, offset_y)
end
