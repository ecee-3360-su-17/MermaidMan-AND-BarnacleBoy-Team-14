
 .global fib

fib:
	push {lr}

case_zero:
	cmp r0, #0
	bne case_one
	mov r0, #0
	pop{pc}

case_one:
	cmp r0, #1
	bne fib_seq
	mov r0, #1
	pop{pc}

fib_seq:

	push{r0}
	sub r0, r0, #1
	bl fib

	mov r1, r0
	pop{r0}

	push{r1}
	sub r0, r0, #2
	bl fib

	pop{r1}
	add r0, r0, r1
	pop{pc}

