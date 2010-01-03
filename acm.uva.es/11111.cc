#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>

int n, m, a[1048576], sz[1048576], in[1048576];
char buf[18*1048576];

int main() {
	while (gets(buf)) {
		n = 0;

		for (char *p = buf; *p;) {
			if (*p != '-' && !isdigit(*p)) { p++; continue; }

			int sign = 1;
			if (*p == '-') { p++; sign = -1; }

			a[n] = 0;
			while (*p && isdigit(*p)) a[n] = a[n] * 10 + *p++ - '0';
			a[n] *= sign;
			n++;
		}

		if (n < 2 || a[0] != -a[n-1] || a[0] >= 0)
			goto no;

		sz[0] = -a[0];
		in[0] = 0;
		m = 1;

		for (int i = 1; i < n; i++) {
			if (m == 0) goto no;
			if (a[i] == 0) goto no;

			if (a[i] > 0) {
				if (sz[m-1] != a[i]) goto no;
				if (in[m-1] >= sz[m-1]) goto no;
				m--;
				if (m == 0) {
					if (i == n-1)
						break;
					else
						goto no;
				}
				if ((in[m-1] += sz[m]) >= sz[m-1]) goto no;
			} else {
				sz[m] = -a[i];
				if (sz[m] >= sz[m-1]) goto no;
				in[m] = 0;
				m++;
			}
		}

		printf(":-) Matrioshka!\n");
		continue;

no:		printf(":-( Try again.\n");
	}
}
