	push sp
	push 1
	add
	pop sp
	push	7
	pop	sb[0]
	push sp
	push 1
	add
	pop sp
	push	'y'
	pop	sb[1]
	push sp
	push 1
	add
	pop sp
	push	"Wat the fuck?"
	pop	sb[2]
	push	sb[0]
	puti
	push	sb[2]
	puts
	push	sb[1]
	putc
	push sp
	push 1
	add
	pop sp
	push	0
	pop	sb[0]
	push sp
	push 1
	sub
	pop sp
	push	sb[0]
	puti
	push sp
	push 1
	add
	pop sp
	push	'z'
	pop	sb[2]
	push sp
	push 1
	sub
	pop sp
	push sp
	push 1
	add
	pop sp
	push	"Hopefully this works..."
	pop	sb[1]
	push sp
	push 1
	sub
	pop sp
	push	sb[2]
	putc
	push	sb[1]
	puts
