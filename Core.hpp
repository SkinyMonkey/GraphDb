#ifndef __CORE__
#define __CORE__

#include "IGraphDB.hpp"
#include "ISearchEngine.hpp"
#include "AProtocol.hpp"
#include "Configuration.hpp"

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

  bool		use(std::string const& graph_name)
    {
      return this->__graphdb->use(graph_name);
    }

  bool		add(std::string const& graph_name)
    {
      return this->__graphdb->add(graph_name);
    }

  Edge::id	add(Vertex::id from, Vertex::id to)
    {
      return this->__graphdb->add(from, to);
    }

  Vertex::id	add(void)
    {
      return this->__graphdb->add();
    }

  bool		remove(std::string const& graph_name)
    {
      return this->__graphdb->remove(graph_name);
    }

  bool		remove(Edge::id id)
    {
      return this->__graphdb->remove(id);
    }

  bool		remove(Vertex::id id)
    {
      return this->__graphdb->remove(id);
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
