	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L999:
	push	7
	pop	sb[0]
	push	'y'
	pop	sb[1]
	push	"Wat the f**k?"
	pop	sb[2]
	push	sb[0]
	puti
	push	sb[2]
	puts
	push	sb[1]
	putc
	push	0
	pop	sb[0]
	push	sb[0]
	puti
	push	'z'
	pop	sb[2]
	push	"Hopefully this works..."
	pop	sb[1]
	push	sb[2]
	putc
	push	sb[1]
	puts
