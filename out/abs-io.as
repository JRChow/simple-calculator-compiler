	push sp
	push 1
	add
	pop sp
	geti
	pop	sb[0]
	push	sb[0]
	push	0
	complt
	j0	L000
	push sp
	push 1
	add
	pop sp
	push	sb[0]
	neg
	pop	sb[0]
	push sp
	push 1
	sub
	pop sp
L000:
	push	sb[0]
	puti
