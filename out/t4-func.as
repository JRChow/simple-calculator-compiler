    // # Function-Label Table
    // abs | 0
    // mul | 2
    //
    // # Local Variable Table (1)
    // x | -4
    // neg | 0
    //
    // # Local Variable Table (2)
    // y | -4
    // x | -5
    //
    // # Global Variable Table
    // z | 0
    // x | 1

    // ======================================
    // Pre-allocate stack space for global vars
    push sp
    push 1000
    add
    pop sp
    // Jump to MAIN
    jmp L999

    // ----- func abs(x) ----
L000:  // abs not in table, add
    // Pre-allocate stack space for local vars
    push sp
    push 100
    add
    pop sp
    // Parse parameters
    // neg = -1;
    push -1
    pop fp[0]
    // if (x < z)
    push fp[-4]
    // *Reference* of z not found, add to global table
    push sb[0]
    complt
    j0 L001  // If condition fails
    // mul(x, -1)
    push fp[-4]
    push -1
    // mul not found, add to func table
    call L002, 2
    pop fp[-4]
L001:
    // Probably need to lower sp here?
    push fp[-4]
    ret
    // Clean local table
    
    // ---- func mul(x,y) ----
L002:  // Lookup in table, found label 2
    // Pre-allocate 100 local variables
    push sp
    push 100
    add
    pop sp
    // Parse parameters into local table
    // return x * y
    push fp[-4]
    push fp[-5]
    mul
    ret
    // Clean local table

L999:  // MAIN (stack space already allocated at start)
    // x = -77
    push -77
    pop sb[1]
    push 0
    pop sb[0]
    // puti(abs(x))
    // abs(x)
    // x
    push sb[1]
    call L000, 1
    puti
    push "should see 77"
    puts
    push sb[1]
    puti
    push "should see -77"
    puts

