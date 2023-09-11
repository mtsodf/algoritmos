mkdir -p circles

alg=jarvis
for i in {1..5}
do
    for n in 10 100 1000 10000 100000 1000000
    do
        ./convex_hull --random_point ${n} --circle 1 --output ./circles/random_${alg}_${n}_${i}.json --alg ${alg}
    done
done
 
alg=n3
for i in {1..5}
do
    for n in 10 100 1000 10000 100000
    do
        ./convex_hull --random_point ${n} --circle 1 --output ./circles/random_${alg}_${n}_${i}.json --alg ${alg}
    done
done

alg=naive
for i in {1..5}
do
    for n in 5 10 100 200 300
    do
        ./convex_hull --random_point ${n} --circle 1 --output ./circles/random_${alg}_${n}_${i}.json --alg ${alg}
    done
done