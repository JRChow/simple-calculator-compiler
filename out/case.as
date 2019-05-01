	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L999:
	push	100
	pop	sb[0]
	push	sb[0]
	push	7
	mul
	pop	sb[1]
	push	sb[1]
	puti
	push	"Should be 700"
	puts
