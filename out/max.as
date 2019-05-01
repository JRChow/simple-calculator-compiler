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
	push	fp[-5]
	push	fp[-4]
	compgt
	j0	L001
	push	fp[-5]
	ret
L001:
	push	fp[-4]
	ret
L999:
	push	"Enter 2 numbers: "
	puts
	geti
	pop	sb[0]
	geti
	pop	sb[1]
	push	sb[0]
	push	sb[1]
	call	L000, 2
	pop	sb[2]
	push	sb[2]
	puti_
	push	" is larger"
	puts
