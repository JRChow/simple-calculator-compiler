	push	"How many times? "
	puts
	push sp
	push 1
	add
	pop sp
	geti
	pop	sb[0]
L000:
	push	sb[0]
	push	0
	compgt
	j0	L001
	push	sb[0]
	puti
	push sp
	push 1
	add
	pop sp
	push	sb[0]
	push	1
	sub
	pop	sb[0]
	push sp
	push 1
	sub
	pop sp
	jmp	L000
L001:
