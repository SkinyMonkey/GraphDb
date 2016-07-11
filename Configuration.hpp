#ifndef __CONFIGURATION__
#define __CONFIGURATION__

class Configuration
{
public:
	Configuration(std::string const&)
	  {
	    //FIXME : read the configuration
	  }

	~Configuration()
	  {}

  Core* operator()(int argc, const char** argv, boost::asio::io_service& io_service)
    {
      int	port = 5005;

      if (argc == 2)
        port = std::atoi(argv[1]);

      // FIXME : charge configuration from file
      ISearchEngine*	 search_engine = new SearchEngine(); // FIXME : uncomplete
      AProtocol*	     protocol = new TextProtocol();
      ANetwork*		     network = new Network(io_service, port, protocol);
      IGraphDB*		     graphdb = new GraphDB();
      IPersistence*    persistence = new MysqlPersistence("default");

      return new Core(network,
                      graphdb,
                      search_engine,
                      protocol,
                      persistence);
    }

private:
	Configuration(const Configuration&);
	Configuration& operator=(const Configuration&);
};


#endif /* __CONFIGURATION__ */
