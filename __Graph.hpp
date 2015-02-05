#ifndef ____GRAPH__
#define ____GRAPH__

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

class AGraph
{
};

template<typename G>
class __Graph : public AGraph, public G
{
  public:
    __Graph()
    {
    }

    Vertex::id		add(std::string const& vertex_name,
                      std::vector<std::string> const& args)
    {
      typename G::vertex_descriptor id;

      id = boost::add_vertex(*this);
      (*this)[id].uid = id;

      if (vertex_name != "")
        (*this)[id].name = vertex_name;
      else
        (*this)[id].name = boost::lexical_cast<std::string>(id);

      // FIXME : finish
      // this->__fill_attributes(args, (*this)[id].attributes)
      
      return id;
    }

    Edge::id		add(Vertex::id const& from,
                    Vertex::id const& to,
                    std::string const& edge_name,
                    Protocol::error_code& error_code)
    {
      typename  G::edge_descriptor id;
      bool		  res;
      Edge::id 	edge_id(from, to, edge_name);

      if (this->__exists(from) == false
          || this->__exists(to) == false)
      {
        error_code = Protocol::DOESNT_EXIST;
        return edge_id;
      }

      if (this->__exists(edge_id) == true)
      { 
        error_code = Protocol::ALREADY_EXIST;
        return edge_id;
      }

      boost::tie(id, res) = boost::add_edge(from, to, *this);

      if (res == false)
      {
        error_code = Protocol::CANT_ADD;
        return edge_id;
      }

      // FIXME : create, fill, add
      (*this)[id].name = edge_name;
      error_code = Protocol::OK;
      this->__edge_mapping[edge_id] = id;
      return edge_id;
    }

    bool      remove(Vertex::id const id, Protocol::error_code& error_code)
    {
      if (this->__exists_error(id, error_code) == false)
        return false;
      boost::remove_vertex(id, *this);
      return true;
    }

    bool			remove(Edge::id const& id, Protocol::error_code& error_code)
    {
      if (this->__exists_error(id, error_code) == false)
        return false;
      boost::remove_edge(this->__edge_mapping[id], *this);
      return true;
    }

    Vertex::Vertex*	get(Vertex::id const id, Protocol::error_code& error_code)
    {
      if (this->__exists_error(id, error_code) == false)
        return NULL;
      return (&(*this)[id]);
    }

    Edge::Edge*		get(Edge::id const& id, Protocol::error_code& error_code)
    {
      if (this->__exists_error(id, error_code) == false)
        return NULL;
      return (&(*this)[this->__edge_mapping[id]]);
    }

    unsigned long vertex_count() const
    {
      num_vertices(*this);
    }

    unsigned long edges_count() const
    {
      num_edges(*this);
    }

  private:
    template<typename Target>
      bool			__exists_error(Target id, Protocol::error_code& error_code) const
      {
        if (this->__exists(id) == false)
        {
          error_code = Protocol::DOESNT_EXIST;
          return (false);
        }
        error_code = Protocol::OK;
        return (true);
      }

    bool			__exists(Vertex::id const id) const
    {
      for(auto vertices = boost::vertices(*this);
          vertices.first != vertices.second;
          ++vertices.first)
      {
        if ((*vertices.first) == id)
          return true;
      }
      return false;
    }

    bool      __exists(Vertex::id const src, Vertex::id const dst) const
    {
      boost::edge(src, dst, *this).second;
    }

    bool			__exists(Edge::id const& id) const
    {
      return this->__edge_mapping.find(id) != this->__edge_mapping.end();
    }

    void      __fill_attributes(std::vector<std::string> const& args) const
    {
      ;
    }

    std::map<Edge::id, typename G::edge_descriptor>	__edge_mapping;
};

#endif /* ____GRAPH__ */
