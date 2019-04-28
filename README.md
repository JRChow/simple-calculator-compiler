# A Simple Calculator Language (`sc`) - Compiler

## To make

`make c5c`

## To run

- To compile: `./c5c test/fact.sc > out/fact.as`
- To execute using `nas`: `./nas/nas out/fact.as`

Note that there's an abstraction that compiles and executes together. `./run.sh fact` is equivalent to the above three instructions.

## General TODO

- [ ] Maybe add `end` at the end?
- [x] Add the constraint that the maximum variable name length is 12 characters
- [ ] Need to distinguish between global and local variables in the grammar
- [x] Variable modification after definition
- [ ] Finish remaining non-functional language features (e.g., loops)

## General FIXME

- [x] Execution order is problematic... See 'test/var.sc'
- [x] The current method doesn't work because updates happen only locally... Probably still need something like a hash table for storing variable info

