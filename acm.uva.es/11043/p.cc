#include <cstdio>
#include <cstring>

int P[256][256], in[8], n=0, A=0, B=0;

void doit() {
	int out[8]={64}, m=1;
	for (int i = 0; i < n; i++) {
		if (P[A][B] == in[i])
			out[0] += 1 << i;
		else
			out[m++] = P[A][B] = in[i];
		B = A;
		A = in[i];
	}
	for (int i = 0; i < m; i++)
		putchar(out[i]);
}

int main() {
	memset(P, 0xff, sizeof(P));
	for (;;) {
		if (n < 6 && ((in[n] = getchar()) != EOF)) { n++; continue; }
		if (n == 0) break;
		doit();
		n = 0;
	}
}
