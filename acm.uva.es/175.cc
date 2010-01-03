#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

struct Profile {
	int d;
	vector<string> w;
	vector<int> out;
};

vector<Profile> prof;

int main()
{
	char s[4096];
	int ntit = 0;

	while (scanf(" %[A-Z] :", s) == 1 && (s[0] == 'P' || s[0] == 'T')) {
		int c;
		if (s[0] == 'P') {
			Profile p;
			scanf("%d", &p.d);
			while ((c = getchar()) != EOF && c != '\n') {
				if (isspace(c)) continue;
				ungetc(c, stdin);
				scanf(" %s", s);
				p.w.push_back(string(s));
			}
			p.out.clear();
			prof.push_back(p);
		} else {
			vector<string> words;
			string w = "";

			ntit++;

			do {
				c = getchar();
				if (c != EOF && c != '|' && !isspace(c) && !isalpha(c))
					continue;

				if (c != EOF && isalpha(c)) {
					w += tolower(c);
				} else if (w.size() > 0) {
					words.push_back(w);
					w = "";
				}
			} while (c != EOF && c != '|');

			for (int p = 0; p < (int)prof.size(); p++) {
				for (int k = 0; k < (int)prof[p].w.size(); k++)
				for (int m = 0; m < (int)prof[p].w.size(); m++) if (k!=m)
				for (int i = 0; i < (int)words.size(); i++)
				for (int j = i+1; j < (int)words.size(); j++) {
					if (j-i-1 > prof[p].d)
						break;
					if (words[i] == prof[p].w[k] &&
					    words[j] == prof[p].w[m]) {
						prof[p].out.push_back(ntit);
						goto done;
					}
				}
done:;
			}
		}
	}

	for (int i = 0; i < (int)prof.size(); i++) {
		printf("%d: ", i+1);
		for (int j = 0; j < (int)prof[i].out.size(); j++)
			printf(j?",%d":"%d", prof[i].out[j]);
		printf("\n");

	}
}
