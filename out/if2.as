	push	7
	push	65
	push	sb[1]
	push	4
	complt
	j0	L000
	push	6
	pop	sb[0]
L000:
	push	sb[0]
	puti
	push	"Should be 7"
	puts
