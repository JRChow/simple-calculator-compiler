	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L999:
	push	7
	pop	sb[0]
	push	65
	pop	sb[1]
	push	sb[1]
	push	4
	complt
	j0	L000
	push	6
	pop	sb[0]
L000:
	push	sb[0]
	puti
	push	"Should be 7"
	puts
