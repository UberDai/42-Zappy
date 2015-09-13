--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:Map
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-04 21:09:31
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-04 21:44:02
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

Object = require 'libs.classic'

Map = Object:extend()
function Map:new(image, size)
	self.hash = {}
	for i=0,zappy.widthMap - 1 do
		self.hash[i] = {}
		for j=0,zappy.heightMap - 1 do
			self.hash[i][j] = nil
		end
	end

	self.cells = {}
	local x,y = 0,0
	for i = 1,zappy.widthMap * zappy.heightMap do
		table.insert(self.cells, {
			x = x,
			y = y,
			content = {},
			mesh = self:newCell(image, size)
		})
		table.insert(zappy.shapes, {
			x = x,
			y = y,
			shape = zappy.HC:addPolygon(size / 2, 0, size, size / 4, size / 2, size / 2, 0, size / 4),
			update = function (self, dt)
				local x, y = zappy:normalize(self.x, self.y)
				self.shape:moveTo(x * zappy.scale + (zappy.size * zappy.scale) / 2, y * zappy.scale + (zappy.size * zappy.scale) / 4)
			end,
			draw = function (self)
				self.shape:draw()
			end
		})

		zappy.shapes[#zappy.shapes].shape:scale(zappy.scale, zappy.scale)
		-- zappy.shapes[#zappy.shapes].shape:moveTo(zappy:normalize(zappy.shapes[#zappy.shapes].x * zappy.scale, zappy.shapes[#zappy.shapes].y * zappy.scale))

		self.hash[x][y] = self.cells[#self.cells]
		x = x + 1
		if x % zappy.widthMap == 0 then
			x = 0
			y = y + 1
		end
	end

	self.players = {}
end

function Map:draw()
	for i,v in ipairs(self.cells) do
		local x, y = zappy:normalize(v.x, v.y)
		love.graphics.draw(v.mesh, x * zappy.scale, y * zappy.scale, 0, zappy.scale, zappy.scale)

		for i,_v in pairs(v.content) do
			if _v.count ~= nil and _v.count > 0 then
				_v.stone:draw(x, y)
			elseif _v.quantity ~= nil and _v.quantity > 0 then
				gold_egg:draw(x, y)
			end
		end
	end
end

function Map:addStone(stone)
	if self.hash[stone.x][stone.y].content[stone.id] == nil then
		self.hash[stone.x][stone.y].content[stone.id] = {stone = stone, count = 0}
	end
	self.hash[stone.x][stone.y].content[stone.id].count = self.hash[stone.x][stone.y].content[stone.id].count + 1
end

function Map:removeStone(x, y, id)
	if self.hash[x][y].content[id] == nil or self.hash[x][y].content[id].count <= 0 then
		return
	end
	self.hash[x][y].content[id].count = self.hash[x][y].content[id].count - 1
end

function Map:newCell(image, size)
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

function Map:addEgg(team, x, y)
	if self.hash[x][y].content['egg'] == nil then
		self.hash[x][y].content['egg'] = {quantity = 0}
	end
	self.hash[x][y].content['egg'].quantity = self.hash[x][y].content['egg'].quantity + 1
end

function Map:removeEgg(team, x, y)
	self.hash[x][y].content['egg'].quantity = self.hash[x][y].content['egg'].quantity - 1
	if self.hash[x][y].content['egg'].quantity < 0 then
		self.hash[x][y].content['egg'].quantity = 0
	end
end
