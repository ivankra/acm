#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <ctime>
using namespace std;
 
typedef vector<int> vi;
typedef vector<string> vs;
#define si size()
#define pb push_back
#define mp make_pair
 
int N;
 
int R, C;
double tab[105][105];
double rhs[105];
 
double A[51], B[51];
 
class PreciousStones {
  public:
  double value(vector <int> silver, vector <int> gold) {
    N = silver.si;
    for (int i = 0; i < N; i++) A[i] = silver[i], B[i] = gold[i];
    
    for (int i = 0; i < 105; i++) rhs[i] = 0;
    for (int i = 0; i < 105; i++) for (int j = 0; j < 105; j++) tab[i][j] = 0;
    
    double sumb = 0;
    for (int i = 0; i < N; i++) sumb += B[i];
    R = N+2, C = 2*N+3;
    for (int i = 0; i < N; i++) {tab[i][i] = tab[i][i+N] = 1; rhs[i] = 1;}
    for (int j = 0; j < N; j++) tab[N][j] = A[j] + B[j]; tab[N][2*N] = 1; rhs[N] = sumb;
    for (int j = 0; j < N; j++) tab[N+1][j] = -A[j];
    tab[N+1][C-1] = 1;
    
    while (1) {
      
      int col = -1; double val = -1e-9;
      for (int i = 0; i < C; i++) {
        if (tab[N+1][i] < val) {
          val = tab[N+1][i];
          col = i;
        }
      }
      if (col == -1) break;
      
      double bestratio = 1e9;
      int row = -1;
      for (int i = 0; i < R; i++) {
        if (tab[i][col] <= 0) continue;
        double temprat = rhs[i] / tab[i][col];
        if (temprat < bestratio) {bestratio = temprat; row = i;}
      }
      val = tab[row][col];
      for (int j = 0; j < C; j++) tab[row][j] /= val; rhs[row] /= val;
      for (int i = 0; i < R; i++) {
        if (i == row) continue;
        double mult = -tab[i][col];
        
        for (int j = 0; j < C; j++) tab[i][j] += mult * tab[row][j];
        rhs[i] += mult * rhs[row];
      }
    }
    
    return rhs[N+1];
  }
};
 
// Powered by PopsEdi
