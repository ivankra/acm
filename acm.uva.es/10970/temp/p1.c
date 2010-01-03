int read(int, char *, int);
int write(int, char *, int);

static char buf[1048576];
static int d[128];

__asm__(".globl _main\n_main: jmp _main1\n");

__asm__(
"proc:\n"
"	subl	$32, %esp\n"

/* esi = p,  edi = q */
"	movl	$_buf, %esi\n"
"	movl	%esi, %edi\n"
"	dec	%esi\n"

"A1:	inc	%esi\n"
"	movzbl	(%esi), %ebx\n"
"	movl	_d(,%ebx,4), %ecx\n"
"	testl	%ecx, %ecx\n"
"	jz	A1\n"

"	subl	$'0', %ebx\n"
"	movl	%ebx, %eax\n"
"A2:	incl	%esi\n"
"	movzbl	(%esi), %ebx\n"
"	movl	_d(,%ebx,4), %ecx\n"
"	testl	%ecx, %ecx\n"
"	jz	A3\n"
"	imull	$10, %eax, %eax\n"
"	subl	$'0', %ebx\n"
"	addl	%ebx, %eax\n"
"	jmp	A2\n"
"A3:	testl	%eax, %eax\n"
"	jz	Adone\n"
"	pushl	%eax\n"

"A4:	inc	%esi\n"
"	movzbl	(%esi), %ebx\n"
"	movl	_d(,%ebx,4), %ecx\n"
"	testl	%ecx, %ecx\n"
"	jz	A4\n"

"	subl	$'0', %ebx\n"
"	movl	%ebx, %eax\n"
"A5:	incl	%esi\n"
"	movzbl	(%esi), %ebx\n"
"	movl	_d(,%ebx,4), %ecx\n"
"	testl	%ecx, %ecx\n"
"	jz	A6\n"
"	imull	$10, %eax, %eax\n"
"	subl	$'0', %ebx\n"
"	addl	%ebx, %eax\n"
"	jmp	A5\n"
"A6:	popl	%ebx\n"
"	imull	%ebx, %eax\n"
"	decl	%eax\n"
"	jz	Azero\n"

"	movl	%eax, %ebx\n"
"	xorl	%ecx, %ecx\n"

"A7:	movl	$1717986919, %eax\n"
"	imull	%ebx\n"
"	sarl	$2, %edx\n"
"	movl	%ebx, %eax\n"
"	sarl	$31, %eax\n"
"	subl	%eax, %edx\n"
"	leal	(%edx,%edx,4), %eax\n"
"	addl	%eax, %eax\n"
"	subl	%eax, %ebx\n"
"	pushl	%ebx\n"
"	incl	%ecx\n"
"	movl	%edx, %ebx\n"
"	test	%ebx, %ebx\n"
"	jnz	A7\n"

"A8:	popl	%eax\n"
"	add	$'0', %eax\n"
"	movb	%al, (%edi)\n"
"	incl	%edi\n"
"	dec	%ecx\n"
"	jnz	A8\n"

"	movb	$'\n', (%edi)\n"
"	inc	%edi\n"
"	jmp	A1\n"

"Azero:\n"
"	movw	$0x0A30, (%edi)\n"
"	inc	%edi\n"
"	inc	%edi\n"
"	jmp	A1\n"

"Adone:\n"
"	movl	$1, (%esp)\n"
"	movl	$_buf, 4(%esp)\n"
"	subl	$_buf, %edi\n"
"	movl	%edi, 8(%esp)\n"
"	call	_write\n"
"	movl	$0, (%esp)\n"
"	call	_exit\n"
);

void main1()
{
	int i;

	for (i = '0'; i <= '9'; i++) d[i] = 1;

	i = read(0, buf, sizeof(buf));
	buf[i++] = ' '; buf[i++] = '0'; buf[i++] = ' ';

	__asm__("jmp proc\n");
}
