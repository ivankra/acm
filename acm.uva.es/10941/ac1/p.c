#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

char buf[1048576];
int got[1048576], dict[1024], bufptr, id, n;

int sol(int st)
{
	static int queue[1048576], dist[1048576], head, tail;
	int i, j, k;

	if (buf[st] == '\0') return 0;

	head = 0; tail = 1; got[queue[0] = st] = id; dist[0] = 0;
	for (; head < tail; head++) {
		for (k = 0; k < n; k++) {
			i = queue[head]; j = dict[k];
			while (buf[i] == buf[j] && buf[i] != '\0') i++, j++;

			if (buf[i] == '\0' && buf[j] == '\0')
				return (dist[head] + 1);

			if (buf[i] == '\0' && got[j] != id) {
				got[queue[tail] = j] = id;
				dist[tail++] = dist[head] + 1;
			} else if (buf[j] == '\0' && got[i] != id) {
				got[queue[tail] = i] = id;
				dist[tail++] = dist[head] + 1;
			}
		}
	}

	return -1;
}

int get()
{
	int i, j, r;
	gets(buf + bufptr);
	for (i = j = r = bufptr; buf[j]; j++)
		if (isalpha(buf[j])) buf[i++] = tolower(buf[j]);
	assert(i > bufptr);
	buf[i++] = '\0';
	bufptr = i;
	return r;
}

int getint()
{
	static char s[2048];
	int x;

	for (;;) {
		if (gets(s) == NULL) abort();
		if (sscanf(s, "%d", &x) == 1) return x;
	}
}

int main()
{
	int w1, w2, i, t;

	memset(got, 0, sizeof(got));
	id = 42;

	for (t = getint(); t-- > 0;) {
		id++;
		bufptr = 1;
		w1 = get();
		w2 = get();

		n = getint();
		assert(0 <= n && n <= 1000);

		for (i = 0; i < n; i++)
			dict[i] = get();

		while (buf[w1] == buf[w2] && buf[w1] != '\0')
			w1++, w2++;

		if (buf[w1] == '\0')
			printf("%d\n", sol(w2));
		else if (buf[w2] == '\0')
			printf("%d\n", sol(w1));
		else
			printf("-1\n");
	}

	return 0;
}
