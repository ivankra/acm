#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>

#include <math.h>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>
#include <map>

#define fo(a,b,c) for( a = ( b ); a < ( c ); ++ a )
#define fr(a,b) fo( a, 0, ( b ) )
#define fi(a) fr( i, ( a ) )
#define fj(a) fr( j, ( a ) )
#define fk(a) fr( k, ( a ) )
#define pb push_back
#define mp make_pair
#define all(v) (v).begin( ), (v).end( )

using namespace std;

const int maxn = 1005;

int n, m;
char f[maxn][maxn];
int l[maxn][maxn];

int st[maxn];
int stx[maxn];
int stn;

int main( )
{
	int i, j, k;

//	freopen( "in.txt", "r", stdin );

	scanf( "%d %d", &m, &n );

	fi( n ) scanf( "%s", &f[i] );

	fi( n ) fj( m ) if( f[i][j] == '1' )
	{
		l[i][j] = 1;
		if( i ) l[i][j] += l[i - 1][j];
	} else l[i][j] = 0;

	int ans = 0;
	fi( n )
	{
		stn = 0;
		fj( m + 1 )
		{
			int nx = j;
			while( stn && st[stn - 1] >= l[i][j] )
			{
				int cur = ( j - stx[stn - 1] ) * st[stn - 1];
				if( cur > ans ) ans = cur;
				nx = stx[stn - 1];
				-- stn;
			}
			st[stn] = l[i][j];
			stx[stn] = nx;
			++ stn;
		}
	}

	printf( "%d\n", ans );

	return 0;
}
