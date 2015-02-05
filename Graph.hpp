#ifndef __GRAPH__
#define __GRAPH__

#include "__Graph.hpp"

// FIXME : cog to generate different types
//         mother class to contain in hash table an instance of each?

typedef __Graph<boost::adjacency_list<boost::vecS
	       ,boost::vecS
	       ,boost::undirectedS
	       ,Vertex::Vertex
	      ,Edge::Edge> > Graph;


std::map<std::string, AGraph*>  graph_types;

void  init_graph_types(void)
{
// The following python code generates each specialisation possibility

/* [[[cog
import cog
  
for graph_type in ("adjacency_list",):
   for direction in ("undirectedS", "directedS", "bidirectionalS"):
       for out_edge_list in ("vecS", "listS"):
           for vertex_list in ("vecS", "listS"):
               cog.outl("""
    graph_types["{}_{}_{}_{}"] = new __Graph<boost::{}<boost::{}
	                                          ,boost::{}
	                                          ,boost::{}
	                                          ,Vertex::Vertex
	                                          ,Edge::Edge> >();
""".format(graph_type, direction, out_edge_list, vertex_list,
                                  graph_type, direction, out_edge_list, vertex_list))
]]]*/
//[[[end]]]

   // graph_types["adjacency_matrix"] = new __Graph<boost::adjacency_matrix<boost::undirectedS, Vertex::Vertex, Edge::Edge>>();
}

#endif /* __GRAPH__ */
