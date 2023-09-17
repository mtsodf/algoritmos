mkdir -p circles

alg=graham
for i in 1 2 3 4 5
do
    for n in 10 100 1000 10000 100000 1000000
    do
        ./main --random_point ${n} --circle 1 --output ./circles/random_${alg}_${n}_${i}.json 
    done
done
