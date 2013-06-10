#ifndef __CORE__
#define __CORE__

#include "AProtocol.hpp"
#include "IGraphDB.hpp"
#include "ISearchEngine.hpp"
#include "Configuration.hpp"

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

  void		use(std::string const& graph_name, Protocol::error_code* code)
    {
      this->__graphdb->use(graph_name, code);
    }

  void		add(std::string const& graph_name, Protocol::error_code* code)
    {
      this->__graphdb->add(graph_name, code);
    }

  Edge::id	add(Vertex::id from, Vertex::id to, Protocol::error_code* code)
    {
      return this->__graphdb->add(from, to, code);
    }

  Vertex::id	add(void)
    {
      return this->__graphdb->add();
    }

  void		remove(std::string const& graph_name, Protocol::error_code* code)
    {
      this->__graphdb->remove(graph_name, code);
    }

  void		remove(Edge::id id, Protocol::error_code* code)
    {
      this->__graphdb->remove(id, code);
    }

  void		remove(Vertex::id id, Protocol::error_code* code)
    {
      this->__graphdb->remove(id, code);
    }

// FIXME : update/read methods, need search engine
private:
  Core(const Core&);
  Core& operator=(const Core&);

  Configuration		__configuration;
  AProtocol*		__protocol;
  IGraphDB*		__graphdb;
  ISearchEngine*	__search_engine;
};

#endif /* __CORE__ */
