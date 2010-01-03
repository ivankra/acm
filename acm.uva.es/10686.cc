#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

struct Cat { string s; int p; vector<int> w; };

int main()
{
	static char buf[65536];
	int nw, m, C, T;
	vector<Cat> cat;
	map<string, int> W;

	for (scanf("%d", &T); T-- > 0 && scanf("%d", &C) == 1;) {
		W.clear(); cat.clear(); cat.resize(C); nw = 0;
		for (int i = 0; i < C; i++) {
			scanf(" %s %d %d", buf, &m, &cat[i].p);
			cat[i].s = string(buf);
			while (m-- && scanf(" %s", buf) == 1) {
				if (W.count(buf) == 0) W[buf] = nw++;
				cat[i].w.push_back(W[buf]);
			}
			sort(cat[i].w.begin(), cat[i].w.end());
			cat[i].w.erase(unique(cat[i].w.begin(), cat[i].w.end()), cat[i].w.end());
		}

		while ((m = getchar()) != EOF && m != '\n');

		vector<int> seen(nw, 0);

		while (gets(buf) && buf[0] && buf[0]!='\r' && buf[0]!='\n') {
			m = 0;
			strcat(buf, " ");
			for (char *p = buf; *p; p++) {
				if (isalpha(*p)) { m++; continue; }
				if (m > 0) {
					*p = '\0';
					string s = string(p-m);
					if (W.count(s) > 0) seen[W[s]] = 1;
					m = 0;
				}
			}
		}

		m = 0;
		for (int i = 0; i < C; i++) {
			for (; !cat[i].w.empty(); cat[i].w.pop_back())
				if (seen[cat[i].w.back()]) cat[i].p--;
			if (cat[i].p <= 0)
				printf(m++ ? ",%s" : "%s", cat[i].s.c_str());
		}
		printf(m ? "\n" : "SQF Problem.\n");
	}

	return 0;
}

