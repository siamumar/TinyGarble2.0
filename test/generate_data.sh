#!/bin/bash

./test/throttle.sh del
./test/throttle.sh lan
for ((b=45000;b<=4500000;b=b+45000))
do
    c=2048
    w1=32
    w2=32
    w3=$(expr $w1 + $w2 - 1)
    echo $w1 $w2 $w3 $c $b
    ./bin/TinyGarble -n tinygarble/netlists_pi/mult_${w1}_${w2}_${w3}bit.emp.bin -m 1 -c $c -b $b --oo >> test/MvsT.txt &
    ./bin/TinyGarble -k 2 -n tinygarble/netlists_pi/mult_${w1}_${w2}_${w3}bit.emp.bin -m 1 -c $c -b $b --oo > /dev/null
done

# ./test/throttle.sh del
# for i in {1..512}
# do
#     c=$(( ( RANDOM % 16384 ) + 16384 ))
#     w1=$(( ( RANDOM % 63 ) + 2 ))
#     w2=$(( ( RANDOM % 63 ) + 2 ))
#     w3=$(expr $w1 + $w2 - 1)
#     echo $w1 $w2 $w3 $c
#     ./bin/TinyGarble -n tinygarble/netlists_pi/mult_${w1}_${w2}_${w3}bit.emp.bin -m 1 -c $c --oo >> test/MEM.txt &
#     ./bin/TinyGarble -k 2 -n tinygarble/netlists_pi/mult_${w1}_${w2}_${w3}bit.emp.bin -m 1 -c $c --oo > /dev/null
# done

# ./test/throttle.sh lan
# for i in {1..512}
# do
#     c=$(( ( RANDOM % 1024 ) + 128 ))
#     w1=$(( ( RANDOM % 63 ) + 2 ))
#     w2=$(( ( RANDOM % 63 ) + 2 ))
#     w3=$(expr $w1 + $w2 - 1)
#     echo $w1 $w2 $w3 $c
#     ./bin/TinyGarble -n tinygarble/netlists_pi/mult_${w1}_${w2}_${w3}bit.emp.bin -m 1 -c $c --oo >> test/LAN.txt &
#     ./bin/TinyGarble -k 2 -n tinygarble/netlists_pi/mult_${w1}_${w2}_${w3}bit.emp.bin -m 1 -c $c --oo > /dev/null
# done

# ./test/throttle.sh del
# ./test/throttle.sh wan
# for i in {1..512}
# do
#     c=$(( ( RANDOM % 1024 ) + 128 ))
#     w1=$(( ( RANDOM % 63 ) + 2 ))
#     w2=$(( ( RANDOM % 63 ) + 2 ))
#     w3=$(expr $w1 + $w2 - 1)
#     echo $w1 $w2 $w3 $c
#     ./bin/TinyGarble -n tinygarble/netlists_pi/mult_${w1}_${w2}_${w3}bit.emp.bin -m 1 -c $c --oo >> test/WAN.txt &
#     ./bin/TinyGarble -k 2 -n tinygarble/netlists_pi/mult_${w1}_${w2}_${w3}bit.emp.bin -m 1 -c $c --oo > /dev/null
# done

# ./test/throttle.sh del