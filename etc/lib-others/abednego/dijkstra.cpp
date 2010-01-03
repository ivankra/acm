/**
 *   //////////////////////////////
 *   // DIJKSTRA'S SHORTEST PATH //
 *   //////////////////////////////
 *
 * This file is part of my library of algorithms found here:
 *      http://www.palmcommander.com:8081/tools/
 * LICENSE:
 *      http://www.palmcommander.com:8081/tools/index.html
 * Copyright (c) 2004
 * Contact author:
 *      igor at cs.ubc.ca
 **/
 
/*****************
 * Shortest Path * (Dijkstra's with a fast heap)
 *****************
 * Takes a directed graph where each edge has a weight and returns 
 * the shortest path from s to t. If you have thousands of vertices,
 * it is an easy modification to remove graph[][] and make adj[] a
 * one-dimensional array of dynamic arrays.
 *
 * PARAMETERS:
 *      - graph (global): adjacency matrix where graph[u][v] is the weight
 *          of the edge u->v.
 *      - deg (global): (out-)degree of each vertex
 *      - adj (global): adjacency list. For each u, adj[u][0..deg[u]) are
 *          the neighbours.
 *      - n: the number of vertices ([0, n-1] are considered as vertices).
 *      - s: source vertex.
 *      - t: sink.
 * RETURNS:
 *      - the length of the shortest path from s to t
 *      - prev[] contains the path predecessors
 * COMPLEXITY:
 *      - Fast. O(m * log(n)).
 * FIELD TESTING:
 *      - Valladolid 423: MPI Maelstrom
 *      - Valladolid 10594: Data flow (used as part of mcmf4.cpp)
 * #include <string.h>
 **/

#include <string.h>

#define NN 1024

int graph[NN][NN], adj[NN][NN], deg[NN];
int d[NN], q[NN], inq[NN], prev[NN], qs;

#define CLR( x, v ) memset( x, v, sizeof( x ) )
#define BUBL { \
    t = q[i]; q[i] = q[j]; q[j] = t; \
    t = inq[q[i]]; inq[q[i]] = inq[q[j]]; inq[q[j]] = t; }

int dijkstra( int n, int s, int t )
{
    CLR( d, 9 ); CLR( inq, -1 ); CLR( prev, -1 );
    d[s] = qs = 0;
    inq[q[qs++] = s] = 0;
    prev[s] = -2;
    
    while( qs )
    {
        // get the minimum from the q
        int u = q[0]; inq[u] = -1;
        
        // bubble down
        q[0] = q[--qs];
        if( qs ) inq[q[0]] = 0;
        for( int i = 0, j = 2*i + 1, t; j < qs; i = j, j = 2*i + 1 )
        {
            if( j + 1 < qs && d[q[j + 1]] < d[j] ) j++;
            if( d[q[j]] >= d[q[i]] ) break;
            BUBL;
        }
        
        // relax neighbours
        for( int k = 0, v = adj[u][k]; k < deg[u]; v = adj[u][++k] )
        {
            int newd = d[u] + graph[u][v];
            if( newd < d[v] )
            {
                d[v] = newd;
                prev[v] = u;
                if( inq[v] < 0 ) { inq[q[qs] = v] = qs; qs++; }
                
                // bubble up
                for( int i = inq[v], j = i/2, t; 
                     d[q[i]] < d[q[j]]; i = j, j = i/2 )
                     BUBL;
            }
        }
    }
    
    return d[t];
}

//------- TESTING --------
#include <stdio.h>
int main()
{
    int n, m;
    while( scanf( " %d %d\n", &n, &m ) == 2 )
    {
        memset( deg, 0, sizeof( deg ) );
        while( m-- )
        {
            int u, v, w;
            scanf( " %d %d %d", &u, &v, &w );
            graph[u][v] = graph[v][u] = w;
            adj[u][deg[u]++] = v;
            adj[v][deg[v]++] = u;
        }    
        
        int ans = dijkstra( n, 0, n - 1 );
        
        printf( "%d\n", ans );
    }
    return 0;
}
