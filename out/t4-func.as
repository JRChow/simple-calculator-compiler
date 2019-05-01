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
	push	1
	neg
	pop	fp[0]
	push	fp[-4]
	push	sb[0]
	complt
	j0	L001
	push	fp[-4]
	push	1
	neg
	call	L002, 2
	pop	fp[-4]
L001:
	push	fp[-4]
	ret
	ret
L002:
	push	sp
	push	100
	add
	pop	sp
	push	fp[-5]
	push	fp[-4]
	mul
	ret
	ret
L999:
	push	789
	neg
	pop	sb[1]
	push	0
	pop	sb[0]
	push	sb[1]
	call	L000, 1
	puti
	push	"should see 789"
	puts
	push	sb[1]
	puti
	push	"should see -789"
	puts
