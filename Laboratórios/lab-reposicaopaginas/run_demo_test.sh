#/bin/bash

# This script uses a minimal workload. It's only purpose is for debbuging and better understanding of your code

npages=7
clock=2

if [ -z $1 ]; then
  alg=random
else
  alg=$1 # This is where you select the algorithm you want to test
fi
    
for nframes in 2 3 4 5 6 7
do
    python3 memory_simulation.py $npages $nframes $alg $clock < load/minimal > output/minimal.$alg.$nframes.out
done
