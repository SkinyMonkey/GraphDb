#ifndef __GRAPHDB__
#define __GRAPHDB__

class GraphDB : public IGraphDB
{
public:
	GraphDB()
	  : IGraphDB(), __current(0x0)
	  {
	    Protocol::error_code	error_code;

	    this->add("default", &error_code);
	    this->use("default", &error_code);
	  }

	~GraphDB()
	  {}

	void	 	use(std::string const& graph_name, Protocol::error_code* error_code)
	  {
	    if (this->__exists(graph_name) == false)
	      {
		*error_code = Protocol::DOESNT_EXIST;
		return;
	      }
	    *error_code = Protocol::OK;
	    this->__current = this->__graphs[graph_name];
	  }

	void		add(std::string const& graph_name, Protocol::error_code* error_code)
	  {
	    if (this->__exists(graph_name) == true)
	      {
		*error_code = Protocol::ALREADY_EXIST;
		return;
	      }
	    *error_code = Protocol::OK;
	    this->__graphs[graph_name] = new Graph();
	  }
	
    	Edge::id	add(Vertex::id from, Vertex::id to, Protocol::error_code* error_code)
	  {
	    return this->__current->add(from, to, error_code);
	  }

	// FIXME : set vertex attributes
	Vertex::id	add(std::string const& vertex_name, std::vector<std::string> const& args)
	  {
	    return this->__current->add(vertex_name, args);
	  }

	void		remove(std::string const& graph_name, Protocol::error_code* error_code)
	  {
	    if (this->__exists(graph_name) == false)
	      {
		*error_code = Protocol::DOESNT_EXIST;
		return;
	      }
	    *error_code = Protocol::OK;
	    this->__graphs.erase(graph_name);
	  }

	void		remove(Edge::id id, Protocol::error_code* error_code)
	  {
	    this->__current->remove(id, error_code);
	  }

	void		remove(Vertex::id id, Protocol::error_code* error_code)
	  {
	    this->__current->remove(id, error_code);
	  }

	Graph*		get(std::string const& graph_name, Protocol::error_code* error_code)
	  {
	    if (this->__exists(graph_name) == false)
	      {
		*error_code = Protocol::DOESNT_EXIST;
		return NULL;
	      }
	    *error_code = Protocol::OK;
	    return (this->__graphs[graph_name]);
	  }

	Vertex::Vertex*	get(Vertex::id id, Protocol::error_code* error_code) const
	  {
	    return this->__current->get(id, error_code);
	  }

	Edge::Edge*	get(Edge::id id, Protocol::error_code* error_code) const
	  {
	    return this->__current->get(id, error_code);
	  }

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
