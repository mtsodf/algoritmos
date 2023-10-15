folder=experiments_detection
mkdir -p ${folder}


for container in "list" "unordered_list" "naive"
do
for i in 1 2 3 4 5
do
    for n in 10 100 1000 10000 100000 1000000
    do
       gtimeout -k 2 2s ./semana06 --no_intersect ${n} --container ${container} --container_event list --output ./${folder}/nointersect_${container}_${n}_${i}.json
    done
done
done

for container in "list" "unordered_list" "naive"
do
for i in 1 2 3 4 5
do
    for n in 10 100 1000 10000 100000
    do
       gtimeout -k 2 2s ./semana06 --no_intersect_big ${n} --container ${container} --container_event list --output ./${folder}/nointersectbig_${container}_${n}_${i}.json
    done
done
done

for container in "binary_tree"
do
for i in 1 2 3 4 5
do
    for n in 10 100 1000 10000 100000 1000000 10000000
    do
        gtimeout -k 10 10s ./semana06 --no_intersect ${n} --container ${container} --container_event list --output ./${folder}/nointersect_${container}_${n}_${i}.json
        gtimeout -k 10 10s ./semana06 --no_intersect_big ${n} --container ${container} --container_event list --output ./${folder}/nointersectbig_${container}_${n}_${i}.json
    done
done
done


