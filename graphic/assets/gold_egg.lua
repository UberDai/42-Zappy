Object = require 'libs.classic'

gold_egg = Object:extend()
gold_egg.image = love.graphics.newImage('assets/gold_egg.png')

function gold_egg:new()
	self.update = self.update
	self.draw = self.draw
end

function gold_egg:update(dt)
end

function gold_egg:draw(x, y)
	love.graphics.draw(self.image, x, y)
end

return gold_egg
