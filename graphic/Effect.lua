--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:Effect
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-03 22:27:46
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-03 23:19:03
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

local Effect = {}

function Effect.newPop(self, parent)
	local e = {}

	e.image = love.graphics.newImage("assets/pop.png")
	e.listQuads = Quadlist:new({
		image = e.image,
		imagewidth = 80,
		imageheight = 100
	})
	e.count = 0
	e.maxcount = 4
	e.delay = 0
	e.maxdelay = 0.2
	e.quad = 1
	e.quadmax = 4
	e.parent = parent
	e.update = self.update
	e.draw = self.draw
	return e
end

function Effect.update(self, dt)
	if self.count >= self.maxcount then
		self.parent.effect = nil return
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

function Effect.draw(self, x, y, offset_x, offset_y)
	love.graphics.draw(self.listQuads[0], self.listQuads[self.quad], x * zappy.scale, y * zappy.scale, 0, zappy.scale * -1, zappy.scale, offset_x, offset_y)
end

return Effect
