#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

/*Given a directed graph G and adjacency list adj, find the number of storngly connected components.
  
  Approach: The algorithm first reverses the edges of the graph to do a post order traversal of the
  reversed graph. The post order traversal of the reversed graph is done with a stack. 
  The nodes are explored within the original graph in the descending order of their postorder in the
  reversed graph.  */

using std::vector;
using std::pair;
using std::stack;

void get_reversed_graph( const vector<vector<int>>& adj, vector<vector<int>>& adjR ) {

    for (size_t i = 0; i < adj.size(); i++) {
      for (size_t j = 0; j < adj[i].size(); j++) {
        adjR[adj[i][j]].push_back(i);
      }
    }
    
}

void dfs( const vector<vector<int>>& adjR, vector<int>& visited, stack<int>& postCount, int x ) {
  
  visited[x] = 1;

  int idx{0};
  while ( idx < adjR[x].size() ) {
    if( !visited[adjR[x][idx]] ) {
      dfs( adjR, visited, postCount, adjR[x][idx] );
    }
    idx += 1;
  }

  postCount.push(x);
  
}

void update_post_count( const vector<vector<int>>& adjR, stack<int>& postCount ) {

  vector<int> visited( adjR.size(), 0 );

  int idx{0};
  int postCountVal{0};
  while ( idx < adjR.size() )
  {
    if( !visited[idx] ) {
      dfs( adjR, visited, postCount, idx);
    }
    idx += 1;
  }
  
}

void explore( vector<vector<int>>& adj, vector<int>& visited, int x ) {

  visited[x] = 1;

  int idx{0};
  while ( idx < adj[x].size() )
  {
    if( !visited[adj[x][idx]] ) {
      explore( adj, visited, adj[x][idx] );
    }
    idx += 1;
  }
  
}

int number_of_strongly_connected_components(vector<vector<int> > adj) {
  int result = 0;
  
  vector<vector<int>> adjR( adj.size(), vector<int>() );
  get_reversed_graph( adj, adjR );

  stack<int> postCount;

  update_post_count(adjR, postCount);

  vector<int> visited( adj.size(), 0 );
  while ( !postCount.empty() ) {
    int topVal = postCount.top();

    if( !visited[topVal] ) {
      explore( adj, visited, topVal );
      result += 1;
    }

    postCount.pop();
  }
  

  return result;
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
  std::cout << number_of_strongly_connected_components(adj);
}
