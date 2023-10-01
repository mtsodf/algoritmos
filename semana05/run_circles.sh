mkdir -p circles

for i in 1 2 3 4 5
do
    for n in 10 100 1000 10000
    do
        ./semana05 --random_point ${n} --alg ${alg} --circle 1 --output ./circles/random_${n}_${i}.json 
    done
done
