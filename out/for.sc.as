	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L999:
	push	"Gonna print 0...9"
	puts
	push	0
	pop	sb[0]
L000:
	push	sb[0]
	push	10
	complt
	j0	L001
	push	sb[0]
	puti
	push	sb[0]
	push	1
	add
	pop	sb[0]
	jmp	L000
L001:
