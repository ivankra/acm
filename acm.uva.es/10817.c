#include <stdio.h>
#include <string.h>

#define INF	0x3FFFFFFF

int nsubj, nserv, napp, serv[8], nstates;
int app_cost[128], app_subj[128][8], pwr[64];

int tab[65536], next[65536];

void process(int a)
{
	int i, j, k, s;

	for (i = 0; i < nstates; i++)
		next[i] = tab[i];

	for (i = 0; i < nstates; i++) {
		if (tab[i] == INF) continue;

		for (s = 0, j = 0; j < nsubj; j++) {
			k = ((i / pwr[j]) % 3) + app_subj[a][j];
			if (k > 2) k = 2;
			s += k * pwr[j];
		}

		k = tab[i] + app_cost[a];
		if (k < next[s])
			next[s] = k;
	}
}

int main()
{
	static char buf[65536];
	int i, j, cost, x, y;

	for (pwr[0] = 1, i = 1; i < 64; i++)
		pwr[i] = 3 * pwr[i - 1];

	while (scanf("%d %d %d", &nsubj, &nserv, &napp) == 3 && nsubj > 0) {
		memset(serv, 0, sizeof(serv));

		for (i = cost = 0; i < nserv; i++) {
			buf[0] = '\0';
			scanf("%d%[^\n]", &x, buf);

			for (cost += x, j = 0; sscanf(buf + j, "%d%n", &x, &y) > 0; j += y)
				serv[x - 1]++;
		}

		memset(app_subj, 0, sizeof(app_subj));
		for (i = 0; i < napp; i++) {
			buf[0] = '\0';
			scanf("%d%[^\n]", &app_cost[i], buf);

			for (j = 0; sscanf(buf + j, "%d%n", &x, &y) > 0; j += y)
				app_subj[i][x - 1] = 1;
		}

		for (i = 0, j = 0; i < nsubj; i++) {
			if (serv[i] > 2) serv[i] = 2;
			j += serv[i] * pwr[i];
		}

		nstates = pwr[nsubj];

		for (i = 0; i < nstates; i++)
			tab[i] = INF;
		tab[j] = cost;

		for (i = 0; i < napp; i++) {
			process(i);
			memcpy(tab, next, nstates * sizeof(int));
		}

		printf("%d\n", tab[pwr[nsubj] - 1]);
	}

	return 0;
}
