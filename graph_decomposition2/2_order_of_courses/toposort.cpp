#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
/* Given a graph G and adjacency list adj, find the topological ordering of the graph
  
  Approach: The algorithm first marks all nodes as unused. It recursively calls dfs on 
  each child of the root node until it reaches a dead end. It puts the node in a stack 
  as soon as it reaches a dead end. */ 

using std::vector;
using std::pair;
using std::stack;

void dfs(vector<vector<int> > &adj, vector<int> &used, stack<int> &order, int x) {
  //write your code here
  int idx{0};

  // Recursively call DFS on each child of the root node
  while( idx < adj[x].size() ) {
    if( used[adj[x][idx]] == 0 ) {
      used[ adj[x][idx] ] = 1;
      dfs( adj, used, order, adj[x][idx] );
    }
    idx += 1;
  }

  // Once all child paths are processed, add the root to the sorted order
  order.push(x);
}     

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  stack<int> order;
  
  int idx{0};
  int x{0};

  while ( idx < used.size() ) {

    if( used[idx] == 0 ) {
      used[idx] = 1;
      dfs( adj, used, order, idx );
    }
    idx += 1;

  }

  vector <int> finalOrder;

  while( !order.empty() ) {
    finalOrder.push_back(order.top());
    order.pop();
  }

  return finalOrder;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
