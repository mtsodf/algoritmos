folder=plot_grid
mkdir -p ${folder}


for container in "binary_tree" "list"
do
for container_event in "list" "heap" 
do
for i in 1 2 3
do
    for n in 10 100 1000 
    do
       ./semana06 --grid ${n} --container ${container} --container_event ${container_event} --output ./${folder}/grid_${container}_${container_event}_${n}_${i}.json
    done
done
done
done

for container in "avl"
do
for container_event in "list" "heap" 
do
for i in 1 2 3
do
    for n in 10 100 1000 10000 
    do
       ./semana06 --grid ${n} --container ${container} --container_event ${container_event} --output ./${folder}/grid_${container}_${container_event}_${n}_${i}.json
    done
done
done
done



for container in "naive"
do
for container_event in ""
do
for i in 1 2 3
do
    for n in 10 100 1000 10000
    do
       ./semana06 --grid ${n} --container ${container} --output ./${folder}/grid_${container}_${container_event}_${n}_${i}.json
    done
done
done
done
