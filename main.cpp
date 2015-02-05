#include <string>
#include <map>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Vertex.hpp"
#include "Edge.hpp"
#include "AProtocol.hpp"
#include "ISearchEngine.hpp"
#include "Configuration.hpp"
#include "Graph.hpp"
#include "IGraphDB.hpp"
#include "GraphDB.hpp"
#include "ADumper.hpp"
#include "DumperManager.hpp"
#include "Core.hpp"
#include "SearchEngine.hpp"
#include "TextProtocol.hpp"
#include "ANetwork.hpp"
#include "NetworkSession.hpp"
#include "Network.hpp"

int	main(int argc, const char *argv[]) // FIXME : add options for conf
{
#ifdef DEBUG
  if (argv[1] && std::string(argv[1]) == "--mangling")
  {
    init_graph_types();
    return 0;
  }
#endif

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
      AProtocol*	p = new TextProtocol();
      ANetwork*		n = new Network(io_service, port, p);
      Core		c(n, g, s, p);

      /*
      // FIXME : Test adjacent vertices
      // graph -> "default"
      Vertex::id v = g->add();
      error_code	error_code;

      adjacency_iterator	begin;
      adjacency_iterator	end;

      boost::tie(begin, end) = adjacent_vertices(v, *g->get("default", &error_code));
      // ENDFIXME
      */

      std::cout << "Launching server on port " << port << std::endl;
      io_service.run();
    }
  catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << "\n";
    }
  return 0;
}
