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

const int maxn = 105;
const double eps = 1e-9;

bool eq( double a, double b ) { return a - b < eps && b - a < eps; };

int n, m, w, h;

struct v_t
{
	int x1, y1, x2, y2;
	int a, b, c;

	void moo( )
	{
		a = y1  -y2;
		b = x2  -x1;
		c = x1 * a + y1 * b;
	}
} lf, rg, bt, tp, v[maxn];

struct p_t
{
	double x, y;

	p_t( ) { };
	p_t( double _x, double _y ) { x = _x; y = _y; }
};

bool operator < ( const p_t & a, const p_t & b )
{
	if( !eq( a.x, b.x ) ) return a.x < b.x;
	return a.y < b.y - eps;
}

set< p_t > st;
int en = 0;

bool intersect( const v_t & a, const v_t & b, double & x, double & y )
{
	int d = a.a * b.b - b.a * a.b;
	if( !d ) return false;

	int d1 = a.c * b.b - b.c * a.b;
	int d2 = a.a * b.c - b.a * a.c;

	x = ( double ) d1 / d;
	y = ( double ) d2 / d;

	return true;
}

bool intersect2( const v_t & a, const v_t & b, double & x, double & y )
{
	int d = a.a * b.b - b.a * a.b;
	if( !d ) return false;

	int d1 = a.c * b.b - b.c * a.b;
	int d2 = a.a * b.c - b.a * a.c;

	x = ( double ) d1 / d;
	y = ( double ) d2 / d;

	if( ( b.x1 - x ) * ( x - b.x2 ) < - eps ) return false;
	if( ( b.y1 - y ) * ( y - b.y2 ) < - eps ) return false;

	return true;
}

bool intersect3( const v_t & a, const v_t & b, double & x, double & y )
{
	int d = a.a * b.b - b.a * a.b;
	if( !d ) return false;

	int d1 = a.c * b.b - b.c * a.b;
	int d2 = a.a * b.c - b.a * a.c;

	x = ( double ) d1 / d;
	y = ( double ) d2 / d;

	if( eq( b.x1, x ) && eq( b.y1, y ) ) return false;
	if( eq( b.x2, x ) && eq( b.y1, y ) ) return false;
	if( eq( b.x1, x ) && eq( b.y2, y ) ) return false;
	if( eq( b.x2, x ) && eq( b.y2, y ) ) return false;

	if( ( b.x1 - x ) * ( x - b.x2 ) < - eps ) return false;
	if( ( b.y1 - y ) * ( y - b.y2 ) < - eps ) return false;

	return true;
}

int main( )
{
	int i, j, k;
	double x, y;

//	freopen( "in.txt", "r", stdin );

	scanf( "%d %d %d", &w, &h, &n );

	n += 4;

	lf.x1 = lf.y1 = lf.x2 = 0; lf.y2 = h; lf.moo( );
	rg.x1 = rg.x2 = w; rg.y2 = h; rg.y1 = 0; rg.moo( );
	tp.x1 = tp.y1 = tp.y2 = 0; tp.x2 = w; tp.moo( );
	bt.y1 = bt.y2 = h; bt.x2 = w; bt.x1 = 0; bt.moo( );

	v[0] = lf;
	v[1] = rg;
	v[2] = tp;
	v[3] = bt;

	fi( n ) if( i >= 4 )
	{
		scanf( "%d %d %d %d", &v[i].x1, &v[i].y1, &v[i].x2, &v[i].y2 );
		v[i].moo( );
		if( !intersect2( v[i], lf, x, y ) && !intersect2( v[i], rg, x, y ) && !intersect2( v[i], bt, x, y ) && !intersect2( v[i], tp, x, y ) )
		{
			-- i;
			-- n;
			continue;
		}
		fj( i ) if( v[i].a * v[j].b == v[i].b * v[j].a && v[i].c == v[j].x1 * v[i].a + v[j].y1 * v[i].b )
		{
			-- i;
			-- n;
			break;
		}
	}

	en = n;
	fi( n )
	{
		set< p_t > cur;
		fj( i ) if( intersect( v[i], v[j], x, y ) )
		{
			if( x > eps && y > eps && x < w - eps && y < h - eps )
			{
				if( cur.find( p_t( x, y ) ) == cur.end( ) )
				{
					cur.insert( p_t( x, y ) );
					if( st.find( p_t( x, y ) ) == st.end( ) )
					{
						st.insert( p_t( x, y ) );
						++ en;
					}
					++ en;
				}
			}
			else if( intersect3( v[i], v[j], x, y ) && x > - eps && y > - eps && x < w + eps && y < h + eps && j < 4 && i >= 4 )
			{
				if( st.find( p_t( x, y ) ) == st.end( ) )
				{
					st.insert( p_t( x, y ) );
					++ en;
				}
			}
		}
	}

	int vn = st.size( ) + 4;
//	printf( "%d %d\n", en, vn );
	printf( "%d\n", en - vn + 1 );

	return 0;
}
