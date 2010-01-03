#include <stdio.h>
#include <string.h>

int phi[2000002];

int main()
{
	memset(phi, 0, sizeof(phi));
	for (int i = 2; i <= 1415; i++) {
		if (phi[i] != 0) continue;
		for (int j = i*i; j <= 2000000; j += i)
			phi[j] = i;
	}

	phi[0] = 0;
	phi[1] = 1;
	for (int i = 2; i <= 2000000; i++) {
		if (phi[i] == 0) { phi[i] = i-1; continue; }

		int d = phi[i], f1 = i, f2 = 1;
		while ((f1 % d) == 0) { f1 /= d; f2 *= d; }

		if (f1 > 1)
			phi[i] = phi[f1] * phi[f2];
		else
			phi[i] = (i / d) * (d - 1);	
	}

	phi[0] = phi[1] = 0;
	for (int i = 2; i <= 2000000; i++)
		phi[i] = 1 + phi[phi[i]];

	phi[0] = 0;
	for (int i = 1; i <= 2000000; i++)
		phi[i] += phi[i-1];

	int T, a, b;
	for (scanf("%d", &T); T-- > 0 && scanf("%d %d", &a, &b) == 2;)
		printf("%d\n", phi[b]-phi[a-1]);

	return 0;
}
