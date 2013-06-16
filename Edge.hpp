#ifndef __EDGE__
#define __EDGE__

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

namespace							Edge
{
  typedef boost::tuple<Vertex::id, Vertex::id, std::string>	id;
  typedef struct 						edge
    {
      id							uid;
      std::string						name;
    }								Edge;
}

#endif /* __EDGE__ */
