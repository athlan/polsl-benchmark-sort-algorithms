#/bin/bash

# Script generated random values between MIN_VALUE and MAX_VALUE
# exactly COUNT times in each line. If COUNT is not defined,
# one number will be generated.
#
# In first line the total number of generated items are printed.
# 
# Author: Piotr Pelczar

function usage {
	echo "usage: rand-dataset.sh MIN_VALUE MAX_VALUE [COUNT]";
}

min="$1"
max="$2"
count="$3"

if [ -z $min ]; then echo "Missing MIN_VALUE" && usage; exit; fi;
if [ -z $max ]; then echo "Missing MAX_VALUE" && usage; exit; fi;
if [ -z $count ]; then count=1; fi;

diff=$((max - min + 1));

echo $count;

i=0;
while [ $i -lt $count ] ; do
    echo $(( ( RANDOM % diff ) + min ));
    i=$[i + 1]
done
