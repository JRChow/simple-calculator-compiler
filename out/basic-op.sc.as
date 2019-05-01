	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L999:
	push	1
	push	3
	add
	pop	sb[0]
	push	6
	push	7
	sub
	pop	sb[1]
	push	sb[0]
	push	sb[1]
	mul
	pop	sb[2]
	push	sb[2]
	push	2
	neg
	div
	pop	sb[0]
	push	7
	push	sb[0]
	mod
	pop	sb[0]
	push	sb[0]
	puti
	push	"should be 1"
	puts
