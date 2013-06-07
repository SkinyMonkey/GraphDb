#ifndef __GRAPH__
#define __GRAPH__

#include <boost/graph/adjacency_list.hpp>
#include "vertex.hpp"
#include "edge.hpp"

// FIXME : how to set type with conf?
typedef boost::adjacency_list<boost::vecS
			     ,boost::vecS
			     ,boost::undirectedS
			     ,Vertex::Vertex
			     ,Edge::Edge>
			     Graph;

namespace	Edge
{
  typedef Graph::edge_descriptor	id;
}

namespace	Vertex
{
  typedef Graph::vertex_descriptor	id;
}

#endif /* __GRAPH__ */
