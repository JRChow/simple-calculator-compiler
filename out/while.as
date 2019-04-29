	push	"How many times? "
	puts
	geti
Hash table updated for n : 0 to idx 0
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
Hash table updated for n : 0 to idx 1
	jmp	L000
L001:
