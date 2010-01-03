#include <stdio.h>
#include <string.h>

#define MOD 25219

struct { char S[64], T[64]; int Sn, Tn, X1; } rules[1024]; int n;
char buf[24*1048576], *bufptr, *word[65536];
int htab[MOD], next[65536], count;

int hash(char *s) { unsigned h; for (h=0; *s;) h=h*37 + *s++; return h%MOD; }

void add(char *s)
{
	int i, h = hash(s);
	for (i = htab[h]; i; i = next[i]) if (strcmp(word[i], s) == 0) return;
	strcpy(word[++count] = bufptr, s); while (*bufptr++);
	next[count] = htab[h];
	htab[h] = count;
}

int main()
{
	int i, j, k, t;
	char *p, *q;

	while (gets(buf) && sscanf(buf, "%d", &t) != 1);

	while (t-- > 0) {
		count = 0; memset(htab, 0, sizeof(htab));

		bufptr = buf+131072;
		while (gets(buf) && strchr(buf, '\"') == NULL);
		p = strchr(buf, '\"')+1;
		for (q = p; *q && *q != '\r' && *q != '\"'; q++); *q = '\0';

		add(p);

		for (n = 0; gets(buf) && (p=strchr(buf, '\"')) != NULL;) {
			for (q = ++p; *q && *q != '\r' && *q != '\"'; q++); *q++ = '\0';
			strcpy(rules[n].S, p); rules[n].Sn = strlen(p);

			while (*q && *q != '\"') q++;

			for (p = ++q; *q && *q != '\r' && *q != '\"'; q++); *q++ = '\0';
			strcpy(rules[n].T, p); rules[n].Tn = strlen(p);

			if (rules[n].Sn == rules[n].Tn && strcmp(rules[n].S, rules[n].T) == 0)
				continue;
			n++;
		}

		for (i = 0; i < n; i++)
			rules[i].X1 = (rules[i].Tn > rules[i].Sn &&
				       memcmp(rules[i].S, rules[i].T, rules[i].Sn) == 0);

		for (i = 1; i <= count && count <= 1000; i++) {
			for (j = 0; j < n; j++) {
				for (p = word[i]; (p = strstr(p, rules[j].S)) != NULL; p++) {
					k = p - word[i];
					memcpy(buf, word[i], k);
					memcpy(buf+k, rules[j].T, rules[j].Tn);
					strcpy(buf+k+rules[j].Tn, p+rules[j].Sn);
					add(buf);
					if (rules[j].X1) count=9999;
					if (count > 1000) break;
				}
				if (count > 1000) break;
			}
		}

		printf((count <= 1000) ? "%d\n" : "Too many.\n", count);
		if (t) printf("\n");
	}

	return 0;
}
