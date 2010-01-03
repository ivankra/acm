#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

void chop(char *s) {
	int n = strlen(s);
	while (n > 0 && isspace(s[n-1])) s[--n] = 0;
}

long long num(const char *s, int w) {
	while (w > 0 && *s && isspace(*s)) s++, w--;

	int sign = 1;
	if (*s == '-') { s++; w--; sign = -1; }

	long long n = 0;
	while (w > 0 && *s && isdigit(*s)) {
		n = n * 10LL + *s++ - '0';
		w--;
	}

	return sign * n;
}

const char *pretty(long long x) {
	static char buf[16];
	long long a = x < 0 ? -x : x;
	sprintf(buf, "%s%lld.%.2d", x<0?"-":"", a/100, (int)(a%100));
	return buf;
}

int main() {
	static char line[1024], name[1001][64];

	memset(name, 0, sizeof(name));
	while (gets(line)) {
		chop(line);
		int n = num(line, 3);
		if (n == 0) break;
		strcpy(name[n], line+3);
	}

	int prev = 0;
	vector<long long> t1, t2;

	while (gets(line)) {
		chop(line);
		int tr = num(line, 3);

		if (tr != prev && prev != 0) {
			long long sum = 0;
			for (int i = 0; i < (int)t2.size(); i++)
				sum += t2[i];

			if (sum != 0) {
				printf("*** Transaction %d is out of balance ***\n", prev);
				for (int i = 0; i < (int)t2.size(); i++) {
					printf("%.3d %-31s %9s\n",
						(int)t1[i], name[t1[i]],
						pretty(t2[i]));
				}
				printf("999 %-31s %9s\n\n", "Out of Balance", pretty(-sum));
			}

			t1.clear();
			t2.clear();
		}

		if (tr == 0) break;

		prev = tr;
		t1.push_back(num(line+3, 3));
		t2.push_back(num(line+6, 999));
	}
}
