#! /bin/sh

for country in $(ls ./countrydata/*.txt) 
do
    python ./cli.py $country -i -o -s
done