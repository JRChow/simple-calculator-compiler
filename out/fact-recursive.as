	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L000:
	push	sp
	push	100
	add
	pop	sp
	push	fp[-4]
	push	0
	compeq
	j0	L001
	push	1
	ret
L001:
	push	fp[-4]
	push	fp[-4]
	push	1
	sub
	call	L000, 1
	mul
	ret
L999:
	push	"Enter a number:"
	puts
	geti
	pop	sb[0]
	push	sb[0]
	call	L000, 1
	puti
