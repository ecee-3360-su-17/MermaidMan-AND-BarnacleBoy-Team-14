
 .global fib



fib:
	push {lr}
case_zero:
	cmp r1, #0
	beq case_one
	mov r0, #0
	mov pc, lr
	pop {pc}

case_one:
	cmp r1, #1
	beq fib_seq
	mov r0, #1
	mov pc, lr
	pop{pc}

fib_seq:
	push{r0}
	sub r0, r0, #1
	bl fib

	mov r1, r0
	pop{r0}
	sub r0, r0, #2
	bl fib

	add r0, r0, r1
	pop {pc}

