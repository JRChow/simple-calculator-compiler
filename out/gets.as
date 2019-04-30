	push	"Enter a char: "
	puts
	push sp
	push 1
	add
	pop sp
	getc
	pop	sb[0]
	push	sb[0]
	putc
	push	"Enter a string: "
	puts
	push sp
	push 1
	add
	pop sp
	gets
	pop	sb[1]
	push	sb[1]
	puts
	push	"Enter another string: "
	puts
	push sp
	push 1
	add
	pop sp
	gets
	pop	sb[1]
	push sp
	push 1
	sub
	pop sp
	push	sb[1]
	puts
