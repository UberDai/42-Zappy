#!/bin/sh
# @Author: adebray
# @Date:   2015-05-31 21:18:48
# @Last Modified by:   adebray
# @Last Modified time: 2015-06-01 23:03:56

make -C server &&
(
	./server.sh > /dev/null &
	sleep 1
	./gfx.sh ; pkill serveur
)
