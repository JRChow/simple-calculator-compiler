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
	push	0
	ret
	jmp	L002
L001:
	push	fp[-4]
	push	1
	compeq
	j0	L003
	push	1
	ret
L003:
	push	fp[-4]
	push	1
	sub
	call	L000, 1
	push	fp[-4]
	push	2
	sub
	call	L000, 1
	add
	ret
L002:
L999:
	push	"Enter a number:"
	puts
	geti
	pop	sb[0]
	push	sb[0]
	call	L000, 1
	puti
