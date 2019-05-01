#!/bin/sh

# Make the compiler
make c5c

# Run all test cases (.sc)
for fname in test/*.sc; do
    # Parameter extension
    echo ">>>>> Testing ${fname##*/} <<<<<"
    ./c5c $fname > out/${fname##*/}.as
    echo "[compilation finished]"
    ./nas/nas out/${fname##*/}.as
    echo "\n-------------------------------------\n"
done
