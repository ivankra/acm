#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
using namespace std;

int main()
{
	char line[1024];
	int N;

	gets(line);
	sscanf(line, "%d", &N);

	for (int i = 0; i < N; i++) {
		vector<string> words;

		assert(gets(line) != NULL);

		int i = 0;
		while (line[i] && line[i] != '\"') i++;
		if  (line[i] == '\"') i++; else continue;

		string s = "";
		for (; line[i] && line[i] != '\"'; i++) {
			if (isalpha(line[i])) {
				if (s != "" && s[0] == '-') {
					words.push_back(s);
					s = "";
				}
				s += line[i];
			} else if (line[i] == '-') {
				if (s != "" && isalpha(s[0])) {
					words.push_back(s);
					s = "";
				}
				s += '-';
			} else if (s != "" && isalpha(s[0])) {
				words.push_back(s);
				s = "";
			}
		}

		if (s != "") words.push_back(s);

		string out = "";

		for (int i = 0; i < (int)words.size();) {
			s = words[i];

			if (s == "-") {
				if (out == "" || i+1 >= (int)words.size()) goto err;
				if (!isalpha(out[out.size()-1])) goto err;
				out += "-";
				out += words[i+1];
				i += 2;
			} else if (s[0] == '-') {
				int n = s.size();
				if ((n % 2) == 0) {
					for (int j = 0; j < n; j += 2) out += " --";
				} else {
					out += " ---";
					for (int j = 3; j < n; j += 2) out += " --";
				}
				out += " ";
				i++;
			} else {
				if (out != "" && isalpha(out[out.size()-1])) out += " ";
				out += s;
				i++;
			}
		}

		printf("\"%s\"\n", out.c_str());
		continue;
err:
		printf("error\n");
		continue;
	}
}
