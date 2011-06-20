 #include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>
#include <numeric>
#include <bitset>
#include <stack>
#include <queue>
#include <set>
using namespace std;
 
int dr[]={0,1,0,-1,1,1,-1,-1};
int dc[]={1,0,-1,0,1,-1,1,-1};
#define zmax(a,b) (((a)>(b))?(a):(b))
#define zmin(a,b) (((a)>(b))?(b):(a))
#define zabs(a) (((a)>=0)?(a):(-(a)))
#define iif(c,t,f) ((c)?(t):(f))
template<class A, class B> A cvt(B x) {stringstream s;s<<x;A r;s>>r;return r;}
 
#define MAXVAR 100
#define MAXCONSTRAINT 100
#define lptype double
#define EPS 1e-7
 
//Simplex input
//  Maximizes CX subject to AX <= B with X >= 0
lptype C[MAXVAR];
lptype A[MAXCONSTRAINT][MAXVAR];
lptype B[MAXCONSTRAINT];
 
//simplex output
//  The X vector that maximizes CX subject to AX = B with x >= 0
lptype X[MAXVAR];
 
//simplex temporaries
lptype tableau[MAXCONSTRAINT + 1][MAXVAR + MAXCONSTRAINT + 2];
 
//Returns CX
lptype simplex(int variables, int constraints)
{
  //Initialize tablueau
  int rows = constraints;      //Note rows and cols doesn't count the outermost row/col for convenience
  int cols = variables + constraints + 1;
  for(int i = 0; i < constraints; i++)
  {
    for(int j = 0; j < variables; j++) tableau[i][j] = A[i][j];
    for(int j = 0; j < constraints; j++) tableau[i][j + variables] = i == j ? 1 : 0;
    tableau[i][variables + constraints] = 0;
    tableau[i][variables + constraints + 1] = B[i];
  }
  for(int j = 0; j < variables; j++)
  {
    tableau[constraints][j] = C[j] == 0 ? 0 : -C[j];
    tableau[constraints][j + variables] = 0;
  }
  tableau[constraints][variables + constraints] = 1;
  tableau[constraints][variables + constraints + 1] = 0;
 
  //Pivot until done
  while(true)
  {
    //Select pivot column
    int pivot_col = 0;
    for(int i = 1; i < cols; i++)
      if(tableau[rows][i] < tableau[rows][pivot_col])
        pivot_col = i;
 
    //Check for finishing condition
    if(tableau[rows][pivot_col] >= 0) break;
 
    //Select pivot row
    int pivot_row = 0;
    for(int i = 1; i < rows; i++)
      if(tableau[i][pivot_col] >= EPS)
        if(tableau[pivot_row][pivot_col] < EPS || tableau[i][cols] / tableau[i][pivot_col] < tableau[pivot_row][cols] / tableau[pivot_row][pivot_col])
          pivot_row = i;
 
    //Perform pivot
    for(int i = 0; i <= rows; i++)
    {
      if(i == pivot_row) continue;
      lptype ratio = tableau[i][pivot_col] / tableau[pivot_row][pivot_col];
      for(int j = 0; j <= cols; j++)
        tableau[i][j] -= ratio * tableau[pivot_row][j];
      tableau[i][pivot_col] = 0; //should already be zero, just to keep things precise
    }
 
    //Normalize table
    for(int i = 0; i <= rows; i++)
    {
      double max = 0;
      for(int j = 0; j <= cols; j++)
        max >?= zabs(tableau[i][j]);
      for(int j = 0; j <= cols; j++)
        tableau[i][j] /= max;
    }
 
  }
 
 
  //Extract X vector
  for(int i = 0; i < variables; i++)
  {
    bool found = false;
    for(int j = 0; j < constraints; j++)
    {
      if(tableau[j][i] != 0)
      {
        if(!found)
        {
          X[i] = tableau[j][cols] / tableau[j][i];
          found = true;
        }
        else
        {
          X[i] = 0;
          break;
        }
      }
    }
  }
 
  return tableau[rows][cols] / tableau[rows][cols - 1];
}
 
 
class PreciousStones
{
public:
double PreciousStones::value(vector <int> silver, vector <int> gold)
{
  int n = silver.size();
  memset(&C, 0, sizeof(C));
  memset(&B, 0, sizeof(B));
  memset(&A, 0, sizeof(A));
  for(int i = 0; i < n; i++) C[i] = silver[i];
  for(int i = 0; i < n; i++)
  {
    A[i][i] = 1;
    B[i] = 1;
  }
  for(int i = 0; i < n; i++)
  {
    A[n][i] = silver[i] + gold[i];
  }
  B[n] = accumulate(gold.begin(), gold.end(), 0);
  double ret = simplex(n, n + 1);
  return ret;
}
};
 
 
//Powered by [KawigiEdit] 2.0

