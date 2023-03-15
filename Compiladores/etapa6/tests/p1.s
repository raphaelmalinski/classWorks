##FIXED_INIT 
.printintstr: .string "%d\n"
.printstringstr: .string "%s\n"
	
##TAC_BEGINFUN
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp

##TAC_PRINT
	movl	_888(%rip), %esi
	leaq	.printintstr(%rip), %rax
	movq	%rax, %rdi
	call	printf

##TAC_ENDFUN
	popq	%rbp
	ret

## DATA SECTION
	.section	.rodata

a:	.long 4
_888: .long 888


