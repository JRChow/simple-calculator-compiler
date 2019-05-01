	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L999:
	push	0
	pop	sb[0]
	push	sb[0]
	push	1
	add
	pop	sb[0]
	push	sb[0]
	push	1
	add
	pop	sb[0]
	push	sb[0]
	push	1
	add
	pop	sb[0]
	push	sb[0]
	puti
	push	"Should be 3"
	puts
