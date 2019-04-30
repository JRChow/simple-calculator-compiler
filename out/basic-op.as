	push sp
	push 1
	add
	pop sp
	push	1
	push	3
	add
	pop	sb[0]
	push sp
	push 1
	add
	pop sp
	push	6
	push	7
	sub
	pop	sb[1]
	push sp
	push 1
	add
	pop sp
	push	sb[0]
	push	sb[1]
	mul
	pop	sb[2]
	push sp
	push 1
	add
	pop sp
	push	sb[2]
	push	2
	neg
	div
	pop	sb[0]
	push sp
	push 1
	sub
	pop sp
	push sp
	push 1
	add
	pop sp
	push	7
	push	sb[0]
	mod
	pop	sb[0]
	push sp
	push 1
	sub
	pop sp
	push	sb[0]
	puti
	push	"should be 1"
	puts
