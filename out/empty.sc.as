	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L999:
	push	' '
	pop	sb[0]
	push	""
	pop	sb[1]
	push	sb[0]
	putc
	push	sb[1]
	puts
