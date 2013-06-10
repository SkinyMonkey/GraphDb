#ifndef __GRAPH__
#define __GRAPH__

#include <boost/graph/adjacency_list.hpp>
#include <utility>
#include "vertex.hpp"
#include "edge.hpp"

// FIXME : how to set type with conf?
typedef boost::adjacency_list<boost::vecS
			     ,boost::vecS
			     ,boost::undirectedS
			     ,Vertex::Vertex
			     ,Edge::Edge>
			     Graph;

namespace	Vertex
{
  typedef Graph::vertex_descriptor	id;
}

namespace	Edge
{
  typedef Graph::edge_descriptor		rid;
  typedef std::pair<Vertex::id, Vertex::id>	id;
  
  std::map<id, rid> 		__translation;

  id		add(Vertex::id from, Vertex::id to, Graph& graph)
    {
      bool	res;
      rid	rid;
      id	id = std::make_pair(from, to);

      boost::tie(rid, res) = boost::add_edge(from, to, graph);
      __translation[id] = rid;
      return id;
    }

  // FIXME : add error code pointer
  // 		 enum for errors
  // 		 string array with message
  // 		 DOESNT_EXIST
  // 		 ALREADY_EXIST
  rid		get_rid(id edge)
    {
      return __translation[edge];
    }
}

#endif /* __GRAPH__ */
