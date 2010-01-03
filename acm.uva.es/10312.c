#include <stdio.h>

char *s[] = {
	"0", "0", "0", "1", "6", "31", "155", "771", "3850", "19363", "98187",
	"502063", "2587937", "13440857", "70296473", "370019079", "1959106674",
	"10428220683", "55779368219", "299681788263", "1616594895397",
	"8752745540025", "47550361333961", "259124455145823",
	"1416118615851221", "7759443920290221", "42620109348084205"
};

int main()
{
	int n;

	while (scanf("%d", &n) == 1)
		printf("%s\n", s[n]);

	return 0;
}
/*
#include <stdio.h>

long long tab[1024];

long long f(long long n)
{
	long long a[32], i, j, k, r;

	if (n < 0) return 0;
	if (n <= 1) return 1;
	if (tab[n] >= 0) return tab[n];

	for (a[k = 0] = 0, r = 0; k >= 0;) {
		a[k]++;
		n--;

		if (n != 0) {
			a[++k] = 0;
			continue;
		}

		if (k >= 1) {
			for (j = 1, i = 0; i <= k; i++)
				j *= f(a[i]);
			r += j;
		}

		n += a[k--];
	}

	return (tab[n] = r);
}

int main()
{
	static long long b[1024], r[1024], n;
	long long i, j, k;

	for (b[0] = b[1] = b[2] = 1, k = 3; k <= 26; k++)
		for (b[k] = 0, i = 1; i < k; i++)
			b[k] += b[i] * b[k - i];

	for (k = 0; k <= 26; k++)
		tab[k] = -1;

for(k=0;k<=26;k++){printf("\"%lld\", ", f(k)-b[k]);fflush(stdout);}
return 0;

	while (scanf("%lld", &n) == 1)
		printf("%lld\n", f(n)-b[n]);

	return 0;
}
*/