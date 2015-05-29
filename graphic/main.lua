--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  None:main
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-05-29 17:25:20
-- :ddddddddddhyyddddddddddd: Modified: 2015-05-29 22:50:51
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

socket = require 'socket'
inspect = require 'inspect'
Quadlist = require 'Quadlist'

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

function love.newPlayer(team)
	local player = {}
	player.listQuads = Quadlist:new({
		image = 'assets/test1.png',
		imagewidth = 80,
		imageheight = 104
	})
	player.delay = 0
	player.maxdelay = 0.3
	player.quad = 1
	player.quadmax = 4
	player.update = function (self, dt)
		-- print(dt, inspect(self))
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
	end
	player.draw = function (self, offx, offy)
		love.graphics.draw(self.listQuads[0], self.listQuads[self.quad], offx * scale, offy * scale, 0, scale, scale)
	end
	return player
end

function love.load()
	love.math.setRandomSeed(love.timer.getTime())
	size = 100
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

	Players = {}
	table.insert(Players, love.newPlayer('team 1'))
end

function love.keypressed(key)
	print("keypressed", key)
end

function love.update(dt)
	for i,v in ipairs(Players) do
		v:update(dt)
	end
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
	for i,v in ipairs(Players) do
		v:draw(offx, offy)
	end
end
