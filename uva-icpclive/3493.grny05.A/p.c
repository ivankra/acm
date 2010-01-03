#include <stdio.h>
#include <string.h>

int main()
{
	char s1[128], s2[128];
	int a[128], b[128], i, j, t, T;

	for (scanf("%d", &T), t = 1; t <= T && scanf(" %s %s", s1, s2) == 2; t++) {
		memset(a, 0, sizeof(a));
		for (j = 0, i = strlen(s1)-1; i >= 0; i--) a[j++]=s1[i]-'0';
		memset(b, 0, sizeof(b));
		for (j = 0, i = strlen(s2)-1; i >= 0; i--) b[j++]=s2[i]-'0';

		for (i = j = 0; i < 128; i++, j >>= 1)
			a[i] = (j += a[i] + b[i]) & 1;

		printf("%d ",t);
		for (i = 127; i > 0 && a[i]==0; i--);

		while (i >= 0) printf("%d", a[i--]);
		printf("\n");
	}

	return 0;
}
