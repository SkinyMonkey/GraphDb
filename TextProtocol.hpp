#ifndef __TEXTPROTOCOL__
#define __TEXTPROTOCOL__

#include <boost/algorithm/string.hpp>

class TextProtocol : public AProtocol
{
  // FIXME : change for std::function?
  typedef std::string (TextProtocol::*interpretation)
		      (std::vector<std::string> const&);

  typedef std::string (TextProtocol::*subinterpretation)
		      (std::vector<std::string> const&, Protocol::error_code&);

  // FIXME : unordered_map
  typedef std::map<std::string, interpretation>		execution_table;
  typedef std::map<std::string, subinterpretation>	sub_execution_table;

  enum	placeholders
    {
      COMMAND,
      TYPE,
      USE_NAME = TYPE,
      NAME,
      FROM = NAME,
      TO
    };

  static std::string const	errors[Protocol::ERROR_CODE_SIZE];

public:
  TextProtocol()
    : AProtocol()
    {
      this->__execution["use"] 	= &TextProtocol::__use;
      this->__execution["add"] 	= &TextProtocol::__add;
      this->__execution["rm"] 	= &TextProtocol::__remove;
      this->__execution["batch"]= &TextProtocol::__batch;
      this->__execution["dump"] = &TextProtocol::__dump;

      this->__add_bind["vertex"]= &TextProtocol::__add_vertex;
      this->__add_bind["edge"] 	= &TextProtocol::__add_edge;
      this->__add_bind["graph"] = &TextProtocol::__add_graph;

      this->__rm_bind["vertex"] = &TextProtocol::__rm_vertex;
      this->__rm_bind["edge"] 	= &TextProtocol::__rm_edge;
      this->__rm_bind["graph"] 	= &TextProtocol::__rm_graph;
    }

  ~TextProtocol(){}

  std::string		interpret(std::string const& command)
    {
      std::vector<std::string>	split_buffer;
      error_code		error_code;
      interpretation	function;

      boost::split(split_buffer ,command ,boost::is_any_of(" "));
      if (this->__check(split_buffer, COMMAND, error_code, NO_COMMAND))
	{
	  if (this->__exists(split_buffer[COMMAND], this->__execution))
	    {
	      if (this->__check(split_buffer, TYPE, error_code, NO_TYPE))
		{
		  function = this->__execution[split_buffer[COMMAND]];
		  return (this->*function)(split_buffer);
		}
	    }
	  return ("ERROR Command not found");
	}
      return ("ERROR Empty Command");
    }

private:
  TextProtocol(const TextProtocol&);
  TextProtocol& operator=(const TextProtocol&);

  std::string		__answer(error_code const& error_code
				,std::string const& type
				,std::string const& infos = "") const
    { 
      if (error_code != OK)
	return ("ERROR " + type + infos + errors[error_code]);
      return (type + infos);
    }

  std::string		__use(std::vector<std::string> const& args)
    {
      error_code	error_code;

      this->__core->use(args[USE_NAME], error_code);
      return __answer(error_code, "GRAPH ", args[USE_NAME]);
    }

  std::string		__call_sub(std::vector<std::string> const& args
				   ,sub_execution_table const& table)
    {
      error_code	error_code;
      subinterpretation function;

      if (this->__exists(args[TYPE], table) == true)
	{
	  function = table.at(args[TYPE]);
	  return (this->*function)(args, error_code);
	}

      error_code = DOESNT_EXIST;
      return __answer(error_code, "TYPE ", args[TYPE]);
    }

  std::string		__add(std::vector<std::string> const& args)
    {
      return this->__call_sub(args, this->__add_bind);
    }

  std::string		__add_vertex(std::vector<std::string> const& args
				    ,Protocol::error_code& error_code)
    {
      Vertex::id id =
	this->__core->add(this->__check(args, NAME, ""), args);

      error_code = OK;
      return __answer(error_code
		     ,"VERTEX "
		     ,boost::lexical_cast<std::string>(id));
    }

  std::string		__add_edge(std::vector<std::string> const& args
				  ,Protocol::error_code& error_code)
    {
      if (this->__check(args, FROM, error_code, NO_FROM) == true\
	  && this->__check(args, TO, error_code, NO_TO) == true)
	{
	  Vertex::id from = std::atol(args[FROM].c_str());
	  Vertex::id to = std::atol(args[TO].c_str());
	  Edge::id   id = this->__core->add(from, to, "", error_code);

	  return __answer(error_code
	      ,"EDGE "
	      ,boost::lexical_cast<std::string>(boost::tuples::get<0>(id))
	      +" "
	      +boost::lexical_cast<std::string>(boost::tuples::get<1>(id)));
	}
      return __answer(error_code, "EDGE ", "");
    }

  std::string		__add_graph(std::vector<std::string> const& args
				   ,Protocol::error_code& error_code)
    {
      if (this->__check(args, NAME, error_code, NO_NAME) == true)
	this->__core->add(args[NAME], error_code);
      return __answer(error_code, "GRAPH ", args[NAME]);
    }

  std::string		__remove(std::vector<std::string> const& args)
    {
      return this->__call_sub(args, this->__rm_bind);
    }

  std::string		__rm_vertex(std::vector<std::string> const& args
				   ,Protocol::error_code& error_code)
    {
      if (this->__check(args, NAME, error_code, NO_NAME) == true)
	this->__core->remove(std::atoi(args[NAME].c_str()), error_code);
      return __answer(error_code, "RM");
    }

  std::string		__rm_edge(std::vector<std::string> const& args
				 ,Protocol::error_code& error_code)
    {
      if (this->__check(args, FROM, error_code, NO_FROM) == true\
	  && this->__check(args, TO, error_code, NO_TO) == true)
	this->__core->remove(
	    boost::tuples::make_tuple(std::atol(args[FROM].c_str())
				     ,std::atol(args[TO].c_str())
				     ,"")
			    ,error_code);
      return __answer(error_code, "RM");
    }

  std::string		__rm_graph(std::vector<std::string> const& args
				  ,Protocol::error_code& error_code)
    {
      if (this->__check(args, NAME, error_code, NO_NAME) == true)
	this->__core->remove(args[NAME], error_code);
      return __answer(error_code, "RM");
    }

  std::string		__batch(std::vector<std::string> const& args)
    {
      error_code	error_code = NOT_IMPLEMENTED;

      return __answer(error_code, "BATCH ");
    }

  std::string		__dump(std::vector<std::string> const& args)
    {
      error_code	error_code;
      std::string	dump = "";

      if (this->__check(args, NAME, error_code, NO_NAME) == true)
	{
	  std::string dump =
	    this->__core->dump(args[TYPE], args[NAME], error_code);
	}
      return __answer(error_code, "DUMP " + dump);
    }

  std::string		__check(std::vector<std::string> const& args\
			       ,unsigned int to_check\
			       ,std::string const& default_) const
    {
      if (args.size() - 1 < to_check)
	return default_;
      return args[to_check];
    }

  bool			__check(std::vector<std::string> const& args
			       ,unsigned int to_check
			       ,Protocol::error_code& error_code
			       ,Protocol::error_code error) const
    {
      if (args.size() - 1 < to_check)
	{
	  error_code = error;
	  return false;
	}
      return true;
    }

  template<typename target>
  bool			__exists(std::string const& name
				,target const& table) const
    {
      return (table.find(name) != table.end());
    }

  execution_table		__execution;
  sub_execution_table		__add_bind;
  sub_execution_table		__rm_bind;
};

std::string const	TextProtocol::errors[Protocol::ERROR_CODE_SIZE] =
{
 " OK"
," EXIST"
," NOT EXIST"
," NOT IMPLEMENTED"
," CANT ADD"
," NO NAME"
," NO FROM"
," NO TO"
};

#endif /* __TEXTPROTOCOL__ */
