#include <cstdio>
#include <cstring>

char A[20], B[20], C[20];
int lead[256], enc[256], used[10], cnt;

void doit(int m, int carry) {
	if (m == 0) {
		if (carry == 0) cnt++;
		return;
	}

	for (int i = 0; i < 3; i++) {
		char *s = (i==0 ? A : (i==1 ? B : C));
		if (enc[s[m]] != -1) continue;
		
		int &z = enc[s[m]];
		for (z = lead[s[m]]; z <= 9; z++) {
			if (used[z]) continue;
			used[z] = 1;
			doit(m, carry);
			used[z] = 0;
		}
		z = -1;
		return;
	}

	int t = enc[A[m]] + enc[B[m]] + carry;
	if (t % 10 == enc[C[m]]) doit(m-1, t/10);
}

int rom(char *s) {
	static int val[256]={-1};
	if (val[0] < 0) {
		int a[] = {1, 5, 10, 50, 100, 500, 1000 };
		for (int i = 0; i < 256; i++) val[i] = 0;
		for (int i = 0; i < 7; i++) val["IVXLCDM"[i]] = a[i];
	}

	int res = 0;
	for (; *s; s++) {
		res += val[*s];
		for (char *t = s+1; *t; t++) {
			if (val[*t] > val[*s]) {
				res -= 2*val[*s];
				break;
			}
		}
	}
	return res;
}

int main() {
	char a[20], b[20], c[20];
	while (scanf(" %[A-Z] + %[A-Z] = %[A-Z]", a, b, c) == 3) {
		printf("%s ", rom(a)+rom(b)==rom(c) ? "Correct" : "Incorrect");

		int m = strlen(c);
		if (m < strlen(a) || m < strlen(b)) {
			printf("impossible\n");
			continue;
		}

		sprintf(A, " %*s", m, a);
		sprintf(B, " %*s", m, b);
		sprintf(C, " %*s", m, c);

		memset(enc, 0xff, sizeof(enc));
		enc[' '] = 0;
		memset(lead, 0, sizeof(lead));
		lead[a[0]] = lead[b[0]] = lead[c[0]] = 1;
		memset(used, 0, sizeof(used));

		cnt = 0;
		doit(m, 0);

		if (cnt == 0)
			printf("impossible\n");
		else if (cnt == 1)
			printf("valid\n");
		else
			printf("ambiguous\n");
	}
}
