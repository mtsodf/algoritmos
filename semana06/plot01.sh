folder=plot_01
mkdir -p ${folder}

for container in "unordered_list" "naive"
do
for container_event in "list"
do
for i in 1 2 3
do
    for n in 10 100 1000 10000 100000
    do

       ./semana06 --no_intersect ${n} --container ${container} --container_event ${container_event} --output ./${folder}/nointersect_${container}_${container_event}_${n}_${i}.json
    done

done
done
done

for container in "binary_tree" "avl" "list"
do
for container_event in "list" 
do
for i in 1 2 3
do
    for n in 10 100 1000 10000 100000 1000000
    do
       ./semana06 --no_intersect ${n} --container ${container} --container_event ${container_event} --output ./${folder}/nointersect_${container}_${container_event}_${n}_${i}.json
    done
done
done
done