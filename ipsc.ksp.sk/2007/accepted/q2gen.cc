#include <cstdio>

/*
0 0 0

:MainLoop
>h ZhRMZ1
:L1 >x ZxL2 <x JL1 :L2 0
:L3 >x ZxL4 <x JL3 :L4 <h 0
:L5 >x ZxL6 <x JL5 :L6 <h 0
JMainLoop

:RMZ1 >x ZxRMZ2 <x JRMZ1
:RMZ2 >x ZxRMZ3 <x JRMZ2
:RMZ3
*/

int main()
{
	int K = 25;

	printf("0 0 0\n\n:L\n");
	for (int i = 0; i < K; i++)
		printf(">%c Z%cT%d\n", 'a'+i, 'a'+i, i);
	
	printf(":A >z ZzD <z JA :D 0\n");
	
	printf(":B >z ZzE <z JB :E");
	for (int i = 0; i < K; i++)
		printf(" <%c", 'a'+i);
	printf(" 0\n");

	printf(":C >z ZzF <z JC :F");
	for (int i = 0; i < K; i++)
		printf(" <%c", 'a'+i);
	printf(" 0\n");
	printf("JL\n\n");

	for (int t = 1; t < K; t++) {
		printf(":T%d\n", t);

		printf(":B%d >z ZzE%d <z JB%d :E%d", t, t, t, t);
		for (int i = 0; i < t; i++)
			printf(" <%c", 'a'+i);
		printf(" 0\n");

		printf(":C%d >z ZzF%d <z JC%d :F%d", t, t, t, t);
		for (int i = 0; i < t; i++)
			printf(" <%c", 'a'+i);
		printf(" 0\n");

		printf("JT0\n\n");
	}

	printf(
		":T0\n"
		":R1 >z ZzR2 <z JR1\n"
		":R2 >z ZzR3 <z JR2\n"
		":R3\n"
	);
}

