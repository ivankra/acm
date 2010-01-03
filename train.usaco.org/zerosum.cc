/*
ID: infnty1
PROB: zerosum
LANG: C++
*/
#include <stdio.h>
#include <stdlib.h>

char s[1024];
int n;

void go(int k, int num, int sum, int p)
{
	if (k > n) {
		sum += num;
		if (sum == 0) { s[p]=0; printf("%s\n", s); }
		return;
	}

	s[p+1]=k+'0';
	s[p] = ' '; go(k+1, (num<0?-1:1) * (abs(num)*10+k), sum, p+2);
	s[p] = '+'; go(k+1, k, sum+num, p+2);
	s[p] = '-'; go(k+1, -k, sum+num, p+2);
}

int main()
{
	freopen("zerosum.in", "r", stdin);
	freopen("zerosum.out", "w", stdout);
	scanf("%d", &n);
	s[0]='1'; go(2, 1, 0, 1);
	return 0;
}
