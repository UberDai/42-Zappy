#!/bin/sh
# @Author: adebray
# @Date:   2015-05-31 21:18:48
# @Last Modified by:   adebray
# @Last Modified time: 2015-05-31 21:54:02

make -C server &&
(
	./server.sh > /dev/null &
	./gfx.sh
)
