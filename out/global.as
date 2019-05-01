	push	sp
	push	1000
	add
	pop	sp
	jmp	L999
L000:
	push	sp
	push	100
	add
	pop	sp
	push	sb[0]
	puts
	ret
L999:
	push	"Hello world!"
	pop	sb[0]
	call	L000, 0
