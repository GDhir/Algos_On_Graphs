#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>

/* Given a directed graph G and an adjacency list adj, find whether the graph contains a cycle.

  Approach: Given a directed graph, mark all elements as unexplored initially. Start with the
  first unexplored node and add it to the stack. Also add it to the currStk hash table. 
  
  This is needed to provide O(1) complexity to find whether the neighbour being explored has already been 
  added to the stack. If the neighbour being explored is already in the stack, this means that 
  it is possible to reach the neighbour from the current node and it is also possible to reach the 
  current node from the neighbour since the neighbour is already in the stack. 
  
  If the above scenario happens, this means that there is a cycle in the graph from the current node
  to the neighbour. */

using namespace std;
using std::vector;
using std::pair;

int acyclic(vector<vector<int> > &adj) {
  // Algorithm to check whether there is a cycle in the graph or not

  stack<int> stk;
  unordered_set<int> currStk;
  unordered_set<int> unexplored;

  for(int i = 0; i < adj.size(); i++) {
    unexplored.insert(i);
  }

  while( !unexplored.empty() ) {
    stk.push( *unexplored.begin() );
    currStk.insert( *unexplored.begin() );
    while(!stk.empty()) {

      auto topElem = stk.top();

      int nIdx = 0;
      
      while( nIdx < adj[topElem].size() ) {

        auto it = unexplored.find(adj[topElem][nIdx]); // Find whether the neighbour has already been explored or not

        if( it == unexplored.end() ) {
          /* If the neighbour has already been explored and the neighbour is also in the stack, 
          this means that there is a cycle in the graph */

          if( currStk.find( adj[topElem][nIdx] ) != currStk.end() ) {
              return 1;
          }
          nIdx += 1;
          it = unexplored.find(adj[topElem][nIdx]);
        }
        else {

          /* If the neighbour has not been explored, add it to the stack 
          and remove it from the unexplored hash table */
          stk.push( *it );
          currStk.insert( *it );
          unexplored.erase( *it );
          break;
        }

      } 

      if ( nIdx == adj[topElem].size() ) {
        /* If all neighbours have been explored, remove the element from the stack and 
        from the currStk hash table */
        currStk.erase(topElem);
        stk.pop();
        auto val = unexplored.find(topElem);
        if ( val != unexplored.end() ) {
          unexplored.erase(topElem);
        }
      }
    }
  }


  return 0;
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
  std::cout << acyclic(adj);
  return 0;
}
