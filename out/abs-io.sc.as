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
	complt
	j0	L000
	push	sb[0]
	neg
	pop	sb[0]
L000:
	push	sb[0]
	puti
