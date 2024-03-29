#/bin/bash

# This script uses simple workloads. You should use it as a test for your code

npages=100
clock=10

for alg in fifo lru nru aging second-chance
do
    for nframes in 4 8 16 32
    do
	python3 memory_simulation.py $npages $nframes $alg $clock < load/10000.100.random.r.in > output/10000.100.random.r.$alg.$nframes.out
    done
done
