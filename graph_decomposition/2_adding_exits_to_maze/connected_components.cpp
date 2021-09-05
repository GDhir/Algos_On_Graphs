#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

/* Algorithm to find number of connected components given a graph G: The algorithm
   marks all nodes as unexplored initially. As soon as a node is visited, it is 
   removed from the unexplored table. 

   The algorithm iteratively checks after the program stack is empty whether there 
   are any unexplored nodes remaining. If there are any nodes remaining, it adds them to 
   the program stack to explore the remaining graph component. It also updates the number of 
   components accordingly. */

using namespace std;
using std::vector;
using std::pair;

int number_of_components(vector< vector<int> > &adj) {
  int res = 0;
  //write your code here
  stack<int> stk;
  unordered_set<int> unexplored;

  for(int i = 0; i < adj.size(); i++) {
    unexplored.insert(i);
  }

  while( !unexplored.empty() ) {
    res += 1;
    stk.push(*unexplored.begin());
    while( !stk.empty() ) {

      auto val = stk.top();
      int idx = 0;

      while( idx < adj[val].size() ) {

        auto item = unexplored.find( adj[val][idx] );
        if( item != unexplored.end() ) {
          stk.push( adj[val][idx] );
          unexplored.erase( adj[val][idx] );
          break;
        }
        idx += 1;
      }

      if( idx == adj[val].size() ) {
        stk.pop();
        auto item = unexplored.find( val );
        if( item != unexplored.end() ) {
          unexplored.erase(val);
        }
      }
    }
  }

  return res;
}


int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
  return 0;
}
