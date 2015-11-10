#ifndef __BATCHERMANAGER__
#define __BATCHERMANAGER__

#include "GraphvizBatcher.hpp"

/*
#include "Manager.hpp"

// Rewritten
class BatcherManager : public Manager<ABatcher>
{
public:
  BatcherManager(IGraphDB* graphdb)
    : Manager<ABatcher>(graphdb)
    {
      this->__elements["graphviz"] = new GraphvizBatcher();
      this->__elements["graphml"] = new GraphMLBatcher();
    }

  ~BatcherManager()
  {}

  std::string	operator()(std::string const& graph_name, std::string const& batcher_name, Protocol::error_code& error_code) const
  {
    Graph*      current;
    std::string error_string("");
   
    if ((current =\
      this->__check_get_graph(graph_name, element_name, error_code, error_string, "batcher")) != NULL)
    {
      this->__elements.at(batcher_name)(current, error_code);
      return std::string("");
    }

    return error_string;
  }
};
*/

class BatcherManager
{
public:
  BatcherManager(IGraphDB* graphdb)
    : __graphdb(graphdb)
    {
      this->__batchers["graphviz"] = new GraphvizBatcher();
      this->__batchers["graphml"] = new GraphMLBatcher();
    }

  ~BatcherManager()
  {}

  std::string	operator()(std::string const& graph_name, std::string const& batcher_name, Protocol::error_code& error_code) const
  {
    if (this->__exists(batcher_name) == false)
    {
      error_code = Protocol::DOESNT_EXIST;
      return std::string("");
    }
    error_code = Protocol::OK;

    Graph*	current = this->__graphdb->get(graph_name, error_code);
    if (error_code != Protocol::OK)
      return std::string("");
    return (*this->__batchers.at(batcher_name))(current, error_code);
  }

private:
  BatcherManager(const BatcherManager&);
  BatcherManager& operator=(const BatcherManager&);

  bool		__exists(std::string const& batcher_name) const
  {
    return (this->__batchers.find(batcher_name) != this->__batchers.end());
  }

  IGraphDB*				                        __graphdb;
  std::map<std::string, ABatcher const*>	__batchers;
};

#endif /* __BATCHERMANAGER__ */
