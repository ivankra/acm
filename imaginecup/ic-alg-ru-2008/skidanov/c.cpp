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

const int maxn = 100005;
const int maxt = 262144;
const int rright = 131072;

int n, m;
int a[maxn];
int t[maxt];

bool addt( int id, int l, int r, int val )
{
	if( val >= r ) return false;
	if( t[id] == r - l ) return false;
	if( r - l > 1 )
	{
		int e = ( l + r ) / 2;
		if( !addt( id * 2, l, e, val ) )
			if( !addt( id * 2 + 1, e, r, val ) ) return false;
	}
	++ t[id];
	return true;
}

int gett( int id, int l, int r, int val )
{
	if( val <= l ) return t[id];
	else if( val >= r ) return 0;

	int e = ( l + r ) / 2;
	return gett( id * 2, l, e, val ) + gett( id * 2 + 1, e, r, val );
}

int main( )
{
	int i, j, k;

//	freopen( "in.txt", "r", stdin );

	scanf( "%d", &n );
	fi( n )
	{
		scanf( "%d", &a[i] );
		-- a[i];
	}

	int ret = 0;
	fi( n )
	{
		if( gett( 1, 0, rright, a[i] ) == n - a[i] ) continue;
		++ ret;
		addt( 1, 0, rright, a[i] );
	}

	printf( "%d\n", n - ret );

	return 0;
}
