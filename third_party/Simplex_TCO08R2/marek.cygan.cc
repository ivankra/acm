#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <numeric>
using namespace std;
 
 
typedef vector <int > VI;
#define REP(i,n) for (int i=0; i<n; ++i)
#define FOREACH(it,x) for(__typeof((x).begin()) it=(x.begin()); it!=(x).end(); ++it)
#define FOR(i,p,k) for (int i=p; i<=k; ++i)
#define PB push_back
#define ALL(x) x.begin(),x.end()
#define SIZE(x) (int)x.size()
 
typedef long double LD;
const LD EPS = 1e-11;
namespace Simplex{
  /*jak chcemy zmienic typ, to zmieniamy typedef'a oraz wartosc EPS,
   na doublach tez powinno dzialac, ale troche szybciej i mniej dokladnie*/
  typedef long double T;
  typedef vector<T> VT;
  vector<VT> A;
  VT b,c,res;
  VI kt,N;
  int m;
  inline void pivot(int k,int l,int e){
      int x=kt[l]; T p=A[l][e];
      REP(i,k) A[l][i]/=p; b[l]/=p; N[e]=0;
      REP(i,m) if (i!=l) b[i]-=A[i][e]*b[l],A[i][x]=A[i][e]*-A[l][x];
      REP(j,k) if (N[j]){
        c[j]-=c[e]*A[l][j];
        REP(i,m) if (i!=l) A[i][j]-=A[i][e]*A[l][j];
      }
      kt[l]=e; N[x]=1; c[x]=c[e]*-A[l][x];
  }
  /*k == #zmiennych bazowych + #zmiennych niebazowych*/
  VT doit(int k){
    VT res; T best;
    while (1){
      int e=-1,l=-1; REP(i,k) if (N[i] && c[i]>EPS) {e=i; break;}
      if (e==-1) break;
      REP(i,m) if (A[i][e]>EPS && (l==-1 || best>b[i]/A[i][e]))
        best=b[ l=i ]/A[i][e];
      if (l==-1) /*rozwiazanie nieograniczone,zwracam cokolwiek*/ return VT();
      pivot(k,l,e);
    }
    res.resize(k,0); REP(i,m) res[kt[i]]=b[i];
    return res;
  }
/*A*x<=b, maksymalizujemy x*c (a[0][0]*x[0]+a[0][1]*x[1]+...<=b[0]), dla x>=0*/
/*jak chcemy zeby xj moglo byc ujemne to podstawiamy zamiast xj dwie nowe    */
/*zmiene (xj1-xj2), gdzie xj1,xj2>=0, funkcja zwraca najlepszy wektor, jesli */
/*rozwiazanie nie istnieje, lub jest nieograniczone, to zwracany jest pusty  */
/*wektor                                                                     */
  VT simplex(vector<VT> AA,VT bb,VT cc){
    int n=AA[0].size(),k;
    m=AA.size(); k=n+m+1; kt.resize(m); b=bb; c=cc; c.resize(n+m);
    A=AA; REP(i,m){ A[i].resize(k); A[i][n+i]=1; A[i][k-1]=-1; kt[i]=n+i;}
    N=VI(k,1); REP(i,m) N[kt[i]]=0;
    int pos=min_element(ALL(b))-b.begin();
    if (b[pos]<-EPS){ /*uwaga na epsilony*/
      c=VT(k,0); c[k-1]=-1; pivot(k,pos,k-1); res=doit(k);
      if (res[k-1]>EPS) /*brak rozwiazan*/ return VT();
      REP(i,m) if (kt[i]==k-1)
          REP(j,k-1) if (N[j] && (A[i][j]<-EPS || EPS<A[i][j])){
            pivot(k,i,j); break;
          }
      c=cc; c.resize(k,0); REP(i,m) REP(j,k) if (N[j]) c[j]-=c[kt[i]]*A[i][j];
    }
    res=doit(k-1); if (!res.empty()) res.resize(n);
    return res;
  }
};
 //Begin of the code
typedef long double T;
typedef vector<T> VT;
 
    class PreciousStones
        { 
        public: 
        double value(vector <int> silver, vector <int> gold){ 
          int n=SIZE(silver);
          int m=2*n+2;
          vector<VT> A(m,VT(2*n,0.0));
          VT b(m,0.0),c(2*n,0.0);
          int nr=0;
          REP(i,n){
            A[nr][2*i]=1.0; A[nr][2*i+1]=1.0; b[nr]=1.0;
            nr++;
            A[nr][2*i]=-1.0; A[nr][2*i+1]=-1.0; b[nr]=-1.0;
            nr++;
          }
          REP(i,n) A[nr][2*i]=silver[i],A[nr][2*i+1]=-gold[i];
          nr++;
          REP(i,n) A[nr][2*i]=-silver[i],A[nr][2*i+1]=gold[i];
          nr++;
          REP(i,n) c[2*i]=silver[i];
          VT res=Simplex::simplex(A,b,c);
          LD x=0.0;
          REP(i,2*n) x+=res[i]*c[i];
          return (double)x;
        } 
        
 
         }; 
 
    
 
 
// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
