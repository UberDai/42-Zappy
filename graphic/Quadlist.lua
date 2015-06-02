Quadlist = {}

function Quadlist:new(tileset)
	local i = 0
	local j = 0
	local Quadlist = {}

	Quadlist[0] = tileset.image
	while j < Quadlist[0]:getHeight() do
		i = 0
		while i < Quadlist[0]:getWidth() do
			table.insert(Quadlist,
				love.graphics.newQuad(i, j, tileset.imagewidth, tileset.imageheight,
					Quadlist[0]:getWidth(), Quadlist[0]:getHeight()))
			i = i + tileset.imagewidth
		end
		j = j + tileset.imageheight
	end

	return Quadlist
end

return Quadlist
