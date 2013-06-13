#ifndef __GRAPH__
#define __GRAPH__

#include <boost/graph/graphviz.hpp>
#include <ostream>

template<typename G>
class Graph : public AGraph, public G
{
public:
  typedef typename G::adjacency_iterator	adjacency_iterator;
  Graph()
    : __vertex_count(0)
  {
      this->__dumpers["graphviz"] = &Graph::__graphviz;
  }

  Vertex::id		add(void)
    {
      this->__vertex_mapping[++this->__vertex_count] = boost::add_vertex(*this);
      (*this)[this->__vertex_mapping[this->__vertex_count]].uid = this->__vertex_count;
      return this->__vertex_count;
    }

  Edge::id		add(Vertex::id const from, Vertex::id const to, Protocol::error_code* error_code)
    {
      bool		res;
      typename G::edge_descriptor id;
      Edge::id edge_id = std::make_pair(from, to);

      if (this->__exists(from) == false
	|| this->__exists(to) == false)
	{
	  *error_code = Protocol::DOESNT_EXIST;
	  return edge_id;
	}
      if (this->__exists(edge_id) == true)
	{ 
	  *error_code = Protocol::ALREADY_EXIST;
	  return edge_id;
	}

      boost::tie(id, res) = boost::add_edge(\
			    this->__vertex_mapping[from],
			    this->__vertex_mapping[to], *this);
      if (res == false)
	{
	  *error_code = Protocol::CANT_ADD;
	  return edge_id;
	}
      *error_code = Protocol::OK;
      this->__edge_mapping[edge_id] = id;
      return edge_id;
    }

  void			remove(Vertex::id const id, Protocol::error_code* error_code)
    {
      if (this->__exists_error(id, error_code) == false)
	return;
      boost::remove_vertex(this->__vertex_mapping[id], *this);
      this->__vertex_mapping.erase(id);
    }

  void			remove(Edge::id const& id, Protocol::error_code* error_code)
    {
      if (this->__exists_error(id, error_code) == false)
	return;
      boost::remove_edge(this->__edge_mapping[id], *this);
    }

  Vertex::Vertex*	get(Vertex::id const id, Protocol::error_code* error_code)
    {
      if (this->__exists_error(id, error_code) == false)
	return NULL;
      return (&(*this)[this->__vertex_mapping[id]]);
    }

  Edge::Edge*		get(Edge::id const& id, Protocol::error_code* error_code)
    {
      if (this->__exists_error(id, error_code) == false)
	return NULL;
      return (&(*this)[this->__edge_mapping[id]]);
    }

  std::string		dump(std::string const& name, Protocol::error_code* error_code)
    {
//      if (this->__exists_error(name, error_code) == false)
//	return std::string("");
//      return (this->*this->__dumpers[name])();
      *error_code = Protocol::OK;
      return this->__graphviz();
    }

private:
  template<typename Target>
  bool			__exists_error(Target id, Protocol::error_code* error_code) const
    {
      if (this->__exists(id) == false)
	{
	  *error_code = Protocol::DOESNT_EXIST;
	  return (false);
	}
      *error_code = Protocol::OK;
      return (true);
    }

  bool			__exists(Vertex::id const id) const
    {
      return this->__vertex_mapping.find(id) != this->__vertex_mapping.end();
    }
  
  bool			__exists(Edge::id const& id) const
    {
      return this->__edge_mapping.find(id) != this->__edge_mapping.end();
    }

  bool			__exists(std::string const& name) const
    {
      return this->__dumpers.find(name) != this->__dumpers.end();
    }

  std::string		__graphviz(void)
    {
      std::ostringstream out;

      boost::write_graphviz(out, *this,
			    boost::make_label_writer(
			    boost::get(&Vertex::Vertex::uid, *this)));
      return (out.str());
    }

  Vertex::id							__vertex_count;
  std::map<std::string, std::string (Graph::*)(void)>		__dumpers;
  std::map<Vertex::id, typename G::vertex_descriptor>		__vertex_mapping;
  std::map<Edge::id, typename G::edge_descriptor>		__edge_mapping;
};

#endif /* __GRAPH__ */
