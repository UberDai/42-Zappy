--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:Map
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-01 22:44:12
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-01 23:59:01
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

local map = {}

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
	self.cells = {}
	local x,y = 0,0
	for i = 1,zappy.widthMap * zappy.heightMap do
		table.insert(self.cells, {
			x = x,
			y = y,
			mesh = map.newCell(image, size)
		})
		x = x + 1
		if x % zappy.widthMap == 0 then
			x = 0
			y = y + 1
		end
	end
	return self
end

function map.draw(self)
	for i,v in ipairs(self.cells) do
		local x, y = zappy:normalize(v.x, v.y)
		love.graphics.draw(v.mesh, x * zappy.scale, y * zappy.scale, 0, zappy.scale, zappy.scale)
	end
end

return map
