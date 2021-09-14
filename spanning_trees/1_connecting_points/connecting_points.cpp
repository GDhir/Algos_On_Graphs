#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

/*Given n vertices, find the minimum spanning tree connecting all the vertices 

Approach: First find the weights of all the edges in the graph and
store them in sorted order. Loop over each one of the edges and identify
the edge which has the least weight and does not form a cycle. For cycle detection,
use the union find algorithm. 

Union can be done by finding the parent vertices
of the two vertices connecting the edge and then setting the parent of one of them as
the other one. To find the parent, simply try to search for a node whose root node
is equal to itself*/


using std::vector;

int getParent( int, vector<int>& );

void unionize( int first, int second, vector<int>& root ) {

  int firstRoot = getParent( first, root );
  int secondRoot = getParent( second, root );

  root[firstRoot] = secondRoot; 

}

int getParent( int val, vector<int>& root ) {

  int idx = val;

  while( root[idx] != idx ) {

    idx = root[idx];

  }

  return idx;

}


double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;

  vector< std::tuple< double, int, int > > edges;
  int nVertices = x.size();

  for( int i = 0; i < nVertices; i++ ) {
    for( int j = i + 1; j < nVertices; j++ ) {

      auto dist = sqrt( pow( x[i] - x[j], 2 ) + pow( y[i] - y[j], 2 ) );

      edges.push_back( std::make_tuple(dist, i, j) );
    }
  } 

  auto cmp = []( std::tuple< double, int, int > left, std::tuple< double, int, int > right ) {
    return std::get<0>( left ) < std::get<0>( right );
  };

  std::sort( edges.begin(), edges.end(), cmp );

  std::vector<int> root;

  for( int i = 0; i < nVertices; i++ ) {
    root.push_back(i);
  }

  for( auto it = edges.begin(); it != edges.end(); it++ ) {

    auto val = *it;

    auto parentFirst = getParent( std::get<1>( val ), root );
    auto parentSecond = getParent( std::get<2>( val ), root );

    if( parentFirst != parentSecond ) {

      unionize( parentFirst, parentSecond, root );
      result += std::get<0>( val );
    }
  }
  //write your code here
  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
