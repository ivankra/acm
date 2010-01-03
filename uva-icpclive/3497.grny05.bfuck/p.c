#include <stdio.h>
#include <string.h>

unsigned char M[32768], C[131072];
unsigned arg[131072], list[131072], n, mp, cp;

int main()
{
	int i,c,N,T;

	for (scanf("%d", &N), T=1; T<=N; T++) {
		printf("PROGRAM #%d:\n", T);

		for (i = n = 0; (c = getchar()) != EOF && i < 3;) {
			if (c == '\r') continue;
			if (strchr("<>+-.[]", c)) {i=0; C[n++] = c;}
			else if (c == '%') { i=0; while((c=getchar()) != EOF && c != '\n'); ungetc('\n',stdin); }
			else if (c == "end"[i]) i++;
		}

		for (i = c = 0; i < n; i++) {
			if (C[i]=='[') list[c++]=i;
			else if (C[i]==']') {
				if (c-- == 0) break;
				arg[list[c]] = i+1;
				arg[i] = list[c];
			}
		}

		if (i < n || c != 0) {
			printf("COMPILE ERROR\n");
			continue;
		}

		for (i = 0; i < n;) {
			if (C[i]=='[' || C[i]==']' || C[i]=='.') {i++;continue;}
			for (c = 1; i+c < n && C[i+c] == C[i]; c++);
			arg[i] = c;
			i += c;
		}

		memset(M,0,sizeof(M));
		mp = cp = 0;

		while (cp < n) {
			if (C[cp]=='>') {
				mp=(mp+arg[cp])&0x7FFF; cp+=arg[cp];
			} else if (C[cp]=='<') {
				mp=(mp+0x8000-(arg[cp]&0x7FFF))&0x7FFF;
				cp+=arg[cp];
			} else if (C[cp]=='+') {
				M[mp]+=arg[cp]; cp+=arg[cp];
			} else if (C[cp]=='-') {
				M[mp]-=arg[cp]; cp+=arg[cp];
			} else if (C[cp]=='.') {
				putchar(M[mp]); cp++;
			} else if (C[cp]=='[') {
				cp = M[mp] ? (cp+1) : arg[cp];
			} else if (C[cp]==']') {
				cp = M[mp] ? arg[cp] : (cp+1);
			}
		}
		printf("\n");
	}

	return 0;
}
