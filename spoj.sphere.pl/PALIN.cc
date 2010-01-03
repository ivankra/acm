#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char s[1048576], z[1048576];
int n;

int odd()
{
	int i, m=(n-1)/2, c=s[m];
	char *a=s, *b=s+m+1;

	for (i = 0; i < m && a[m-1-i] == b[i]; i++);
	if (i < m && a[m-1-i] > b[i]) {
		for (i = 0; i < m; i++)
			b[i] = a[m-1-i];
		return printf("%s\n", s);
	}

	if (c != '9') {
		s[m]++;
		for (i = 0; i < m; i++)
			b[i] = a[m-1-i];
		return printf("%s\n", s);
	}

	for (i = m-1; i >= 0; i--)
		if (a[i]++ == '9') a[i] = '0'; else break;

	if (i >= 0) {
		s[m] = '0';
		for (i = 0; i < m; i++)
			b[i] = a[m-1-i];
		return printf("%s\n", s);
	}

	return printf("1%.*s1\n", n-1, z);
}

int even()
{
	int i, m=n/2;
	char *a=s, *b=s+m;

	for (i = 0; i < m && a[m-1-i] == b[i]; i++);
	if (i < m && a[m-1-i] > b[i]) {
		for (i = 0; i < m; i++)
			b[i] = a[m-1-i];
		return printf("%s\n", s);
	}

	for (i = m-1; i >= 0; i--)
		if (a[i]++ == '9') a[i] = '0'; else break;

	if (i >= 0) {
		for (i = 0; i < m; i++)
			b[i] = a[m-1-i];
		return printf("%s\n", s);
	}

	return printf("1%.*s1\n", n-1, z);
}

int main()
{
	int T;

	memset(z, '0', sizeof(z));

	for (scanf("%d", &T); T-- > 0;) {
		int i = scanf(" %[0-9]", s);
		assert(i == 1 && s[0] != '0');

		n = strlen(s);
		if (n == 1)
			printf("%d\n", atoi(s) < 9 ? (atoi(s) + 1) : 11);
		else if (n & 1)
			odd();
		else
			even();
	}

	return 0;
}
