

 .global fib


fib:
case_zero:
	cmp r1, #0
	beq case_one
	mov r0, #0
	mov pc, lr

case_one:
	cmp r1, #1
	beq fib_seq
	mov r0, #1
	mov pc, lr

fib_seq:
	push{r0}
	sub r1, r1, #1
	b fib
	pop{r3}

	sub r1, r1, #2
	b fib
	pop{r4}
	add r3, r4
	mov pc, lr

