#ifndef ____GRAPH__
#define ____GRAPH__

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <ctime>

#include <iostream>

template<typename G>
class __Graph: public G
{
  public:
    bool			exists(Vertex::id const& id) const
    {
      // FIXME : there must be a better way
      for(auto vertices = boost::vertices(*this);
          vertices.first != vertices.second;
          ++vertices.first)
      {
        if ((*vertices.first) == id)
          return true;
      }
      return false;
    }

    bool      exists(Vertex::id const& src, Vertex::id const& dst) const
    {
      return boost::edge(src, dst, *this).second;
    }

    bool			exists(Edge::id const& id) const
    {
      return this->__edge_mapping.find(id) != this->__edge_mapping.end();
    }

    template<typename Target>
    bool			__exists_error(Target id, Protocol::error_code& error_code)
    {
      if (exists(id) == false)
      {
        error_code = Protocol::DOESNT_EXIST;
        return (false);
      }
      error_code = Protocol::OK;
      return (true);
    }

    template<typename Map>
    void      __update_map(Map const& src, Map& dst)
    {
      for (auto e : src)
        dst[e.first] = e.second;
    }

    Vertex::id		add(std::string const& vertex_name,
                      std::map<std::string, std::string> const& args)
    {
      typename G::vertex_descriptor id;


      id = boost::add_vertex(*this);
      (*this)[id].uid = id;

      if (vertex_name != "")
        (*this)[id].name = vertex_name;
      else
        (*this)[id].name = boost::lexical_cast<std::string>(id);

      this->vertex_attributes[id] = args;
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

      if (exists(from) == false
          || exists(to) == false)
      {
        error_code = Protocol::DOESNT_EXIST;
        return edge_id;
      }

      if (exists(edge_id) == true)
      { 
        error_code = Protocol::ALREADY_EXIST;
        return edge_id;
      }

      boost::tie(id, res) = boost::add_edge(from, to, (*this));

      if (res == false)
      {
        error_code = Protocol::CANT_ADD;
        return edge_id;
      }

      (*this)[id].name = edge_name;
      this->__edge_mapping[edge_id] = id;

      error_code = Protocol::OK;
      return edge_id;
    }

    bool      remove(Vertex::id const id, Protocol::error_code& error_code)
    {
      if (__exists_error(id, error_code) == false)
        return false;
      // FIXME : clear_vertex?
      boost::remove_vertex(id, *this);
      return true;
    }

    bool			remove(Edge::id const& id, Protocol::error_code& error_code)
    {
      if (__exists_error(id, error_code) == false)
        return false;
      boost::remove_edge(this->__edge_mapping[id], *this);
      return true;
    }

    Vertex::Vertex*	get(Vertex::id const id, Protocol::error_code& error_code)
    {
      if (__exists_error(id, error_code) == false)
        return NULL;
      return (&(*this)[id]);
    }

    Edge::Edge* get(Edge::id const& id, Protocol::error_code& error_code)
    {
      if (__exists_error(id, error_code) == false)
        return NULL;
      return (&(*this)[this->__edge_mapping[id]]);
    }

    unsigned long vertex_count(void) const
    {
      return num_vertices(*this);
    }

    unsigned long edges_count(void) const
    {
      return num_edges(*this);
    }

    typedef std::map<std::string, std::string>  attributes;

    std::map<Vertex::id, attributes>   vertex_attributes;
    std::map<Edge::id, attributes>   edge_attributes;
    attributes                graph_properties;

  private:
    std::map<Edge::id, typename G::edge_descriptor>	__edge_mapping;
};

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
  // FIXME : why not pure functions?
  // FIXME : log an error message if used.
  public:
    virtual std::string type_name() const {return "";}
    virtual bool			  exists(Vertex::id const) {return false;}
    virtual bool        exists(Vertex::id const&,
                               Vertex::id const&) const {return false;}

    virtual Vertex::id  add(std::string const&,
                            std::map<std::string, std::string> const&) {return 0;}
    virtual Edge::id		add(Vertex::id const&,
                            Vertex::id const&,
                            std::string const&,
                            Protocol::error_code&) {return 0;}

    virtual bool      remove(Vertex::id const,
                             Protocol::error_code&) {return false;}
    virtual bool			remove(Edge::id const&,
                             Protocol::error_code&) {return false;}

    virtual Vertex::Vertex*	get(Vertex::id const,
                                Protocol::error_code&) {return NULL;}
    virtual Edge::Edge* get(Edge::id const&, Protocol::error_code&) {return NULL;}

    // FIXME : update?

    virtual unsigned long vertex_count(void) const {return 0;}
    virtual unsigned long edges_count(void) const {return 0;}
    virtual std::string   dump(std::string const&, Protocol::error_code&) const{return "";}
};

// -------------------------------------------------------------------------------

template<typename G>
class Graph : public __Graph<G>, public RTTI<G>, public AGraph
{
  public:
  Graph()
    : __dumpers(new Manager<ADumper>("dumper"))
    {
      this->__dumpers->add("graphviz", new GraphvizDumper<Graph<G>>());
    }
    
  inline Vertex::id  add(std::string const& vertex_name,
                  std::map<std::string, std::string> const& args)
  {
    // FIXME : remove time 
    Vertex::id  res;
    const clock_t begin_time = clock();

    res = __Graph<G>::add(vertex_name, args);
    std::cout << "Elapsed time : " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << std::endl;
    return res;
  }

  inline Edge::id		add(Vertex::id const& from,
                            Vertex::id const& to,
                            std::string const& edge_name,
                            Protocol::error_code& error_code)
  {
    return __Graph<G>::add(from, to, edge_name, error_code);
  }
    
  inline bool      remove(Vertex::id const id, Protocol::error_code& error_code)
  {
    return __Graph<G>::remove(id, error_code);
  }
    
  inline bool			remove(Edge::id const& id, Protocol::error_code& error_code)
  {
    return __Graph<G>::remove(id, error_code);
  }
    
  inline Vertex::Vertex*	get(Vertex::id const id, Protocol::error_code& error_code)
  {
    return __Graph<G>::get(id, error_code);
  }
    
  inline Edge::Edge* get(Edge::id const& id, Protocol::error_code& error_code)
  {
    return __Graph<G>::get(id, error_code);
  }
    
  inline unsigned long vertex_count(void) const
  {
    return __Graph<G>::vertex_count();
  }
  
  inline unsigned long edges_count(void) const
  {
    return __Graph<G>::edges_count();
  }
    
  inline bool			exists(Vertex::id const& id) const
  {
    return __Graph<G>::exists(id);
  }
    
  inline bool      exists(Vertex::id const& src, Vertex::id const& dst) const
  {
    return __Graph<G>::exists(src, dst);
  }

  inline bool			exists(Edge::id const& id) const
  {
    return __Graph<G>::exists(id);   
  }

  std::string     dump(std::string const& dumpers_name,
                       Protocol::error_code& error_code) const
  {
    std::string   error_string("");

    // FIXME : reassmble in one function exists_or_error and get
    if (this->__dumpers->exists_or_error(dumpers_name, error_code, error_string) == false)
      return error_string;

    error_code = Protocol::OK;
    return this->__dumpers->get(dumpers_name)->dump(this, error_code);
  }

  std::string     type_name() const
    {
      return this->__type_name;
    }

  AManager<ADumper>*                 __dumpers;
//  AManager<ABatcher>*       __batchers; // FIXME : implement batchers
};

// FIXME : specialize on adjacency_matrix?

#endif /* ____GRAPH__ */
