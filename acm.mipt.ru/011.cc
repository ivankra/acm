#include <cstdio>

char s[100010];
int main() {
	int n=0, c;
	while ((c=getchar())!=EOF) {
		for (int i = 0; i < 4; i++) {
			if (c == "([{<"[i]) {
				s[n++] = ")]}>"[i];
				break;
			} else if (c == ")]}>"[i]) {
				if (n == 0 || s[--n] != c) { n=1; goto stop; }
			}
		}
	}
stop:
	printf(n ? "NO\n" : "YES\n");
}
