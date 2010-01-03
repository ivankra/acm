#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

char *kmp_strstr(const char *s, const char *t) {
	if (*t == '\0') return (char *)s;
	if (*s == '\0') return NULL;

	int m = strlen(t), *f = (int *)malloc((m+1)*sizeof(int));
	for (int i = 1, j = f[0] = f[1] = 0; i < m; i++) {
		while (j > 0 && t[i] != t[j]) j = f[j];
		f[i+1] = j = (t[i] == t[j] ? j+1 : 0);
	}

	for (int i = 0;;) {
		if (*s == t[i]) {
			if (++i == m) { free(f); return (char *)(s-m+1); }
			if (*++s == '\0') break;
		} else if (i == 0) {
			if (*++s == '\0') break;
		} else {
			i = f[i];
		}
	}

	free(f);
	return NULL;
}


#include <ctime>
int main()
{
	srand(time(NULL));
	for (int i = 0; i < 1000000; i++) {
		if ((i % 1000) == 0) printf("[%d]\n",i);

		static char s[256], t[256];
		int n = (rand() % 20), m =  (rand() % 20);
		if (n < m) swap(n,m);

		for (int i = 0; i < n; i++) s[i] = 'a' + (rand() & 1); s[n]=0;
		for (int i = 0; i < m; i++) t[i] = 'a' + (rand() & 1); t[m]=0;

		if (strstr(s,t) != kmp_strstr(s,t)) {
			printf("s=%s\nt=%s\n", s, t);
			char *r1=strstr(s,t), *r2=kmp_strstr(s,t);
			printf("strstr: %s\n", r1 ? r1 : "(null)");
			printf("KMP:    %s\n", r2 ? r2 : "(null)");
			return 1;
		}
	}
}
