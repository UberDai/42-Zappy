--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:Map
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-01 22:44:12
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-02 20:29:52
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

local map = {}

function map.addStone(self, stone)
	table.insert(self.hash[stone.x][stone.y].content, stone)
end


function map.newCell(image, size)
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

function map.init(self, image, size)
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
			mesh = map.newCell(image, size)
		})
		self.hash[x][y] = self.cells[#self.cells]
		x = x + 1
		if x % zappy.widthMap == 0 then
			x = 0
			y = y + 1
		end
	end

	self.players = {}
	return self
end

function map.draw(self)
	-- local size = 150
	-- for i=0,zappy.widthMap - 1 do
	-- 	for j=0,zappy.heightMap - 1 do
	-- 		love.graphics.rectangle("line", i * (size + 1), j * (size + 1), size, size)
	-- 		love.graphics.print(inspect(self.hash[i][j], {depth = 2}), i * (size + 1), j * (size + 1))
	-- 	end
	-- end
	for i,v in ipairs(self.cells) do
		local x, y = zappy:normalize(v.x, v.y)
		love.graphics.draw(v.mesh, x * zappy.scale, y * zappy.scale, 0, zappy.scale, zappy.scale)
		for i,_v in ipairs(v.content) do
			_v:draw(x, y)
		end
	end
end

return map