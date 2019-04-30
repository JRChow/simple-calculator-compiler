	push	"Gonna print 0...9"
	puts
	push sp
	push 1
	add
	pop sp
	push	0
	pop	sb[0]
L000:
	push	sb[0]
	push	10
	complt
	j0	L001
	push	sb[0]
	puti
	push sp
	push 1
	add
	pop sp
	push	sb[0]
	push	1
	add
	pop	sb[0]
	push sp
	push 1
	sub
	pop sp
	jmp	L000
L001:
