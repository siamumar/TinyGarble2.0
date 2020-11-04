#!/bin/bash

./test/throttle.sh del
./test/throttle.sh lan
for i in {1..128}
do
    c=$(( ( RANDOM % 64 ) + 16 ))
    w1=$(( ( RANDOM % 63 ) + 2 ))
    w2=$(( ( RANDOM % 63 ) + 2 ))
    w3=$(expr $w1 + $w2 - 1)
    echo $w1 $w2 $w3
    ./bin/TinyGarble -n tinygarble/netlists_pi/mult_${w1}_${w2}_${w3}bit.emp.bin -m 1 -c $c --oo >> test/LAN.txt &
    ./bin/TinyGarble -k 2 -n tinygarble/netlists_pi/mult_${w1}_${w2}_${w3}bit.emp.bin -m 1 -c $c --oo > /dev/null
done

./test/throttle.sh del
./test/throttle.sh wan
for i in {1..128}
do
    c=$(( ( RANDOM % 64 ) + 16 ))
    w1=$(( ( RANDOM % 63 ) + 2 ))
    w2=$(( ( RANDOM % 63 ) + 2 ))
    w3=$(expr $w1 + $w2 - 1)
    echo $w1 $w2 $w3
    ./bin/TinyGarble -n tinygarble/netlists_pi/mult_${w1}_${w2}_${w3}bit.emp.bin -m 1 -c $c --oo >> test/WAN.txt &
    ./bin/TinyGarble -k 2 -n tinygarble/netlists_pi/mult_${w1}_${w2}_${w3}bit.emp.bin -m 1 -c $c --oo > /dev/null
done

./test/throttle.sh del