	push sp
	push 1
	add
	pop sp
	push	0
	pop	sb[0]
	push sp
	push 1
	add
	pop sp
	push	10
	pop	sb[1]
	push sp
	push 1
	add
	pop sp
	push	1
	pop	sb[2]
L000:
	push	sb[0]
	push	3
	complt
	j0	L001
	push sp
	push 1
	add
	pop sp
	push	sb[1]
	push	sb[2]
	sub
	pop	sb[1]
	push sp
	push 1
	sub
	pop sp
	push sp
	push 1
	add
	pop sp
	push	sb[0]
	push	sb[2]
	add
	pop	sb[0]
	push sp
	push 1
	sub
	pop sp
	jmp	L000
L001:
	push	sb[1]
	puti
	push	"Should see 7"
	puts
	push	sb[2]
	puti
	push	"Should see 1"
	puts
	push	sb[0]
	puti
	push	"Should see 3"
	puts
