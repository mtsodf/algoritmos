folder=plot_nintersects
mkdir -p ${folder}


for length in 0.1 0.3 0.6
do
for container in "naive"
do
for container_event in ""
do
for i in 1 2 3 4 5
do
    for n in $(seq 10 10 100)
    do
       ./semana06 --random ${n} --container ${container}  --length ${length} --length_std 0.02 --output ./${folder}/random_${container}_${container_event}_${length}_${n}_${i}.json
    done

    for n in $(seq 100 100 1000)
    do
       ./semana06 --random ${n} --container ${container}  --length ${length} --length_std 0.02 --output ./${folder}/random_${container}_${container_event}_${length}_${n}_${i}.json
    done

    for n in $(seq 1000 1000 10000)
    do
       ./semana06 --random ${n} --container ${container}  --length ${length} --length_std 0.02 --output ./${folder}/random_${container}_${container_event}_${length}_${n}_${i}.json
    done

done
done
done
done