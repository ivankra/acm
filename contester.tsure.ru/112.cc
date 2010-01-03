#include <cstdio>
#include <cstring>

int cmp(const char *a, const char *b) {
	int s1=(a[0]=='-')?-1:1, s2=(b[0]=='-')?-1:1;
	if (s1 != s2) return s1-s2;
	while (a[0] && strchr("+-0", a[0])) a++;
	while (b[0] && strchr("+-0", b[0])) b++;
	if (strlen(a) != strlen(b)) return (strlen(a)-strlen(b))*s1;
	for (int i = 0; a[i]; i++)
		if (a[i] != b[i]) return (a[i]-b[i])*s1;
	return 0;
}

int main()
{
	char s1[4096], o[4096], s2[4096];
	while (scanf(" %[-+0-9] %[<>=] %[-+0-9]", s1, o, s2) == 3) {
		int x = cmp(s1, s2), r=0;
		for (int i = 0; i < 2 && o[i]; i++) {
			if (o[i]=='>') r |= (x > 0);
			if (o[i]=='=') r |= (x == 0);
			if (o[i]=='<') r |= (x < 0);
		}
		printf(r ? "TRUE\n" : "FALSE\n");
	}
}
