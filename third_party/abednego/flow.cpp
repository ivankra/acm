/**
 *   //////////////////
 *   // MAXIMUM FLOW //
 *   //////////////////
 *
 * This file is part of my library of algorithms found here:
 *      http://www.palmcommander.com:8081/tools/
 * LICENSE:
 *      http://www.palmcommander.com:8081/tools/LICENSE.html
 * Copyright (c) 2004
 * Contact author:
 *      igor at cs.ubc.ca
 **/

/****************
 * Maximum flow * (Ford-Fulkerson on an adjacency matrix)
 ****************
 * Takes a weighted directed graph of edge capacities as an adjacency 
 * matrix 'cap' and returns the maximum flow from s to t.
 *
 * PARAMETERS:
 *      - cap (global): adjacency matrix where cap[u][v] is the capacity
 *          of the edge u->v. cap[u][v] is 0 for non-existent edges.
 *      - n: the number of vertices ([0, n-1] are considered as vertices).
 *      - s: source vertex.
 *      - t: sink.
 * RETURNS:
 *      - the flow
 *      - fnet contains the flow network. Careful: both fnet[u][v] and
 *          fnet[v][u] could be positive. Take the difference.
 *      - prev contains the minimum cut. If prev[v] == -1, then v is not
 *          reachable from s; otherwise, it is reachable.
 * DETAILS:
 * FIELD TESTING:
 *      - Valladolid 10330: Power Transmission
 *      - Valladolid 653:   Crimewave
 *      - Valladolid 753:   A Plug for UNIX
 *      - Valladolid 10511: Councilling
 *      - Valladolid 820:   Internet Bandwidth
 *      - Valladolid 10779: Collector's Problem
 * #include <string.h>
 * #include <queue>
 **/

#include <string.h>
#include <queue>

// the maximum number of vertices
#define NN 1024

// adjacency matrix (fill this up)
int cap[NN][NN];

// flow network
int fnet[NN][NN];

// BFS predecessor
int prev[NN];

int fordFulkerson( int n, int s, int t )
{
    // init the flow network
    memset( fnet, 0, sizeof( fnet ) );
    
    int flow = 0;
    
    while( true )
    {
        // find an augmenting path
        memset( prev, -1, sizeof( prev ) );
        queue< int > q;
        prev[s] = -2;
        q.push( s );
        while( !q.empty() && prev[t] == -1 )
        {
            int u = q.front();
            q.pop();
            
            for( int v = 0; v < n; v++ ) 
                if( prev[v] == -1 && fnet[u][v] - fnet[v][u] < cap[u][v] )
                    { prev[v] = u; q.push( v ); }
        }
        
        // see if we're done
        if( prev[t] == -1 ) break;
        
        // get the bottleneck capacity
        int bot = 0x7FFFFFFF;
        for( int v = t, u = prev[v]; u >= 0; v = u, u = prev[v] )
            bot <?= cap[u][v] - fnet[u][v] + fnet[v][u];
            
        // update the flow network
        for( int v = t, u = prev[v]; u >= 0; v = u, u = prev[v] )
            fnet[u][v] += bot;
            
        flow += bot;
    }
    
    return flow;
}

//----------------- EXAMPLE USAGE -----------------
int main()
{
    memset( cap, 0, sizeof( cap ) );
    int numVertices = 100;
    
    // ... fill up cap with existing edges.
    // if the edge u->v has capacity 6, set cap[u][v] = 6.        
    
    cout << fordFulkerson( numVertices, s, t ) << endl;
    
    return 0;
}
