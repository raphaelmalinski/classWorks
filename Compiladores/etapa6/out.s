##FIXED INIT
.printintstr: .string "%d\n"
.printstringstr: .string "%s\n"

## TAC_BEGINFUN
	.globl main
main: 
	pushq %rbp
	movq	%rsp, %rbp
##TAC_PRINT
	movl	mYWeeirT_emp1(%rip), %esi
	leaq	.printintstr(%rip), %rax
	movq	%rax, %rdi
	call	printf
##TAC_PRINT
	movl	a(%rip), %esi
	leaq	.printintstr(%rip), %rax
	movq	%rax, %rdi
	call	printf
##TAC_PRINT
	movl	"Digite um numero: \n"(%rip), %esi
	leaq	.printintstr(%rip), %rax
	movq	%rax, %rdi
	call	printf
##TAC_PRINT
	movl	"Digite mais um numero: \n"(%rip), %esi
	leaq	.printintstr(%rip), %rax
	movq	%rax, %rdi
	call	printf
##TAC_PRINT
	movl	"Incrementado algumas vezes a fica "(%rip), %esi
	leaq	.printintstr(%rip), %rax
	movq	%rax, %rdi
	call	printf
##TAC_PRINT
	movl	mYWeeirT_emp6(%rip), %esi
	leaq	.printintstr(%rip), %rax
	movq	%rax, %rdi
	call	printf
##TAC_PRINT
	movl	a(%rip), %esi
	leaq	.printintstr(%rip), %rax
	movq	%rax, %rdi
	call	printf
##TAC_PRINT
	movl	"\n"(%rip), %esi
	leaq	.printintstr(%rip), %rax
	movq	%rax, %rdi
	call	printf
##TAC_PRINT
	movl	"A era=15\n"(%rip), %esi
	leaq	.printintstr(%rip), %rax
	movq	%rax, %rdi
	call	printf
##TAC_PRINT
	movl	"Nao tem como isso...\n"(%rip), %esi
	leaq	.printintstr(%rip), %rax
	movq	%rax, %rdi
	call	printf
##TAC_PRINT
	movl	"OK!\n"(%rip), %esi
	leaq	.printintstr(%rip), %rax
	movq	%rax, %rdi
	call	printf
##TAC_ENDFUN
	popq	%rbp
	ret
## TAC_BEGINFUN
	.globl incn
incn: 
	pushq %rbp
	movq	%rsp, %rbp
##TAC_ENDFUN
	popq	%rbp
	ret
## TAC_BEGINFUN
	.globl tese
tese: 
	pushq %rbp
	movq	%rsp, %rbp
##TAC_ENDFUN
	popq	%rbp
	ret
## DATA SECTION
	.section	.rodata

_a:	.long	0
_c:	.long	0
_d:	.long	0
_f:	.long	0
_i:	.long	0
_n:	.long	0
_v:	.long	0
_x:	.long	0
_mYWeeirT_emp0:	.long	0
_mYWeeirT_emp14:	.long	0
_matrix:	.long	0
_mYWeeirT_emp1:	.long	0
_mYWeeirT_emp2:	.long	0
_mYWeeirT_emp3:	.long	0
_mYWeeirT_emp10:	.long	0
_mYWeeirT_emp4:	.long	0
_mYWeeirT_emp5:	.long	0
_mYWeeirT_emp6:	.long	0
_mYWeeirT_emp11:	.long	0
_mYWeeirT_emp7:	.long	0
_mYWeeirT_emp8:	.long	0
_a.5:	.long	0
_mYWeeirT_emp9:	.long	0
_mYWeeirT_emp12:	.long	0
_mYWeeirT_emp13:	.long	0
