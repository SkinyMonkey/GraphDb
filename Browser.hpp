#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/depth_first_search.hpp>

// TODO : create a list of QueryElements from the written query
//        call it from the examine_edge, examine_vertex

// TODO : do query language... 
template <class G>
class BFSGenericVisitor: public boost::default_bfs_visitor
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

    result = accumulate(query, (check, result) => {
      return result && check(vertex);
    }, true);

    if (result) {
      this->__vertex_results.push(vertex.id)
    }
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

//, const Visitor* vis)
template<class G>
void  bfs(G const* graph)
{
  BFSGenericVisitor<G> vis;

  // TODO : what if 0 does not exists?
  breadth_first_search(*graph, vertex(0, *graph), boost::visitor(vis));
}

/*
template <class Vertex, class G>>
class dfs_visitor {
	public:
		dfs_visitor() { }
		dfs_visitor(Visitors vis) : __visitors(vis) { }

		void initialize_vertex(G::vertex_descriptor u, const G& g) {
		}

		void start_vertex(G::vertex_descriptor u, const G& g) {
		}

		void discover_vertex(G::vertex_descriptor u, const G& g) {
		}

		void examine_edge(G::Edge_descriptor u, const G& g) {
		}

		void tree_edge(G::Edge_descriptor u, const G& g) {
		}

		void back_edge(G::Edge_descriptor u, const G& g) {
		}

		void forward_or_cross_edge(G::Edge_descriptor u, const G& g) {
		}

		void finish_edge(G::Edge_descriptor u, const G& g) {
		}

		void finish_vertex(G::vertex_descriptor u, const G& g) {
		}
}

template<class G>
void  dfs(G const* graph)
{
  DFSGenericVisitor<G> vis;

  depth_first_search(*graph, boost::visitor(vis));
}
*/
