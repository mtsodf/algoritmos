folder=plot_random
mkdir -p ${folder}


for length in 0.1 0.3 0.6
do
for container in "binary_tree" "list" "avl"
do
for container_event in "list" "heap" 
do
for i in 1 2 3
do
    for n in 10 100 1000 10000
    do
       ./semana06 --random ${n} --container ${container} --length ${length} --length_std 0.02 --container_event ${container_event} --output ./${folder}/random_${container}_${container_event}_${length}_${n}_${i}.json
    done
done
done
done
done

for length in 0.1 0.3 0.6
do
for container in "unordered_list"
do
for container_event in "list" "heap" 
do
for i in 1 2 3
do
    for n in 10 100 1000 
    do
       ./semana06 --random ${n} --container ${container} --length ${length} --length_std 0.02 --container_event ${container_event} --output ./${folder}/random_${container}_${container_event}_${length}_${n}_${i}.json
    done
done
done
done
done



for length in 0.1 0.3 0.6
do
for container in "naive"
do
for container_event in ""
do
for i in 1 2 3
do
    for n in 10 100 1000 10000
    do
       ./semana06 --random ${n} --container ${container}  --length ${length} --length_std 0.02 --output ./${folder}/random_${container}_${container_event}_${length}_${n}_${i}.json
    done
done
done
done
done

for length in 0.1 0.3 
do
for container in "unordered_list"
do
for container_event in "list" "heap" 
do
for i in 1 2 3
do
    for n in 10000
    do
       ./semana06 --random ${n} --container ${container} --length ${length} --length_std 0.02 --container_event ${container_event} --output ./${folder}/random_${container}_${container_event}_${length}_${n}_${i}.json
    done
done
done
done
done
