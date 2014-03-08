#/bin/bash

# array of possible items count
arr_count=(100 1000 10000)

# array of possible key lengths
arr_keylength=(100 1000 10000 100000)

# number of sort iterations
iterations=10

all_compilations=1

pushd ./bin

arr_count_max=0
for n in "${arr_count[@]}" ; do
    ((n > arr_count_max)) && arr_count_max=$n
done

for r_keylength in ${arr_keylength[*]}
do	
	#printf "\t%d\n" $r_keylength
	
	# generate dataset
	./rand-dataset.sh 0 $r_keylength $arr_count_max > dataset.tmp
	
	for r_count in ${arr_count[*]}
	do
		# replace first number in file to count and pass data to program
		cat dataset.tmp | sed "1s/.*/$r_count/" | ../target/benchmark bucket counting
		
    	#printf "%d\n" $r_count

		#if [ $all_compilations -gt 0 ]; then
		#	echo "ALL"
		#else
		#	echo "NOT ALL"
		#fi
	done
	
	rm dataset.tmp
done

popd
