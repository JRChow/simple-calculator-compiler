	push	0
	push	10
L000:
	push	sb[0]
	push	3
	complt
	j0	L001
	push	sb[1]
	push	1
	sub
	pop	sb[1]
	push	sb[0]
	push	1
	add
	pop	sb[0]
	jmp	L000
L001:
	push	sb[1]
	puti
	push	"Should see 7"
	puts
