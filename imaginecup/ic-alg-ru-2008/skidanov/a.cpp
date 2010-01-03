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

int n, m;

int main( )
{
	int i, j, k;

//	freopen( "in.txt", "r", stdin );

	scanf( "%d %d", &n, &m );

	string ans = "";
	int cur = n;
	int ost = 0;
	for( i = 0; i < 100; ++ i )
	{
		ans.pb( cur + '0' );
		cur = cur * m + ost;
		ost = cur / 10;
		cur -= ost * 10;
		if( cur == n && !ost ) break;
	}
	if( i == 100 || ans[ans.size( ) - 1] == '0' )
	{
		printf( "No solution\n" );
		return 0;
	}
	reverse( all( ans ) );
	printf( "%s\n", ans.c_str( ) );

	return 0;
}
