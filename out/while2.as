	push	0
Hash table updated for i : 0 to idx 0
	push	10
Hash table updated for x : 0 to idx 1
L000:
	push	sb[0]
	push	3
	complt
	j0	L001
	push	sb[1]
	push	1
	sub
Hash table updated for x : 0 to idx 2
	push	sb[0]
	push	1
	add
Hash table updated for i : 0 to idx 3
	jmp	L000
L001:
	push	sb[2]
	puti
