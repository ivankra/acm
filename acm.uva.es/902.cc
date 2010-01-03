#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

char *p[1000100], s[1000100];
int m;

bool cmp(const char *a, const char *b) { return memcmp(a, b, m) < 0; }
bool eq(const char *a, const char *b) { return memcmp(a, b, m) == 0; }

int main()
{
	while (scanf("%d %s", &m, s) == 2) {
		int n = strlen(s) - m + 1;
		for (int i = 0; i < n; i++)
			p[i] = s+i;
		sort(p, p+n, cmp);

		char *ans = s;
		int most = 0;

		for (int i = 0; i < n;) {
			char *x = p[i];
			int k = 0;
			while (i < n && eq(x, p[i])) { i++; k++; }

			if (k > most) { most = k; ans = x; }

		}

		printf("%.*s\n", m, ans);
	}
}
