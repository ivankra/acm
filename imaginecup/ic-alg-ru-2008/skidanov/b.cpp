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

const int maxn = 2005;

int n, m;
int a[maxn];
int d[maxn][maxn * 2];

int main( )
{
	int i, j, k;

//	freopen( "in.txt", "r", stdin );

	scanf( "%d", &n );
	++ n;
	fi( n )
	{
		scanf( "%d", &a[i] );
		a[i] += maxn;
	}

	memset( d, 0x7F, sizeof( d ) );
	d[0][a[0]] = 0;

	fi( n - 1 ) fj( maxn * 2 ) if( d[i][j] != 0x7F7F )
	{
		d[i + 1][j] = min( d[i + 1][j], d[i][j] + abs( j - a[i + 1] ) );
		if( j + 1 < maxn * 2 - 1 ) d[i + 1][j + 1] = min( d[i + 1][j + 1], d[i][j] + abs( j + 1 - a[i + 1] ) );
		if( j - 1 >= 0 ) d[i + 1][j - 1] = min( d[i + 1][j - 1], d[i][j] + abs( j - 1 - a[i + 1] ) );
	}

	printf( "%d\n", d[n - 1][a[n - 1]] );
	vector< int > ans;
	j = a[n - 1];
	i = n - 1;
	while( 1 )
	{
		ans.pb( j - maxn );
		if( !i ) break;
		if( d[i - 1][j] == d[i][j] - abs( j - a[i] ) ) ;
		else if( j < maxn * 2 - 1 && d[i - 1][j + 1] == d[i][j] - abs( j - a[i] ) ) ++ j;
		else if( j > 0 && d[i - 1][j - 1] == d[i][j] - abs( j - a[i] ) ) -- j;
		-- i;
	}
	reverse( all( ans ) );
	fi( ans.size( ) ) printf( "%d%c", ans[i], " \n"[i == ans.size( ) - 1] );

	return 0;
}
