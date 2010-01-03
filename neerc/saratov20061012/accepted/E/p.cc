#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

char text[1<<20];
int cnt[256], N;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	gets(text);
	sscanf(text, "%d", &N);

	while (N-- > 0) {
		gets(text);

		vector<string> vs;

		for (int i = 0; text[i];) {
			if (text[i] != '-' && !isalpha(text[i])) { i++; continue; }

			if (text[i] == '-') {
				string s = "";
				for (; text[i] && !isalpha(text[i]); i++)
					if (text[i] == '-') s += '-';
				vs.push_back(s);
				continue;
			}

			if (isalpha(text[i])) {
				string s = "";
				for (; text[i] && isalpha(text[i]); i++)
					s += text[i];
				vs.push_back(s);
			}
		}

		string out = "";
		for (int i = 0; i < (int)vs.size();) {
			if (vs[i] == "-") {
				if (out.size() == 0 || !isalpha(out[out.size()-1])) goto fail;
				if (i+1 >= vs.size() || vs[i+1].size() == 0 || vs[i+1][0] == '-') goto fail;
				out += '-';
				i++;
				continue;
			}

			if (isalpha(vs[i][0])) {
				if (out.size() > 0 && isalpha(out[out.size()-1]))
					out += ' ';
				out += vs[i];
				i++;
				continue;
			}

			int m = vs[i].size();

			if ((m % 2) == 0) {
				for (int i = 0; i < m; i += 2)
					out += " --";
				out += " ";
			} else {
				out += " ---";
				for (int i = 3; i < m; i += 2)
					out += " --";
				out += " ";
			}

			i++;
		}

		printf("\"%s\"\n", out.c_str());
		continue;

fail:
		printf("error\n");
		continue;
	}

	return 0;
}