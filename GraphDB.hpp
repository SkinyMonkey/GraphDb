#ifndef __GRAPHDB__
#define __GRAPHDB__

using namespace Protocol;

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

	void	 	use(std::string const& graph_name, error_code* error_code)
	  {
	    if (this->__exists(graph_name) == false)
	      {
		*error_code = DOESNT_EXIST;
		return;
	      }
	    *error_code = OK;
	    this->__current = this->__graphs[graph_name];
	  }

	void		add(std::string const& graph_name, error_code* error_code)
	  {
	    if (this->__exists(graph_name) == true)
	      {
		*error_code = ALREADY_EXIST;
		return;
	      }
	    *error_code = OK;
	    // FIXME : add graph type to get a custom one
	    this->__graphs[graph_name] = new Graph<
					boost::adjacency_list<boost::vecS
						      ,boost::vecS
						      ,boost::undirectedS
						      ,Vertex::Vertex
						      ,Edge::Edge> >();
	  }
	
    	Edge::id	add(Vertex::id from, Vertex::id to, error_code* error_code)
	  {
	    return this->__current->add(from, to, error_code);
	  }

	// FIXME : set vertex attributes
	Vertex::id	add(void)
	  {
	    return this->__current->add();
	  }

	void		remove(std::string const& graph_name, error_code* error_code)
	  {
	    if (this->__exists(graph_name) == false)
	      {
		*error_code = DOESNT_EXIST;
		return;
	      }
	    *error_code = OK;
	    this->__graphs.erase(graph_name);
	  }

	void		remove(Edge::id id, error_code* error_code)
	  {
	    this->__current->remove(id, error_code);
	  }

	void		remove(Vertex::id id, error_code* error_code)
	  {
	    this->__current->remove(id, error_code);
	  }

	AGraph*		get(std::string const& graph_name, error_code* error_code)
	  {
	    if (this->__exists(graph_name) == false)
	      {
		*error_code = DOESNT_EXIST;
		return NULL;
	      }
	    *error_code = OK;
	    return (this->__graphs[graph_name]);
	  }

	Vertex::Vertex*	get(Vertex::id id, error_code* error_code) const
	  {
	    return this->__current->get(id, error_code);
	  }

	Edge::Edge*	get(Edge::id id, error_code* error_code) const
	  {
	    return this->__current->get(id, error_code);
	  }

	std::string	dump(std::string const& name, error_code* error_code) const
	  {
	    return this->__current->dump(name, error_code);
	  }

private:
	GraphDB(const GraphDB&);
	GraphDB& operator=(const GraphDB&);

	bool	__exists(std::string const& graph_name) const
	  {
	    return this->__graphs.find(graph_name) != this->__graphs.end();
	  }

	AGraph*				__current;
	std::map<std::string, AGraph*>	__graphs;
};

#endif /* __GRAPHDB__ */
