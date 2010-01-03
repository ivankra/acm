#include <stdio.h>
#include <string.h>

int cnt[16];

int cmp(char *s, char *t)
{
	return strlen(s) != strlen(t) ? (strlen(s) - strlen(t)) : strcmp(s, t);
}

void check(char *s, int r)
{
	static char t[1024];
	int i, j, k;

	for (i = 0; i < 10; i++)
		r += cnt[i] * i;
	if ((r % 3) != 0) return;

	for (i = 9, k = 0; i >= 0; i--)
		for (j = cnt[i]; j > 0; j--)
			t[k++] = i+'0';
	t[k] = 0;

	if (t[0] == '0' || k == 0) return;

	if (s[0] == 0 || cmp(t, s) > 0)
		strcpy(s, t);
}

void make(char *s, int r)
{
	s[0] = 0;
	check(s, r);
	for (int a = 0; a < 10; a++) {
		if (cnt[a] == 0) continue;
		cnt[a]--;
		check(s, r);
		for (int b = a; b < 10; b++) {
			if (cnt[b] == 0) continue;
			cnt[b]--;
			check(s, r);
			for (int c = b; c < 10; c++) {
				if (cnt[c] == 0) continue;
				cnt[c]--;
				check(s, r);
				cnt[c]++;
			}
			cnt[b]++;
		}
		cnt[a]++;
	}
}

void solve(char *r)
{
	static char s[1024];
	int i;

	r[0] = 0;

	if (cnt[0] == 0 && cnt[5] == 0) return;

	for (i = 1; i < 10 && cnt[i] == 0; i++);
	if (i == 10) { strcpy(r, "0"); return; }

	r[0] = 0;
	for (i = 0; i <= 5; i += 5) {
		if (cnt[i] == 0) continue;
		cnt[i]--;
		make(s, i % 3);
		if (s[0] != 0) {
			sprintf(s+strlen(s), "%c", i+'0');
			if (r[0] == 0 || cmp(s, r) > 0) strcpy(r, s);
		}
		cnt[i]++;
	}

	if (r[0] == 0 && cnt[0] > 0)
		strcpy(r, "0");
}

int main()
{
	char s[1024];
	int T;

	for (scanf("%d", &T); T-- > 0 && scanf(" %[0-9]", s) == 1;) {
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; s[i]; i++)
			cnt[s[i]-'0']++;

		solve(s);

		if (s[0] == 0)
			printf("impossible\n");
		else
			printf("%s\n", s);
	}

	return 0;
}
