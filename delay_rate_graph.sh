#!/bin/bash
num_samples=100000
spin=$1
file0=table_s.txt
file1=table_pr.txt
file2=table_r.txt
mini_err=$(expr $num_samples - $2 \* $num_samples / 100)


#clean
rm -fr ./tables/*

wait=5000
for((wait=50000; wait<500000; wait+=50000))
do
	file=./tables/table_$wait.txt
	#origin point + clean
	echo 0  > $file0
	echo $num_samples > $file1
	echo 0  > $file2
	killall udp_server &> /dev/null

	#sample
	#for buf_size in 1024 2048 4096 8192 16384 32768
	for((buf_size=1024; buf_size<33000; buf_size+=512))
	do
		/home/rock64/UDP_multiport/udp_server 1234567 1 $buf_size $spin > temp &
		rate=$(ssh ducretf@193.48.111.54 "~/UDP_multiport/udp_client 10.10.15.1  1234567 1 $buf_size $spin $num_samples $wait 3210 | grep MB/s | cut -f 3 | tail -n 1 | cut -d'M' -f 1")
		sleep 1
        	packets_received=$(tail -c 33 temp | rev | cut -d'#' -f 1 | rev)
		#packets_received=$(cat temp | rev | cut -d'#' -f 1 | rev)
		killall udp_server
		packets_received2=${packets_received//[$'\t\r\n ']}
		echo packets_received
		echo -ne $packets_received2
		if [ "$packets_received2" -lt "$mini_err" ]
		then
			let rate=0
		fi
        	echo $buf_size | tee -a $file0
		echo $packets_received2 | tee -a $file1
		echo $wait
		echo $rate | tee -a $file2
	done
paste $file0 $file1 $file2 > $file
sed -i "s/$/\t$wait/" $file

#clean
rm $file0 $file1 $file2

done

cat ./tables/* > table.txt
