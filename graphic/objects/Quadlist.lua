--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:Quadlist
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-04 02:39:33
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-04 02:43:17
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

Object = require 'classic'

Quadlist = Object:extend()
function Quadlist:new(tileset)
	local i = 0
	local j = 0

	self[0] = tileset.image
	while j < self[0]:getHeight() do
		i = 0
		while i < self[0]:getWidth() do
			table.insert(self,
				love.graphics.newQuad(i, j, tileset.imagewidth, tileset.imageheight,
					self[0]:getWidth(), self[0]:getHeight()))
			i = i + tileset.imagewidth
		end
		j = j + tileset.imageheight
	end
end
