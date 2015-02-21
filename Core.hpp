#ifndef __CORE__
#define __CORE__

using namespace Protocol;

class Core
{
public:
  Core(ANetwork* n
      ,IGraphDB* g
      ,ISearchEngine* s
      ,AProtocol* p
      ,std::string const& conf_filename = "default.conf")
      : __configuration(conf_filename)
      , __protocol(p)
      , __graphdb(g)
      , __search_engine(s)
  {
    p->set_network(n);
    p->set_core(this);
  }

  ~Core()
    {
      ;
    }

  void		use(std::string const& graph_name, Protocol::error_code& code)
    {
      this->__graphdb->use(graph_name, code);
    }

  void		add(std::string const& graph_name, Protocol::error_code& code)
    {
      this->__graphdb->add(graph_name, code);
    }

  Edge::id	add(Vertex::id const from, Vertex::id const to, std::string const& name, Protocol::error_code& code)
    {
      return this->__graphdb->add(from, to, name, code);
    }

  Vertex::id	add(std::string const& vertex_name, std::vector<std::string> const& args)
    {
      return this->__graphdb->add(vertex_name, args);
    }

  void		remove(std::string const& graph_name, Protocol::error_code& code)
    {
      this->__graphdb->remove(graph_name, code);
    }

  void		remove(Edge::id id, Protocol::error_code& code)
    {
      this->__graphdb->remove(id, code);
    }

  void		remove(Vertex::id id, Protocol::error_code& code)
    {
      this->__graphdb->remove(id, code);
    }

  std::string	dump(std::string const& dumper_name, Protocol::error_code& error_code) const
    {
      return this->__graphdb->dump(dumper_name, error_code);
    }

// FIXME : update/read methods, need search engine
private:
  Core(const Core&);
  Core& operator=(const Core&);

  Configuration				__configuration;
  AProtocol*				  __protocol;
  IGraphDB*				    __graphdb;
  ISearchEngine*			__search_engine;
};

#endif /* __CORE__ */
