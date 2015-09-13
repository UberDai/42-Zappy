Object = require 'libs.classic'

emotion = Object:extend()
emotion.image = love.graphics.newImage('assets/emotion.png')
emotion.listQuads = Quadlist({
	image = emotion.image,
	imagewidth = 40,
	imageheight = 40
})
function emotion:new(parent)
	self.count = 0
	self.maxcount = 3
	self.delay = 0
	self.maxdelay = 0.2
	self.quad = 1
	self.quadmax = 3
	self.parent = parent

	self.update = self.update
	self.draw = self.draw
end

function emotion:update(dt)
	if self.count >= self.maxcount then
		self.parent.effect = nil
		return
	end

	self.delay = self.delay - dt
	if self.delay < 0 then
		self.quad = self.quad + 1
		self.delay = self.maxdelay
		if self.quad >= self.quadmax then
			self.quad = 1
			self.count = self.count + 1
		end
	end
end

function emotion:draw(x, y)
	love.graphics.draw(self.listQuads[0], self.listQuads[self.quad], x * zappy.scale, y * zappy.scale, 0, zappy.scale, zappy.scale, 0, 20)
end

return emotion
