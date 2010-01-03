char outbuf[30*1048576], inbuf[1048576];

int read(int, char *, int);
int write(int, char *, int);
int exit(int);

void main2()
{
	static int isdig[256];
	char *inp, *outp;
	unsigned i, n;

	for (i = 0; i < 256; i++) isdig[i] = 0;
	for (i = '0'; i <= '9'; i++) isdig[i] = 1;

	read(0, inp = inbuf, sizeof(inbuf));
	outp = outbuf;

	for (;;) {
		while (!isdig[*inp]) inp++;
		for (n = *inp++ - '0'; isdig[*inp];) n = n * 10 + *inp++ - '0';

		if (n == 0) break;

		if (n <= 2) {
			for (i = 0; i < 11; i++)
				*outp++ = "Impossible\n"[i];
			continue;
		}

		for (i = 0; i < n; i++) outp[i] = '1';

		for (i = n >> 1; i < n; i++) {

asm(
"movl	%0, %%eax\n"
"mull	%%eax\n"
"addl	$-1, %%eax\n"
"adcl	$-1, %%edx\n"
"divl	%1\n"
"movb	$48, (%2,%%edx)\n"
 :: "br" (i), "cr" (n), "Dr" (outp) : "eax", "edx", "cc");


/*
ebx = i, ecx = n, edi = outp

movl	ebx, eax
mull	eax
addl	$-1, eax
adcl	$-1, edx
divl	ecx
movb	$48, (%edi,%edx)

uses eax, edx

outp[((unsigned long long)i * (unsigned long long)i - 1) % n] = '0';
*/

		}

		outp[n - 1] = '\n';
		outp += n;
	}

	write(1, outbuf, outp - outbuf);
	exit(0);
}

int main()
{
	main2();
	return 0;
}
