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
	getc
	pop	fp[0]
	push	fp[0]
	push	10
	compne
	j0	L001
	call	L000, 0
	push	fp[0]
	putc_
L001:
	push	0
	ret
L999:
	push	"Please enter a line:"
	puts
	call	L000, 0
