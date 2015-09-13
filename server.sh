#!/bin/sh
# @Author: adebray
# @Date:   2015-05-30 19:53:34
# @Last Modified by:   adebray
# @Last Modified time: 2015-08-18 22:33:32


./server/bin/serveur -t 300 -x 8 -y 8 -c 6 -p 4242 $* && echo $?
