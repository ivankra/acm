#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>
using namespace std;

char line[100000];

int main()
{
	gets(line);
	while (line[0] != '0') {
		if (!isupper(line[0])) { gets(line); continue; }

		map<string, string> stud;
		map<string, int> res;

		while (line[0] != '1') {
			string project = line;
			if (res.count(project) == 0)
				res[project] = 0;
			while (gets(line) && islower(line[0])) {
				string s = line;
				if (stud.count(s) > 0) {
					if (stud[s] != "" && stud[s] != project) {
						res[stud[s]]--;
						stud[s] = "";
					}
				} else {
					stud[s] = project;
					res[project]++;
				}
			}
		}
		gets(line);

		typedef pair<int, string> P;
		vector<P> v;
		for (map<string, int>::iterator it = res.begin(); it != res.end(); ++it)
			v.push_back(P(-it->second, it->first));
		sort(v.begin(), v.end());

		for (int i = 0; i < (int)v.size(); i++)
			cout << v[i].second << " " << -v[i].first << "\n";
	}
}
