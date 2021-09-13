#include <iostream>
#include <vector>


/* Given a weighted directed graph G, check whether the graph contains a negative cycle or not. 
  
  Approach: Perform V edge relaxations on the graph for the bellman ford algorithm. If on the
  Vth iteration, an edge is relaxed, this means that the graph contains a negative cycle.

  Relaxation Procedure:
  For each iteration, relax the edges by looping through the adjacency list adj. For each edge
  in the adjacency list, check whether the cost of the incoming edge and the previous vertex
  is less than the cost already stored in the dist[] array. If that is the case, update its 
  cost in the dist[] array. If a cost is updated on the Vth iteration, this means a cycle is
  present*/

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  //write your code here

  int nVertices = adj.size();

  vector<int> dist( nVertices, INT32_MAX );

  dist[0] = 0;
  int iter{1};

  while ( iter <= nVertices ) {

    for( int vertex = 0; vertex < nVertices; vertex++  ) {

      for( int edge = 0; edge < adj[vertex].size(); edge++ ) {

        if ( dist[vertex] != INT32_MAX ) {
          auto currDist = dist[vertex] + cost[vertex][edge];
          
          if( currDist < dist[ adj[vertex][edge] ] ) {

            dist[ adj[vertex][edge] ] = currDist;

            if( iter == nVertices ) 
              return 1;

          }
        }
        else {

          dist[vertex] = 0;

        }
      }
    }
    iter += 1;
  }


  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
