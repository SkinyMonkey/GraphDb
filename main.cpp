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
#include "Manager.hpp"
#include "ADumper.hpp"
#include "GraphvizDumper.hpp"
#include "Graph.hpp"
#include "IGraphDB.hpp"
#include "GraphDB.hpp"
#include "IPersistence.hpp"
#include "Mysql.hpp"
#include "Core.hpp"
#include "SearchEngine.hpp"
#include "TextProtocol.hpp"
#include "ANetwork.hpp"
#include "NetworkSession.hpp"
#include "Network.hpp"
#include "Configuration.hpp"

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
      boost::asio::io_service io_service;

      Core const* c = Configuration("default.conf")(argc, argv, io_service);

      std::cout << "Launching server on port " << port << std::endl;

      io_service.run();
    }
  catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << "\n";
    }
  return 0;
}
