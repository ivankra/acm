#include <cstdio>
#include <cstring>

int main() {
	unsigned long long w[256], C, next, tmp;
	int n;
	char buf[1024], s[256];

	while (gets(buf)) {
		printf("%s\n", buf);
		n = 0;
		for (int i = 0, k = 0;; i++) {
			if (buf[i] && ('a' <= buf[i] && buf[i] <= 'z')) {
				s[k++] = buf[i];
			} else if (k > 0) {
				w[n] = 0;
				for (int j = 0; j < k; j++)
					w[n] = w[n] * 32 + s[j] - 'a' + 1;
				n++;
				k = 0;
			}
			if (buf[i] == 0) break;
		}

		next = 1;
		do {
			C = next;
			for (int i = 0; i < n; i++)
			for (int j = i+1; j < n; j++) {
				if ((C/w[i])%n == (C/w[j])%n) {
					tmp = ((C/w[i])+1)*w[i];
					tmp <?= ((C/w[j])+1)*w[j];
					next >?= tmp;
					next >?= C+1;
				}
			}
		} while (next > C);

		printf("%llu\n\n", C);
	}	
}
