#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
#include <string>
#include <sstream>
#include <set>
#include <cmath>
#include <queue>
#include <stack>
#include <list>
#include <numeric>
#include <bitset>
#include <cstdio>
#include <valarray>      
#include <ext/hash_set> 
#include <ext/hash_map>

using namespace   std;
using namespace    __gnu_cxx;


#define COND 0
#define q(x) ( { if (COND) { cerr << __LINE__ << " : " << #x << ": " << x; cerr << endl; }; })

#define PB      push_back
#define ve      vector
#define ld      long double
#define st      string

#define INIT(a, b)    memset(a, b, max(sizeof(*a), sizeof(a)))
#define ALL(x)      (x).begin(), (x).end()
#define INRANGE(x, a, b)  ((x) >= (a) && (x) <= (b))
#define FOREACH(it, a)    for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); ++it)

#define ll      long long
#define BET(i, a, b)    for(int i = (a); i <= (int)(b); ++i)
#define REP(i, b)    for(int i = (0); i < (int)(b); ++i)
#define REV(i, a, b)    for(int i = (a); i >= (b); --i)

#define PII      pair <int, int>
#define x      first
#define y      second




struct PreciousStones {
  double value(vector <int> S, vector <int> G) { 
    int n = S.size();
    int m = n + 1;
    vector<VT> A(m,VT(n));
    VT b(m),c(n),res;
    REP (i, n) {
      A[0][i] = (S[i] + G[i]);
      b[0] += G[i];

      c[i] = S[i];
    }
    REP (i, n) {
      A[i + 1][i] = 1;
      b[i + 1] = 1;
    }
    

 
    res=Simplex::simplex(A,b,c);
    T acc=0; REP(i,SIZE(res)) acc+=res[i]*c[i];   
    return acc;
  }
  
 
};
 



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
