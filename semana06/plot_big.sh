folder=plot_big
mkdir -p plot_big


for container in "naive"
do
for i in 1 2 3 4 5
do
    for n in 10 100 1000 10000
    do
        ./semana06 --no_intersect_big ${n} --container ${container} --output ./${folder}/nointersectbig_${container}_${n}_${i}.json
    done
done
done

for container in "list" "unordered_list"
do
for i in 1 2 3 4 5
do
    for n in 10 100 1000
    do
        ./semana06 --no_intersect_big ${n} --container ${container} --output ./${folder}/nointersectbig_${container}_${n}_${i}.json
    done
done
done

for container in "binary_tree" "avl"
do
for i in 1 2 3 4 5
do
    for n in 10 100 1000 10000 100000 1000000
    do
        ./semana06 --no_intersect_big ${n} --container ${container} --output ./${folder}/nointersectbig_${container}_${n}_${i}.json
    done
done
done
