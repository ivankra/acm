#include <cstdio>
#include <cstring>

int main() {
	char s[1024];
	scanf(" %s", s);

	int n = strlen(s);
	if (n % 2 != 0) { printf("NO\n"); return 0; }

	int r = 0, o = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == '(') {
			o++;
		} else if (o > 0) {
			o--;
		} else {
			r++; o++;
		}
	}
	printf("%d\n", r+o/2);
}
