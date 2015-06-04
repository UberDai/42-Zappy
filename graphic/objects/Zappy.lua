--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:Zappy
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-04 21:34:28
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-04 21:42:26
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

Object = require 'libs.classic'

Zappy = Object:extend()
function Zappy:getMStack()
	local t = {}
	local str = ""
	while str ~= nil do
		str = self.tcp:receive('*l')
		table.insert(t, str)
	end
	return t
end

function Zappy:makeMStack(tab)
	for i,v in ipairs(tab) do
		if v:find("%+%s*%d+%s*%d+%s*%d+") then
			self.map:addStone(Stone(v:match("(%d+)%s*(%d+)%s*(%d+)")))
			self.itemcount = self.itemcount + 1
		elseif v:find("%-%s*%d+%s*%d+%s*%d+") then
			self.map:removeStone(v:match("(%d+)%s*(%d+)%s*(%d+)"))
			self.itemcount = self.itemcount - 1
		else
			print("else", v)
		end
	end
end

--		INIT SOCKET READ
--

function Zappy:readMap()
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

function Zappy:readTime()
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

function Zappy:addPlayer(player)
	table.insert(self.players, player)
	-- table.insert(self.hash[player.x][player.y].content, player)
end

function Zappy:normalize(x, y)
	return self.offx + -self.size / (2 + self.margin) * x + y * self.size / (2 + self.margin),
		self.offy + self.size / (4 + self.margin) * (x + y)
end

function Zappy:new(host, port)
	self.tcp = socket.connect('localhost', 4242)
	if self.tcp then

		local msg = self.tcp:receive('*l')
		if msg ~= 'BIENVENUE' then love.event.quit() end
		self.tcp:send('g\n')

		Zappy.widthMap, Zappy.heightMap = self:readMap()
		Zappy.widthMap = tonumber(Zappy.widthMap)
		Zappy.heightMap = tonumber(Zappy.heightMap)

		Zappy.timer = self:readTime()
		self.tcp:settimeout(0.01)
	else
		Zappy.widthMap, Zappy.heightMap = 10, 10
		Zappy.timer = 1
	end
	self.itemcount = 0

	self.size = 100
	self.margin = -0.5
	self.scale = 1.5
	self.offx, self.offy = width / 2 - self.size / 2, 0

	self.shapes = {}
	self.HC = Collider.new(self.size)
	self.players = {}
	self.mouse = self.HC:addCircle(0, 0, 1)
end

function Zappy:update(dt)
	self.mouse:moveTo(love.mouse.getPosition())
	if self.tcp then self:makeMStack(self:getMStack()) end
	for i,v in ipairs(self.players) do
		v:update(dt)
	end
	for i,v in ipairs(self.shapes) do
		v:update(dt)
	end
	self.collision = false
	for i,v in ipairs(self.shapes) do
		if self.mouse:collidesWith(v.shape) then
			self.collision = v
		end
	end
end

function Zappy:draw()
	self.map:draw()
	self.mouse:draw()
	for i,v in ipairs(self.players) do
		local x, y = zappy:normalize(v.x - 1, v.y - 1)
		v:draw(x, y)
	end

	if self.collision ~= false then
		ui.list:Clear()
		ui.list:SetVisible(true)
		-- ui.list:AddItem(loveframes.Create("text"):SetText("Yolo"))
		ui.list:AddItem(loveframes.Create("text"):SetText(inspect(self.map.hash[self.collision.x][self.collision.y], {depth = 3})))
	else
		ui.list:SetVisible(false)
	end

	love.graphics.print(zappy.itemcount)
end
