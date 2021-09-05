#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

/*  Given a graph G with adjacency list adj, find whether two nodes 
    x and y are reachable in the graph. The algorithms uses Depth first
    search to find y starting from x as the root node. Iterative 
    implementation is developed with a stack which stores the unexplored nodes

    Once a node is visited, it is added into the visited hash table to provide 
    O(1) access while searching whether a node is visited or not. The algorithm
    searches for the first unvisited node given a root node and adds it into the stack
    for further exploration*/


using namespace std;
using std::vector;
using std::pair;


int reach(vector< vector<int> > &adj, int x, int y) {
  //Algorithm to search whether a node is reachable or not

  stack<int> stk;
  unordered_set<int> visited;

  stk.push(x);

  while( !stk.empty() ) {

    auto val = stk.top();
    stk.pop();
    visited.insert(val);

    int idx = 0;

    while( idx < adj[val].size() ) {

      if( adj[val][idx] == y ) {
        return 1;
      }
      else {
        auto item = visited.find( adj[val][idx] );
        if( item == visited.end() ) {
          stk.push(adj[val][idx]);
          break;
        }
      }
      idx += 1;
    }
  }
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>()); // Adjacency list given a graph
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
  return 0;
}
