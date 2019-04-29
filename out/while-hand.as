	push	"How many times? "
	puts
	geti
    push 0
    pop in
L000:
	push	sb[in]
	push	0
	compgt
	j0	L001
	push	sb[in]
	puti
	push	sb[in]
	push	1
	sub
    push in
    push 1
    add
    pop in
	jmp	L000
L001:
