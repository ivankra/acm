#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX 131072

int op[MAX], arg[MAX], R[MAX], loop[MAX], loopc[MAX];
int fin[MAX], topo[MAX], n, m;

int max(int x, int y) { return (x > y) ? x : y; }

static int dfs(int x)
{
	if (fin[x] < 0) return 1;
	if (fin[x] != 0) return 0;
	fin[x] = -1;
	if (op[x] == 'i') {
		if (dfs(x+1) || dfs(arg[x])) return 1;
	} else if (op[x] == 'j') {
		if (dfs(arg[x])) return 1;
	}
	topo[m] = x;
	fin[x] = m++;
	return 0;
}

int main()
{
	static char buf[1024], cmd[1024];
	int i, k, z;

	for (;;) {
		loop[0] = 0;
		for (n = 0;;) {
			loop[n+1] = 0;

			if (gets(buf) == NULL) {
				if (n == 0) return 0;
				break;
			}
			assert(strlen(buf) < 1000);

			i = sscanf(buf, " %[A-Za-z] %d %d",
				   cmd, &arg[n+1], &z);
			if (i < 1) break;

			k = tolower(cmd[0]);
			assert(strchr("ijpdl", k) != NULL);

			n++;
			op[n] = k;
			R[n] = 1;
			if (k == 'i' || k == 'j') {
				assert(i >= 2);
			} else if (k == 'p') {
				op[n] = 'j';
				arg[n] = n+1;
			} else if (k == 'd') {
				op[n] = 'j';
				arg[n] = 0;
			} else {
				assert(i >= 3 && arg[n] < n && loop[arg[n]] == 0);
				loop[arg[n]] = n;
				loopc[arg[n]] = z;
				op[n] = 'j';
				arg[n] = n+1;
			}
		}

		n++;
		op[n] = 'j';
		loop[n] = 0;
		arg[n] = 1;
		R[n] = 0;

		op[0] = 'x';
		arg[0] = loop[0] = R[0] = 0;

		for (i = 0; i <= n; i++) fin[i] = 0;
		m = 1;
		if (dfs(1)) {
			printf("infinity\n");
			continue;
		}

		for (k = 1; k < m; k++) {
			i = topo[k];

			if (op[i] == 'i') {
				R[i] += max(R[i+1], R[arg[i]]);
			} else if (op[i] == 'j') {
				R[i] += R[arg[i]];
			}

			if (loop[i] != 0)
				R[i] += (loopc[i] - 1) * (R[i]-R[loop[i]]+1);
		}

		printf("%d\n", R[1]);
	}

	return 0;
}
