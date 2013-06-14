#ifndef __GRAPH__
#define __GRAPH__

#include "__Graph.hpp"

typedef __Graph<boost::adjacency_list<boost::vecS
	       ,boost::vecS
	       ,boost::undirectedS
	       ,Vertex::Vertex
	      ,Edge::Edge> > Graph;


#endif /* __GRAPH__ */
