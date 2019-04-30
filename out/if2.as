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
	push	65
	pop	sb[1]
	push	sb[1]
	push	4
	complt
	j0	L000
	push sp
	push 1
	add
	pop sp
	push	6
	pop	sb[0]
	push sp
	push 1
	sub
	pop sp
L000:
	push	sb[0]
	puti
	push	"Should be 7"
	puts
