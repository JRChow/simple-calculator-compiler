# A Simple Calculator Language (`sc`) - Compiler

## To make

`make c5c`

## To run

- To compile: `./c5c test/fact.sc > out/fact.as`
- To execute using `nas`: `./nas/nas out/fact.as`

Note that there's an abstraction that compiles and executes together. `./run.sh fact` is equivalent to the above three instructions.

## A few notes

- Global variables will only be *referenced* inside functions but never redefined.
- Can consider using a label `main:` in `c5` if necessary...
- Function declaration and return should be `stmt`
- Function body should also be statements (function within function is not required)
- Function call should be an `expr`
- OK to have both function declaration and body as statements 
- For both main and functions, need to adjust `sp` at the beginning to point above local variables
- Use a boolean variable to indicate I'm parsing inside a function body, so can use `fp` instead of `sb` which is for the main program

## General TODO

- [x] Maybe add `end` at the end? Nah, I think it's used for functions.
- [x] Add the constraint that the maximum variable name length is 12 characters
- [ ] Need to distinguish between global and local variables in the grammar
- [x] Variable modification after definition
- [x] Finish remaining non-functional language features (e.g., `for`, `while`, `if`)
- [ ] Deal with variable naming case insensitivity
- [ ] Use `func xx() { ... }` and `xx();` to differentiate function definition and call
- [ ] Function definitions may appear anywhere.
- [ ] Is there a need to distinguish between function and variable names?
- [ ] Probably use two tables, one for global and one for local?

## General FIXME

- [x] Execution order is problematic... See 'test/var.sc'
- [x] The current method doesn't work because updates happen only locally... Probably still need something like a hash table for storing variable info
- [ ] `test/gets.sc` has a bug: after reading the first char, the second string read is skipped. Probably a problem with NAS not flushing its input buffer? Uh better not fix it yet, just leave it be right now
- [x] `test/while.sc` is not working...
- [x] F\\k me, `test/abs.sc` is also not f\\king working, what the f\\k!
- [x] Double nested for loop is not working correctly
