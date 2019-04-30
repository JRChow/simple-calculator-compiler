	push	"Gonna see:"
	puts
	push	"0..3"
	puts
	push	"0..4"
	puts
	push	"0..5"
	puts
	push	3
L000:
	push	sb[0]
	push	6
	complt
	j0	L001
	push	0
L002:
	push	sb[1]
	push	sb[0]
	comple
	j0	L003
	push	sb[1]
	puti
	push	sb[1]
	push	1
	add
	pop	sb[1]
	jmp	L002
L003:
	push	sb[0]
	push	1
	add
	pop	sb[0]
	jmp	L000
L001:
