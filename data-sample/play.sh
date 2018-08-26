#!/bin/bash

if [ _${1} = _ ];then
	data=icandump-2018-08-21_083632.log
else
	data=${1}
fi

sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
canplayer vcan0=can0 -v -I ${data}

