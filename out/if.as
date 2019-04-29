	push	"Enter an int: "
	puts
	geti
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
