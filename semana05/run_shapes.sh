mkdir -p shapes

for alg in graham  trig
do

./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/alienbs.txt --output ./shapes/alienbs_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/aliendp.txt --output ./shapes/aliendp_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/camel.txt --output ./shapes/camel_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/cartbs.txt --output ./shapes/cartbs_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/cartdp.txt --output ./shapes/cartdp_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/cathole.txt --output ./shapes/cathole_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/catholebs.txt --output ./shapes/catholebs_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/crownbs.txt --output ./shapes/crownbs_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/crowndp.txt --output ./shapes/crowndp_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/deer20dp.txt --output ./shapes/deer20dp_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/deerbs.txt --output ./shapes/deerbs_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/deerdp.txt --output ./shapes/deerdp_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/dog.txt --output ./shapes/dog_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/dogbs.txt --output ./shapes/dogbs_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/dogdp.txt --output ./shapes/dogdp_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/dogsbs.txt --output ./shapes/dogsbs_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/dovebs.txt --output ./shapes/dovebs_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/dovedp.txt --output ./shapes/dovedp_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/duckbs.txt --output ./shapes/duckbs_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/duckdp.txt --output ./shapes/duckdp_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/fishbs.txt --output ./shapes/fishbs_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/fishdp.txt --output ./shapes/fishdp_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/head.txt --output ./shapes/head_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/headbs.txt --output ./shapes/headbs_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/introbs.txt --output ./shapes/introbs_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/introdp.txt --output ./shapes/introdp_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/jig.txt --output ./shapes/jig_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/jigbs.txt --output ./shapes/jigbs_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/knightbs.txt --output ./shapes/knightbs_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/knightdp.txt --output ./shapes/knightdp_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/multfishbs.txt --output ./shapes/multfishbs_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/multfishdp.txt --output ./shapes/multfishdp_${alg}.json
./semana05 --alg ${alg} --input ../../semana03/Reconstruction-CTShape/Sample_Data/noise.txt --output ./shapes/noise_${alg}.json

python ../../semana03/read_convex.py ./shapes/alienbs_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/aliendp_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/camel_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/cartbs_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/cartdp_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/cathole_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/catholebs_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/crownbs_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/crowndp_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/deer20dp_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/deerbs_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/deerdp_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/dog_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/dogbs_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/dogdp_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/dogsbs_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/dovebs_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/dovedp_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/duckbs_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/duckdp_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/fishbs_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/fishdp_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/head_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/headbs_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/introbs_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/introdp_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/jig_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/jigbs_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/knightbs_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/knightdp_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/multfishbs_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/multfishdp_${alg}.json -iy -lw 0.1
python ../../semana03/read_convex.py ./shapes/noise_${alg}.json -iy -lw 0.1


done