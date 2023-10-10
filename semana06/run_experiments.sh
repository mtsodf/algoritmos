mkdir -p experiments


for container in "list" "unordered_list" "naive"
do
for i in 1 2 3 4 5
do
    for n in 10 100 1000 10000 100000 1000000
    do
        length=0.5
        length_std=0.1
        ./semana06 --random_point ${n} --container ${container} --length ${length} --length_std ${length} --output ./experiments/random_${container}_${length}_${length_std}_${n}_${i}.json

        length=0.01
        length_std=0.001
        ./semana06 --random_point ${n} --container ${container} --length ${length} --length_std ${length} --output ./experiments/random_${container}_${length}_${length_std}_${n}_${i}.json
        ./semana06 --no_intersect ${n} --container ${container} --output ./experiments/nointersect_${container}_${n}_${i}.json
    done
done
done

for container in "naive"
do
for i in 1 2 3 4 5
do
    for n in 10 100 1000 10000 100000
    do
        ./semana06 --no_intersect_big ${n} --container ${container} --output ./experiments/nointersectbig_${container}_${n}_${i}.json
    done
done
done

for container in "list" "unordered_list"
do
for i in 1 2 3 4 5
do
    for n in 10 100 1000
    do
        ./semana06 --no_intersect_big ${n} --container ${container} --output ./experiments/nointersectbig_${container}_${n}_${i}.json
    done
done
done

for container in "binary_tree" 
do
for i in 1 2 3 4 5
do
    for n in 10 100 1000 10000 100000 1000000
    do
        length=0.5
        length_std=0.1
        ./semana06 --random_point ${n} --container ${container} --length ${length} --length_std ${length} --output ./experiments/random_${container}_${length}_${length_std}_${n}_${i}.json

        length=0.01
        length_std=0.001
        ./semana06 --random_point ${n} --container ${container} --length ${length} --length_std ${length} --output ./experiments/random_${container}_${length}_${length_std}_${n}_${i}.json

        ./semana06 --no_intersect_big ${n} --container ${container} --output ./experiments/nointersectbig_${container}_${n}_${i}.json
        ./semana06 --no_intersect ${n} --container ${container} --output ./experiments/nointersect_${container}_${n}_${i}.json
    done
done
done