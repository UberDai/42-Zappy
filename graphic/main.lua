--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  None:main
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-05-29 17:25:20
-- :ddddddddddhyyddddddddddd: Modified: 2015-05-29 20:33:40
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

socket = require 'socket'
inspect = require 'inspect'

function love.readMap()
	local t = {}
	local line = tcp:receive('*l')
	if string.sub(line, line:find("%d+%s+%d+")) ~= nil then
		print('Got map')
	end
	for num in string.gmatch(line, "%d+") do
		table.insert(t, num)
	end
	return t[1], t[2]
end

function love.readTime()
	local t = {}
	local line = tcp:receive('*l')
	if string.sub(line, line:find("%d+")) ~= nil then
		print('Got time')
	end
	local num = string.match(line, "%d+")
	return num
end

function love.newCell(image, size)
	local vertices = {
		{
			size / 2, 0,
			0, 0,
			255, 255, 255,
		},
		{
			size, size / 4,
			1, 0,
			255, 255, 255
		},
		{
			size / 2, size / 2,
			1, 1,
			255, 255, 255
		},
		{
			0, size / 4,
			0, 1,
			255, 255, 255
		},
	}
	return love.graphics.newMesh(vertices, image, "fan")
end

function love.newMap(img, size)
	Map = {}
	local x,y = 0,0
	for i = 1,widthMap * heightMap do
		table.insert(Map, {mesh = love.newCell(nil, size), x = x, y = y})
		x = x + 1
		if x % widthMap == 0 then
			x = 0
			y = y + 1
		end
	end
	return Map
end

function love.load()
	size = 50
	fontsize = 15
	tcp = socket.connect('localhost', 4242)
	msg = tcp:receive('*l')
	if msg ~= 'BIENVENUE' then love.event.quit() end
	tcp:send('g\n')

	widthMap, heightMap = love.readMap()
	widthMap = tonumber(widthMap)
	heightMap = tonumber(heightMap)

	timer = love.readTime()

	img = love.graphics.newImage("assets/O.png")

	Map = love.newMap(img, size)

	print(widthMap, heightMap, inspect(Map))
	margin = 0
	offx, offy = love.graphics.getWidth() / 2 - size / 2, 0
	scale = 1
end

function love.keypressed(key)
	print("keypressed", key)
end

function love.update(dt)
	if love.keyboard.isDown('rshift') and love.keyboard.isDown('[') then
		margin = margin + dt
	end
	if love.keyboard.isDown('rshift') and love.keyboard.isDown(']') then
		margin = margin - dt
	end
	if love.keyboard.isDown('[') then
		scale = scale + dt
	end
	if love.keyboard.isDown(']') then
		scale = scale - dt
	end
	if love.keyboard.isDown('up') then
		offy = offy - dt * 500
	end
	if love.keyboard.isDown('down') then
		offy = offy + dt * 500
	end
	if love.keyboard.isDown('left') then
		offx = offx - dt * 500
	end
	if love.keyboard.isDown('right') then
		offx = offx + dt * 500
	end
end

function love.draw()
	for i,v in ipairs(Map) do
		local x = offx + -size / (2 + margin) * v.x + v.y * size / (2 + margin)
		local y = offy + size / (4 + margin) * (v.x + v.y)
		love.graphics.draw(v.mesh, x * scale, y * scale, 0, scale, scale)
	end
end
