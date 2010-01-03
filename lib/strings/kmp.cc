#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct KMP {
	char *pat;
	int m, *f;

	KMP(const char *P) {
		m = strlen(pat = strdup(P));
		f = (int *)malloc(sizeof(int)*(1+m));
		for (int i=1, j=f[0]=f[1]=0; i < m; i++) {
			while (j > 0 && pat[j] != pat[i]) j = f[j];
			f[i+1] = j = (pat[j] == pat[i] ? j+1 : 0);
		}
	}
	KMP(const KMP &k) { pat=k.pat; m=k.m; f=k.f; f[0]++; }
	~KMP() { if (f[0]-- == 0) { free(f); free(pat); } }

	char *match(const char *s) {
		if (m == 0) return (char *)s;
		for (int i = 0; *s; s++) {
			while (i > 0 && *s != pat[i]) i = f[i];
			if (*s != pat[i]) i = 0;
			else if (++i == m) return (char *)(s-m+1);
		}
		return NULL;
	}
};

#include <ctime>
int main()
{
	srand(time(NULL));
	for (int i = 0; i < 1000000; i++) {
		if ((i % 1000) == 0) printf("[%d]\n",i);

		static char s[256], t[256];
		int n = 1 + (rand() % 20), m = 1 + (rand() % 20);
		if (n < m) swap(n,m);

		for (int i = 0; i < n; i++) s[i] = 'a' + (rand() & 1); s[n]=0;
		for (int i = 0; i < m; i++) t[i] = 'a' + (rand() & 1); t[m]=0;

		if (strstr(s,t) != KMP(t).match(s)) {
			printf("s=%s\nt=%s\n", s, t);
			char *r1=strstr(s,t), *r2=KMP(t).match(s);
			printf("strstr: %s\n", r1 ? r1 : "(null)");
			printf("KMP:    %s\n", r2 ? r2 : "(null)");
			return 1;
		}
	}
}
