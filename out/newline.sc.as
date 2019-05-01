	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L999:
	push	"Enter a char:"
	puts
	getc
	pop	sb[0]
	push	sb[0]
	push	10
	compeq
	j0	L000
	push	"It's a newline!"
	puts
	jmp	L001
L000:
	push	"It's not..."
	puts
L001:
