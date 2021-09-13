#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

long long distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {

  int nVertices = adj.size();

  using vecPairType = std::vector<std::pair<int, int>>;
  using pairType = std::pair<int, int>;

  auto cmp = []( pairType left, pairType right ) { return left.second > right.second; };

  vecPairType val;

  for ( int i = 0; i < nVertices; i++ ) {
    if ( i == s ) {
      val.push_back( std::make_pair(i, 0) );
    }
    else {
      val.push_back( std::make_pair(i, INT32_MAX) );
    }
  }

  std::priority_queue< pairType, vecPairType, decltype(cmp)> known( cmp, val );

  while( !known.empty() ) {

    auto minVal = known.top();
    known.pop();

    if( minVal.second == INT32_MAX )
      continue;

    for ( int idx = 0; idx < adj[ minVal.first ].size(); idx++ ) {

      auto dist = cost[minVal.first][idx] + minVal.second;

      if ( dist < val[ adj[minVal.first][idx] ].second ) {

          val[ adj[minVal.first][idx] ] = std::make_pair( adj[minVal.first][idx], dist );
          known.push( std::make_pair( adj[minVal.first][idx], dist ) );

      }
    }
  }
  
  for( int idx = 0; idx < val.size(); idx ++ ) {

    if( val[idx].first == t && val[idx].second != INT32_MAX ) {

      return val[idx].second;
    }

  }

  return -1;
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
