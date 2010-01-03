#include <cstdio>
#include <cstring>
#include <cctype>

char line[110000];

int main() {
	int N;
	while (gets(line)) {
		if (sscanf(line, "%d", &N) != 1) continue;
		if (N <= 0) break;

		gets(line);

		int R = 0, D = 1;
		for (char *p = line; *p;) {
			if (*p != 'm' && *p != 'r') { p++; continue; }

			int op = *p++;

			while (*p && !isdigit(*p)) p++;
			if (*p == 0) break;

			int m = 0;
			while (*p && isdigit(*p)) m = m * 10 + *p++ - '0';

			if (op == 'r') {
				R += D * (m % N);
				if (R >= 0) R %= N;
				else R = (N - ((-R) % N)) % N;
			} else if ((m & 1) == 1) {
				D *= -1;
			}
		}

//printf("-----\nR=%d D=%d N=%d\n",R,D,N);

		if (R == 0) {
			printf(D==1 ? "\n" : "m1\n");
		} else {
			int ops1 = R + (D == 1 ? 0 : 1);
			char seq1[200];
			sprintf(seq1, D==1 ? "r%d\n" : "r%d m1\n", R);

			int ops2 = 1 + N-R + (D == -1 ? 0 : 1);
			char seq2[200];
			sprintf(seq2, D==-1 ? "m1 r%d\n" : "m1 r%d m1\n", N-R);

			printf("%s", ops1<=ops2 ? seq1 : seq2);
		}
	}
}
