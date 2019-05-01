    push sp
    push 1000
    add
    pop sp
    jmp L999

L000:
    push sp
    push 100
    add
    pop sp
    push -1
    pop fp[0]
    push fp[-4]
    push sb[0]
    complt
    j0 L001
    push fp[-4]
    push -1
    call L002, 2
    pop fp[-4]
L001:
    push fp[-4]
    return
    
L002:
    push sp
    push 100
    add
    pop sp
    push fp[-4]
    push fp[-5]
    mul
    return

L999:
    push -1
    pop sb[1]
    push 0
    pop sb[0]
    push sb[1]
    call L000, 1
    puti
    push "should see 1"
    puts
    push sb[1]
    puti
    push "should see -1"
    puts

