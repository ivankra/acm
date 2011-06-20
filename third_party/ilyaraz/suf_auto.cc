#include <stdio.h>
#include <string.h>

#pragma comment (linker, "/STACK:20000000")

#define MAX 200010

int N, La, Ne[MAX][2], Su[MAX], L[MAX];
int U[MAX], ON = 0, Ord[MAX], F[MAX];
__int64 Sum = 0;

void dfs( int v )
{
  int i;

  if (U[v])
    return;
  U[v] = 1;
  for (i = 0; i < 2; i++)
    if (Ne[v][i] != -1)
      dfs(Ne[v][i]);
  Ord[ON++] = v;
}

int main( void )
{
  int i, j, c, p, q, r;

  freopen("substrings.in", "rt", stdin);
  freopen("substrings.out", "wt", stdout);
  memset(Ne, -1, sizeof(Ne));
  La = 1, N = 2;
  while ((c = getc(stdin)) != -1)
    if (c == '0' || c == '1')
    {
      c -= '0';
      p = La, La = N++, L[La] = L[p] + 1;
      while (p && Ne[p][c] == -1)
        Ne[p][c] = La, p = Su[p];
      if (!p)
        Su[La] = 1;
      else if (L[q = Ne[p][c]] == L[p] + 1)
        Su[La] = q;
      else
      {
        r = N++, L[r] = L[p] + 1;
        memcpy(Ne[r], Ne[q], sizeof(Ne[0]));
        Su[La] = r, Su[r] = Su[q], Su[q] = r;
        while (p && Ne[p][c] == q)
          Ne[p][c] = r, p = Su[p];
      }
    }
  memset(U, 0, sizeof(U));
  dfs(1);
  memset(F, 0, sizeof(F)), F[1] = 1;
  for (i = ON - 1; i >= 0; i--)
    for (j = 0; j < 2; j++)
      if (Ne[p = Ord[i]][j] != -1)
        F[Ne[p][j]] += F[p];
  for (i = 2; i < N; i++)
    Sum += F[i];
  printf("%I64d\n", Sum);
  return 0;
}

