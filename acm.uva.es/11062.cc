#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

int main() {
	char buf[65536];
	set<string> out;
	string w = "";

	while (gets(buf)) {
		int n = strlen(buf);
		while (n > 0 && (buf[n-1]=='\n' || buf[n-1]=='\r'))
			buf[--n] = 0;

		for (int i = 0; ; i++) {
			if (isalpha(buf[i])) {
				w += (char)tolower(buf[i]);
				continue;
			}

			if (buf[i]=='-' && buf[i+1]==0) break;

			if (buf[i] == '-') { w += '-'; continue; }

			if (w.size() > 0) {
				out.insert(w);
				w = "";
			}

			if (buf[i] == 0) break;
		}
	}

	if (w.size() > 0) out.insert(w);

	for (set<string>::iterator it = out.begin(); it != out.end(); it++)
		printf("%s\n", it->c_str());
	return 0;
}
