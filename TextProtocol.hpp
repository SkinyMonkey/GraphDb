#ifndef __TEXTPROTOCOL__
#define __TEXTPROTOCOL__

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "AProtocol.hpp"

class TextProtocol : public AProtocol
{
  typedef std::string	(TextProtocol::*interpretation)(std::vector<std::string>&);
  typedef std::map<std::string, interpretation>	execution_table;
  enum	placeholders
    {
      COMMAND,
      TYPE,
      USE_NAME = TYPE,
      NAME,
      FROM = NAME,
      TO
    };

  static std::string const	errors[4];

public:
  TextProtocol()
    : AProtocol()
    {
      this->__execution["use"] = &TextProtocol::use;
      this->__execution["add"] = &TextProtocol::add;
      this->__execution["remove"] = &TextProtocol::remove;
      this->__execution["batch"] = &TextProtocol::remove;
    }

  ~TextProtocol(){}

  std::string		interpret(std::string const& command)
    {
      std::vector<std::string>	split_buffer;
      std::cout << "To interpret : " << command << std::endl;

      boost::split(split_buffer ,command ,boost::is_any_of(" "));
      std::cout << "Command [" << split_buffer[COMMAND] << "]" << std::endl;
      execution_table::iterator it = this->__execution.find(split_buffer[COMMAND]);
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
  TextProtocol(const TextProtocol&);
  TextProtocol& operator=(const TextProtocol&);

  // FIXME : add all the parsing and checks of args
  std::string	answer(error_code *code
		      ,std::string const& type
		      ,std::string const& infos = "")
    { 
      if (*code != OK)
	return ("ERROR " + type + infos + errors[*code]);
      return (type + infos);
    }

  std::string	use(std::vector<std::string>& args)
    {
      error_code	error_code;

      this->__core->use(args[USE_NAME], &error_code);
      return answer(&error_code, "GRAPH ", args[USE_NAME]);
    }

  std::string	add(std::vector<std::string>& args)
    {
      error_code	error_code;

      if (args[TYPE] == "vertex")
	{
	  Vertex::id id = this->__core->add();
	  error_code = OK;
	  return answer(&error_code
		       ,"VERTEX "
		       ,boost::lexical_cast<std::string>(id));
	}
      else if (args[TYPE] == "graph")
	{
	  this->__core->add(args[NAME], &error_code);
	  return answer(&error_code
		       ,"GRAPH "
		       ,args[NAME]);
	}
      else if (args[TYPE] == "edge")
	{
	  Vertex::id from = std::atol(args[FROM].c_str());
	  Vertex::id to = std::atol(args[TO].c_str());
	  Edge::id   id	= this->__core->add(from, to, &error_code);

	  return answer(&error_code
		       ,"EDGE "
		       ,boost::lexical_cast<std::string>(id.first)
		       +" "
		       +boost::lexical_cast<std::string>(id.second));
	}
      error_code = DOESNT_EXIST;
      return answer(&error_code, "TYPE ", args[TYPE]);
    }

  std::string	remove(std::vector<std::string>& args)
    {
      error_code	error_code;

      if (args[TYPE] == "vertex")
	{
	  this->__core->remove(std::atoi(args[NAME].c_str()), &error_code);
	  return answer(&error_code, "OK");
	}
      else if (args[TYPE] == "graph")
	{
	  this->__core->remove(args[NAME], &error_code);
	  return answer(&error_code, "OK");
	}
      else if (args[TYPE] == "edge")
	{
	  this->__core->remove(std::make_pair(std::atol(args[FROM].c_str())
					      ,std::atol(args[TO].c_str()))
			      ,&error_code);
	  return answer(&error_code, "OK");
	}
      error_code = DOESNT_EXIST;
      return answer(&error_code, "TYPE ", args[TYPE]);
    }

  std::string	batch(std::vector<std::string>& args)
    {
      error_code	error_code = NOT_IMPLEMENTED;

      return answer(&error_code, "BATCH ");
    }

  execution_table		__execution;
};

std::string const	TextProtocol::errors[4] = {" OK"
	       ," EXIST"
	       ," NOT EXIST"
	       ," NOT IMPLEMENTED"};

#endif /* __TEXTPROTOCOL__ */
