#!/bin/sh
# @Author: adebray
# @Date:   2015-05-31 21:18:48
# @Last Modified by:   adebray
# @Last Modified time: 2015-08-18 20:47:46

rm -rf debug/*
./server.sh -n 1 team1 > server.log &
sleep 2
./gfx.sh localhost 4242 &
sleep 2
./client.sh -n team1 -p 4242 > client.log 
