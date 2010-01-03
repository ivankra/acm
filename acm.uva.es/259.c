#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define V_SRC    0
#define V_SINK   1
#define V_APP(n) (2 + (n))
#define V_COM(n) (12 + (n))
#define NVERT    22

int adj[32][32];

int maxflow()
{
	int q[32], v[32], p[32], h, t, i, j, f;

	for (f = 0;; f++) {
		memset(v, 0, sizeof(v));

		for (v[q[h = 0] = V_SRC] = 1, t = 1; h < t && v[V_SINK] == 0;) {
			for (i = q[h++], j = 0; j < NVERT; j++) {
				if (adj[i][j] && v[j] == 0) {
					v[j] = 1;
					p[j] = i;
					q[t++] = j;
				}
			}
		}

		if (v[V_SINK] == 0)
			return f;

		for (i = V_SINK; i != V_SRC; i = p[i]) {
			adj[p[i]][i] = 0;
			adj[i][p[i]] = 1;
		}
	}
}

int chop(char *s)
{
	char *p;
	for (p = s; *p; p++);
	for (p--; p >= s && (*p == ' '); p--);
	*++p = '\0';
	return (*s != '\0');
}

int main()
{
	struct { int count, run[10]; } app[32];
	char buf[1024], s1[1024], s2[1024], label[32];
	int i, j, k, m, nr_app;

	for (;;) {
		memset(app, 0, sizeof(app));

		for (k = 0; gets(buf) && chop(buf); k++) {
			if (sscanf(buf, " %[A-Z]%d %[0-9]", s1, &m, s2) != 3)
				continue;

			i = toupper(s1[0]) - 'A';
			app[i].count = m;

			for (j = 0; s2[j]; j++)
				app[i].run[s2[j] - '0'] = 1;
		}

		if (k == 0)
			break;

		for (nr_app = 0, i = 0; i < 26; i++)
			nr_app += app[i].count;

		if (nr_app > 10) {
			printf("!\n");
			continue;
		}

		memset(adj, 0, sizeof(adj));
		memset(label, 0, sizeof(label));

		for (m = 0, i = 0; i < 26; i++) {
			for (j = 0; j < app[i].count; j++, m++) {
				adj[V_SRC][V_APP(m)] = 1;
				label[m] = i + 'A';
				for (k = 0; k < 10; k++)
					if (app[i].run[k])
						adj[V_APP(m)][V_COM(k)] = 1;
			}
		}

		for (i = 0; i < 10; i++)
			adj[V_COM(i)][V_SINK] = 1;

		if (maxflow() != nr_app) {
			printf("!\n");
			continue;
		}

		for (k = 0; k < 10; k++) {
			for (i = 0; i < 10; i++) {
				if (adj[V_COM(k)][V_APP(i)]) {
					putchar(label[i]);
					break;
				}
			}

			if (i >= 10)
				putchar('_');
		}
		putchar('\n');
	}

	return 0;
}
