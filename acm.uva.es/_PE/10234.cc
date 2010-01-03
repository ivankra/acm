#include <cstdio>
#include <cctype>
#include <cassert>
#include <algorithm>
using namespace std;

char data[2048], buf[2048];
int T, N, ans[2048], ans_f[2048], pos[2048], suf[2048], xsuf[2048], xlcp[2048];

bool xcmp(int s, int t) {
	if (s == t) return false;
	while (tolower(data[s]) == tolower(data[t])) s++, t++;
	return tolower(data[s]) < tolower(data[t]);
}

bool cmp(int s, int t) { return s != t && strcmp(data+s, data+t) < 0; }

int main() {
	while (gets(data)) {
		if (gets(buf)==NULL || sscanf(buf, "%d", &T) != 1) break;

		N = strlen(data);
		while (N > 0 && (data[N-1] == '\r' || data[N-1] == '\n'))
			data[--N] = 0;

		for (int i = 0; i <= N; i++) xsuf[i] = suf[i] = i;
		sort(xsuf, xsuf+N, xcmp);
		sort(suf, suf+N, cmp);

		for (int i = 0; i < N; i++) pos[suf[i]] = i;
		pos[N] = N;

		for (int i = 0; i < N-1; i++)
			for (xlcp[i] = 0;; xlcp[i]++)
				if (tolower(data[xsuf[i]+xlcp[i]]) !=
				    tolower(data[xsuf[i+1]+xlcp[i]]))
					break;
		xlcp[N-1] = xlcp[N] = 0;

		for (int m = 1; m <= N; m++) {
			ans_f[m] = 0;
			ans[m] = 0;
			for (int s = 0, t; s < N; s = t) {
				if (N-xsuf[s] < m) { t = s+1; continue; }

				int mi = pos[xsuf[s]], q = s;
				for (t = s+1; xlcp[t-1] >= m; t++) {
					if (pos[xsuf[t]] < mi) {
						mi = pos[xsuf[t]];
						q = t;
					}
				}

				if (t-s > ans_f[m] ||
				    (t-s == ans_f[m] && mi < pos[ans[m]])) {
					ans_f[m] = t - s;
					ans[m] = xsuf[q];
				}
			}
		}

		int m;
		while (T-- > 0 && gets(buf) && sscanf(buf, "%d", &m) == 1) {
			assert(1 <= m && m <= N);
			printf("%d %.*s\n", ans_f[m], m, data+ans[m]);
		}
	}
}
