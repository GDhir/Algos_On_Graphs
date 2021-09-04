#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;
using std::vector;
using std::pair;


int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here

  stack<int> stk;
  unordered_set<int> visited;

  stk.push(x);

  while( !stk.empty() ) {

    auto val = stk.top();
    stk.pop();
    visited.insert(val);

    for( auto& item: adj[val] ) {

      if ( item == y ) {

        return 1;

      }
      else {

        if( visited.find(item) == visited.end() ) {

          stk.push(item);

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
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
