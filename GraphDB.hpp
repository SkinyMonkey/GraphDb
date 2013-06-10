#ifndef __GRAPHDB__
#define __GRAPHDB__

#include "Graph.hpp"
// FIXME:
#include "debug.hpp"

class GraphDB : public IGraphDB
{
public:
	GraphDB()
	  : IGraphDB(), __current(0x0)
	  {
	    this->add("default");
	    this->use("default");
	  }
	~GraphDB()
	  {}

	bool		use(std::string const& graph_name)
	  {
	    bool res = this->__exists(graph_name);

	    if (res)
	      this->__current = this->__graphs[graph_name];
	    return (res);
	  }

	bool		add(std::string const& graph_name)
	  {
	    bool res = this->__exists(graph_name);

	    // FIXME : catch bad_alloc?
	    if (res == false)
	      this->__graphs[graph_name] = new Graph();
	    return (res == false);
	  }
	
    	Edge::id	add(Vertex::id from, Vertex::id to)
	  {
	    return (Edge::add(from, to, (*this->__current)));
	  }

	Vertex::id	add(void)
	  {
	    Vertex::id	id = boost::add_vertex(*this->__current);
	    // FIXME : set vertex attributes
	    // *this->__current[id]
	    return (id);
	  }

	bool	remove(std::string const& graph_name)
	  {
	    bool res = this->__exists(graph_name);

	    if (res)
	      this->__graphs.erase(graph_name);
	    return (res);
	  }

	bool	remove(Edge::id id)
	  {
	    // FIXME : no return value?
	    boost::remove_edge(Edge::get_rid(id), *this->__current);
	    return (true);
	  }

	bool	remove(Vertex::id id)
	  {
	    // FIXME : no return value?
	    boost::remove_vertex(id, *this->__current);
	    return (true);
	  }

	Graph*		get(std::string const& graph_name)
	  {
	    bool res = this->__exists(graph_name);

	    if (res == true)
	      return (this->__graphs[graph_name]);
	    return (0x0);
	  }

	Vertex::Vertex*	get(Vertex::id id) const
	  {
	    // FIXME : check si le vertex existe?
	    return &((*this->__current)[id]);
	  }

	Edge::Edge*	get(Edge::id id) const
	  {
	    // FIXME : check si l'edge existe?
	    return &((*this->__current)[Edge::get_rid(id)]);
	  }

	/*
	**
	// FIXME : test	
	template<typename T>
	T*		get(T::id) const
	  {
	    return &this->__current[id];
	  }

	// specialize?
	*/

private:
	GraphDB(const GraphDB&);
	GraphDB& operator=(const GraphDB&);

	bool	__exists(std::string const& graph_name) const
	  {
	    return this->__graphs.find(graph_name) != this->__graphs.end();
	  }

	Graph*				__current;
	std::map<std::string, Graph*>	__graphs;
};


#endif /* __GRAPHDB__ */
