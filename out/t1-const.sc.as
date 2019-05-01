	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L999:
	push	'c'
	pop	sb[0]
	push	27
	pop	sb[1]
	push	"hello, world!"
	pop	sb[2]
