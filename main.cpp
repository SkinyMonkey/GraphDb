#include "Core.hpp"
#include "GraphDB.hpp"
#include "SearchEngine.hpp"
#include "Protocol.hpp"
#include "Network.hpp"

int	main(int argc, const char *argv[]) // FIXME : add options for conf
{
  try
    {
      int	port;

      if (argc != 2)
	port = 5005;
      else
	port = std::atoi(argv[1]);

      ISearchEngine*	s = new SearchEngine(); // FIXME : uncomplete

      boost::asio::io_service io_service;
      IGraphDB*		g = new GraphDB();
      AProtocol*	p = new Protocol();
      ANetwork*		n = new Network(io_service, port, p);
      Core		c(n, g, s, p);

      std::cout << "Launching server on port " << port << std::endl;
      io_service.run();
    }
  catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << "\n";
    }
  return 0;
}
/*
  p->set_core(&c);
  class JSON{};
  std::vector<JSON>	test;
  p->batch<std::vector<JSON> >(0, test);  
  
  int	i, j, count;
  int	n = 1000;
  for (i = 0; i < n; ++i)
    {
      std::cout << i + 1 << "\b\b\b\b\b\b\b\b\b\b";
      c.add();
    }
  std::cout << std::endl;
  std::cout << n << " vertex created" << std::endl;
  count = 0;
  for (i = 0; i < n; ++i)
    {
      for (j = 0; j < n; j++)
        {
	  if (j != i)
	    {
	      c.add(i, j);
	      ++count;
	      std::cout << count << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	    }
        }
    }
  return 0;
  */
