#include <cstdio>
#include <cstring>

char s[20010];
int p[20010], T;

int main()
{
	for (scanf("%d", &T); T-- > 0 && scanf(" %s", s) == 1;) {
		int n = strlen(s);
		for (int i = 0; i < n; i++) s[n+i] = s[i];

		int best = 0, m = 0;
		p[0] = p[1] = 0;
		for (int i = 0; i < 2*n; i++) {
			while (m > 0 && s[best + p[m-1]] > s[i]) {
				m = p[m-1];
				best = i - m;
			}

			if (m <= 1) {
				best = i - m;
				m++;
			} else {
				int k;
				for (k = p[m-1]; k > 0 && s[best + k] != s[i];)
					k = p[k];
				p[m] = (s[best + k] == s[i]) ? k + 1 : 0;
				m++;
			}
		}

		printf("%d\n", best%n+1);
	}
}
