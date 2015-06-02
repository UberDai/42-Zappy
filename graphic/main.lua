--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  None:main
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-05-29 17:25:20
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-02 18:23:07
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

FPS = {}

function FPS:new(delay)
	self.width = love.window.getWidth()
	self.height = love.window.getHeight()
	self.delay = delay
	self.list = {}

	self.update = function (self, dt)
		self.delay = self.delay - dt
		if self.delay < 0 then
			table.insert(self.list, love.timer.getFPS())
			if #self.list - 1 > self.width / 3 then
				table.remove(self.list, 1)
			end
			self.delay = delay
		end
	end
	self.draw = function (self)
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
end

require 'player'
require 'stone'

socket = require 'socket'
inspect = require 'inspect'
Quadlist = require 'Quadlist'

Event = require 'Event'
Map = require 'Map'
zappy = require 'zappy'

stones_img = {}
stones_img[0] = love.graphics.newImage("assets/00.png")
stones_img[1] = love.graphics.newImage("assets/01.png")
stones_img[2] = love.graphics.newImage("assets/02.png")
stones_img[3] = love.graphics.newImage("assets/03.png")
stones_img[4] = love.graphics.newImage("assets/04.png")
stones_img[5] = love.graphics.newImage("assets/05.png")
stones_img[6] = love.graphics.newImage("assets/06.png")

function love.load()
	FPS:new(1)
	width = love.window.getWidth()
	height = love.window.getHeight()
	time = 0

	love.math.setRandomSeed(love.timer.getTime())

	zappy:init("localhost", 4242)

	zappy.map:addPlayer(newPlayer('team 1'))

end

function love.keypressed(key)
	print("keypressed", key)
	if Event[key] then
		Event[key]()
	end
end

function love.update(dt)
	FPS:update(dt)
	time = time + dt * 100

	zappy:update(dt)

	for i,v in ipairs(zappy.map.players) do
		v:update(dt)
	end

	if love.keyboard.isDown('rshift') and love.keyboard.isDown('[') then
		zappy.margin = zappy.margin + dt
	end
	if love.keyboard.isDown('rshift') and love.keyboard.isDown(']') then
		zappy.margin = zappy.margin - dt
	end
	if love.keyboard.isDown('[') then
		zappy.scale = zappy.scale + 0.1
	end
	if love.keyboard.isDown(']') then
		zappy.scale = zappy.scale - 0.1
	end
	if love.keyboard.isDown('up') then
		zappy.offy = zappy.offy - dt * 500
	end
	if love.keyboard.isDown('down') then
		zappy.offy = zappy.offy + dt * 500
	end
	if love.keyboard.isDown('left') then
		zappy.offx = zappy.offx - dt * 500
	end
	if love.keyboard.isDown('right') then
		zappy.offx = zappy.offx + dt * 500
	end
	if love.keyboard.isDown('backspace') then
		dofile('extern.lua')
	end
end

function love.draw()
	FPS:draw()
	zappy:draw(offx, offy)
end
