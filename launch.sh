#!/bin/sh
# @Author: adebray
# @Date:   2015-05-31 21:18:48
# @Last Modified by:   adebray
# @Last Modified time: 2015-08-18 20:47:46

rm -rf debug/*
./server.sh -n 10 team1 team2 team3 team4 team5 team6 team7 team8 team9 team10 > server.log 2> error.log &
sleep 2
./gfx.sh localhost 4242 > gfx.log &
sleep 2
./client.sh -n team1 -p 4242 > client.log &
./client.sh -n team2 -p 4242 > client.log &
./client.sh -n team3 -p 4242 > client.log &
./client.sh -n team4 -p 4242 > client.log &
./client.sh -n team5 -p 4242 > client.log &
./client.sh -n team6 -p 4242 > client.log &
./client.sh -n team7 -p 4242 > client.log &
./client.sh -n team8 -p 4242 > client.log &
./client.sh -n team9 -p 4242 > client.log &
./client.sh -n team10 -p 4242 > client.log &
