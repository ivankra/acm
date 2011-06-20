#include <sstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#define foreach(i,c) for(__typeof((c).end())i=(c).begin();i!=(c).end();++i)
using namespace std;
 
#define MAXM 400
#define MAXN 400
#define EPS 1e-9
#define INF (1.0 / 0.0)
double mtx[MAXM][MAXN];
int bas[MAXM], out[MAXN];
void pivot( int m, int n, int a, int b )
{
   for( int i = 0; i <= m; i++ ) if( i != a )
   for( int j = 0; j <= n; j++ ) if( j != b )
      mtx[i][j] -=  mtx[a][j] * mtx[i][b] / mtx[a][b];
   for( int j = 0; j <= n; j++ ) if( j != b ) mtx[a][j] /=  mtx[a][b];
   for( int i = 0; i <= m; i++ ) if( i != a ) mtx[i][b] = -mtx[i][b] / mtx[a][b];
   mtx[a][b] =  1 / mtx[a][b];
   swap( bas[a], out[b] );
}
 
double simplex( int m, int n, double M[][MAXN], double X[] )
{
   for( int i = 1; i <= m; i++ ) for( int j = 0; j <= n; j++ ) mtx[i][j] = M[i][j];
     for( int j = 0; j <= n; j++ ) mtx[0][j] = -M[0][out[j] = j];
  for( int i = 0; i <= m; i++ ) bas[i] = -i;
  
  // Find a feasible solution.
     while( 1 )
     {
      int i, ii;
      for( i = ii = 1; i <= m; i++ )
           if( mtx[i][n] < mtx[ii][n] || ( mtx[i][n] == mtx[ii][n] && bas[i] < bas[ii] ) )
               ii = i;
    if( mtx[ii][n] >= -EPS ) break;
        
    int j, jj;    
        for( j = jj = 0; j < n; j++ )
          if( mtx[ii][j] < mtx[ii][jj] - EPS || ( mtx[ii][j] < mtx[ii][jj] - EPS && out[i] < out[j] ) )
        jj = j;
      
        if( mtx[ii][jj] >= -EPS) return -INF;
    
    pivot(m, n, ii, jj);
  }
  
  // Optimize.
     while( 1 )
     {
      int j, jj;
       for( j = jj = 0; j < n; j++ )
           if( mtx[0][j] < mtx[0][jj] || ( mtx[0][j] == mtx[0][jj] && out[j] < out[jj] ) )
               jj = j;
    if( mtx[0][jj] > -EPS ) break;
    
    int i, ii;
    for( i = 1, ii = 0; i <= m; i++ )
          if( mtx[i][jj] > EPS &&
              ( !ii ||
                    mtx[i][n] / mtx[i][jj] < mtx[ii][n] / mtx[ii][jj] - EPS ||
          (
            mtx[i][n] / mtx[i][jj] < mtx[ii][n] / mtx[ii][jj] + EPS && 
            bas[i] < bas[ii] 
          ) 
        ) 
      )
               ii = i;
        if( mtx[ii][jj] <= EPS) return INF;
    
    pivot( m, n, ii, jj );
  }
  
  // Output the solution vector.
     memset( X, 0, sizeof( *X ) * n );
     for( int i = 1; i <= m; i++) if( bas[i] >= 0 ) X[bas[i]] = mtx[i][n];
     return mtx[0][n];
}
 
double spg[128], M[MAXM][MAXN], c[MAXN];
 
class PreciousStones {
  public:
  double value(vector <int> s, vector <int> g) {
    int n = s.size();
    double gdot1 = 0.0;
    for( int i = 0; i < n; i++ )
    {
      gdot1 += g[i];
      spg[i] = s[i] + g[i];
    }
    
    memset( M, 0, sizeof( M ) );
    for( int i = 0; i < n; i++ ) M[0][i] = s[i];
    for( int i = 0; i < n; i++ )
    {
      M[1][i] = spg[i];
      M[2][i] = -spg[i];
    }
    M[2][n] = -( M[1][n] = gdot1 );
    for( int i = 0; i < n; i++ )
    {
      M[3 + i + i][i] = -( M[4 + i + i][i] = -1.0 );
      M[3 + i + i][n] = 1.0;
      M[4 + i + i][n] = 0;
    }
    
    return simplex( 3 + n + n, n, M, c );
  }
};
 
// Powered by PopsEdit
