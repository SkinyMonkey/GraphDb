#ifndef __GRAPHDB__
#define __GRAPHDB__

#include "AProtocol.hpp"
#include "Graph.hpp"

class GraphDB : public IGraphDB
{
public:
	GraphDB()
	  : IGraphDB(), __current(0x0)
	  {
	    error_code	error_code;
	    this->add("default", &error_code);
	    this->use("default", &error_code);
	  }
	~GraphDB()
	  {}

	void	 	use(std::string const& graph_name, error_code* code)
	  {
	    if (this->__exists(graph_name) == false)
	      {
		*code = DOESNT_EXIST;
		return;
	      }
	    *code = OK;
	    this->__current = this->__graphs[graph_name];
	  }

	void		add(std::string const& graph_name, error_code* code)
	  {
	    if (this->__exists(graph_name) == true)
	      {
		*code = ALREADY_EXIST;
		return;
	      }
	    *code = OK;
	    this->__graphs[graph_name] = new Graph();
	  }
	
    	Edge::id	add(Vertex::id from, Vertex::id to, error_code* code)
	  {
	    return (Edge::add(from, to, (*this->__current), code));
	  }

	Vertex::id	add(void)
	  {
	    Vertex::id	id = boost::add_vertex(*this->__current);
	    // FIXME : set vertex attributes
	    // *this->__current[id]
	    return (id);
	  }

	void		remove(std::string const& graph_name, error_code* code)
	  {
	    if (this->__exists(graph_name) == false)
	      {
		*code = DOESNT_EXIST;
		return;
	      }
	    *code = OK;
	    this->__graphs.erase(graph_name);
	  }

	void		remove(Edge::id id, error_code* code)
	  {
	    // FIXME : check if edge exists
	    *code = OK;
	    boost::remove_edge(Edge::get_rid(id), *this->__current);
	  }

	void		remove(Vertex::id id, error_code* code)
	  {
	    // FIXME : check if vertex exists
	    *code = OK;
	    boost::remove_vertex(id, *this->__current);
	  }

	Graph*		get(std::string const& graph_name, error_code* code)
	  {
	    if (this->__exists(graph_name) == false)
	      {
		*code = DOESNT_EXIST;
		return NULL;
	      }
	    *code = OK;
	    return (this->__graphs[graph_name]);
	  }

	Vertex::Vertex*	get(Vertex::id id, error_code* code) const
	  {
	    // FIXME : check si le vertex existe?
	    *code = OK;
	    return &((*this->__current)[id]);
	  }

	Edge::Edge*	get(Edge::id id, error_code* code) const
	  {
	    // FIXME : check si l'edge existe?
	    *code = OK;
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
