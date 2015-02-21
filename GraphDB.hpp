#ifndef __GRAPHDB__
#define __GRAPHDB__

class GraphDB : public IGraphDB
{
  public:
    GraphDB()
      : IGraphDB(), __current(0x0)
    {
      Protocol::error_code	error_code;

      init_graph_types();

      this->add("default", error_code);
      this->use("default", error_code);
    }

    ~GraphDB()
    {}

    void	 	use(std::string const& graph_name, Protocol::error_code& error_code)
    {
      if (this->__exists(graph_name) == false)
      {
        error_code = Protocol::DOESNT_EXIST;
        return;
      }
      error_code = Protocol::OK;
      this->__current = this->__graphs[graph_name];
    }

    void		add(std::string const& graph_name, Protocol::error_code& error_code)
    {
      if (this->__exists(graph_name) == true)
      {
        error_code = Protocol::ALREADY_EXIST;
        return;
      }
      error_code = Protocol::OK;
      // FIXME : fixed type
      this->__graphs[graph_name] = graph_types["adjacency_list_vecS_vecS_undirectedS"];
    }

    Edge::id	add(Vertex::id const from,
                  Vertex::id const to,
                  std::string const& name,
                  Protocol::error_code& error_code)
    {
      return this->__current->add(from, to, name, error_code);
    }

    // FIXME : set vertex attributes
    Vertex::id	add(std::string const& vertex_name,
                    std::vector<std::string> const& args)
    {
      return this->__current->add(vertex_name, args);
    }

    void		remove(std::string const& graph_name,
                   Protocol::error_code& error_code)
    {
      if (this->__exists(graph_name) == false)
      {
        error_code = Protocol::DOESNT_EXIST;
        return;
      }
      error_code = Protocol::OK;
      this->__graphs.erase(graph_name);
    }

    void		remove(Vertex::id const id, Protocol::error_code& error_code)
    {
      this->__current->remove(id, error_code);
    }

    void		remove(Edge::id const& id, Protocol::error_code& error_code)
    {
      this->__current->remove(id, error_code);
    }

    AGraph*		get(std::string const& graph_name,
                  Protocol::error_code& error_code) const
    {
      if (this->__exists(graph_name) == false)
      {
        error_code = Protocol::DOESNT_EXIST;
        return NULL;
      }
      error_code = Protocol::OK;
      return (this->__graphs.at(graph_name));
    }

    Vertex::Vertex*	get(Vertex::id const id,
                        Protocol::error_code& error_code) const
    {
      return this->__current->get(id, error_code);
    }

    Edge::Edge*	get(Edge::id const& id, Protocol::error_code& error_code) const
    {
      return this->__current->get(id, error_code);
    }
  
    std::string   dump(std::string const& dumper_name, Protocol::error_code& error_code) const
    {
      return this->__current->dump(dumper_name, error_code);
    }

  private:
    GraphDB(const GraphDB&);
    GraphDB& operator=(const GraphDB&);

    bool	__exists(std::string const& graph_name) const
    {
      return this->__graphs.find(graph_name) != this->__graphs.end();
    }

    AGraph*				                  __current;
    std::map<std::string, AGraph*>	__graphs;
};

#endif /* __GRAPHDB__ */
