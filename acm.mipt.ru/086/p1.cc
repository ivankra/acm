#include <cstdio>
#include <cstring>

int main() {
	char s[999], t[999];
	scanf(" %s", s);

	int a[999], i, j;
	memset(a, 0, sizeof(a));
	a[0] = 1;

	for (int n = 1;; n++) {
		for (i = j = 0; i < 260; i++, j /= 10)

			a[i] = (j += a[i] * n) % 10;
		for (i = 260; !a[i]; i--);
		for (j = 0; i >= 0;) t[j++] = a[i--] + '0'; t[j]=0;
		if (strcmp(s, t) == 0) { printf("%d\n", n); break; }
	}
}
