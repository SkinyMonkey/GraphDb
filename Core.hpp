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
      ,IPersistence* pers)
      : __protocol(p)
      , __graphdb(g)
      , __search_engine(s)
      , __persistence(pers)
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
      this->__persistence->use(graph_name, code);
    }

  void		add(std::string const& graph_name, Protocol::error_code& code)
    {
      this->__graphdb->add(graph_name, code);
      this->__persistence->add(graph_name, code);
    }

  Edge::id	add(Vertex::id const from, Vertex::id const to, std::string const& name, Protocol::error_code& code)
    {
      const Edge::id& id = this->__graphdb->add(from, to, name, code);
      this->__persistence->add(id, name, code);
      return id;
    }

  Vertex::id	add(std::string const& vertex_name, std::map<std::string, std::string> const& args, Protocol::error_code& code)
    {
      const Vertex::id& id = this->__graphdb->add(vertex_name, args);
      this->__persistence->add(id, vertex_name, args, code);
      return id;
    }

  void		remove(std::string const& graph_name, Protocol::error_code& code)
    {
      this->__graphdb->remove(graph_name, code);
      this->__persistence->remove(graph_name, code);
    }

  void		remove(Edge::id id, Protocol::error_code& code)
    {
      this->__graphdb->remove(id, code);
      this->__persistence->remove(id, code);
    }

  void		remove(Vertex::id id, Protocol::error_code& code)
    {
      this->__graphdb->remove(id, code);
      this->__persistence->remove(id, code);
    }

  std::string	dump(std::string const& dumper_name, Protocol::error_code& error_code) const
    {
      return this->__graphdb->dump(dumper_name, error_code);
    }

// FIXME : update/read methods, need search engine
private:
  Core(const Core&);
  Core& operator=(const Core&);

  AProtocol*				  __protocol;
  IGraphDB*				    __graphdb;
  ISearchEngine*			__search_engine;
  IPersistence*       __persistence;
};

#endif /* __CORE__ */
