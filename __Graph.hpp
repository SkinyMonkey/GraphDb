#ifndef ____GRAPH__
#define ____GRAPH__

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

#include <iostream>

namespace GraphTools
{
  template<typename G>
    bool			exists(G& graph, Vertex::id const id)
    {
      for(auto vertices = boost::vertices(graph);
          vertices.first != vertices.second;
          ++vertices.first)
      {
        if ((*vertices.first) == id)
          return true;
      }
      return false;
    }

  template<typename G>
    bool      exists(G& graph, Vertex::id const src, Vertex::id const dst)
    {
      boost::edge(src, dst, graph).second;
    }

  template<typename G>
    bool			exists(G& graph, Edge::id const& id)
    {
      return graph.edge_mapping.find(id) != graph.edge_mapping.end();
    }

  template<typename G, typename Target>
    bool			exists_error(G& graph, Target id, Protocol::error_code& error_code)
    {
      if (exists(graph, id) == false)
      {
        error_code = Protocol::DOESNT_EXIST;
        return (false);
      }
      error_code = Protocol::OK;
      return (true);
    }

  template<typename G>
    void      fill_attributes(G& graph, std::vector<std::string> const& args)
    {
      ;
    }

  template<typename G>
    Vertex::id		add(G& graph,
        std::string const& vertex_name,
        std::vector<std::string> const& args)
    {
      typename G::vertex_descriptor id;

      id = boost::add_vertex(graph);
      graph[id].uid = id;

      if (vertex_name != "")
        graph[id].name = vertex_name;
      else
        graph[id].name = boost::lexical_cast<std::string>(id);

      // FIXME : finish
      // this->__fill_attributes(args, (*this)[id].attributes)

      return id;
    }

  template<typename G>
    Edge::id		add(G& graph,
        Vertex::id const& from,
        Vertex::id const& to,
        std::string const& edge_name,
        Protocol::error_code& error_code)
    {
      typename  G::edge_descriptor id;
      bool		  res;
      Edge::id 	edge_id(from, to, edge_name);

      if (exists(graph, from) == false
          || exists(graph, to) == false)
      {
        error_code = Protocol::DOESNT_EXIST;
        return edge_id;
      }

      if (exists(graph, edge_id) == true)
      { 
        error_code = Protocol::ALREADY_EXIST;
        return edge_id;
      }

      boost::tie(id, res) = boost::add_edge(from, to, graph);

      if (res == false)
      {
        error_code = Protocol::CANT_ADD;
        return edge_id;
      }

      graph[id].name = edge_name;
      graph.edge_mapping[edge_id] = id;

      error_code = Protocol::OK;
      return edge_id;
    }

  template<typename G>
    bool      remove(G& graph, Vertex::id const id, Protocol::error_code& error_code)
    {
      if (exists_error(graph, id, error_code) == false)
        return false;
      boost::remove_vertex(id, graph);
      return true;
    }

  template<typename G>
    bool			remove(G& graph, Edge::id const& id, Protocol::error_code& error_code)
    {
      if (exists_error(graph, id, error_code) == false)
        return false;
      boost::remove_edge(graph.edge_mapping[id], graph);
      return true;
    }

  template<typename G>
    Vertex::Vertex*	get(G& graph, Vertex::id const id, Protocol::error_code& error_code)
    {
      if (exists_error(graph, id, error_code) == false)
        return NULL;
      return (&graph[id]);
    }

  template<typename G>
    Edge::Edge*		get(G& graph, Edge::id const& id, Protocol::error_code& error_code)
    {
      if (exists_error(graph, id, error_code) == false)
        return NULL;
      return (&graph[graph.edge_mapping[id]]);
    }

  template<typename G>
    unsigned long vertex_count(G& graph)
    {
      num_vertices(graph);
    }

  template<typename G>
    unsigned long edges_count(G& graph)
    {
      num_edges(graph);
    }
}

// -------------------------------------------------------------------------------

template<typename G>
class RTTI
{
  public:
    RTTI()
      : __type_name(typeid(G).name())
    {
#ifdef DEBUG
      std::cout << this->__type_name << std::endl;
#endif
    }

  protected:
    std::string     __type_name;
};

class AGraph
{
  public:
    virtual std::string type_name() const = 0;
};

template<typename G>
class __Graph : public AGraph, public RTTI<G>, public G
{
  public:
    __Graph()
    {
    }

  std::map<Edge::id, typename G::edge_descriptor>	edge_mapping;
  
  std::string     type_name() const
    {
      return this->__type_name;
    }
};

#endif /* ____GRAPH__ */
