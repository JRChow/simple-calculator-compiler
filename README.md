# A Simple Calculator Language (`sc`) - Compiler

## To make

`make c5c`

## To run

- To compile: `./c5c test/fact.sc > out/fact.as`
- To execute using `nas`: `./nas/nas out/fact.as`

Note that there's an abstraction that compiles and executes together. `./run.sh fact` is equivalent to the above three instructions.

You can also run *all* the test cases in `/test` with `./run_all.sh`.

## Design of My Language

- Global variables will only be *referenced* inside functions but never redefined.
- I allow for 1,000 global variables, and 100 local variables for each function call
- Variable names are case-insensitive. Maximum 12 characters.

A program consists of two parts: function definition and the main section. `Main:` here is different from C's main--it's just the outmost scope. Function definitions can reference global variables in the main section. An example program is shown below:

```
// -- Function definitions --
// ...
func addOne(x) {
    result = x + one;
    return result;
}
// ...

// -- Main section --
Main:
one = 1;
puti(addOne(10));
```

The result would be 11.

## Test Cases

- Reverse string [test/t5-rev-c.sc](./test/t5-rev-c.sc)
- Max of two numbers [test/t5-max.sc](./test/t5-max.sc)
- Recursive factorial [test/t5-fact-recursive.sc](./test/t5-fact-recursive.sc)

## General TODO

- [x] Maybe add `end` at the end? Nah, I think it's used for functions.
- [x] Add the constraint that the maximum variable name length is 12 characters
- [x] Need to distinguish between global and local variables
- [x] Variable modification after definition
- [x] Finish remaining non-functional language features (e.g., `for`, `while`, `if`)
- [x] Deal with variable naming case insensitivity
- [x] Use `func xx() { ... }` and `xx();` to differentiate function definition and call
- [x] Is there a need to distinguish between function and variable names? I guess no need, just store them in separate tables
- [x] Probably use two tables, one for global and one for local?
- [x] Pre-allocate stack space for global & local variables
- [x] Label/offset should be defined by the first appearance of function/variable declaration OR reference

## General FIXME

- [x] Execution order is problematic... See 'test/var.sc'
- [x] The current method doesn't work because updates happen only locally... Probably still need something like a hash table for storing variable info
- [ ] `test/gets.sc` has a bug: after reading the first char, the second string read is skipped. Probably a problem with NAS not flushing its input buffer? Uh better not fix it yet, just leave it be right now
- [x] `test/while.sc` is not working...
- [x] \\\\ me, `test/abs.sc` is also not \\\\\\\ working, what the \\\\!
- [x] Double nested for loop is not working correctly

## Future Work
- [ ] Avoid the use of `main:` label and allow function declarations *everywhere*.

