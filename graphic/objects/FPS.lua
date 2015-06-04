--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:FPS
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-04 02:46:27
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-04 02:47:04
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

Object = require 'classic'

_FPS = Object:extend()
function _FPS:new(delay)
	self.width = love.window.getWidth()
	self.height = love.window.getHeight()
	self.delay = delay
	self.maxdelay = delay
	self.list = {}
end

function _FPS:update(dt)
	self.delay = self.delay - dt
	if self.delay < 0 then
		table.insert(self.list, love.timer.getFPS())
		if #self.list - 1 > self.width / 3 then
			table.remove(self.list, 1)
		end
		self.delay = self.maxdelay
	end
end

function _FPS:draw()
	love.graphics.setColor(255, 255, 255, 100)
	for k,v in pairs(self.list) do
		if v < 30 then love.graphics.setColor(255, 0, 0, 100) end
		love.graphics.rectangle('fill',
			self.width - (k * 3),
			self.height - v,
			3, v)
		if v < 30 then love.graphics.setColor(255, 255, 255, 100) end
	end
	love.graphics.setColor(255, 255, 255, 255)
end
