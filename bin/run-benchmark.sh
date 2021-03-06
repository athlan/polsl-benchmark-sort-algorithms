#/bin/bash

# array of possible items count
arr_count=(100 1000 10000 100000)

# array of possible key lengths
arr_keylength=(100 1000 10000 65000)
#arr_keylength=(100 1000)

# number of sort iterations
iterations=100

all_compilations=1

pushd ./bin

arr_count_max=0
for n in "${arr_count[@]}" ; do
    ((n > arr_count_max)) && arr_count_max=$n
done

echo -e "optimization level;key range max;algorithm iterations;tab size;bucket sort time;counting sort time;quick sort time;";

for r_keylength in ${arr_keylength[*]}
do	
	#printf "\t%d\n" $r_keylength
	
	# generate dataset
	./rand-dataset.sh 0 $r_keylength $arr_count_max > dataset.tmp
	
	for r_count in ${arr_count[*]}
	do
		if [ $all_compilations -gt 0 ]; then
			printf "0;";
			printf "$r_keylength;";
			cat dataset.tmp | ../target/benchmark-o0 $iterations $r_count bucket counting quick
			echo "";
			
			printf "1;";
			printf "$r_keylength;";
			cat dataset.tmp | ../target/benchmark-o1 $iterations $r_count bucket counting quick
			echo "";
			
			printf "2;";
			printf "$r_keylength;";
			cat dataset.tmp | ../target/benchmark-o2 $iterations $r_count bucket counting quick
			echo "";
			
			printf "3;";
			printf "$r_keylength;";
			cat dataset.tmp | ../target/benchmark-o3 $iterations $r_count bucket counting quick
			echo "";
			
		else
			
			printf "0;";
			printf "$r_keylength;";
			cat dataset.tmp | ../target/benchmark $iterations $r_count bucket counting quick
			echo "";
		fi
	done
	
	rm dataset.tmp
done

popd
