	push sp
	push 1
	add
	pop sp
	push	' '
	pop	sb[0]
	push sp
	push 1
	add
	pop sp
	push	""
	pop	sb[1]
	push	sb[0]
	putc
	push	sb[1]
	puts
