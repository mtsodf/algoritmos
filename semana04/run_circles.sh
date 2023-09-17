mkdir -p circles

for alg in "selection" "heap" "std" "insertion" "quick"
do
for i in 1 2 3 4 5
do
    for n in 10 100 1000 10000 100000
    do
        ./main --random_point ${n} --alg ${alg} --circle 1 --output ./circles/random_${alg}_${n}_${i}.json 
    done
done
done
