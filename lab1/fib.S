/*
 * fib.S
 *
 *  Created on: Jun 8, 2017
 *      Author: Albader
 */

/*int fib(int n){
    if(n == 0){         //Short pulse
        return 0;
    }
    else if(n == 1){    //Long pulse
        return 1;
    }
    else
        return fib(n-1) + fib(n-2);
}*/

/*.syntax unified
.cpu cortex-m0
.align 2
.global fib
.thumb
.thumb_func

fib:
case_zero:
	cmp r1, 0
	bne case_one
	mov r0, 0
	mov pc, lr

case_one:
	cmp r1, 1
	bne fib_seq
	mov r0, 1
	mov pc, lr

fib_seq:
	push{r0}
	sub r1, 1
	b fib
	pop{r3}
	sub r1, 2
	b fib
	pop{r4}
	add r3, r4
	mov pc, lr
*/
