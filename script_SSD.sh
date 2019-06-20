#!/bin/bash
echo How much GB do you want to write?
read number
t0=`date +%s`
echo $t0
(for ((i=0;i<$number; i++)); do
	cat /dev/shm/1GB.rnd | sudo tee /media/file.txt >/dev/null;
done)
t1=`date +%s`
echo $t1
dt=$(expr $t1 - $t0 )
MB=$(expr 1024 \* $number )
echo $dt's '`expr $MB / $dt`'MB/s'

