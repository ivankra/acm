#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int main()
{
	vector<string> out;

	for (int no = 1;; no++) {
		char rec[5][128];
		sprintf(rec[0], "%d", no);

		for (int i = 1; i <= 4; i++) {
			if (scanf(" %s", rec[i]) != 1) goto done;
		}

		char buf[1024];
		sprintf(buf, "%-3s%-25s%-25s%-2s%-3s", rec[0], rec[2], rec[1], rec[4], rec[3]);
		for (int i = 0; buf[i]; i++)
			if (buf[i] == ' ') buf[i] = '_';
		out.push_back(buf);
	}
done:
	for (int i = out.size()-1; i >= 0; i--)
		printf("%s\n", out[i].c_str());
}
