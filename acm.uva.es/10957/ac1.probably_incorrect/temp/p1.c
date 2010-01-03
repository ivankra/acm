#include <stdio.h>
#include <string.h>

typedef struct {
	int a[16][16];
} sudoku;

typedef struct {
	int left /*, cleft[16], rleft[16]*/;
	int c[16][16];
} sudoku_stat;

int n3[16][16], n3r[16][16], n3c[16][16], nbits[2049], sbit[2049];
int found;

void sstat(sudoku_stat *st, sudoku *S)
{
	int i, j;

	st->left = 0;
/*	for (i = 1; i <= 9; i++) st->cleft[i] = st->rleft[i] = 0;*/

	for (i = 1; i <= 9; i++)
		for (j = 1; j <= 9; j++)
			if (st->a[i][j] == 0) {
				st->left++;
/*				st->rleft[i]++;
				st->cleft[j]++;*/
			}
}

void makecand(sudoku_stat *st, sudoku *S)
{
	int i, j, k, r, c;

	for (i = 1; i <= 9; i++)
		for (j = 1; j <= 9; j++) {
			st->c[i][j] = (1 << 10) - 2;
			if (S->a[i][j] != 0) st->c[i][j] = 0;
		}

	for (r = 1; r <= 9; r++) {
		for (c = 1; c <= 9; c++) {
			if (S->a[r][c] == 0) continue;

			k = n3[r][c];
			for (i = 1; i <= 9; i++) {
				st->c[r][i] &= ~(1 << S->a[r][c]);
				st->c[i][c] &= ~(1 << S->a[r][c]);
				st->c[n3r[k][i]][n3c[k][i]] &= ~(1 << S->a[r][c]);
			}
		}
	}
}

int intell(sudoku *S)
{
	static sudoku_stat st;
	int k, r, c, u;

	do {
		sstat(&st, S);
		if (st->left == 0) break;

		makecand(&st, S);

/*printf("board:\n");
for(r=1;r<=9;r++){for(c=1;c<=9;c++)printf("%d",S->a[r][c]);printf("\n");}
printf("cand:\n");
for(r=1;r<=9;r++){for(c=1;c<=9;c++){
for(k=1;k<=9;k++)
  if (S->c[r][c] & (1 << k)) printf("%d",k); else printf(".");
printf(" ");
}printf("\n");}
*/
		u = 0;
		for (r = 1; r <= 9; r++) {
			for (c = 1; c <= 9; c++) {
				if (S->a[r][c] != 0) continue;
				if (st.c[r][c] == 0) return 1;
				if (nbits[st.c[r][c]] != 1) continue;
				S->a[r][c] = sbit[st.c[r][c]];
				u++;
			}
		}
/*printf("[u=%d]", u);*/
	} while (u);

	return 0;
}

void backtr(sudoku *S)
{
	sudoku T;
	int r=0, c=0, i, j, k;

printf("<back>");

	if (found > 1 || intell(S)) return;

	if (S->left == 0) {
		found++;
		return;
	}

	sstat(S);
	makecand(S);

	k = -1;
	for (i = 1; i <= 9; i++)
		for (j = 1; j <= 9; j++)
			if (S->a[i][j] == 0 && (k < 0 || nbits[S->c[i][j]] < k))
				k = nbits[S->c[r=i][c=j]];
	if (k < 0) return;

	for (k = 1; k <= 9; k++) {
		if ((S->c[r][c] & (1 << k)) == 0) continue;
		memcpy(T.a, S->a, sizeof(S->a));
		T.c[r][c] = k;
		backtr(&T);
		if (found > 1) break;
	}
}

char *solve(sudoku *S)
{
	int i, j, k, t;

	for (i = 1; i <= 9; i++) {
		for (j = 1; j <= 9; j++) {
			if (S->a[i][j] < 0 || S->a[i][j] > 9) return "Illegal";
			if (S->a[i][j] == 0) continue;
			t = n3[i][j];
			for (k = 1; k <= 9; k++) {
				if (S->a[i][k] == S->a[i][j] && j != k) return "Illegal";
				if (S->a[k][j] == S->a[i][j] && i != k) return "Illegal";

				if (S->a[n3r[t][k]][n3c[t][k]] == S->a[i][j] &&
				    (n3r[t][k] != i || n3c[t][k] != j))
					return "Illegal";
			}
		}
	}

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
			n3[i][j] = k = ((i - 1) / 3) * 3 + (j - 1) / 3;
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
