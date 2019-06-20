#!/bin/bash
echo How much GB do you want to transmit?
read number
ssh ducretf@193.48.111.54 'nc -v -l -p 12345 > md5sum_file & && sleep 1 && exit'
t0=`date +%s`
echo $t0
(for ((i=0;i<$number-1; i++)); do
		echo $i && cat /dev/shm/1GB.rnd
	done) | nc -v -4 -q 0 10.10.15.2 12345
t1=`date +%s`
echo $t1
ssh ducretf@193.48.111.54 'md5sum md5sum_file > result && scp result rock64@193.48.111.153:~/scripts_UDP/results && exit'
dt=$(expr $t1 - $t0 )
MB=$(expr 1024 \* $number )
echo $dt's '`expr $MB / $dt`'MB/s'
