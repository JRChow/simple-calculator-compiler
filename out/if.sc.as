	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L999:
	push	"Enter an int: "
	puts
	geti
	pop	sb[0]
	push	sb[0]
	puti_
	push	sb[0]
	push	10
	compge
	j0	L000
	push	" >= 10"
	puts
	jmp	L001
L000:
	push	" < 10"
	puts
L001:
