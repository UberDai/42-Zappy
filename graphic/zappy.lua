--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:zappy
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-01 23:24:11
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-02 20:29:44
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

local zappy = {}

function zappy.getMStack(self)
	local t = {}
	local str = ""
	while str ~= nil do
		str = self.tcp:receive('*l')
		table.insert(t, str)
	end
	return t
end

function zappy.makeMStack(self, tab)
	for i,v in ipairs(tab) do
		if v:find("%+%s*%d+%s*%d+%s*%d+") then
			self.map:addStone(love.newStone(v:match("(%d+)%s*(%d+)%s*(%d+)")))
		end
	end
end

--		INIT SOCKET READ
--

function zappy.readMap(self)
	local t = {}
	local line = self.tcp:receive('*l')
	if string.sub(line, line:find("%d+%s+%d+")) ~= nil then
		print('Got map')
	end
	for num in string.gmatch(line, "%d+") do
		table.insert(t, num)
	end
	return t[1], t[2]
end

function zappy.readTime(self)
	local t = {}
	local line = self.tcp:receive('*l')
	if string.sub(line, line:find("%d+")) ~= nil then
		print('Got time')
	end
	local num = string.match(line, "%d+")
	return num
end

--		ZAPPY ENGINE
--

function zappy.addPlayer(self, player)
	table.insert(self.players, player)
	-- table.insert(self.hash[player.x][player.y].content, player)
end

function zappy.normalize(self, x, y)
	return self.offx + -self.size / (2 + self.margin) * x + y * self.size / (2 + self.margin),
		self.offy + self.size / (4 + self.margin) * (x + y)
end

function zappy.init(self, host, port)
	self.tcp = socket.connect('localhost', 4242)
	if self.tcp then
		self.tcp:settimeout(0.01)

		local msg = self.tcp:receive('*l')
		if msg ~= 'BIENVENUE' then love.event.quit() end
		self.tcp:send('g\n')

		self.widthMap, self.heightMap = zappy:readMap()
		self.widthMap = tonumber(self.widthMap)
		self.heightMap = tonumber(self.heightMap)

		self.timer = zappy:readTime()
	else
		self.widthMap, self.heightMap = 10, 10
		self.timer = 1
	end

	self.size = 100
	self.margin = -0.5
	self.scale = 1.5
	self.offx, self.offy = width / 2 - self.size / 2, 0

	self.map = Map:init(love.graphics.newImage("assets/test6.png"), self.size)
	self.players = {}

	return self
end

function zappy.update(self, dt)
	if self.tcp then self:makeMStack(self:getMStack()) end
	for i,v in ipairs(self.players) do
		v:update(dt)
	end
end

function zappy.draw(self)
	self.map:draw()
	for i,v in ipairs(self.players) do
		local x, y = zappy:normalize(v.x - 1, v.y - 1)
		v:draw(x, y)
	end
end

return zappy