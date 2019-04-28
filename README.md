# A Simple Calculator Language (`sc`) - Compiler

## To make

`make c5c`

## To run

- To compile: `./c5c test/fact.sc > out/fact.as`
- To execute using `nas`: `./nas/nas out/fact.as`

## General TODO

- [ ] Maybe add `end` at the end?
- [ ] Add the constraint that the maximum variable name length is 12 characters
- [ ] Need to distinguish between global and local variables in the grammar
- [ ] Variable modification after definition

## General FIXME

- [ ] Execution order is problematic... See 'test/var.sc'
- [ ] The current method doesn't work because updates happen only locally... Probably still need something like a hash table for storing variable info

