	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L999:
	push	"Enter a char: "
	puts
	getc
	pop	sb[0]
	push	sb[0]
	putc
	push	"Enter a string: "
	puts
	gets
	pop	sb[1]
	push	sb[1]
	puts
	push	"Enter another string: "
	puts
	gets
	pop	sb[1]
	push	sb[1]
	puts
