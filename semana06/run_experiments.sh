mkdir -p experiments


length=0.1
length_std=0.01
for container in "list" "unordered_list" "binary_tree" 
do
for i in 1 2 3 4 5
do
    for n in 10 100 1000 10000 100000 1000000
    do
        ./semana06 --random_point ${n} --container ${container} --length ${length} --length_std ${length} --output ./experiments/random_${container}_${length}_${length_std}_${n}_${i}.json
    done
done
done