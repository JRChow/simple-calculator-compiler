#!/bin/bash

make c5c

# Compile test case into nas language
./c5c test/$1.sc > out/$1.as
# Run nas code
./nas/nas out/$1.as

