	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L999:
	push	"Enter a number:"
	puts
	geti
	pop	sb[0]
	push	sb[0]
	push	0
	compeq
	j0	L000
	push	1
	puti
	jmp	L001
L000:
	push	sb[0]
	push	1
	compge
	push	sb[0]
	push	12
	comple
	and
	j0	L002
	push	1
	pop	sb[1]
L003:
	push	sb[0]
	push	1
	compgt
	j0	L004
	push	sb[1]
	push	sb[0]
	mul
	pop	sb[1]
	push	sb[0]
	push	1
	sub
	pop	sb[0]
	jmp	L003
L004:
	push	sb[1]
	puti
L002:
L001:
