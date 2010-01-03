#include <stdio.h>
#include <string.h>

int rem(char *s, int d) {
	int r = 0;
	for (; *s; s++)
		r = (r * 10 + *s - '0') % d;
	return r;
}

int main()
{
	static char s[65536];
	int T=0;

	while (scanf(" %[0-9]", s) == 1) {
		{ int k=0;for(k=0;s[k]&&s[k]=='0';k++);if(s[k]=='\0')break; }

		if (T++) printf("\n");

		printf("%s\n", s);

		int cnt = 0;

		int X=0;
		for (int i = 0; X < 9999 && s[i]; i++)
			X = X * 10 + s[i] - '0';
		if (X < 2148) goto no;	


		if (rem(s,2) == 2148%2) cnt+=printf("Ghost of Tanveer Ahsan!!!\n");
		if (rem(s,5) == 2148%5) cnt+=printf("Ghost of Shahriar Manzoor!!!\n");
		if (rem(s,7) == 2148%7) cnt+=printf("Ghost of Adrian Kugel!!!\n");
		if (rem(s,11) == 2148%11) cnt+=printf("Ghost of Anton Maydell!!!\n");
		if (rem(s,15) == 2148%15) cnt+=printf("Ghost of Derek Kisman!!!\n");
		if (rem(s,20) == 2148%20) cnt+=printf("Ghost of Rezaul Alam Chowdhury!!!\n");
		if (rem(s,28) == 2148%28) cnt+=printf("Ghost of Jimmy Mardell!!!\n");
		if (rem(s,36) == 2148%36) cnt+=printf("Ghost of Monirul Hasan!!!\n");

		if ( ((rem(s,4)==0 && rem(s,100)!=0) || rem(s,400)==0) )
			cnt+=printf("Ghost of K. M. Iftekhar!!!\n");
no:
		if (cnt == 0) printf("No ghost will come in this year\n");

//		printf("\n");
	}

	return 0;
}
