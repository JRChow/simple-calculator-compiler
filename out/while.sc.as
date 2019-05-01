	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L999:
	push	"How many times? "
	puts
	geti
	pop	sb[0]
L000:
	push	sb[0]
	push	0
	compgt
	j0	L001
	push	sb[0]
	puti
	push	sb[0]
	push	1
	sub
	pop	sb[0]
	jmp	L000
L001:
