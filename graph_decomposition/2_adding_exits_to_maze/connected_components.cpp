#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;
using std::vector;
using std::pair;

int number_of_components(vector< vector<int> > &adj) {
  int res = 0;
  //write your code here
  stack<int> stk;
  unordered_set<int> visited;

  unordered_set<int> unexplored;

  for(int i = 0; i < adj.size(); i++) {
    unexplored.insert(i);
  }

  while( !unexplored.empty() ) {
    res += 1;
    stk.push(*unexplored.begin());

    while( !stk.empty() ) {

      auto val = stk.top();
      stk.pop();
      visited.insert(val);

      for( auto& item: adj[val] ) {

        if( visited.find(item) == visited.end() ) {

          stk.push(item);

        }
      }
      unexplored.erase(val);
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
