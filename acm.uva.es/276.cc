// P.E.
#include <cstdio>
#include <cstring>

int read(long long &n) {
	char s[1024];
	if (gets(s) == NULL) return 0;

	n = 0;
	for (int i = 0; s[i]; i++)
		for (int j = 0, k = 1; j < 5; j++, k *= 10)
			if (s[i] == "|n98r"[j]) n += k;
	n %= 100000;
	return 1;
}

char *print(long long n) {
	static char s[256], out[256];
	n %= 100000;
	sprintf(s, "%lld", n);

	int k = 0;
	for (int i = strlen(s)-1, j = 0; j < 5 && i >= 0; i--, j++) {
		if (s[i] != '0' && k > 0) out[k++] = ' ';
		while (s[i]-- > '0') out[k++] = "|n98r"[j];
	}
	out[k] = 0;
	return out;
}

int main() {
	long long n, m;
	while (read(n) && read(m)) {
		for (int i = 0; (1LL << i) <= m; i++) {
			char buf[256];
			sprintf(buf, "%s%s", print(1LL<<i), (m&(1LL<<i)) ? " *" : "");
			printf("%-34s%s\n", buf, print(n * ((1LL<<i) % 100000)));
		}
		printf("The solution is: %s\n", print(n*m));
	}
}
