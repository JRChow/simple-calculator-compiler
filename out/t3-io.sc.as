	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L999:
	push	1
	pop	sb[0]
	push	'b'
	pop	sb[1]
	push	"This is C babe! "
	pop	sb[2]
	push	sb[0]
	puti_
	push	sb[0]
	puti
	push	sb[1]
	putc_
	push	sb[1]
	putc
	push	sb[2]
	puts_
	push	sb[2]
	puts
	push	1
	push	2
	push	3
	mul
	add
	puti_
	push	'F'
	putc_
	push	"UCK!"
	puts
	push	"Enter int and it'll be * 10: "
	puts
	geti
	pop	sb[3]
	push	sb[3]
	push	10
	mul
	puti
	push	"Enter char: "
	puts
	getc
	pop	sb[2]
	push	sb[2]
	putc
	push	"Enter string: "
	puts
	gets
	pop	sb[4]
	push	sb[4]
	puts
	push	"Enter another string: "
	puts
	gets
	pop	sb[4]
	push	sb[4]
	puts
