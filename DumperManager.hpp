#ifndef __DUMPERMANAGER__
#define __DUMPERMANAGER__

#include "GraphvizDumper.hpp"

class DumperManager
{
public:
  DumperManager(IGraphDB* graphdb)
    : __graphdb(graphdb)
    {
      this->__dumpers["graphviz"] = new GraphvizDumper();
    }
  ~DumperManager()
    {}

  std::string	operator()(std::string const& graph_name, std::string const& dumper_name, Protocol::error_code& error_code) const
    {
      if (this->__exists(dumper_name) == false)
	{
	  error_code = Protocol::DOESNT_EXIST;
	  return std::string("");
	}
      error_code = Protocol::OK;

      AGraph*	current = this->__graphdb->get(graph_name, error_code);
      if (error_code != Protocol::OK)
	return std::string("");
      return (*this->__dumpers.at(dumper_name))(current, error_code);
    }

private:
  DumperManager(const DumperManager&);
  DumperManager& operator=(const DumperManager&);

  bool		__exists(std::string const& dumper_name) const
    {
      return (this->__dumpers.find(dumper_name) != this->__dumpers.end());
    }

  IGraphDB*				__graphdb;
  std::map<std::string, ADumper const*>	__dumpers;
};

#endif /* __DUMPERMANAGER__ */
