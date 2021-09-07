#include <iostream>
#include <vector>
#include <queue>

/* Given an undirected graph, find the shortest distance between two nodes in the
  graph. 

  Approach: The algorithm uses a queue to store the adjacent nodes with their distance 
  stored in a pair from the original node. At each iteration, the node is popped from the queue
  and all of its adjacent nodes are added to the queue at the next level. As soon as the other node
  is reached, the distance is returned. */

using std::pair;
using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {

  queue<pair<int, int>> bfsQueue;
  bfsQueue.push( std::make_pair( s, 0 ) );
  vector<int> visited( adj.size(), 0 );

  while ( !bfsQueue.empty() ) {

    auto val = bfsQueue.front();
    visited[val.first] = 1;

    int idx{0};
    while ( idx < adj[val.first].size() ) {
      if ( adj[val.first][idx] == t ){
        return val.second + 1;
      }

      if ( !visited[adj[val.first][idx]] ) {
        bfsQueue.push( std::make_pair( adj[val.first][idx], val.second + 1 ) );
      }
      idx += 1;
    }
    
    bfsQueue.pop();

  }

  return -1;
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
