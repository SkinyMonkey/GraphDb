#ifndef __PROTOCOL__
#define __PROTOCOL__

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "AProtocol.hpp"

class Protocol : public AProtocol
{
  typedef std::string	(Protocol::*interpretation)(std::vector<std::string>&);
  typedef std::map<std::string, interpretation>	execution_table;

public:
  Protocol()
    : AProtocol()
    {
      this->__execution["use"] = &Protocol::use;
      this->__execution["add"] = &Protocol::add;
      this->__execution["remove"] = &Protocol::remove;
      this->__execution["batch"] = &Protocol::remove;
    }

  ~Protocol(){}

  std::string		interpret(std::string const& command)
    {
      std::vector<std::string>	split_buffer;
      std::cout << "To interpret : " << command << std::endl;

      boost::split(split_buffer ,command ,boost::is_any_of(" "));
      std::cout << "Command [" << split_buffer[0] << "]" << std::endl;
      execution_table::iterator it = this->__execution.find(split_buffer[0]);
      if (it != this->__execution.end())
      {
	interpretation	function = (*it).second;

	std::cout << "Command found" << std::endl;
	return (this->*function)(split_buffer);
      }
      std::cout << "Command not found" << std::endl;
      return ("ERROR Command not found");
    }

private:
  Protocol(const Protocol&);
  Protocol& operator=(const Protocol&);

  // FIXME : add all the parsing and checks

  std::string	use(std::vector<std::string>& args)
    {
      if (this->__core->use(args[1]) == false)
	return ("ERROR No such graph");
      return ("OK");
    }

  std::string	add(std::vector<std::string>& args)
    {
      if (args[1] == "vertex")
	return (std::string("VERTEX ")
		+ boost::lexical_cast<std::string>(this->__core->add()));
      else if (args[1] == "base")
	{
	  if (this->__core->add(args[2]) == true)
	    return ("OK");
	  return ("ERROR Base already exists ");
	}
      else if (args[1] == "edge")
	{
	  Vertex::id from = std::atol(args[2].c_str());
	  Vertex::id to = std::atol(args[3].c_str());
	  Edge::id   id	= this->__core->add(from, to);

	  return (std::string("EDGE ")
		  + boost::lexical_cast<std::string>(id.first)
		  + std::string(" ")
		  + boost::lexical_cast<std::string>(id.second));
	}
      return ("ERROR No such type");
    }

  std::string	remove(std::vector<std::string>& args)
    {
      if (args[1] == "vertex")
	{
	  Vertex::id	vertex = atoi(args[2].c_str());

	  if (this->__core->remove(vertex) == true)
	    return ("OK");
	  return ("ERROR Cannot remove vertex");
	}
      else if (args[1] == "base")
	{
	  if (this->__core->remove(args[2]) == true)
	    return ("OK");
	  return ("ERROR Base already exists ");
	}
      else if (args[1] == "edge")
	{
	  Edge::id edge = std::make_pair(std::atol(args[2].c_str())
					,std::atol(args[3].c_str()));

	  if (this->__core->remove(edge) == true)
	    return ("OK");
	  return ("ERROR Cannot remove edge"); // no error return value
	}
      return (std::string("ERROR No such type ") + args[1]);
    }

  std::string	batch(std::vector<std::string>& args)
    {
      return ("OK");
    }

  execution_table		__execution;
};

#endif /* __PROTOCOL__ */
