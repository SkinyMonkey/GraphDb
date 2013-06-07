#include "Core.hpp"
#include "GraphDB.hpp"
#include "SearchEngine.hpp"
#include "Protocol.hpp"
#include "Network.hpp"

int	main(int argc, const char *argv[]) // FIXME : add options for conf
{
  (void)argc;
  (void)argv;

  IGraphDB*		g = new GraphDB();
  ISearchEngine*	s = new SearchEngine();
  AProtocol*		p = new Protocol(new Network());

  Core	c(g, s, p);
  
  return 0;
}
