#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

int a[128], b[128], n;

void sqr() {
	memset(b, 0, sizeof(b));
	for (int i = 0; i < n; i++)
		for (int j = 0, k = i, c = 0; k < n; j++, k++, c /= 10)
			b[k] = (c += b[k] + a[i] * a[j]) % 10;
	memcpy(a, b, sizeof(b));
}

int main()
{
	scanf("%d", &n);
	if (n <= 1) { printf("0\n1\n5\n6\n"); return 0; }

	memset(a, 0, sizeof(a));
	a[0] = 5;
	for (int i = 0; i < n; i++) sqr();

	string s, t;
	for (int i = 0; i < n; i++) {
		s += (char)(a[n-1-i] + '0');
		t += (char)('9' - a[n-1-i] + (n-1-i == 0 ? 2 : 0));
	}
	if (s > t) swap(s, t);

	if (s[0] != '0') printf("%s\n", s.c_str());
	if (t[0] != '0') printf("%s\n", t.c_str());
}
