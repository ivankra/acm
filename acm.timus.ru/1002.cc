#include <cstdio>
#include <cstring>

char *enc[]={"oqz","ij","abc","def","gh","kl","mn","prs","tuv","wxy"};
char dec[256];

char text[128], dict[50010][51];
int len[50010], f[128], fw[128], N, L;

int main() {
	for (int d = 0; d <= 9; d++)
		for (char *s = enc[d]; *s; s++)
			dec[(int)(*s)] = d+'0';
	dec[0] = '*';

	while (scanf(" %[0-9] %d", text, &N) == 2) {
		for (int i = 0; i < N; i++) {
			scanf(" %s", dict[i]);
			len[i] = strlen(dict[i]);
		}

		L = strlen(text);
		f[L] = 0;

		for (int i = L-1; i >= 0; i--) {
			f[i] = 1<<30;
			fw[i] = -1;
			for (int j = 0; j < N; j++) {
				if (i+len[j] > L) continue;

				char *s = dict[j], *t = text+i;
				while (dec[*s] == *t) s++, t++;

				if (*s == 0 && 1+f[i+len[j]] < f[i]) {
					f[i] = 1 + f[i+len[j]];
					fw[i] = j;
				}
			}
		}

		if (f[0] > L) {
			printf("No solution.\n");
		} else {
			for (int i = 0; i < L;) {
				printf(i?" %s":"%s", dict[fw[i]]);
				i += len[fw[i]];
			}
			printf("\n");
		}
	}
}
