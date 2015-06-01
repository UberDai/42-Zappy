--          `--::-.`
--      ./shddddddddhs+.
--    :yddddddddddddddddy:
--  `sdddddddddddddddddddds`
--  ydddh+sdddddddddy+ydddds  42-Zappy:msgStack
-- /ddddy:oddddddddds:sddddd/ By adebray - adebray
-- sdddddddddddddddddddddddds
-- sdddddddddddddddddddddddds Created: 2015-06-01 18:40:31
-- :ddddddddddhyyddddddddddd: Modified: 2015-06-01 18:44:13
--  odddddddd/`:-`sdddddddds
--   +ddddddh`+dh +dddddddo
--    -sdddddh///sdddddds-
--      .+ydddddddddhs/.
--          .-::::-`

function love.getmsgStack()
	local t = {}
	local str = ""
	while str ~= nil do
		str = tcp:receive('*l')
		table.insert(t, str)
	end
	return t
end

function love.makemsgStack(tab)
	for i,v in ipairs(tab) do
		if v:find("%+%s*%d+%s*%d+%s*%d+") then
			table.insert(Stones, love.newStone(v:match("(%d+)%s*(%d+)%s*(%d+)")))
		end
	end
end
