#!/bin/sh
# @Author: adebray
# @Date:   2015-05-30 19:53:34
# @Last Modified by:   adebray
# @Last Modified time: 2015-05-30 19:53:51


make -C server
./server/bin/serveur -t 1 -x 10 -y 10 -c 10 -p 4242
