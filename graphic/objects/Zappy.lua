--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:Zappy
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-04 21:34:28
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-11 21:54:46
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
		elseif v:find("%*%s*%d+%s*%w+%s*%d+%s*%d+%s*%d+") then
			table.insert(self.players, Player(v:match("(%d+)%s*(%w+)%s*(%d+)%s*(%d+)%s*(%d+)")))
		elseif v:find("%>%s*%d+%s*%d+%s*%d+") then
			-- > ID x y
			local id, x, y = v:match("(%d+)%s*(%d+)%s*(%d+)")
			for i,v in ipairs(self.players) do
				if v.id == tonumber(id) then
					v.x = tonumber(x)
					v.y = tonumber(y)
				end
			end
		elseif v:find("o%s*%d+%s*%d+") then
			local id, orientation = v:match("(%d+)%s*(%d+)")
			for i,v in ipairs(self.players) do
				if v.id == tonumber(id) then
					v.sprite.orientation = noraml(orientation)
				end
			end
		else
			if v ~= "" then print("else", v) end
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
	self.tcp = socket.connect(host, port)
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
		return
	end
	self.itemcount = 0

	self.size = 100
	self.margin = -0.5
	self.scale = 1
	-- self.offx, self.offy = width / 3 - self.size / 2, height / 8
	self.offx, self.offy = width / 2 - self.size / 2, height / 4 - self.size / 2

	self.shapes = {}
	self.HC = Collider.new(self.size)
	self.players = {}
	self.teams = {}
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

test = love.graphics.newShader[[
	vec4 effect( vec4 color, Image texture, vec2 texture_coords, vec2 screen_coords )
	{
		vec4 tmp = Texel(texture, texture_coords);

		return color * tmp;
	}
]]

function Zappy:draw()
	self.map:draw()
	self.mouse:draw()
	for i,v in ipairs(self.players) do
		local x, y = zappy:normalize(v.x - 1, v.y - 1)
		love.graphics.setColor(self.teams[v.team].color)
		love.graphics.setShader(test)
		v:draw(x, y)
		love.graphics.setShader()
		love.graphics.setColor({255, 255, 255, 255})
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

	local count = 0
	for k,v in pairs(self.teams) do
		count = count + 1
	end

	local j = height - 60 - count * 12
	for k,v in pairs(self.teams) do
		love.graphics.setColor(v.color)
		love.graphics.rectangle('fill', 10, j, 100, 12)
		love.graphics.setColor({0, 0, 0, 255})
		love.graphics.print(k, 15, j)
		love.graphics.setColor({255, 255, 255, 255})
		j = j + 12
	end

	local grain = math.floor(width / #self.players)
	if grain == 0 or #self.players == 0 then return end

	local y = 0
	for i,v in ipairs(self.players) do
		love.graphics.setColor(self.teams[v.team].color)
		love.graphics.rectangle("fill", y + 5, height - 50, grain - 10, 50)
		love.graphics.setColor({255, 255, 255, 255})
		y = y + grain
	end

end
