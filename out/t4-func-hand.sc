
label = 3
globalVarCount = 1
localVarCount = 0
inFunc = F

Function-label table
----------------------
abs | 0 -> print immediately at definition
mul | 2 -> print in call


Global var table (sb)
---------------------
z | 0


Local var table 1 (fp)
--------------------
x | -4 <- ...(x)
neg | 0


Local var table 2 (fp)
--------------------
y | -4 <- (x, y)
x | -5 <- (x, y)

====================================

Actual output nas code
--------------------

    jmp L999  // Generate at beginning

// Start parsing func abs(x) { ... }
// inFunc = T
L000:  // func abs -> not in Function table, add
    push -1   // Note: sp movement skipped here
    pop fp[0] // neg = -1;
    // Look up x in local table -> hit
    push fp[-4]
    // Look up z in local table -> no -> lookup z in global table -> no -> new var
    push sb[0]
    cmplt
    j0 L001
    // x = mul(x, -1);
    // mul(x, -1);
    // Look up mul in func table -> no -> new entry; Also need number of arguments in node
    CALL L002, 2  // result on stack top
    pop fp[-4]
    L001:
        // return x
        // execute x first
        push fp[-4]
        ret
        // inFunc = F
        // clear local table

// inFunc = T
// parse func mul(x, y)
// at definition, also first check if name's in table already
// mul -> 2 -> use Label 2
L002:
    // Needa build local table first
    // return x * y;
    // lookup x -> local hit
    push fp[-5]
    // lookup y -> local hit
    push fp[-4]
    mul
    ret
    // inFunc =F
    // clear local table

// MAIN
L999:
    // x = -1; 
    // x -> sb[2]
    push -1;
    pop sb[2];  // OK well there's no other way than to pre-allocate space for variables...


================================

Mechanisms
---------------

- L999 for main
- In function, when seeing variable, first look up Local table, then Global table, if still no, then declare new in global
