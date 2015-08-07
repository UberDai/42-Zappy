socket = require 'socket'

function love.load()
	client = {}
	tcp = socket.tcp()
	tcp:settimeout(0.1)
	bind = tcp:bind('*', 4244)
	print(tcp:listen())
end

function love.update(dt)
	local c,err = tcp:accept()

	if not err then
		table.insert(client, {c = c, table = {}})
	end

	for i,v in ipairs(client) do
		str = v.c:receive()
		if str then
			if (#v.table * 12 > love.window.getHeight()) then
				table.remove(v.table, 1)
			end
			if (#str > 21) then
				str = string.sub(str, 1, 21)
				str = str.." ..."
			end
			table.insert(v.table, str)
		end
	end
end

function love.draw()
	local width = love.window.getWidth() / 7
	local x, y = 0, 0

	for i,v in ipairs(client) do
		y = 0
		for j,w in ipairs(v.table) do
			if string.find(w, 'ko') then
				for aaa=j-3,j+3 do
					if v.table[aaa] then
						love.graphics.print(v.table[aaa], x, y)
					end
					y = y + 12
				end
			end
		end
		x = x + width
	end
end
