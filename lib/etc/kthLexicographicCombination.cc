// Input: N K X
// Output: X-th (1-based) lexicographic K-subset of {1,2,...,N}
#include <cstdio>
#include <cstring>

int main()
{
   unsigned long long C[64][64], X;
   int N, K;

   memset(C, 0, sizeof(C));
   for (int n = 0; n < 64; n++) {
      C[n][0] = 1;
      for (int k = 1; k <= n; k++)
         C[n][k] = C[n-1][k-1] + C[n-1][k];
   }

   while (scanf("%d %d %llu", &N, &K, &X) == 3) {
      for (int i = 1; K > 0 && i <= N; i++) {
         if (X <= C[N-i][K-1]) {
            printf("%d ", i);
            K--;
         } else {
            X -= C[N-i][K-1];
         }
      }
      printf("\n");
   }
} 
