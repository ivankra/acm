#include <cstdio>

int v[65536], n=0, r, p;
char buf[256];

int main()
{
	while (gets(buf)) {
		if (sscanf(buf, "%d %d", &p, &r) < 1) {
			if (n != 0) printf("%d\n", n-1);
			n = 0;
		} else if (p == 0) {
			v[n++] = 1;
		} else {
			while (p > 0 && n > 0) {
				p -= v[--n];
				r += v[n];
			}
			v[n++] = r;
		}
	}
	if (n > 0) printf("%d\n", n-1);
}
