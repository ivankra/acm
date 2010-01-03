#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>
#include <cstdlib>
#include <algorithm>
using namespace std;

int List[1000010], N, K;

int main() {
	char buf[50000];
	for (int cs = 1; gets(buf) && sscanf(buf, "%d", &K) == 1 && K > 0; 
cs++) {
		N = 0;

		gets(buf);

		char *p = buf;
		while (*p) {
			if (!isalpha(*p)) { p++; continue; }

			char s[100];
			int n, diff;
			sscanf(p, " %[A-Za-z] ( %d %n", s, &n, &diff);
			p += diff;

			s[0] = toupper(s[0]);

			if (s[0] == 'N') {
				for (int i = 0; i < n; i++) {
					sscanf(p, " , %d %n", &List[N], &diff);
					p += diff;
					N++;
				}
				sscanf(p, " ) %n", &diff);
				p += diff;
			} else if (s[0] == 'I') {
				int a, d;
				sscanf(p, " , %d , %d ) %n", &a, &d, &diff);
				p += diff;
				for (int i = 0; i < n; i++, a += d)
					List[N++] = a;
			} else {
				int l, h;
				unsigned s;
				sscanf(p, " , %d , %d , %u ) %n", &l, &h, &s, &diff);
				p += diff;

				for (int i = 0; i < n; i++) {
					s = s * 17 + 11;
					List[N++] = l + s % (h - l + 1);
				}
			}
		}
/*
printf("List=[");
for(int i = 0;i<N;i++)printf("%d ", List[i]);printf("]\n");
*/
		K--;
		nth_element(List, List+K, List+N);
		printf("Case %d: %d\n", cs, List[K]);
	}
}