--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  None:main
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-05-29 17:25:20
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-01 23:50:43
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

require 'lib'
require 'stone'

socket = require 'socket'
inspect = require 'inspect'
Quadlist = require 'Quadlist'

map = require 'Map'
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
	width = love.window.getWidth()
	height = love.window.getHeight()
	time = 0

	love.math.setRandomSeed(love.timer.getTime())

	zappy:init("localhost", 4242)


	-- margin = -0.5
	-- offx, offy = love.graphics.getWidth() / 2 - size / 2, 0
	-- scale = 1.5

	Players = {}
	table.insert(Players, love.newPlayer('team 1'))

	Stones = {}
end

function love.keypressed(key)
	print("keypressed", key)
	if key == 'w' then
		if Players[1].orientation ~= 'north' then
			Players[1].orientation = 'north'
		else
			Players[1].x = Players[1].x - 1
		end
	end
	if key == 's' then
		if Players[1].orientation ~= 'south' then
			Players[1].orientation = 'south'
		else
			Players[1].x = Players[1].x + 1
		end
	end
	if key == 'a' then
		if Players[1].orientation ~= 'east' then
			Players[1].orientation = 'east'
		else
			Players[1].y = Players[1].y - 1
		end
	end
	if key == 'd' then
		if Players[1].orientation ~= 'west' then
			Players[1].orientation = 'west'
		else
			Players[1].y = Players[1].y + 1
		end
	end
	if key == '0' then table.insert(Stones, love.newStone(love.math.random(0, 9), love.math.random(0, 9), 0)) end
	if key == '1' then table.insert(Stones, love.newStone(love.math.random(0, 9), love.math.random(0, 9), 1)) end
	if key == '2' then table.insert(Stones, love.newStone(love.math.random(0, 9), love.math.random(0, 9), 2)) end
	if key == '3' then table.insert(Stones, love.newStone(love.math.random(0, 9), love.math.random(0, 9), 3)) end
	if key == '4' then table.insert(Stones, love.newStone(love.math.random(0, 9), love.math.random(0, 9), 4)) end
	if key == '5' then table.insert(Stones, love.newStone(love.math.random(0, 9), love.math.random(0, 9), 5)) end
	if key == '6' then table.insert(Stones, love.newStone(love.math.random(0, 9), love.math.random(0, 9), 6)) end
end

function love.update(dt)
	time = time + dt * 100

	zappy:update(dt)

	for i,v in ipairs(Players) do
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

-- function love.normalize(x, y)
-- 	return offx + -size / (2 + margin) * x + y * size / (2 + margin), offy + size / (4 + margin) * (x + y)
-- end

function love.draw()
	zappy:draw(offx, offy)
	for i,v in ipairs(Stones) do
		local x, y = zappy:normalize(v.x, v.y)
		v:draw(x, y)
	end
	for i,v in ipairs(Players) do
		local x, y = zappy:normalize(v.x, v.y)
		v:draw(x, y)
	end
end
