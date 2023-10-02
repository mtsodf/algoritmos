mkdir -p circles

# for alg in graham 
# do
# for i in 1 2 3 4 5
# do
#     for n in 10 100 1000 10000 100000 1000000
#     do
#         ./semana05 --random_point ${n} --alg ${alg} --circle 1 --output ./circles/random_${alg}_${n}_${i}.json
#     done
# done
# done

for alg in trig 
do
for i in 1 2 3 4 5
do
    for n in 10 100 1000 10000 100000
    do
        ./semana05 --random_point ${n} --alg ${alg} --circle 1 --output ./circles/random_${alg}_${n}_${i}.json
    done
done
done