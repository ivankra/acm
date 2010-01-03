#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cmath>
	#include <cctype>
#include <cassert>
using namespace std;

string add(string a, int mul, string b) {
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	string res = "";

	int c = 0;
	for (int i = 0; c != 0 || i < (int)a.size() || i < (int)b.size(); i++) {
		c += (i < (int)a.size() ? a[i]-'0' : 0) +
			mul * (i < (int)b.size() ? b[i]-'0' : 0);

		int c1 = ((c%10)+10)%10;
		res += c1+'0';

		c = (c - c1) / 10;
	}

	while (res.size() > 0 && res[res.size()-1] == '0')
		res.resize(res.size()-1);
	reverse(res.begin(), res.end());

	return res.size() == 0 ? "0" : res;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		char num1[1024], num2[1024], op;
		scanf(" %[0-9] %c %[0-9]", num1, &op, num2);

		vector<string> out;

		out.push_back(num1);
		out.push_back(string(1, op) + string(num2));
		out.push_back("-");

		if (op == '+' || op == '-') {
			out.push_back(add(num1, op=='+' ? +1 : -1, num2));
		} else {
			assert(op == '*');

			int m = strlen(num2);
			string res = "0";

			for (int i = m-1, j = 0; i >= 0; i--, j++) {
				string s = add("0", num2[i]-'0', num1);
				out.push_back(s + string(j, ' '));
				res = add(res, +1, s + string(j, '0'));
			}

			if (m > 1) {
				out.push_back("-");
				out.push_back(res);
			}
		}

		int width = 0;
		for (int i = 0; i < (int)out.size(); i++)
			width = max(width, (int)out[i].size());

		for (int i = 0; i < (int)out.size(); i++) {
			if (out[i] == "-") continue;
			out[i] = string(width - out[i].size(), ' ') + out[i];
		}

		for (int i = 0; i < (int)out.size(); i++) {
			if (out[i] == "-") {
				out[i] = "";
				for (int j = 0; j < width; j++)
					out[i] += (out[i-1][j] != ' ' || out[i+1][j] != ' ') ? '-' : ' ';
			}
		}

		for (int i = 0; i < (int)out.size(); i++) {
			while (out[i].size() > 0 && out[i][out[i].size()-1] == ' ')
				out[i].resize(out[i].size()-1);
			printf("%s\n", out[i].c_str());

		}

		printf("\n");
	}
}
