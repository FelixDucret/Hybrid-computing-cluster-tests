#!/bin/bash
echo $1 $2 $3 $4
/home/rock64/UDP_multiport/udp_server $1 $2 $3 $4 > temp &
ssh ducretf@193.48.111.54 'echo Hi && ~/UDP_multiport/udp_client 10.10.15.1  1234567 1 4096 block 100000  50000 3210 & && exit '
cat temp && echo
killall udp_server

