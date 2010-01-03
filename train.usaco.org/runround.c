/*
ID: infnty1
PROB: runround
LANG: C
*/
#include <stdio.h>

int a[16], b[16], u[16], n, m, R=0x7FFFFFFF;

void go(int k)
{
	if (k < n) {
		for (a[k] = 1; a[k] <= 9; a[k]++)
			if (u[a[k]] == 0) { u[a[k]]++; go(k+1); u[a[k]]=0; }
	} else {
		int i;
		for (i = 0; i < 10; i++) b[i] = 0;
		for (i = k = 0; b[i] == 0; k++,i=(i+a[i])%n) b[i]=1;
		if (i!=0||k!=n) return;
		for (i = k = 0; i < n; i++) k = k * 10 + a[i];
		if (m < k && k < R) R = k;
	}
}

int main()
{
	freopen("runround.in", "r", stdin);
	freopen("runround.out", "w", stdout);
	scanf("%d", &m);
	for (n = 1; n <= 9; n++) go(0);
	printf("%d\n", R);
	return 0;
}
