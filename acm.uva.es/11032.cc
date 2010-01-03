#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int sod(int n) {
       int r = 0;
       while (n > 0) { r += n % 10; n /= 10; }
       return r;
}

int f(int a) {
	int i;
	for (i = max(1, a-80); i <= a; i++)
		if (i + sod(i) == a) return i;
	return -1;
}

char arr[10000000/8+100];
int tab[100100];

#define SET(a,k) (a)[(k)>>3] |= 1U << ((k) & 7)
#define GET(a,k) ((((a)[(k)>>3]) >> ((k) & 7)) & 1)

int g(int n) {
	int res = tab[n/128];
	for (int i = (n/128)*128; i <= n; i++)
		res += 1 - GET(arr, i);
	return res;
}

int main() {
	char buf[1024];
	int T, n, m;

	memset(arr, 0, sizeof(arr));
	for (int i = 0; i <= 10000000;) {
		int k = i + sod(i);
		for (int j = 0; j < 10; j++, i++, k+=2)
			SET(arr, k);
	}

	tab[0] = 0;
	for (int i = 0, j = 1; i <= 10000000; i += 128, j++) {
		tab[j] = tab[j-1];
		for (int k = 0; k < 128; k++)
			tab[j] += 1 - GET(arr, i+k);
	}

	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		printf("Case %d: ", cs);
		while (gets(buf) && sscanf(buf, "%d", &n) != 1);
		if (sscanf(buf, "%d %d", &n, &m) == 2)
			printf("%d\n", n<=m ? g(m)-g(n-1) : 0);
		else
			printf("%d\n", f(n));
	}
}
