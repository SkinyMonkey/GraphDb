#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/depth_first_search.hpp>

template <class G>
class TestVisitor: public boost::default_bfs_visitor
{
public:
  void initialize_vertex(const typename G::vertex_descriptor &s, const G &g) const 
  {
    std::cout << "Initialize: " << s << std::endl;
  }
/*
  void discover_vertex(const G::vertex_descriptor &s, const G &g) const {
    std::cout << "Discover: " << g[s] << std::endl;
  }

  void examine_vertex(const G::vertex_descriptor &s, const G &g) const {
    std::cout << "Examine vertex: " << g[s] << std::endl;
  }

  void examine_edge(const G::edge_descriptor &e, const G &g) const {
    std::cout << "Examine edge: " << g[e] << std::endl;
  }

  void tree_edge(const G::edge_descriptor &e, const G &g) const {
    std::cout << "Tree edge: " << g[e] << std::endl;
  }

  void non_tree_edge(const G::edge_descriptor &e, const G &g) const {
    std::cout << "Non-Tree edge: " << g[e] << std::endl;
  }

  void gray_target(const G::edge_descriptor &e, const G &g) const {
    std::cout << "Gray target: " << g[e] << std::endl;
  }

  void black_target(const G::edge_descriptor &e, const G &g) const {
    std::cout << "Black target: " << g[e] << std::endl;
  }

  void finish_vertex(const G::vertex_descriptor &s, const G &g) const {
    std::cout << "Finish vertex: " << g[s] << std::endl;
  }
*/
};

void  bfs(Graph const* graph)//, const Visitor* vis)
{
  TestVisitor<Graph> vis;

  breadth_first_search(*graph, vertex(0, *graph), boost::visitor(vis));
}

void  dfs(Graph const* graph)
{
  TestVisitor<Graph> vis;

  depth_first_search(*graph, boost::visitor(vis));
}
