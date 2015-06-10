#!/bin/sh
# @Author: adebray
# @Date:   2015-05-31 21:18:48
# @Last Modified by:   adebray
# @Last Modified time: 2015-06-09 17:14:20

./server.sh -n 1 team1 > server.log &
sleep 2
./gfx.sh > gfx.log &
sleep 2
./client.sh -n team1
