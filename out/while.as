	push	"How many times? "
	puts
	geti
L000:
	push	sb[0]
	push	0
	compgt
	j0	L001
	push	sb[0]
	puti
	push	sb[0]
	push	1
	sub
	jmp	L000
L001:
