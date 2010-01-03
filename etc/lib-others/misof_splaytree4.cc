// another fine solution by misof
#include <algorithm>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cassert>

#include <cmath>
#include <complex>
using namespace std;

// defines: REP, FOR, FORD, FOREACH, CLEAR {{{
#define REP(i,n) for(__typeof(n) i=0;i<(n);++i)
#define FOR(i,a,b) for(__typeof(b) i=(a);i<=(b);++i)
#define FORD(i,a,b) for(__typeof(a) i=(a);i>=(b);--i)
#define FOREACH(it,c) for(__typeof((c).begin()) it=(c).begin();it!=(c).end();++it)
#define CLEAR(t) memset((t),0,sizeof(t))
// }}}
// typedefs: PII, TRI, VI, VVI, VS, VVS, MII, MSI, LL {{{
typedef pair<int,int> PII;
typedef pair<int, pair<int,int> > TRI;
typedef vector<int> VI;
typedef vector< vector<int> > VVI;
typedef vector<string> VS;
typedef vector< vector<string> > VVS;
typedef map<int,int> MII;
typedef map<string,int> MSI;
typedef long long LL;
// }}}
// strings: split, splitInt, toUpper, toLower {{{
vector<string> split( const string& s, const string& delim =" " ) { vector<string> res; string t; for ( unsigned int i = 0 ; i != s.size() ; i++ ) { if ( delim.find( s[i] ) != string::npos ) { if ( !t.empty() ) { res.push_back( t ); t = ""; } } else { t += s[i]; } } if ( !t.empty() ) { res.push_back(t); } return res; }
vector<int> splitInt( const string& s, const string& delim =" " ) { vector<string> tok = split( s, delim ); vector<int> res; for ( unsigned int i = 0 ; i != tok.size(); i++ ) res.push_back( atoi( tok[i].c_str() ) ); return res; }
string toUpper(string S) { for (unsigned int i=0; i<S.size(); i++) S[i] = toupper(S[i]); return S; }
string toLower(string S) { for (unsigned int i=0; i<S.size(); i++) S[i] = tolower(S[i]); return S; }
// }}}
// helper functions: SQR, BITCNT {{{
#define SQR(x) ((x)*(x))
template <class T> inline int BITCNT(T x) { int res=0; while (x) { res++; x&=x-1; } return res; }
// }}}
// debug: DEBUG and ostream operators for containers {{{
#define DEBUG(var) { cout << #var << ": " << (var) << endl; }
template <class T> ostream& operator << (ostream &os, const vector<T> &temp) { os << "[ "; for (unsigned int i=0; i<temp.size(); ++i) os << (i?", ":"") << temp[i]; os << " ]"; return os; } // DEBUG
template <class T> ostream& operator << (ostream &os, const set<T> &temp) { os << "{ "; for(__typeof((temp).begin()) it=(temp).begin();it!=(temp).end();++it) os << ((it==(temp).begin())?"":", ") << (*it); os << " }"; return os; } // DEBUG
template <class T> ostream& operator << (ostream &os, const multiset<T> &temp) { os << "{ "; for(__typeof((temp).begin()) it=(temp).begin();it!=(temp).end();++it) os << ((it==(temp).begin())?"":", ") << (*it); os << " }"; return os; } // DEBUG
template <class S, class T> ostream& operator << (ostream &os, const pair<S,T> &a) { os << "(" << a.first << "," << a.second << ")"; return os; } // DEBUG
template <class S, class T> ostream& operator << (ostream &os, const map<S,T> &temp) { os << "{ "; for(__typeof((temp).begin()) it=(temp).begin();it!=(temp).end();++it) os << ((it==(temp).begin())?"":", ") << (it->first) << "->" << it->second; os << " }"; return os; } // DEBUG
// }}}

/////////////////// CODE WRITTEN DURING THE COMPETITION FOLLOWS ////////////////////////////////

class splayTree {
  public:

  splayTree *left, *right, *up;
  int value;
  int count;
  int subtreeSize;

  splayTree() { this->left = this->right = this->up = NULL; this->count=1; }
  void updateSubtreeSize();
};

void splayTree::updateSubtreeSize() {
  this->subtreeSize=this->count; 
  if (this->left) this->subtreeSize += (this->left)->subtreeSize;
  if (this->right) this->subtreeSize += (this->right)->subtreeSize;
}

#define isLeftSon(t) ( ((t)->up) && (((t)->up)->left == (t)) )

void rotate(splayTree *t) {
  splayTree *p = t->up;
  if (!p) return;
  
  splayTree *g = p->up;
  int lp = isLeftSon(p);
  
  if (isLeftSon(t)) {
    splayTree *B = t->right;
    
    p->left = B;
    if (B) B->up = p;
    
    t->right = p;
    p->up = t;
    
    t->up = g;
    if (g) { if (lp) g->left = t; else g->right = t; }
  } else {
    splayTree *B = t->left;
    
    p->right = B;
    if (B) B->up = p;
    
    t->left = p;
    p->up = t;
    
    t->up = g;
    if (g) { if (lp) g->left = t; else g->right = t; }
  }
  p->updateSubtreeSize();
  t->updateSubtreeSize();
}

splayTree * splay(splayTree *t, int x) {
  splayTree *v = t;
  while (1) {
    if ((v->value) == x) break;
    if ((v->value) > x) {
      if (v->left) v=v->left; else break;
    } else {
      if (v->right) v=v->right; else break;
    }
  }
  // now bring v to the root
  while (1) {
    if (!(v->up)) break;
    if (!((v->up)->up)) { rotate(v); break; }
    splayTree *p = v->up;
    if (isLeftSon(v) == isLeftSon(p)) {
      rotate(p);
      rotate(v);
    } else {
      rotate(v);
//      rotate(p);
      rotate(v);
    }
  }
  return v;
}

splayTree * insert(splayTree *t, int x) {
  if (!t) {
    t = new splayTree();
    t->value = x;
    t->updateSubtreeSize();
    return t;
  }
  t = splay(t,x);
  if (t->value == x) { t->count++; return t; }
  splayTree *r = new splayTree();
  r->value = x;

  if (x < t->value) {
    r->right = t;
    t->up = r;
    
    r->left = t->left;
    if (t->left) (t->left)->up = r;

    t->left = NULL;
  } else {
    r->left = t;
    t->up = r;

    r->right = t->right;
    if (t->right) (t->right)->up = r;

    t->right = NULL;
  }
  t->updateSubtreeSize();
  r->updateSubtreeSize();
  return r;
}

splayTree * erase(splayTree *t, int x) {
  if (!t) return NULL;
  t = splay(t,x);
  if (!(t->value == x)) return t;
  if (t->count > 1) { t->count--; return t; }
  
  if (t->left) {
    splayTree *l = t->left;
    l->up = NULL;
    l = splay(l,x);
    
    splayTree *r = t->right;
    if (r) r->up = l;
    l->right = r;
    delete(t);
    l->updateSubtreeSize();
    return l;
  } else {
    splayTree *r = t->right;
    if (r) r->up = NULL;
    delete(t);
    return r;
  }
}
  
int main() {
  splayTree *A = NULL; 

  long long res = 0;
  
  long long p,q;
  scanf("%lld %lld ",&p,&q);
  int N;
  scanf("%d ",&N);
  REP(i,N) {
    int T;
    scanf("%d ",&T);
    A = insert(A,T);

    if (!(A->left)) continue;
    long long limit = T*q;
    limit /= p;

    splayTree *L = A->left;
    L->up = NULL;
    L = splay(L,int(limit));

    if (L->left) res += L->left->subtreeSize;
    if (L->value * p < T*q) res += L->count;
    
    L->up = A;
    A->left = L;
  }
  printf("%lld\n",res);
  return 0;
}

// vim: fdm=marker:commentstring=\ \"\ %s:nowrap:autoread
