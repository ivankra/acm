#include <cstdio>
#include <cassert>
#include <string>
#include <map>
#include <vector>
using namespace std;

struct trans {
	string out, to;
};

struct state {
	int tab[257], m;
	string nm;
	vector<trans> tr;
};

int n;
map<string, int> nm2st;
vector<state> S;

void do_out(const char *p, int c)
{
	while (*p) {
		if (*p == '\\') {
			if (p[1] == 'b') { putchar(' '); p += 2; }
			else if (p[1] == 'n') { putchar('\n'); p += 2; }
			else if (p[1] == '\\') { putchar('\\'); p += 2; }
			else if (p[1] == 'c') { putchar(c); p += 2; }
			else if (p[1] == '0') return;
			else { putchar(*p); p++; }
		} else {
			putchar(*p); p++;
		}
	}
}

void parse_in(char *p, int s, int t)
{
	int c;
	while (*p) {
		if (*p == '\\') {
			if (p[1] == 'b') { c = ' '; p += 2; }
			else if (p[1] == 'n') { c = '\n'; p += 2; }
			else if (p[1] == '\\') { c = '\\'; p += 2; }
			else if (p[1] == 'c') { c = 256; p += 2; }
			else { c = *p++; }
		} else {
			c = *p++;
		}
		S[s].tab[c] = t;
	}
}

void run()
{
	assert(nm2st.count("START") > 0);
	for (int s = nm2st["START"]; s >= 0;) {
		int c = getchar();
		assert(c != EOF);

		int t = (S[s].tab[c] >= 0) ? S[s].tab[c] : S[s].tab[256];
		assert(t >= 0);

		do_out(S[s].tr[t].out.c_str(), c);

		s = nm2st[S[s].tr[t].to];
	}
}

int main()
{
	static char buf[131072];

	for (int cs = 1; scanf("%d", &n) == 1 && n > 0; cs++) {
		nm2st.clear(); S.clear(); S.resize(n);
		nm2st["END"] = -1;
		for (int i = 0; i < n; i++) {
			scanf(" %s %d", buf, &S[i].m);
			S[i].nm = string(buf);
			nm2st[S[i].nm] = i;

			S[i].tr.clear();
			S[i].tr.resize(S[i].m);

			for (int j = 0; j < 257; j++)
				S[i].tab[j] = -1;

			for (int j = 0; j < S[i].m; j++) {
				scanf(" %s", buf);
				parse_in(buf, i, j);

				scanf(" %s", buf);
				S[i].tr[j].to = string(buf);

				scanf(" %s", buf);
				S[i].tr[j].out = string(buf);
			}
		}

		int c;
		while ((c = getchar()) != EOF && c != '\n');

		printf("Finite State Machine %d:\n", cs);
		run();
	}

	return 0;
}
