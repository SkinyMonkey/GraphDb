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
	    ;
	  }
	~GraphDB()
	  {}

	bool		create(std::string const& graph_name)
	  {
	    // FIXME : catch bad_alloc?
	    this->__graphs[graph_name] = new Graph();
	    return (true);
	  }
	
	bool		use(std::string const& graph_name)
	  {
	    bool res = this->__exists(graph_name);

	    if (res)
	      this->__current = this->__graphs[graph_name];
	    return (res);
	  }

	Edge::id	add(Vertex::id from, Vertex::id to)
	  {
	    bool	res;
	    Edge::id	id;

	    boost::tie(id, res)\
	      =	boost::add_edge(from
			       ,to
			       ,(*this->__current));
	    // if !res FIXME
	    return id;
	  }

	Vertex::id	add(void)
	  {
	    Vertex::id	id = boost::add_vertex(*this->__current);
	    // FIXME : set vertex attributes
	    // *this->__current[id]
	    return id;
	  }

	bool	remove(Edge::id id)
	  {
	    boost::remove_edge(id, *this->__current);
	    return (true);
	  }

	bool	remove(Vertex::id id)
	  {
	    boost::remove_vertex(id, *this->__current);
	    return (true);
	  }

	Vertex::Vertex*	get(Vertex::id id) const
	  {
	    return &((*this->__current)[id]);
	  }

	Edge::Edge*	get(Edge::id id) const
	  {
	    return &((*this->__current)[id]);
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
