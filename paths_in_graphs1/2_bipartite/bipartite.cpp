#include <iostream>
#include <vector>
#include <queue>

/* Given an undirected graph G, check whether the graph is a bipartite or not. 
  
  Approach: Perform a BFS on the graph. Assign alternate colors to adjacent nodes
  such that each edge always is separated by alternate colored vertices. If it is not
  possible to segregate edges by alternate colored vertices, this means that the graph
  is not a bipartite.  
  
  To check the above, while processing the adjacent nodes of the vertex during BFS, check 
  whether the adjacent node is already colored or not. If it has already been colored with 
  the same color as current vertex, this means graph is not a bipartite. Otherwise, if the 
  all iterations complete successfully, this means that the graph is a bipartite. */

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {

  queue<int> bfsQueue;
  vector<int> colored( adj.size(), 0 );

  int idx{0};
  while ( idx < adj.size() ) {
    
    if( !colored[idx] ) {
    
      bfsQueue.push( idx );
      colored[idx] = 1;

      while ( !bfsQueue.empty() ) {
        auto val = bfsQueue.front();

        for (size_t i = 0; i < adj[val].size(); i++) {
          if( !colored[adj[val][i]] ) {
            colored[adj[val][i]] = (colored[val] == 1) ? 2 : 1;
            bfsQueue.push( adj[val][i] );
          }
          else if( colored[adj[val][i]] == colored[val] ) {
            return 0;
          }
        }

        bfsQueue.pop();
        
      }
    }
    idx += 1;
  }
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
