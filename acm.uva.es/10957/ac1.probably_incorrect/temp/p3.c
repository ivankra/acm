#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct {
	int a[10][10], c[10][10], left;
} sudoku;

int n3[16][16], n3r[16][16], n3c[16][16], nbits[2049], sbit[2049], found;

int valid(sudoku *S)
{
	int i, j, k, t;

	for (i = 1; i <= 9; i++) {
		for (j = 1; j <= 9; j++) {
			if (S->a[i][j] < 0 || S->a[i][j] > 9) return 0;
			if (S->a[i][j] == 0) continue;
			t = n3[i][j];
			for (k = 1; k <= 9; k++) {
				if (S->a[i][k] == S->a[i][j] && j != k) return 0;
				if (S->a[k][j] == S->a[i][j] && i != k) return 0;

				if (S->a[n3r[t][k]][n3c[t][k]] == S->a[i][j] &&
				    (n3r[t][k] != i || n3c[t][k] != j))
					return 0;
			}
		}
	}

	return 1;
}

void sstat(sudoku *S)
{
	int i, j;

	S->left = 0;
	for (i = 1; i <= 9; i++)
		for (j = 1; j <= 9; j++)
			if (S->a[i][j] == 0)
				S->left++;
}

void makecand(sudoku *S)
{
	int i, j, k, r, c;

	for (i = 1; i <= 9; i++)
		for (j = 1; j <= 9; j++) {
			S->c[i][j] = (1 << 10) - 2;
			if (S->a[i][j] != 0) S->c[i][j] = 0;
		}

	for (r = 1; r <= 9; r++) {
		for (c = 1; c <= 9; c++) {
			if (S->a[r][c] == 0) continue;

			k = n3[r][c];
			for (i = 1; i <= 9; i++) {
				S->c[r][i] &= ~(1 << S->a[r][c]);
				S->c[i][c] &= ~(1 << S->a[r][c]);
				S->c[n3r[k][i]][n3c[k][i]] &= ~(1 << S->a[r][c]);
			}
		}
	}
}

int intell(sudoku *S)
{
	int r, c;

	for (;;) {
again:
		sstat(S);
		if (S->left == 0) break;

		makecand(S);

/*{int k;printf("board:\n");
for(r=1;r<=9;r++){for(c=1;c<=9;c++)printf("%d",S->a[r][c]);printf("\n");}
printf("cand:\n");
for(r=1;r<=9;r++){for(c=1;c<=9;c++){
for(k=1;k<=9;k++)
  if (S->c[r][c] & (1 << k)) printf("%d",k); else printf(".");
printf(" ");
}printf("\n");}
printf("valid=%d\n", valid(S));}*/

		for (r = 1; r <= 9; r++) {
			for (c = 1; c <= 9; c++) {
				if (S->a[r][c] != 0) continue;
				if (S->c[r][c] == 0) return 1;
				if (nbits[S->c[r][c]] != 1) continue;
				S->a[r][c] = sbit[S->c[r][c]];
				goto again;
			}
		}

		break;
	}

	return 0;
}

void backtr(sudoku *S)
{
	sudoku T;
	int r=0, c=0, i, j, k;

	if (found > 1 || intell(S)) return;

	if (S->left == 0) {
		found++;

/*printf("solution [%d]:\n", valid(S));
for(r=1;r<=9;r++){for(c=1;c<=9;c++)printf("%d",S->a[r][c]);printf("\n");}*/

		return;
	}

	sstat(S);
	makecand(S);

	k = -1;
	for (i = 1; i <= 9; i++)
		for (j = 1; j <= 9; j++)
			if (S->a[i][j] == 0 && (k < 0 || nbits[S->c[i][j]] < k))
{
				k = nbits[S->c[r=i][c=j]];
goto xxx;
}
	if (k < 0) return;
xxx:
	for (k = 1; k <= 9; k++) {
		if ((S->c[r][c] & (1 << k)) == 0) continue;
		memcpy(T.a, S->a, sizeof(S->a));
		T.a[r][c] = k;
		backtr(&T);
		if (found > 1) break;
	}
}

char *solve(sudoku *S)
{
	if (!valid(S)) return "Illegal";

	found = 0;
	backtr(S);

	if (found == 0) return "Impossible";
	if (found == 1) return "Unique";
	return "Ambiguous";
}

void pre()
{
	int i, j, k, w[16];

	memset(w, 0, sizeof(w));
	for (i = 1; i <= 9; i++) {
		for (j = 1; j <= 9; j++) {
			k = (i - 1) / 3;
			n3[i][j] = k * 3 + (j - 1) / 3;
			k = n3[i][j];
			w[k]++;
			n3r[k][w[k]] = i;
			n3c[k][w[k]] = j;
		}
	}

	for (i = 0; i <= 2048; i++) {
		for (j = i, k = 0; j > 0; j >>= 1) k += (j & 1);
		nbits[i] = k;
	}

	for (i = 0; i <= 11; i++)
		sbit[1 << i] = i;
}

int main()
{
	int i, j, t;
	sudoku S;

	pre();
	for (t = 1;; t++) {
		for (i = 1; i <= 9; i++)
			for (j = 1; j <= 9; j++)
				if (scanf("%d", &S.a[i][j]) != 1) return 0;
		printf("Case %d: %s.\n", t, solve(&S));
	}
}
