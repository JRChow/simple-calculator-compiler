#!/bin/bash
make c5c

./c5c test/$1.sc > out/$1.as
./nas/nas out/$1.as

