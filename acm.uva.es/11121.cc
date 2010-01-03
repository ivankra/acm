#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;


int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		int n, a[100], k = 0;
		scanf("%d", &n);

		while (k == 0 || n != 0) {
			if (n % 2 == 0) {
				a[k++] = 0;
				n /= -2;
			} else {
				a[k++] = 1;
				n = (n - 1) / (-2);
			}
		}

		printf("Case #%d: ", cs);
		while (k-- > 0) putchar(a[k]+'0');
		printf("\n");
	}
}
