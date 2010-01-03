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

	int a[3];

	scanf( "%d %d %d", &a[0], &a[1], &a[2] );
	sort( a, a + 3 );

	if( a[2] > a[0] + a[1] ) printf( "IMPOSSIBLE\n" );
	else if( a[2] == a[0] + a[1] ) printf( "SINGULAR\n" );
	else if( a[2] * a[2] > a[0] * a[0] + a[1] * a[1] ) printf( "OBTUSE\n" );
	else if( a[2] * a[2] == a[0] * a[0] + a[1] * a[1] ) printf( "RIGHT\n" );
	else if( a[2] * a[2] < a[0] * a[0] + a[1] * a[1] ) printf( "ACUTE\n" );
	else assert( 0 );

	return 0;
}
