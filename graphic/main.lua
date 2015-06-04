--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  None:main
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-05-29 17:25:20
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-04 03:04:24
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`


loveframes = require 'loveframes'
Collider = require 'hardoncollider'
socket = require 'socket'
inspect = require 'inspect'


require 'objects.Quadlist'
require 'assets.test1'
require 'objects.FPS'
require 'objects.Player'

require 'stone'

Effect = require 'Effect'
Event = require 'Event'
Map = require 'Map'
zappy = require 'zappy'
ui = require 'ui'

stones_img = {}
stones_img[0] = love.graphics.newImage("assets/00.png")
stones_img[1] = love.graphics.newImage("assets/01.png")
stones_img[2] = love.graphics.newImage("assets/02.png")
stones_img[3] = love.graphics.newImage("assets/03.png")
stones_img[4] = love.graphics.newImage("assets/04.png")
stones_img[5] = love.graphics.newImage("assets/05.png")
stones_img[6] = love.graphics.newImage("assets/06.png")

function love.load()
	FPS = _FPS(1)
	width = love.window.getWidth()
	height = love.window.getHeight()
	time = 0

	love.math.setRandomSeed(love.timer.getTime())

	zappy:init("localhost", 4242)

	zappy:addPlayer(Player('test1', 5, 5, 'west'))
	zappy:addPlayer(Player('sprite1', 5, 5, 'north'))

end

function love.mousepressed(x, y, button)
	loveframes.mousepressed(x, y, button)
end

function love.mousereleased(x, y, button)
	loveframes.mousereleased(x, y, button)
end

function love.keypressed(key, unicode)
	-- print("keypressed", key)
	if Event[key] then
		Event[key]()
	end
loveframes.keypressed(key, unicode)
end

function love.keyreleased(key)
	loveframes.keyreleased(key)
end

function love.textinput(text)
	loveframes.textinput(text)
end

function love.update(dt)
	FPS:update(dt)
	time = time + dt * 100

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
		local tmp = 1 / zappy.scale
		zappy.scale = zappy.scale + 0.1
		for i,v in ipairs(zappy.shapes) do
			v.shape:scale(tmp, tmp)
			v.shape:scale(zappy.scale, zappy.scale)
		end
	end
	if love.keyboard.isDown(']') then
		if zappy.scale - 0.1 < 0 then return end

		local tmp = 1 / zappy.scale
		zappy.scale = zappy.scale - 0.1
		for i,v in ipairs(zappy.shapes) do
			v.shape:scale(tmp, tmp)
			v.shape:scale(zappy.scale, zappy.scale)
		end
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

zappy:update(dt)
loveframes.update(dt)
end

function love.draw()
	FPS:draw()
	zappy:draw()

loveframes.draw()
end
